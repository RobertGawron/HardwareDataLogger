"""
Main application entry point for the Firmware Simulator.

This module initializes the GTK application, sets up the simulation
and main window, and starts the application's event loop. It provides
the foundation for visualizing and interacting with the firmware
simulation.
"""

import sys
import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk, GLib
from HMI.main_window import MainWindow
from simulation import Simulation


class FirmwareSimulatorApp(Gtk.Application):
    """
    Main GTK application class for the Firmware Simulator.
    """
    
    def __init__(self, simulation: Simulation):
        """
        Initialize the GTK application.
        
        Args:
            simulation: The Simulation instance to use
        """
        super().__init__(application_id='com.example.firmwaresimulator')
        self.simulation = simulation
        self.window = None
    
    def do_activate(self):
        """
        Called when the application is activated. Creates and shows the main window.
        """
        if not self.window:
            self.window = MainWindow(self.simulation, application=self)
            self.add_window(self.window)
        
        # Trigger an initial hardware display update
        GLib.idle_add(self.window.update_display)
        
        self.window.present()


def main() -> None:
    """
    Entry point for the application. Initializes the GTK application,
    sets up the simulation and main window, and starts the event loop.
    """
    simulation: Simulation = Simulation()
    app: FirmwareSimulatorApp = FirmwareSimulatorApp(simulation)
    
    # Start the application's event loop
    exit_status = app.run(sys.argv)
    sys.exit(exit_status)


if __name__ == "__main__":
    main()