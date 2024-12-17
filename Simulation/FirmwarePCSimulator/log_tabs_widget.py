from PyQt6.QtWidgets import QWidget, QVBoxLayout, QTabWidget, QTextEdit
from PyQt6.QtGui import QFont


class LogTabsWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Main layout for the widget
        main_layout = QVBoxLayout()
        self.setLayout(main_layout)

        # Create the tab widget
        self.tabs = QTabWidget()

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
        log_output.setText("hello")  # Log content

        # Add the QTextEdit to the tab
        self.tabs.addTab(log_output, "Pulse Counter")

    def create_uart_tabs(self):
        """
        Create tabs for UART logs.
        """
        uarts = ["UART #1", "UART #2", "UART #3"]
        for name in uarts:
            log_output = QTextEdit()
            log_output.setReadOnly(True)
            log_output.setPlaceholderText(f"Logs for {name}")
            self.tabs.addTab(log_output, name)
