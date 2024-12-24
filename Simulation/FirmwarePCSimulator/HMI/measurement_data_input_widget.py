from PyQt6.QtWidgets import QWidget, QGroupBox, QVBoxLayout, QSlider, QLabel, QSizePolicy
from PyQt6.QtCore import Qt

class MeasurementDataInputWidget(QWidget):
    def __init__(self, update_measurement_callback=None):
        super().__init__()

        self.update_measurement_callback = update_measurement_callback

        # Create a group box for the frame
        group_box = QGroupBox("Measurement Data Input")
        group_layout = QVBoxLayout()

        # Create sliders for Pulse Counters
        self.pulse_sliders = []
        for i in range(1, 5):
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
            slider.valueChanged.connect(self.on_slider_value_changed)
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

    def on_slider_value_changed(self):
        """
        Triggered when any slider value is changed. Calls the update_measurement_callback with the current values.
        """
        if self.update_measurement_callback:
            self.update_measurement_callback(self.get_pulse_counter_values())

    def get_pulse_counter_values(self):
        """
        Retrieve current values of all pulse counter sliders.
        :return: list of int
        """
        return [slider.value() for slider in self.pulse_sliders]
