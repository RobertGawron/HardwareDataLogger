import sys
from datetime import datetime
from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QGridLayout, QVBoxLayout, QHBoxLayout, QTabWidget, QLabel, QTextEdit, QPushButton
from PyQt6.QtGui import QImage, QPainter, QColor, QPixmap
from PyQt6.QtCore import Qt
#from PyQt6.QtGui import QPixmap

from device_under_test import DeviceUnderTest

class DirectionButtonWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Create buttons
        self.button_up = QPushButton("Up")
        self.button_down = QPushButton("Down")
        self.button_left = QPushButton("Left")
        self.button_right = QPushButton("Right")

        # Create a grid layout and add buttons to the layout
        layout = QGridLayout()
        layout.addWidget(self.button_up, 0, 1)
        layout.addWidget(self.button_down, 0, 2)
        layout.addWidget(self.button_left, 0, 3)
        layout.addWidget(self.button_right, 0, 4)

        # Set the layout for this widget
        self.setLayout(layout)



class MainControlButtonWidget(QWidget):
    def __init__(self):
        super().__init__()

        # Create buttons
        self.button_start = QPushButton("Start")
        self.button_stop = QPushButton("Stop")
        self.button_reload = QPushButton("Reload")
     
        # Create a grid layout and add buttons to the layout
        layout = QGridLayout()
        layout.addWidget(self.button_start, 0, 1)
        layout.addWidget(self.button_stop, 0, 2)
        layout.addWidget(self.button_reload, 0, 3)
 
        # Set the layout for this widget
        self.setLayout(layout)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # Code specific to the simulation (load lib and initialize it)
        self.dut = DeviceUnderTest()
        self.dut.init() # todo bind it to the key
        self.display_width = self.dut.getDisplayWidth()
        self.display_height = self.dut.getDisplayHeight()

        # Code specific to GUI

        # Set window properties
        self.setWindowTitle("FirmwareSimulator")
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

        # Image placeholder in the middle
        
        # Create a QImage with specified width, height, and format
        self.image = QImage(self.display_width, self.display_height, QImage.Format.Format_RGB32)
        
        # Fill the image with white color
        self.image.fill(Qt.GlobalColor.white)


        self.image_label = QLabel()
 
        # Log output on the right side
        self.log_output = QTextEdit()
        self.log_output.setReadOnly(True)

        # Add widgets to the main layout
        main_layout.addWidget(self.tabs, 1)  # Config tabs
        main_layout.addWidget(self.image_label, 2)  # Image display
        main_layout.addWidget(self.log_output, 3)  # Logs

        self.onHWDisplayUpdate()

    def setup_tabs(self):
        # Layout for Actions tab
        actions_layout = QVBoxLayout()
        self.config_tab1.setLayout(actions_layout)

        # Buttons for the Actions tab
        #self.generate_pulse_button = QPushButton("Pulse #0")
        self.main_control_widget = MainControlButtonWidget()
        self.direction_buttons_widget = DirectionButtonWidget()
        #self.reload_dut_button = QPushButton("Reload DUT")
        self.load_test_data_button = QPushButton("Load Test Data")

        # Add buttons to the Actions tab layout
        #actions_layout.addWidget(self.generate_pulse_button)
        actions_layout.addWidget(self.main_control_widget)
        actions_layout.addWidget(self.direction_buttons_widget)
        #actions_layout.addWidget(self.reload_dut_button)
        actions_layout.addWidget(self.load_test_data_button)

        # Layout for Config tab (empty for now)
        config_layout = QVBoxLayout()
        self.config_tab2.setLayout(config_layout)

    def onHWDisplayUpdate(self):
        painter = QPainter(self.image)

        for y in range(self.display_height):
            for x in range(self.display_width):
                pixel = self.dut.getDisplayPixelValue(x, y)
                
                color = QColor(pixel.red, pixel.green, pixel.blue)
                painter.setPen(color)
                painter.drawPoint(x, y)

        # Finish painting
        painter.end()

        # Convert QImage to QPixmap
        pixmap = QPixmap.fromImage(self.image)

        self.image_label.setPixmap(pixmap)
        

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())