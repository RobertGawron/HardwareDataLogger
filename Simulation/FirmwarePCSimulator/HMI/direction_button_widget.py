"""
Module for creating a direction button widget in a GTK GUI.

This widget provides directional buttons (Up, Down, Left, Right) and
integrates with a simulation to trigger key press and release events.
"""

import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk
from simulation import SimulationKey


class DirectionButtonWidget(Gtk.Box):

    """
    Widget for managing directional hardware buttons.

    This widget creates a graphical interface with directional buttons that
    communicate with a simulation object to handle key press and release
    events.
    """

    # pylint: disable=too-few-public-methods
    # This is a GUI widget with small functionality

    def __init__(self, simulation):
        """
        Initialize the DirectionButtonWidget.

        :param simulation: Simulation instance to handle button events.
        """
        super().__init__(orientation=Gtk.Orientation.VERTICAL, spacing=0)

        self.simulation = simulation

        # Create buttons
        self.button_up = Gtk.Button(label="Up")
        self.button_down = Gtk.Button(label="Down")
        self.button_left = Gtk.Button(label="Left")
        self.button_right = Gtk.Button(label="Right")

        # Create a grid layout and add buttons to the layout
        button_grid = Gtk.Grid()
        button_grid.set_valign(Gtk.Align.START)
        button_grid.set_row_spacing(5)
        button_grid.set_column_spacing(5)
        button_grid.attach(self.button_up, 1, 0, 1, 1)
        button_grid.attach(self.button_down, 1, 1, 1, 1)
        button_grid.attach(self.button_left, 0, 1, 1, 1)
        button_grid.attach(self.button_right, 2, 1, 1, 1)

        # Create gesture controllers for pressed/released events
        self._setup_button_gestures(self.button_up, SimulationKey.UP)
        self._setup_button_gestures(self.button_down, SimulationKey.DOWN)
        self._setup_button_gestures(self.button_left, SimulationKey.LEFT)
        self._setup_button_gestures(self.button_right, SimulationKey.RIGHT)

        # Create a frame to enclose buttons with a title
        frame = Gtk.Frame()
        frame.set_label("Hardware Buttons")
        frame.set_child(button_grid)
        frame.set_margin_start(5)
        frame.set_margin_end(5)
        frame.set_margin_top(5)
        frame.set_margin_bottom(5)

        # Add the frame to this widget
        self.append(frame)

    def _setup_button_gestures(self, button, key):
        """
        Set up gesture controllers for button press and release events.

        :param button: The Gtk.Button to configure.
        :param key: The SimulationKey associated with this button.
        """
        # Create a gesture controller for the button
        gesture = Gtk.GestureClick.new()
        gesture.set_button(1)  # Left mouse button
        
        # Connect pressed signal
        gesture.connect("pressed", lambda g, n, x, y: self.simulation.key_pressed(key))
        
        # Connect released signal
        gesture.connect("released", lambda g, n, x, y: self.simulation.key_released(key))
        
        # Add the gesture to the button
        button.add_controller(gesture)