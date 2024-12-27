"""
Module for managing the simulation speed widget in a PyQt6 GUI.

This module provides the `SimulationSpeedWidget` class, which contains a slider
for adjusting the speed of the firmware simulation.
"""

from PyQt6.QtWidgets import (
    QWidget, QVBoxLayout, QGroupBox, QSlider, QLabel
)
from PyQt6.QtCore import Qt


class SimulationSpeedWidget(QWidget):

    """
    Widget for controlling the simulation speed.

    This widget provides a slider to adjust the speed multiplier of the
    firmware simulation.
    """

    # pylint: disable=too-few-public-methods
    # This is a GUI widget with small functionality

    def __init__(self, simulation):
        """
        Initialize the SimulationSpeedWidget.

        :param simulation: Simulation instance to control simulation speed.
        """
        super().__init__()

        self.simulation = simulation
        self.current_speed = 1  # Default speed multiplier

        # Create a group box to contain the slider and label
        group_box = QGroupBox("Simulation Speed")
        layout = QVBoxLayout()

        # Create a horizontal slider
        self.slider = QSlider(Qt.Orientation.Horizontal)
        self.slider.setMinimum(1)  # Minimum speed x1
        self.slider.setMaximum(5)  # Maximum speed x5
        self.slider.setValue(self.current_speed)
        self.slider.setTickInterval(1)
        self.slider.setTickPosition(QSlider.TickPosition.TicksBelow)
        self.slider.valueChanged.connect(self.update_speed)

        # Label to display current speed
        self.label = QLabel(f"Current speed: x{self.current_speed}")
        self.label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        # Add slider and label to layout
        layout.addWidget(self.slider)
        layout.addWidget(self.label)

        group_box.setLayout(layout)

        # Main layout for the widget
        main_layout = QVBoxLayout()
        main_layout.addWidget(group_box)
        self.setLayout(main_layout)

    def update_speed(self, value):
        """
        Update the simulation speed and the label text.

        :param value: The new speed multiplier value from the slider.
        """
        self.current_speed = value
        self.label.setText(f"Current speed: x{self.current_speed}")
        # self.simulation.set_speed(self.current_speed)  # Assuming simulation has a set_speed method
