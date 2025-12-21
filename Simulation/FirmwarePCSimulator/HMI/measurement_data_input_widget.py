"""
Module for managing the measurement data input widget in a GTK GUI.

This module provides the `MeasurementDataInputWidget` class, which contains sliders
to adjust and simulate pulse counter values.
"""

import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk


class MeasurementDataInputWidget(Gtk.Box):

    """
    Widget for adjusting measurement data inputs via sliders.

    This widget allows users to simulate pulse counter values by adjusting sliders.
    """

    def __init__(self, update_measurement_callback=None):
        """
        Initialize the MeasurementDataInputWidget.

        :param update_measurement_callback: A callback function triggered when
                                            slider values change.
        """
        super().__init__(orientation=Gtk.Orientation.VERTICAL, spacing=0)

        self.update_measurement_callback = update_measurement_callback

        # Create a frame for the widget
        frame = Gtk.Frame()
        frame.set_label("Measurement Data Input")
        
        # Create a box for the frame content
        frame_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=5)
        frame_box.set_margin_start(10)
        frame_box.set_margin_end(10)
        frame_box.set_margin_top(10)
        frame_box.set_margin_bottom(10)

        # Create sliders for Pulse Counters
        self.pulse_sliders = []
        for i in range(1, 5):
            # Label for the pulse counter
            slider_label = Gtk.Label(label=f"Pulse Counter #{i}:")
            slider_label.set_halign(Gtk.Align.START)
            frame_box.append(slider_label)

            # Slider (Scale) for the pulse counter
            slider = Gtk.Scale.new_with_range(
                Gtk.Orientation.HORIZONTAL, 1, 500, 1
            )
            slider.set_value(300)
            slider.set_draw_value(True)
            slider.set_value_pos(Gtk.PositionType.RIGHT)
            slider.set_hexpand(True)
            
            # Connect value changed signal
            slider.connect("value-changed", self.on_slider_value_changed)
            frame_box.append(slider)

            # Store slider reference
            self.pulse_sliders.append(slider)

        frame.set_child(frame_box)

        # Add the frame to this widget
        self.append(frame)

        # Set the widget to expand in available space
        self.set_hexpand(True)
        self.set_vexpand(True)

    def on_slider_value_changed(self, slider):
        """
        Triggered when any slider value is changed.

        Calls the update_measurement_callback with the current slider values.
        
        :param slider: The slider that triggered the event.
        """
        if self.update_measurement_callback:
            self.update_measurement_callback(self.get_pulse_counter_values())

    def get_pulse_counter_values(self):
        """
        Retrieve current values of all pulse counter sliders.

        :return: A list of int representing the slider values.
        """
        return [int(slider.get_value()) for slider in self.pulse_sliders]