"""
Module for managing the simulation control widget in a GTK GUI.

This module provides the `SimulationControlWidget` class, which contains buttons
for starting, stopping, and reloading the firmware simulation.
"""

import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk


class SimulationControlWidget(Gtk.Box):

    """
    Widget for controlling the simulation firmware.

    This widget provides buttons to start, stop, and reload the firmware simulation.
    """

    # pylint: disable=too-few-public-methods
    # This is a GUI widget with small functionality

    def __init__(self, simulation):
        """
        Initialize the SimulationControlWidget.

        :param simulation: Simulation instance to control firmware operations.
        """
        super().__init__(orientation=Gtk.Orientation.VERTICAL, spacing=0)

        self.simulation = simulation

        # Create buttons
        self.button_start = Gtk.Button(label="Start")
        self.button_stop = Gtk.Button(label="Stop")
        self.button_reload = Gtk.Button(label="Reload")

        # Connect button signals to simulation methods
        self.button_start.connect("clicked", lambda btn: self.simulation.start_firmware())
        self.button_stop.connect("clicked", lambda btn: self.simulation.stop_firmware())
        self.button_reload.connect("clicked", lambda btn: self.simulation.reload_firmware())

        # Create a grid layout and add buttons to the layout
        button_grid = Gtk.Grid()
        button_grid.set_valign(Gtk.Align.START)
        button_grid.set_column_spacing(5)
        button_grid.set_row_spacing(5)
        button_grid.attach(self.button_start, 1, 0, 1, 1)
        button_grid.attach(self.button_stop, 2, 0, 1, 1)
        button_grid.attach(self.button_reload, 3, 0, 1, 1)

        # Create a frame with a title "Device Status"
        frame = Gtk.Frame()
        frame.set_label("Device Status")
        
        # Create a box for the frame content
        frame_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=0)
        frame_box.set_margin_start(10)
        frame_box.set_margin_end(10)
        frame_box.set_margin_top(10)
        frame_box.set_margin_bottom(10)
        frame_box.append(button_grid)
        
        frame.set_child(frame_box)

        # Add the frame to this widget
        self.append(frame)