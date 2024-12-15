import sys
import logging
import base64
from pathlib import Path
from io import BytesIO
from PIL import Image

import pytest
import pytest_html

# Add the path to Simulation/FirmwarePCSimulator to sys.path
simulation_path = Path(__file__).parent.parent.parent / "Simulation" / "FirmwarePCSimulator"
sys.path.append(str(simulation_path))

from simulation import Simulation

logger = logging.getLogger(__name__)


@pytest.fixture
def assert_display_content(request):

    if not hasattr(request.node, "assert_display_contents"):
        request.node.assert_display_contents = []

    def generate_image(dut: Simulation):
        """
        Generate an image from the display content of the DUT.
        """
        width = dut.get_display_width()
        height = dut.get_display_height()
        logger.info(f"Display dimensions: width={width}, height={height}")

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

    def validate_display_content(dut: Simulation, assert_name, reference_path):
        """
        Validate the display content by comparing the generated image with a reference.
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


@pytest.hookimpl(hookwrapper=True)
def pytest_runtest_makereport(item, call):
    """Attach all assertion-related images to the HTML report."""
    outcome = yield
    report = outcome.get_result()

    if report.when == "call":
        extras = getattr(report, "extras", [])
        images = getattr(item, "assert_display_contents", [])
        for image_base64, assert_name in images:
            # Append each image to the extras list
            extras.append(pytest_html.extras.image(image_base64, mime_type="image/png", name=assert_name))
        
        report.extras = extras
        
def pytest_html_results_table_header(cells):
    """Add a 'Display' column to the HTML report header."""
    cells.insert(2, '<th class="sortable time" data-column-type="time">Display (Actual)</th>')


def pytest_html_results_table_row(report, cells):
    """Add custom content (images and assertions) to the HTML report row."""
    # Ensure the Display column includes all attached images
    if hasattr(report, "extras"):
        images = [extra for extra in report.extras if extra.get("mime_type") == "image/png"]

        # When constructing the <img> tag, ensure the data:image/png;base64, prefix is added only if it doesn't already exist
        images_html = "".join(
            f'<img src="{extra["content"] if extra["content"].startswith("data:image/png;base64,") else "data:image/png;base64," + extra["content"]}" '
            f'alt="{extra["name"]}" style="padding: 5px;" />'
            for extra in images
        )

        cells.insert(2, f"<td>{images_html}</td>")

 
