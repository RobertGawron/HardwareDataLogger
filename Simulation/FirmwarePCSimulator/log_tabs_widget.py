from PyQt6.QtWidgets import QWidget, QVBoxLayout, QTabWidget, QTextEdit
from PyQt6.QtGui import QFont
from enum import Enum

class LogTabID(Enum):
    PULSE_COUNTER = 0
    UART_1 = 1
    UART_2 = 2
    UART_3 = 3

class LogTabsWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Main layout for the widget
        main_layout = QVBoxLayout()
        self.setLayout(main_layout)

        # Create the tab widget
        self.tabs = QTabWidget()

        # Store references to text edits for each tab
        self.log_outputs = {}

        # Add a single Pulse Counter tab
        self.create_pulse_counter_tab()

        # Add UART tabs
        self.create_uart_tabs()

        # Add tabs to the layout
        main_layout.addWidget(self.tabs)

    def create_pulse_counter_tab(self):
        """
        Create a single tab for Pulse Counter with fixed-width font log output.
        """
        # Create a QTextEdit for log output
        log_output = QTextEdit()
        log_output.setReadOnly(True)
        log_output.setFont(QFont("Courier", 10))  # Fixed-width font
        
        # Store reference and add to the tab
        self.log_outputs[LogTabID.PULSE_COUNTER] = log_output
        self.tabs.addTab(log_output, "Pulse Counter")

    def create_uart_tabs(self):
        """
        Create tabs for UART logs.
        """
        uart_tabs = {
            LogTabID.UART_1: "UART #1",
            LogTabID.UART_2: "UART #2",
            LogTabID.UART_3: "UART #3"
        }
        for tab_id, name in uart_tabs.items():
            log_output = QTextEdit()
            log_output.setReadOnly(True)
            log_output.setPlaceholderText(f"Logs for {name}")
            
            # Store reference and add to the tab
            self.log_outputs[tab_id] = log_output
            self.tabs.addTab(log_output, name)

    def add_log(self, tab_id, timestamp, message):
        """
        Add a log message to the specified tab.
        :param tab_id: ID of the tab (LogTabID)
        :param timestamp: Timestamp of the log message
        :param message: Log message content
        """
        if tab_id in self.log_outputs:
            log_widget = self.log_outputs[tab_id]
            log_widget.append(f"[{timestamp}] {message}")
        else:
            raise ValueError(f"Invalid tab ID: {tab_id}")
