"""
Module for managing log tabs in a GTK GUI application.

This module defines a `LogTabsWidget` class for displaying log messages
in categorized tabs, such as Pulse Counter and various UART channels.
"""

from enum import Enum
import gi
gi.require_version('Gtk', '4.0')
from gi.repository import Gtk, Pango


class LogTabID(Enum):

    """Enumeration of log tab identifiers."""

    PULSE_COUNTER = 0
    STM32_UART_1 = 1
    STM32_UART_2 = 2
    STM32_UART_3 = 3
    ESP8266_UART_0 = 4
    ESP8266_UART_1 = 5


class LogTabsWidget(Gtk.Box):

    """
    Widget for managing log tabs and displaying categorized log messages.

    This widget allows adding and viewing logs in different tabs, including
    Pulse Counter and UART logs for STM32 and ESP8266 devices.
    """

    def __init__(self):
        """
        Initialize the LogTabsWidget.

        Sets up the tabbed interface and initializes log storage for each tab.
        """
        super().__init__(orientation=Gtk.Orientation.VERTICAL, spacing=0)

        # Create the notebook (tab widget)
        self.tabs = Gtk.Notebook()
        self.tabs.set_hexpand(True)
        self.tabs.set_vexpand(True)

        # Store references to text views for each tab
        self.log_outputs = {}

        # Add a single Pulse Counter tab
        self.create_pulse_counter_tab()

        # Add UART tabs
        self.create_uart_tabs()

        # Add tabs to the layout
        self.append(self.tabs)

    def create_pulse_counter_tab(self):
        """Create a single tab for Pulse Counter with fixed-width font log output."""
        # Create a scrolled window
        scrolled_window = Gtk.ScrolledWindow()
        scrolled_window.set_hexpand(True)
        scrolled_window.set_vexpand(True)
        
        # Create a TextView for log output
        log_view = Gtk.TextView()
        log_view.set_editable(False)
        log_view.set_cursor_visible(False)
        log_view.set_monospace(True)  # Fixed-width font
        
        # Set font description
        font_desc = Pango.FontDescription.from_string("Monospace 10")
        log_view.override_font(font_desc)
        
        scrolled_window.set_child(log_view)

        # Store reference and add to the tab
        self.log_outputs[LogTabID.PULSE_COUNTER] = log_view
        
        # Create tab label
        tab_label = Gtk.Label(label="Pulse Counter")
        self.tabs.append_page(scrolled_window, tab_label)

    def create_uart_tabs(self):
        """Create tabs for UART logs."""
        uart_tabs = {
            LogTabID.STM32_UART_1: "STM32 UART #1",
            LogTabID.STM32_UART_2: "STM32 UART #2",
            LogTabID.STM32_UART_3: "STM32 UART #3",
            LogTabID.ESP8266_UART_0: "ESP8266 UART #0",
            LogTabID.ESP8266_UART_1: "ESP8266 UART #1",
        }
        for tab_id, name in uart_tabs.items():
            # Create a scrolled window
            scrolled_window = Gtk.ScrolledWindow()
            scrolled_window.set_hexpand(True)
            scrolled_window.set_vexpand(True)
            
            # Create a TextView for log output
            log_view = Gtk.TextView()
            log_view.set_editable(False)
            log_view.set_cursor_visible(False)
            log_view.set_monospace(True)  # Fixed-width font
            
            # Set font description
            font_desc = Pango.FontDescription.from_string("Monospace 10")
            log_view.override_font(font_desc)
            
            # Set placeholder (using buffer with gray text as placeholder)
            buffer = log_view.get_buffer()
            
            scrolled_window.set_child(log_view)

            # Store reference and add to the tab
            self.log_outputs[tab_id] = log_view
            
            # Create tab label
            tab_label = Gtk.Label(label=name)
            self.tabs.append_page(scrolled_window, tab_label)

    def add_log(self, tab_id, timestamp, message):
        """
        Add a log message to the specified tab.

        :param tab_id: ID of the tab (LogTabID).
        :param timestamp: Timestamp of the log message.
        :param message: Log message content.
        """
        if tab_id in self.log_outputs:
            log_view = self.log_outputs[tab_id]
            buffer = log_view.get_buffer()
            
            # Get end iterator and insert text
            end_iter = buffer.get_end_iter()
            buffer.insert(end_iter, f"[{timestamp}] {message}\n")
            
            # Scroll to the end
            end_mark = buffer.create_mark(None, buffer.get_end_iter(), False)
            log_view.scroll_to_mark(end_mark, 0.0, True, 0.0, 1.0)
            buffer.delete_mark(end_mark)
        else:
            raise ValueError(f"Invalid tab ID: {tab_id}")