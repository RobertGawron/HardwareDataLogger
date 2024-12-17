from PyQt6.QtWidgets import QWidget, QGridLayout, QPushButton, QGroupBox, QVBoxLayout
from PyQt6.QtCore import Qt

class SimulationControlWidget(QWidget):
    def __init__(self, simulation):
        super().__init__()

        self.simulation = simulation

        # Create buttons
        self.button_start = QPushButton("Start")
        self.button_stop = QPushButton("Stop")
        self.button_reload = QPushButton("Reload")
     
        # Connect button signals to simulation methods
        self.button_start.clicked.connect(self.simulation.start_firmware)
        self.button_stop.clicked.connect(self.simulation.stop_firmware)
        self.button_reload.clicked.connect(self.simulation.reload_firmware)

        # Create a grid layout and add buttons to the layout
        button_layout = QGridLayout()
        button_layout.setAlignment(Qt.AlignmentFlag.AlignTop)  # Align layout to the top
        button_layout.addWidget(self.button_start, 0, 1)
        button_layout.addWidget(self.button_stop, 0, 2)
        button_layout.addWidget(self.button_reload, 0, 3)

        # Add buttons to a group box with a title "Device Status"
        group_box = QGroupBox("Device Status")
        group_layout = QVBoxLayout()
        group_layout.addLayout(button_layout)
        group_box.setLayout(group_layout)
 
        # Main layout for this widget
        main_layout = QVBoxLayout()
        main_layout.addWidget(group_box)
        self.setLayout(main_layout)
