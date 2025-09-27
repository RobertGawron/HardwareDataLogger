"""
Main application entry point for the Firmware Simulator.

This module initializes the PyQt6 application, sets up the simulation
and main window, and starts the application's event loop. It provides
the foundation for visualizing and interacting with the firmware
simulation.
"""

import sys
from PyQt6.QtWidgets import QApplication
from HMI.main_window import MainWindow
from simulation import Simulation


def main() -> None:
    """
    Entry point for the application. Initializes the PyQt application,
    sets up the simulation and main window, and starts the event loop.
    """
    app: QApplication = QApplication(sys.argv)
    simulation: Simulation = Simulation()
    window: MainWindow = MainWindow(simulation)
    window.show()

    # Trigger an initial hardware display update
    window.update_display()

    # Start the application's event loop
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
