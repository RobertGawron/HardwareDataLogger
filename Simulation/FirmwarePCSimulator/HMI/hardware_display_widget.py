"""
Module for visualizing ESP8266 hardware states and rendering a simulated display.

This module provides the `HardwareDisplayWidget` class, which includes methods
for updating pixel colors, managing LED states, and integrating with simulation data.
"""

from enum import Enum
from PyQt6.QtWidgets import (
    QWidget, QLabel, QVBoxLayout, QFrame, QHBoxLayout
)
from PyQt6.QtGui import QImage, QPixmap, QColor
from PyQt6.QtCore import Qt


class ESP8266LED(Enum):

    """Enumeration for ESP8266 LED identifiers."""

    WIFI_CONNECTION = 1
    DATA_RECEPTION = 2


class HardwareDisplayWidget(QWidget):

    """
    Widget for simulating and visualizing hardware display.

    This widget renders a simulated hardware display and manages LED indicators
    for ESP8266 hardware states such as WiFi connection and data reception.
    """

    def __init__(self, display_width: int, display_height: int):
        """
        Initialize the HardwareDisplayWidget.

        :param display_width: Width of the display in pixels.
        :param display_height: Height of the display in pixels.
        """
        super().__init__()
        self.display_width = display_width
        self.display_height = display_height

        # Create a QImage with specified width, height, and format
        self.hw_display = QImage(
            self.display_width, self.display_height, QImage.Format.Format_RGB32
        )

        # QLabel to display the image
        self.hw_display_label = QLabel()
        self.hw_display_label.setAlignment(Qt.AlignmentFlag.AlignTop)

        # Layout to contain the QLabel
        main_layout = QVBoxLayout()
        main_layout.setAlignment(Qt.AlignmentFlag.AlignTop)
        main_layout.addWidget(self.hw_display_label)

        # Add ESP8266 LEDs frame
        self.led_states = {
            ESP8266LED.WIFI_CONNECTION: "green",
            ESP8266LED.DATA_RECEPTION: "#8B8000",  # Dark yellow
        }
        self.led_widgets = {}
        esp_leds_frame = self.create_esp_leds_frame()
        main_layout.addWidget(esp_leds_frame)

        self.setLayout(main_layout)

    def create_esp_leds_frame(self):
        """
        Create a frame containing ESP8266 LED indicators.

        :return: QFrame widget with ESP8266 LED indicators.
        """
        frame = QFrame()
        frame.setFrameShape(QFrame.Shape.StyledPanel)
        frame_layout = QVBoxLayout()

        # WiFi Connection indicator
        wifi_layout = QHBoxLayout()
        wifi_label = QLabel("WiFi Connection")
        wifi_circle = QLabel()
        wifi_circle.setFixedSize(20, 20)
        wifi_circle.setStyleSheet(
            "background-color: green; border-radius: 10px;"
        )
        self.led_widgets[ESP8266LED.WIFI_CONNECTION] = wifi_circle
        wifi_layout.addWidget(wifi_label)
        wifi_layout.addWidget(wifi_circle)
        frame_layout.addLayout(wifi_layout)

        # Data Reception indicator
        data_layout = QHBoxLayout()
        data_label = QLabel("UART Reception")
        data_circle = QLabel()
        data_circle.setFixedSize(20, 20)
        data_circle.setStyleSheet(
            "background-color: yellow; border-radius: 10px;"
        )
        self.led_widgets[ESP8266LED.DATA_RECEPTION] = data_circle
        data_layout.addWidget(data_label)
        data_layout.addWidget(data_circle)
        frame_layout.addLayout(data_layout)

        frame.setLayout(frame_layout)
        return frame

    def set_led_state(self, led: ESP8266LED, power_on: bool):
        """
        Set the state of the specified LED.

        :param led: The LED to update (ESP8266LED enum).
        :param power_on: True to power on (brighten), False to power off
                         (return to original color).
        """
        led = ESP8266LED.DATA_RECEPTION  # hack

        if led in self.led_widgets:
            led_widget = self.led_widgets[led]
            original_color = self.led_states[led]
            if power_on:
                brighter_color = (
                    "lightgreen" if original_color == "green" else "#FFFF00"
                )
                led_widget.setStyleSheet(
                    f"background-color: {brighter_color}; border-radius: 10px;"
                )
            else:
                led_widget.setStyleSheet(
                    f"background-color: {original_color}; border-radius: 10px;"
                )

    def update_pixel(self, x: int, y: int, color: QColor) -> None:
        """
        Update the color of a specific pixel in the QImage.

        :param x: X-coordinate of the pixel.
        :param y: Y-coordinate of the pixel.
        :param color: QColor object representing the new pixel color.
        """
        if 0 <= x < self.display_width and 0 <= y < self.display_height:
            self.hw_display.setPixel(x, y, color.rgb())

    def update_display(self) -> None:
        """
        Convert the QImage to QPixmap, scale it by 2x, and set it to QLabel
        for display.

        Avoid pixel aliasing using the `Qt.FastTransformation` scaling mode.
        """
        scaled_pixmap = QPixmap.fromImage(self.hw_display)
        scaled_pixmap = scaled_pixmap.scaled(
            self.display_width * 2,
            self.display_height * 2,
            Qt.AspectRatioMode.IgnoreAspectRatio,
            Qt.TransformationMode.FastTransformation,
        )
        self.hw_display_label.setPixmap(scaled_pixmap)

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
        self.update_display()
