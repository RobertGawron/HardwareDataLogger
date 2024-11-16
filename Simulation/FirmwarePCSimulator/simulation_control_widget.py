from PyQt6.QtWidgets import QWidget, QGridLayout, QPushButton
from PyQt6.QtCore import Qt
class SimulationControlWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Create buttons
        self.button_start = QPushButton("Start")
        self.button_stop = QPushButton("Stop")
        self.button_reload = QPushButton("Reload")
     
        # Create a grid layout and add buttons to the layout
        layout = QGridLayout()
        layout.setAlignment(Qt.AlignmentFlag.AlignTop)  # Align layout to the top
        layout.addWidget(self.button_start, 0, 1)
        layout.addWidget(self.button_stop, 0, 2)
        layout.addWidget(self.button_reload, 0, 3)
 
        # Set the layout for this widget
        self.setLayout(layout)