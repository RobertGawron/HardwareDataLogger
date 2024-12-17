from PyQt6.QtWidgets import QWidget, QVBoxLayout, QGroupBox, QSlider, QLabel
from PyQt6.QtCore import Qt


class SimulationSpeedWidget(QWidget):
    def __init__(self, simulation):
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
        """
        self.current_speed = value
        self.label.setText(f"Current speed: x{self.current_speed}")
        #self.simulation.set_speed(self.current_speed)  # Assuming simulation has a set_speed method
