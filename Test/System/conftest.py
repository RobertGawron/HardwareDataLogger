"""
Module for managing pytest fixtures and hooks for validating simulation display content.

This module includes setup for assertions on the display output of the simulation,
along with integration for pytest HTML reports to include visual validation.
"""

import sys
import logging
import base64
from pathlib import Path
from io import BytesIO
from typing import Generator
from PIL import Image
import pytest
import pytest_html

# Add the path to Simulation/FirmwarePCSimulator to sys.path
# pylint: disable=import-error, wrong-import-position
simulation_path = Path(__file__).parent.parent.parent / "Simulation" / "FirmwarePCSimulator"
sys.path.append(str(simulation_path))

# pylint: disable=import-error, wrong-import-position
# flake8: noqa: E402
from simulation import Simulation

logger = logging.getLogger(__name__)


@pytest.fixture
def assert_display_content(request: pytest.FixtureRequest) -> callable:

    """
    Fixture for validating display content against a reference image.

    :param request: pytest request object.
    :return: Callable for validating display content.
    """

    if not hasattr(request.node, "assert_display_contents"):
        request.node.assert_display_contents = []

    def generate_image(dut: Simulation) -> Image.Image:
        """
        Generate an image from the display content of the DUT.

        :param dut: The device under test (Simulation instance).
        :return: Generated image.
        """
        width = dut.get_display_width()
        height = dut.get_display_height()
        logger.info("Display dimensions: width=%d, height=%d", width, height)

        # Create a new image representing the current display state
        generated_image = Image.new("RGB", (width, height))

        # Populate the image with pixels from the DUT's display
        for y in range(height):
            for x in range(width):
                pixel = dut.get_display_pixel(x, y)  # Get the pixel color
                generated_image.putpixel((x, y), pixel)

        # Scale the image by a factor of 2 without aliasing
        generated_image = generated_image.resize((width * 2, height * 2), Image.NEAREST)

        return generated_image

    # pylint: disable=unused-argument
    def validate_display_content(dut: Simulation, assert_name: str, reference_path: str) -> None:
        """
        Validate the display content by comparing the generated image with a reference.

        :param dut: The device under test (Simulation instance).
        :param assert_name: Name of the assertion.
        :param reference_path: Path to the reference image (for future, unused for now).
        """
        # Generate the image
        generated_image = generate_image(dut)

        # Save the generated image to a memory buffer
        buffer = BytesIO()
        generated_image.save(buffer, format="PNG")
        buffer.seek(0)

        # Encode the buffer content to Base64
        image_base64 = base64.b64encode(buffer.read()).decode("utf-8")

        # Attach the image to the test report
        request.node.assert_display_contents.append((image_base64, assert_name))

    return validate_display_content


# pylint: disable=unused-argument
@pytest.hookimpl(hookwrapper=True)
def pytest_runtest_makereport(item: pytest.Item, call: pytest.CallInfo) -> Generator[None, None, None]:
    """
    Customize the test report generation.

    The `call` argument is part of the pytest hook API and is required even if
    it is not used in this implementation.

    :param item: The pytest test item being executed.
    :param call: Information about the test execution call (unused here).
    :return: Generator for pytest hook implementation.
    """
    outcome = yield
    report = outcome.get_result()

    if report.when == "call":
        extras = getattr(report, "extras", [])
        images = getattr(item, "assert_display_contents", [])
        for image_base64, assert_name in images:
            # Append each image to the extras list
            extras.append(pytest_html.extras.image(image_base64, mime_type="image/png", name=assert_name))

        report.extras = extras


def pytest_html_results_table_header(cells: list) -> None:
    """
    Add a 'Display' column to the HTML report header.

    :param cells: List of cells in the HTML table header.
    """
    cells.insert(2, '<th class="sortable time" data-column-type="time">Display (Actual)</th>')


def pytest_html_results_table_row(report: pytest.TestReport, cells: list) -> None:
    """
    Add custom content (images and assertions) to the HTML report row.

    :param report: pytest test report object.
    :param cells: List of cells in the HTML table row.
    """
    if hasattr(report, "extras"):
        images = [extra for extra in report.extras if extra.get("mime_type") == "image/png"]

        # Construct the <img> tag with proper Base64 encoding
        images_html = "".join(
            f'<img src="{extra["content"] if extra["content"].startswith("data:image/png;base64,") else "data:image/png;base64," + extra["content"]}" '
            f'alt="{extra["name"]}" style="padding: 5px;" />'
            for extra in images
        )

        cells.insert(2, f"<td>{images_html}</td>")
