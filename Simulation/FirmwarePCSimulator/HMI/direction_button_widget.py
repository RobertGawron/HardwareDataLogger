from PyQt6.QtWidgets import QWidget, QGridLayout, QPushButton, QGroupBox, QVBoxLayout
from PyQt6.QtCore import Qt
from simulation import SimulationKey

class DirectionButtonWidget(QWidget):
    def __init__(self, simulation):
        super().__init__()

        self.simulation = simulation

        # Create buttons
        self.button_up = QPushButton("Up")
        self.button_down = QPushButton("Down")
        self.button_left = QPushButton("Left")
        self.button_right = QPushButton("Right")

        # Create a grid layout and add buttons to the layout
        button_layout = QGridLayout()
        button_layout.setAlignment(Qt.AlignmentFlag.AlignTop)  # Align layout to the top
        button_layout.addWidget(self.button_up, 0, 1)
        button_layout.addWidget(self.button_down, 0, 2)
        button_layout.addWidget(self.button_left, 0, 3)
        button_layout.addWidget(self.button_right, 0, 4)

        # Connect signals for pressed/released
        self.button_up.pressed.connect(lambda: self.simulation.key_pressed(SimulationKey.UP))
        self.button_up.released.connect(lambda: self.simulation.key_released(SimulationKey.UP))

        self.button_down.pressed.connect(lambda: self.simulation.key_pressed(SimulationKey.DOWN))
        self.button_down.released.connect(lambda: self.simulation.key_released(SimulationKey.DOWN))

        self.button_left.pressed.connect(lambda: self.simulation.key_pressed(SimulationKey.LEFT))
        self.button_left.released.connect(lambda: self.simulation.key_released(SimulationKey.LEFT))

        self.button_right.pressed.connect(lambda: self.simulation.key_pressed(SimulationKey.RIGHT))
        self.button_right.released.connect(lambda: self.simulation.key_released(SimulationKey.RIGHT))

        # Group box to enclose buttons with a frame and title
        group_box = QGroupBox("Hardware Buttons")
        group_layout = QVBoxLayout()
        group_layout.addLayout(button_layout)
        group_box.setLayout(group_layout)

        # Set the main layout for this widget
        main_layout = QVBoxLayout()
        main_layout.addWidget(group_box)
        self.setLayout(main_layout)
