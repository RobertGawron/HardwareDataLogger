from datetime import datetime

from PyQt6.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QTabWidget
from PyQt6.QtCore import Qt, QTimer

from simulation_control_widget import SimulationControlWidget
from direction_button_widget import DirectionButtonWidget
from hardware_display_widget import HardwareDisplayWidget
from simulation_speed_widget import SimulationSpeedWidget
from measurement_data_input_widget import MeasurementDataInputWidget
from log_tabs_widget import LogTabsWidget, LogTabID
from data_visualization_widget import DataVisualizationWidget


class MainWindow(QMainWindow):
    def __init__(self, simulation):
        super().__init__()

        self.simulation = simulation

        self.display_width = self.simulation.get_display_width()
        self.display_height = self.simulation.get_display_height()

        # Set window properties
        self.setWindowTitle("Firmware Simulator")
        self.setGeometry(100, 100, 800, 600)

        # Create central widget and set layout
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Main layout
        main_layout = QVBoxLayout()  # Vertical layout to align components top to bottom
        central_widget.setLayout(main_layout)

        # Top Layout for Tabs, Hardware Display, and Measurement Input
        top_layout = QHBoxLayout()
        main_layout.addLayout(top_layout)

        # Config tabs on the left side
        self.tabs = QTabWidget()
        self.config_tab1 = QWidget()
        self.data_visualization_tab = DataVisualizationWidget()
        self.tabs.addTab(self.config_tab1, "Actions")
        self.tabs.addTab(self.data_visualization_tab, "Data Visualization")

        # Setup the tabs layout
        self.setup_tabs()

        # Hardware display widget in the middle
        self.hardware_display = HardwareDisplayWidget(self.display_width, self.display_height)

        # Measurement Data Input widget on the right with callback
        self.measurement_data_input_widget = MeasurementDataInputWidget(update_measurement_callback=self.on_measurement_update)

        # Add widgets to the top layout
        top_layout.addWidget(self.tabs, 1)  # Config tabs
        top_layout.addWidget(self.hardware_display, 3)  # Hardware display takes more space
        top_layout.addWidget(self.measurement_data_input_widget, 2)  # Measurement Data Input expands proportionally

        # Log output tabs at the bottom
        self.log_tabs = LogTabsWidget()
        main_layout.addWidget(self.log_tabs, 1)  # Logs take bottom section

        # Use a QTimer for periodic updates
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_display)
        self.timer.start(20)  # 20ms intervals

    def setup_tabs(self):
        # Layout for Actions tab
        actions_layout = QVBoxLayout()
        actions_layout.setAlignment(Qt.AlignmentFlag.AlignTop)
        self.config_tab1.setLayout(actions_layout)

        # Buttons for the Actions tab
        self.main_control_widget = SimulationControlWidget(self.simulation)
        self.direction_buttons_widget = DirectionButtonWidget(self.simulation)
        self.simulation_speed_widget = SimulationSpeedWidget(self.simulation)

        # Add buttons to the Actions tab layout
        actions_layout.addWidget(self.main_control_widget)
        actions_layout.addWidget(self.direction_buttons_widget)
        actions_layout.addWidget(self.simulation_speed_widget)

    def update_display(self):
        """
        Update the hardware display with pixel data from the simulation.
        """
        self.hardware_display.update_from_simulation(self.simulation)

    def on_measurement_update(self, values):
        """
        Handle updates from the MeasurementDataInputWidget sliders.
        :param values: List of current slider values.
        """
        timestamp = "{:%Y-%m-%d %H:%M:%S}".format(datetime.now())
        message = "Simulated pulse counter values: " + ", ".join(f"{value}" for value in values)
        self.log_tabs.add_log(LogTabID.PULSE_COUNTER, timestamp, message)
        
        self.data_visualization_tab.update_pulse_counters(timestamp, values)
        self.simulation.update_pulse_counters(values)
