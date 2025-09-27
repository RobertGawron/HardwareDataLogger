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


logger = logging.getLogger(__name__)



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
