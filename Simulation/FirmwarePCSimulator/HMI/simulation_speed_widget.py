"""
Module for managing the simulation speed widget in a GTK GUI.

This module provides the `SimulationSpeedWidget` class, which contains a slider
for adjusting the speed of the firmware simulation.
"""

import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk


class SimulationSpeedWidget(Gtk.Box):

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
        super().__init__(orientation=Gtk.Orientation.VERTICAL, spacing=0)

        self.simulation = simulation
        self.current_speed = 1  # Default speed multiplier

        # Create a frame to contain the slider and label
        frame = Gtk.Frame()
        frame.set_label("Simulation Speed")
        
        # Create a box for the frame content
        frame_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
        frame_box.set_margin_start(10)
        frame_box.set_margin_end(10)
        frame_box.set_margin_top(10)
        frame_box.set_margin_bottom(10)

        # Create a horizontal slider (Scale)
        self.slider = Gtk.Scale.new_with_range(
            Gtk.Orientation.HORIZONTAL, 1, 5, 1
        )
        self.slider.set_value(self.current_speed)
        self.slider.set_draw_value(False)  # Don't draw value on slider itself
        self.slider.set_hexpand(True)
        
        # Add tick marks
        for i in range(1, 6):
            self.slider.add_mark(i, Gtk.PositionType.BOTTOM, f"x{i}")
        
        # Connect value changed signal
        self.slider.connect("value-changed", self.update_speed)

        # Label to display current speed
        self.label = Gtk.Label(label=f"Current speed: x{self.current_speed}")
        self.label.set_halign(Gtk.Align.CENTER)

        # Add slider and label to layout
        frame_box.append(self.slider)
        frame_box.append(self.label)

        frame.set_child(frame_box)

        # Add the frame to this widget
        self.append(frame)

    def update_speed(self, slider):
        """
        Update the simulation speed and the label text.

        :param slider: The slider widget that triggered the event.
        """
        self.current_speed = int(slider.get_value())
        self.label.set_text(f"Current speed: x{self.current_speed}")
        # self.simulation.set_speed(self.current_speed)  # Assuming simulation has a set_speed method