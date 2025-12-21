"""
Module for visualizing ESP8266 hardware states and rendering a simulated display.

This module provides the `HardwareDisplayWidget` class, which includes methods
for updating pixel colors, managing LED states, and integrating with simulation data.
"""

from enum import Enum
import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk, GdkPixbuf, Gdk
import cairo


class ESP8266LED(Enum):

    """Enumeration for ESP8266 LED identifiers."""

    WIFI_CONNECTION = 1
    DATA_RECEPTION = 2


class HardwareDisplayWidget(Gtk.Box):

    """
    Widget for simulating and visualizing hardware display.

    This widget renders a simulated hardware display and manages LED indicators
    for ESP8266 hardware states such as WiFi connection and data reception.
    """

    def __init__(self, display_width: int, display_height: int):
        """
        Initialize the HardwareDisplayWidget.

        :param display_width: Width of the display in pixels.
        :param display_height: Height of the display in pixels.
        """
        super().__init__(orientation=Gtk.Orientation.VERTICAL, spacing=0)
        self.display_width = display_width
        self.display_height = display_height

        # Create a Cairo ImageSurface for pixel manipulation
        self.hw_display = cairo.ImageSurface(
            cairo.FORMAT_RGB24, self.display_width, self.display_height
        )

        # Create a drawing area to display the image
        self.hw_display_widget = Gtk.DrawingArea()
        self.hw_display_widget.set_valign(Gtk.Align.START)
        self.hw_display_widget.set_content_width(self.display_width * 2)
        self.hw_display_widget.set_content_height(self.display_height * 2)
        self.hw_display_widget.set_draw_func(self._draw_display)

        self.append(self.hw_display_widget)

        # Add ESP8266 LEDs frame
        self.led_states = {
            ESP8266LED.WIFI_CONNECTION: (0, 128, 0),  # green
            ESP8266LED.DATA_RECEPTION: (139, 128, 0),  # Dark yellow
        }
        self.led_widgets = {}
        esp_leds_frame = self.create_esp_leds_frame()
        self.append(esp_leds_frame)

    def _draw_display(self, area, cr, width, height):
        """
        Draw function for the display widget.

        :param area: The DrawingArea widget.
        :param cr: Cairo context.
        :param width: Width of the drawing area.
        :param height: Height of the drawing area.
        """
        # Scale up 2x and use nearest-neighbor (no filtering)
        cr.scale(2.0, 2.0)
        cr.set_source_surface(self.hw_display, 0, 0)
        
        # Use NEAREST filter to avoid aliasing
        pattern = cr.get_source()
        pattern.set_filter(cairo.FILTER_NEAREST)
        
        cr.paint()

    def create_esp_leds_frame(self):
        """
        Create a frame containing ESP8266 LED indicators.

        :return: Gtk.Frame widget with ESP8266 LED indicators.
        """
        frame = Gtk.Frame()
        frame_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=5)
        frame_box.set_margin_start(10)
        frame_box.set_margin_end(10)
        frame_box.set_margin_top(10)
        frame_box.set_margin_bottom(10)

        # WiFi Connection indicator
        wifi_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        wifi_label = Gtk.Label(label="WiFi Connection")
        wifi_circle = Gtk.DrawingArea()
        wifi_circle.set_content_width(20)
        wifi_circle.set_content_height(20)
        wifi_circle.set_draw_func(self._create_led_draw_func((0, 128, 0)))
        self.led_widgets[ESP8266LED.WIFI_CONNECTION] = wifi_circle
        wifi_box.append(wifi_label)
        wifi_box.append(wifi_circle)
        frame_box.append(wifi_box)

        # Data Reception indicator
        data_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        data_label = Gtk.Label(label="UART Reception")
        data_circle = Gtk.DrawingArea()
        data_circle.set_content_width(20)
        data_circle.set_content_height(20)
        data_circle.set_draw_func(self._create_led_draw_func((255, 255, 0)))
        self.led_widgets[ESP8266LED.DATA_RECEPTION] = data_circle
        data_box.append(data_label)
        data_box.append(data_circle)
        frame_box.append(data_box)

        frame.set_child(frame_box)
        return frame

    def _create_led_draw_func(self, color):
        """
        Create a draw function for an LED circle.

        :param color: RGB tuple (0-255 range).
        :return: Draw function.
        """
        def draw_led(area, cr, width, height):
            r, g, b = color
            cr.set_source_rgb(r / 255.0, g / 255.0, b / 255.0)
            cr.arc(width / 2, height / 2, min(width, height) / 2, 0, 2 * 3.14159)
            cr.fill()
        return draw_led

    def set_led_state(self, led: ESP8266LED, power_on: bool):
        """
        Set the state of the specified LED.

        :param led: The LED to update (ESP8266LED enum).
        :param power_on: True to power on (brighten), False to power off
                         (return to original color).
        """
        led = ESP8266LED.DATA_RECEPTION  # hack

        if led in self.led_widgets:
            led_widget = self.led_widgets[led]
            original_color = self.led_states[led]
            if power_on:
                brighter_color = (
                    (144, 238, 144) if original_color == (0, 128, 0) 
                    else (255, 255, 0)
                )
                led_widget.set_draw_func(
                    self._create_led_draw_func(brighter_color)
                )
            else:
                led_widget.set_draw_func(
                    self._create_led_draw_func(original_color)
                )
            led_widget.queue_draw()

    def update_pixel(self, x: int, y: int, color: tuple) -> None:
        """
        Update the color of a specific pixel in the Cairo surface.

        :param x: X-coordinate of the pixel.
        :param y: Y-coordinate of the pixel.
        :param color: Tuple (r, g, b) representing the pixel color (0-255 range).
        """
        if 0 <= x < self.display_width and 0 <= y < self.display_height:
            # Get pixel data from surface
            data = self.hw_display.get_data()
            stride = self.hw_display.get_stride()
            
            # Calculate pixel offset (Cairo uses BGRA format)
            offset = y * stride + x * 4
            r, g, b = color
            
            # Set pixel (BGRA format in memory)
            data[offset] = b      # Blue
            data[offset + 1] = g  # Green
            data[offset + 2] = r  # Red
            data[offset + 3] = 255  # Alpha

    def update_display(self) -> None:
        """
        Queue a redraw of the display widget.
        """
        self.hw_display_widget.queue_draw()

    def update_from_simulation(self, simulation) -> None:
        """
        Update the display using pixel data from the simulation.

        :param simulation: Simulation instance providing pixel data.
        """
        for y in range(self.display_height):
            for x in range(self.display_width):
                red, green, blue = simulation.get_display_pixel(x, y)
                self.update_pixel(x, y, (red, green, blue))
        self.update_display()