"""
Module for managing the main window of the Firmware Simulator GUI.

This module provides the `MainWindow` class, which acts as the central
controller for various widgets, including the hardware display, tabs,
and logging components.
"""

from datetime import datetime
import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk, GLib
from HMI.simulation_control_widget import SimulationControlWidget
from HMI.direction_button_widget import DirectionButtonWidget
from HMI.hardware_display_widget import HardwareDisplayWidget
from HMI.simulation_speed_widget import SimulationSpeedWidget
from HMI.measurement_data_input_widget import (
    MeasurementDataInputWidget
)
from HMI.log_tabs_widget import LogTabsWidget, LogTabID
from HMI.data_visualization_widget import DataVisualizationWidget


class MainWindow(Gtk.ApplicationWindow):

    """
    Main application window for the Firmware Simulator.

    This window integrates various widgets to provide a comprehensive
    simulation environment, including hardware display, log tabs,
    and measurement inputs.
    """

    # By design, this GUI's main class integrates many widgets,
    # resulting in a high number of instance attributes.
    # pylint: disable=too-many-instance-attributes

    def __init__(self, simulation, application):
        """
        Initialize the main window and its components.

        :param simulation: Simulation instance used to provide data and
                           handle interactions.
        :param application: Gtk.Application instance.
        """
        super().__init__(application=application)

        self.simulation = simulation
        self.simulation.set_esp8266_uart0_tx_callback(self.on_esp8266_tx)
        self.simulation.set_esp8266_gpio_callback(self.update_leds)

        self.display_width = self.simulation.get_display_width()
        self.display_height = self.simulation.get_display_height()

        # Set window properties
        self.set_title("Firmware Simulator")
        self.set_default_size(800, 600)

        # Main layout
        main_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=5)
        self.set_child(main_box)

        # Top Layout for Tabs, Hardware Display, and Measurement Input
        top_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=5)
        main_box.append(top_box)

        # Config tabs on the left side
        self.tabs = Gtk.Notebook()
        self.tabs.set_hexpand(True)
        
        # Create tab pages
        self.config_tab1 = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=0)
        self.data_visualization_tab = DataVisualizationWidget()
        
        # Add pages to notebook
        self.tabs.append_page(self.config_tab1, Gtk.Label(label="Actions"))
        self.tabs.append_page(self.data_visualization_tab, Gtk.Label(label="Data Visualization"))

        # Setup the tabs layout
        self.setup_tabs()

        # Hardware display widget in the middle
        self.hardware_display = HardwareDisplayWidget(
            self.display_width, self.display_height
        )
        self.hardware_display.set_hexpand(True)

        # Measurement Data Input widget on the right with callback
        self.measurement_data_input_widget = (
            MeasurementDataInputWidget(
                update_measurement_callback=self.on_measurement_update
            )
        )

        # Add widgets to the top layout with expansion properties
        top_box.append(self.tabs)
        top_box.append(self.hardware_display)
        top_box.append(self.measurement_data_input_widget)

        # Log output tabs at the bottom
        #self.log_tabs = LogTabsWidget()
        #self.log_tabs.set_vexpand(True)
        #main_box.append(self.log_tabs)

        # Use GLib timeout for periodic updates
        self.timer_id = GLib.timeout_add(20, self.update_display)  # 20ms intervals

    def setup_tabs(self):
        """
        Set up the tabs for configuration and data visualization.

        Adds widgets to the "Actions" tab for controlling the simulation.
        """
        # Set alignment for Actions tab
        self.config_tab1.set_valign(Gtk.Align.START)

        # Buttons for the Actions tab
        self.main_control_widget = SimulationControlWidget(self.simulation)
        self.direction_buttons_widget = DirectionButtonWidget(self.simulation)
        self.simulation_speed_widget = SimulationSpeedWidget(self.simulation)

        # Add buttons to the Actions tab layout
        self.config_tab1.append(self.main_control_widget)
        self.config_tab1.append(self.direction_buttons_widget)
        self.config_tab1.append(self.simulation_speed_widget)

    def update_display(self):
        """
        Update the hardware display with pixel data from the simulation.
        
        :return: True to continue the timer, False to stop it.
        """
        self.hardware_display.update_from_simulation(self.simulation)
        return True  # Continue the timer

    def on_measurement_update(self, values):
        """
        Handle updates from the MeasurementDataInputWidget sliders.

        :param values: List of current slider values.
        """
        timestamp = f"{datetime.now():%Y-%m-%d %H:%M:%S}"
        message = (
            "Simulated pulse counter values: "
            f"{', '.join(str(value) for value in values)}"
        )
        self.log_tabs.add_log(LogTabID.PULSE_COUNTER, timestamp, message)

        self.data_visualization_tab.update_pulse_counters(timestamp, values)
        self.simulation.update_pulse_counters(values)

    def on_esp8266_tx(self, message):
        """
        Handle ESP8266 UART transmission from the simulation.

        :param message: The message transmitted.
        """
        timestamp = f"{datetime.now():%Y-%m-%d %H:%M:%S}"
        self.log_tabs.add_log(LogTabID.ESP8266_UART_0, timestamp, message)

    def update_leds(self, gpio, state):
        """
        Update the state of LEDs on the hardware display.

        :param gpio: GPIO identifier for the LED.
        :param state: Boolean representing the LED state (on or off).
        """
        self.hardware_display.set_led_state(gpio, state)
    
    def do_close_request(self):
        """
        Handle window close request. Clean up the timer.
        """
        if self.timer_id:
            GLib.source_remove(self.timer_id)
            self.timer_id = None
        return False  # Allow the window to close