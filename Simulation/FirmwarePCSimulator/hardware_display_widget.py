from PyQt6.QtWidgets import QWidget, QLabel, QVBoxLayout
from PyQt6.QtGui import QImage, QPixmap, QColor
from PyQt6.QtCore import Qt


class HardwareDisplayWidget(QWidget):
    def __init__(self, display_width: int, display_height: int):
        """
        Widget to handle hardware display logic and rendering.

        :param display_width: Width of the display in pixels.
        :param display_height: Height of the display in pixels.
        """
        super().__init__()
        self.display_width = display_width
        self.display_height = display_height

        # Create a QImage with specified width, height, and format
        self.hw_display = QImage(self.display_width, self.display_height, QImage.Format.Format_RGB32)

        # QLabel to display the image
        self.hw_display_label = QLabel()
        self.hw_display_label.setAlignment(Qt.AlignmentFlag.AlignTop)

        # Layout to contain the QLabel
        layout = QVBoxLayout()
        layout.setAlignment(Qt.AlignmentFlag.AlignTop)
        layout.addWidget(self.hw_display_label)
        self.setLayout(layout)

    def update_pixel(self, x: int, y: int, color: QColor) -> None:
        """
        Update the color of a specific pixel in the QImage.

        :param x: X-coordinate of the pixel.
        :param y: Y-coordinate of the pixel.
        :param color: QColor object representing the new pixel color.
        """
        if 0 <= x < self.display_width and 0 <= y < self.display_height:
            self.hw_display.setPixel(x, y, color.rgb())
        self.update_display()

    def update_display(self) -> None:
        """
        Convert the QImage to QPixmap and set it to QLabel for display.
        """
        pixmap = QPixmap.fromImage(self.hw_display)
        self.hw_display_label.setPixmap(pixmap)

    def update_from_simulation(self, simulation) -> None:
        """
        Update the display using pixel data from the simulation.

        :param simulation: Simulation instance providing pixel data.
        """
        for y in range(self.display_height):
            for x in range(self.display_width):
                red, green, blue = simulation.get_display_pixel(x, y)
                color = QColor(red, green, blue)
                self.update_pixel(x, y, color)
