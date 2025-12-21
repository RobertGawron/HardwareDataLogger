"""
Module for visualizing data using a custom GTK widget integrated
with Matplotlib.

This module defines a `DataVisualizationWidget` class, which provides a
graphical representation of pulse counter data over time.
"""

import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_gtk4agg import FigureCanvasGTK4Agg as FigureCanvas


class DataVisualizationWidget(Gtk.Box):

    """
    Widget for visualizing pulse counter data.

    This widget uses Matplotlib to display pulse counter values over time
    in a GTK application.
    """

    # pylint: disable=too-few-public-methods
    # This is a GUI widget with small functionality

    def __init__(self):
        """Initialize the DataVisualizationWidget."""
        super().__init__(orientation=Gtk.Orientation.VERTICAL, spacing=0)
        
        # Set alignment to top
        self.set_valign(Gtk.Align.START)

        # Create a Matplotlib figure and canvas
        self.figure, self.ax = plt.subplots()
        self.canvas = FigureCanvas(self.figure)
        
        # Set the canvas to expand and fill
        self.canvas.set_hexpand(True)
        self.canvas.set_vexpand(True)

        # Add the canvas to the box
        self.append(self.canvas)

        # Initialize data storage for pulse counters
        self.time_stamps = []
        self.pulse_counters = {i: [] for i in range(4)}  # 4 pulse counters

    def update_pulse_counters(self, timestamp, new_values):
        """
        Update the graph with new pulse counter values.

        :param timestamp: The timestamp of the update.
        :param new_values: A list of pulse counter values.
        """
        # Append new data to the storage
        self.time_stamps.append(timestamp)
        for i, value in enumerate(new_values):
            self.pulse_counters[i].append(value)

        # Ensure the time series does not grow indefinitely
        max_points = 100
        if len(self.time_stamps) > max_points:
            self.time_stamps.pop(0)
            for key in self.pulse_counters:
                self.pulse_counters[key].pop(0)

        # Clear and plot new data
        self.ax.clear()
        for i, counter_values in self.pulse_counters.items():
            self.ax.plot(
                self.time_stamps,
                counter_values,
                label=f"Pulse Counter {i + 1}"
            )

        self.ax.set_title("Pulse Counter Values Over Time")
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Value")
        self.ax.legend()

        # Redraw the canvas
        self.canvas.draw()