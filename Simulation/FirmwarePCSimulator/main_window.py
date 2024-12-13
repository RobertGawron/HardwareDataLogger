from PyQt6.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QTabWidget, QTextEdit, QPushButton
from PyQt6.QtCore import Qt, QTimer

from simulation_control_widget import SimulationControlWidget
from direction_button_widget import DirectionButtonWidget
from hardware_display_widget import HardwareDisplayWidget


class MainWindow(QMainWindow):
    def __init__(self, simulation):
        super().__init__()

        self.simulation = simulation

        self.display_width = self.simulation.get_display_width()
        self.display_height = self.simulation.get_display_height()

        # Set window properties
        self.setWindowTitle("Firmware Simulator")
        self.setGeometry(100, 100, 800, 400)

        # Create central widget and set layout
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Main layout
        main_layout = QHBoxLayout()
        central_widget.setLayout(main_layout)

        # Config tabs on the left side
        self.tabs = QTabWidget()
        self.config_tab1 = QWidget()
        self.config_tab2 = QWidget()
        self.tabs.addTab(self.config_tab1, "Actions")
        self.tabs.addTab(self.config_tab2, "Config")

        # Setup the tabs layout
        self.setup_tabs()

        # Hardware display widget in the middle
        self.hardware_display = HardwareDisplayWidget(self.display_width, self.display_height)

        # Log output on the right side
        self.log_output = QTextEdit()
        self.log_output.setReadOnly(True)

        # Add widgets to the main layout
        main_layout.addWidget(self.tabs, 1)  # Config tabs
        main_layout.addWidget(self.hardware_display, 2)  # Hardware display
        main_layout.addWidget(self.log_output, 3)  # Logs

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
        self.load_test_data_button = QPushButton("Load Test Data")

        # Add buttons to the Actions tab layout
        actions_layout.addWidget(self.main_control_widget)
        actions_layout.addWidget(self.direction_buttons_widget)
        actions_layout.addWidget(self.load_test_data_button)

        # Layout for Config tab (empty for now)
        config_layout = QVBoxLayout()
        config_layout.setAlignment(Qt.AlignmentFlag.AlignTop)
        self.config_tab2.setLayout(config_layout)

    def update_display(self):
        """
        Update the hardware display with pixel data from the simulation.
        """
        self.hardware_display.update_from_simulation(self.simulation)
