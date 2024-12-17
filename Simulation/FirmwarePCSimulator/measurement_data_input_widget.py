from PyQt6.QtWidgets import QWidget, QGroupBox, QVBoxLayout, QSlider, QLabel, QSizePolicy
from PyQt6.QtCore import Qt

class MeasurementDataInputWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Create a group box for the frame
        group_box = QGroupBox("Measurement Data Input")
        group_layout = QVBoxLayout()

        # Create sliders for Pulse Counters 1 to 5
        self.pulse_sliders = []
        for i in range(1, 6):  # Pulse Counter 1 to 5
            # Label for the pulse counter
            slider_label = QLabel(f"Pulse Counter #{i}:")
            group_layout.addWidget(slider_label)
            
            # Slider for the pulse counter
            slider = QSlider(Qt.Orientation.Horizontal)
            slider.setMinimum(1)
            slider.setMaximum(500)  # Increased range for finer adjustment
            slider.setSingleStep(1)  # Small step for smooth adjustments
            slider.setPageStep(10)   # Page step for larger increments
            slider.setValue(300)     # Default value in the middle
            slider.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
            group_layout.addWidget(slider)

            # Store slider reference
            self.pulse_sliders.append(slider)

        group_box.setLayout(group_layout)

        # Main layout for this widget
        main_layout = QVBoxLayout()
        main_layout.addWidget(group_box)
        main_layout.setStretch(0, 1)  # Allow group box to expand to fill space
        self.setLayout(main_layout)

        # Set the size policy to make this widget expand in available space
        self.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)

    def get_pulse_counter_values(self):
        """
        Retrieve current values of all pulse counter sliders.
        :return: list of int
        """
        return [slider.value() for slider in self.pulse_sliders]
