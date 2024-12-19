from PyQt6.QtWidgets import QWidget, QVBoxLayout
from PyQt6.QtCore import Qt
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

class DataVisualizationWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Main layout for the Data Visualization Widget
        self.layout = QVBoxLayout()
        self.layout.setAlignment(Qt.AlignmentFlag.AlignTop)

        # Create a Matplotlib figure and canvas
        self.figure, self.ax = plt.subplots()
        self.canvas = FigureCanvas(self.figure)

        # Add the canvas to the layout
        self.layout.addWidget(self.canvas)

        # Initialize data storage for pulse counters
        self.time_stamps = []
        self.pulse_counters = {i: [] for i in range(4)}  # 4 pulse counters

        self.setLayout(self.layout)

    def update_pulse_counters(self, timestamp, values):
        """
        Update the graph with new pulse counter values.

        :param timestamp: The timestamp of the update.
        :param values: A list of pulse counter values.
        """
        # Append new data to the storage
        self.time_stamps.append(timestamp)
        for i, value in enumerate(values):
            self.pulse_counters[i].append(value)

        # Ensure the time series does not grow indefinitely (optional)
        MAX_POINTS = 100
        if len(self.time_stamps) > MAX_POINTS:
            self.time_stamps.pop(0)
            for key in self.pulse_counters:
                self.pulse_counters[key].pop(0)

        # Clear and plot new data
        self.ax.clear()
        for i, values in self.pulse_counters.items():
            self.ax.plot(self.time_stamps, values, label=f"Pulse Counter {i + 1}")

        self.ax.set_title("Pulse Counter Values Over Time")
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Value")
        self.ax.legend()

        # Redraw the canvas
        self.canvas.draw()
