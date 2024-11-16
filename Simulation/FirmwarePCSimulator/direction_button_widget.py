from PyQt6.QtWidgets import QWidget, QGridLayout, QPushButton
from PyQt6.QtCore import Qt
class DirectionButtonWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Create buttons
        self.button_up = QPushButton("Up")
        self.button_down = QPushButton("Down")
        self.button_left = QPushButton("Left")
        self.button_right = QPushButton("Right")

        # Create a grid layout and add buttons to the layout
        layout = QGridLayout()
        layout.setAlignment(Qt.AlignmentFlag.AlignTop)  # Align layout to the top
        layout.addWidget(self.button_up, 0, 1)
        layout.addWidget(self.button_down, 0, 2)
        layout.addWidget(self.button_left, 0, 3)
        layout.addWidget(self.button_right, 0, 4)

        # Set the layout for this widget
        self.setLayout(layout)