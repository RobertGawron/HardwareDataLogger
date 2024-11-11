import ctypes
import os.path

class DeviceUnderTest:
    # PixelValue corresponds to the struct used in the lib.
    class PixelValue(ctypes.Structure):
        _fields_ = [("red", ctypes.c_uint8),
                    ("green", ctypes.c_uint8),
                    ("blue", ctypes.c_uint8)]
        
    def __init__(self):
        dll_name = "libFirmwarePCSimulator.so"
        dllabspath = \
            os.path.dirname(os.path.abspath(os.path.abspath(__file__))) \
            + "/../.." \
            + os.path.sep + "build" + os.path.sep + "Simulation/FirmwarePCSimulator/" \
            + os.path.sep + dll_name

        self.dut = ctypes.CDLL(dllabspath)
 
    def init(self):
       # this is the init for library, it's an embedded project 
       # so it doesn't start automatically.
       self.dut.LibWrapper_Init()

    def tick(self):
        self.dut.LibWrapper_Tick()

    """
    def getLoggedData(self):
        self.dut.Lib_GMLoggerSIM_GetLoggedData.argtypes = \
            [ctypes.POINTER(ctypes.POINTER(ctypes.c_uint8)),
                ctypes.POINTER(ctypes.c_uint8)]

        data = ctypes.POINTER(ctypes.c_uint8)()
        size = ctypes.c_uint8()

        self.dut.Lib_GMLoggerSIM_GetLoggedData(
            ctypes.byref(data), ctypes.byref(size))

        logged_data = ""
        for i in range(size.value):
            logged_data += chr(data[i])

        # it is expected that log  end with new line,
        # this should be stripped application
        return logged_data[:-3]

    def pressKey(self):
        self.dut.Lib_GMLoggerSIM_KeyPress()
    """

    def getDisplayWidth(self) -> int:
        self.dut.LibWrapper_GetDisplayWidth.restype = ctypes.c_uint8
        return self.dut.LibWrapper_GetDisplayWidth()

    def getDisplayHeight(self) -> int:
        self.dut.LibWrapper_GetDisplayHeight.restype = ctypes.c_uint8
        return self.dut.LibWrapper_GetDisplayHeight()
    
    def getDisplayPixelValue(self, x: int, y: int) -> PixelValue:
        """
        Calls the C function Simulation_GetDisplayHeight and returns the PixelValue.
        
        :param x: X-coordinate (uint8_t)
        :param y: Y-coordinate (uint8_t)
        :return: PixelValue struct with red, green, and blue attributes
        """
        self.dut.LibWrapper_GetPixelValue.restype = self.PixelValue
        self.dut.LibWrapper_GetPixelValue.argtypes = [ctypes.c_uint8, ctypes.c_uint8]

        return self.dut.LibWrapper_GetPixelValue(ctypes.c_uint8(x), ctypes.c_uint8(y))
