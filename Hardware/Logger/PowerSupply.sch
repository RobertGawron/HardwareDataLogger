EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 850  2050 0    71   ~ 14
NOTE: \n1/ ESP acceptable supply voltage: 3V-3V6\n2/ Nucleo acceptable supply voltage: 5V \n3/ ST7735S acceptable supply voltage: 3V3\n\nThe device will be powered from power USB (no USB comunication, just used as power supply).\nNucleo will be alimented directly zith USB 5V.\nESP and ST7735S  will be alimented with 3V3\n\nConnecting nucleo to external power supply:\nhttps://pitinker.wordpress.com/2016/05/22/battery-powered-mbed-st-nucleo-f411re/
Text GLabel 9300 3750 2    50   Input ~ 0
3V3
Text GLabel 9300 3400 2    50   Input ~ 0
5V
$Comp
L Connector:USB_B_Micro J5
U 1 1 6144E7C2
P 3800 3950
F 0 "J5" H 3857 4417 50  0000 C CNN
F 1 "USB_B_Micro" H 3857 4326 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex-105017-0001" H 3950 3900 50  0001 C CNN
F 3 "~" H 3950 3900 50  0001 C CNN
	1    3800 3950
	1    0    0    -1  
$EndComp
$Comp
L Logger:LD1117ASTR U3
U 1 1 6144F20E
P 6200 3700
F 0 "U3" H 6200 3875 50  0000 C CNN
F 1 "LD1117ASTR" H 6200 3784 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 6200 3850 50  0001 C CNN
F 3 "https://www.tme.eu/Document/bad00e7fc591b73ff810af309b2bb7a4/LD1117A.pdf" H 6200 3850 50  0001 C CNN
	1    6200 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6145BADB
P 5000 4250
AR Path="/6145BADB" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/6145BADB" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/6145BADB" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/6145BADB" Ref="C?"  Part="1" 
AR Path="/5E27E78E/6145BADB" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/6145BADB" Ref="C?"  Part="1" 
AR Path="/60F74854/6145BADB" Ref="C?"  Part="1" 
AR Path="/6144CC5A/6145BADB" Ref="C2"  Part="1" 
F 0 "C2" H 5115 4296 50  0000 L CNN
F 1 "330n" H 5115 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5038 4100 50  0001 C CNN
F 3 "~" H 5000 4250 50  0001 C CNN
	1    5000 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6145BAE3
P 5000 4700
AR Path="/60F74854/6145BAE3" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/6145BAE3" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 5000 4450 50  0001 C CNN
F 1 "GND" H 5005 4527 50  0000 C CNN
F 2 "" H 5000 4700 50  0001 C CNN
F 3 "" H 5000 4700 50  0001 C CNN
	1    5000 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6145BAEA
P 7400 4050
AR Path="/5DD5C7F6/6145BAEA" Ref="R?"  Part="1" 
AR Path="/5DD5CD1D/6145BAEA" Ref="R?"  Part="1" 
AR Path="/5E27E78E/6145BAEA" Ref="R?"  Part="1" 
AR Path="/5F01FBEA/6145BAEA" Ref="R?"  Part="1" 
AR Path="/60F74854/6145BAEA" Ref="R?"  Part="1" 
AR Path="/6144CC5A/6145BAEA" Ref="R7"  Part="1" 
F 0 "R7" H 7470 4096 50  0000 L CNN
F 1 "TBD" H 7470 4005 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7330 4050 50  0001 C CNN
F 3 "~" H 7400 4050 50  0001 C CNN
	1    7400 4050
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6145BAF0
P 5400 4700
AR Path="/60F74854/6145BAF0" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/6145BAF0" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 5400 4450 50  0001 C CNN
F 1 "GND" H 5405 4527 50  0000 C CNN
F 2 "" H 5400 4700 50  0001 C CNN
F 3 "" H 5400 4700 50  0001 C CNN
	1    5400 4700
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6145CC78
P 5400 4250
AR Path="/6145CC78" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/6145CC78" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/6145CC78" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/6145CC78" Ref="C?"  Part="1" 
AR Path="/5E27E78E/6145CC78" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/6145CC78" Ref="C?"  Part="1" 
AR Path="/60F74854/6145CC78" Ref="C?"  Part="1" 
AR Path="/6144CC5A/6145CC78" Ref="C3"  Part="1" 
F 0 "C3" H 5515 4296 50  0000 L CNN
F 1 "330n" H 5515 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5438 4100 50  0001 C CNN
F 3 "~" H 5400 4250 50  0001 C CNN
	1    5400 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6145D035
P 8100 4250
AR Path="/6145D035" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/6145D035" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/6145D035" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/6145D035" Ref="C?"  Part="1" 
AR Path="/5E27E78E/6145D035" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/6145D035" Ref="C?"  Part="1" 
AR Path="/60F74854/6145D035" Ref="C?"  Part="1" 
AR Path="/6144CC5A/6145D035" Ref="C4"  Part="1" 
F 0 "C4" H 8215 4296 50  0000 L CNN
F 1 "330n" H 8215 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8138 4100 50  0001 C CNN
F 3 "~" H 8100 4250 50  0001 C CNN
	1    8100 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6145D40D
P 8550 4250
AR Path="/6145D40D" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/6145D40D" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/6145D40D" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/6145D40D" Ref="C?"  Part="1" 
AR Path="/5E27E78E/6145D40D" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/6145D40D" Ref="C?"  Part="1" 
AR Path="/60F74854/6145D40D" Ref="C?"  Part="1" 
AR Path="/6144CC5A/6145D40D" Ref="C5"  Part="1" 
F 0 "C5" H 8665 4296 50  0000 L CNN
F 1 "330n" H 8665 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8588 4100 50  0001 C CNN
F 3 "~" H 8550 4250 50  0001 C CNN
	1    8550 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6146244F
P 6200 4500
AR Path="/5DD5C7F6/6146244F" Ref="R?"  Part="1" 
AR Path="/5DD5CD1D/6146244F" Ref="R?"  Part="1" 
AR Path="/5E27E78E/6146244F" Ref="R?"  Part="1" 
AR Path="/5F01FBEA/6146244F" Ref="R?"  Part="1" 
AR Path="/60F74854/6146244F" Ref="R?"  Part="1" 
AR Path="/6144CC5A/6146244F" Ref="R8"  Part="1" 
F 0 "R8" H 6270 4546 50  0000 L CNN
F 1 "TBD" H 6270 4455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6130 4500 50  0001 C CNN
F 3 "~" H 6200 4500 50  0001 C CNN
	1    6200 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5900 3750 5400 3750
Wire Wire Line
	5000 3750 5000 4100
Wire Wire Line
	5400 4100 5400 3750
Connection ~ 5400 3750
Wire Wire Line
	5400 3750 5000 3750
Wire Wire Line
	6500 3750 7400 3750
Wire Wire Line
	7400 3750 7400 3900
Wire Wire Line
	7400 3750 8100 3750
Wire Wire Line
	8100 3750 8100 4100
Connection ~ 7400 3750
Wire Wire Line
	8100 3750 8550 3750
Wire Wire Line
	8550 3750 8550 4100
Connection ~ 8100 3750
Wire Wire Line
	7400 4200 7400 4300
Wire Wire Line
	7400 4300 6950 4300
Wire Wire Line
	6200 4300 6200 4100
Wire Wire Line
	6200 4300 6200 4350
Wire Wire Line
	6200 4650 6200 4700
Wire Wire Line
	8100 4400 8100 4700
Wire Wire Line
	8550 4400 8550 4700
Wire Wire Line
	5400 4400 5400 4700
Wire Wire Line
	5000 4400 5000 4700
$Comp
L Device:C C?
U 1 1 61469D70
P 4600 4250
AR Path="/61469D70" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/61469D70" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/61469D70" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/61469D70" Ref="C?"  Part="1" 
AR Path="/5E27E78E/61469D70" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/61469D70" Ref="C?"  Part="1" 
AR Path="/60F74854/61469D70" Ref="C?"  Part="1" 
AR Path="/6144CC5A/61469D70" Ref="C1"  Part="1" 
F 0 "C1" H 4715 4296 50  0000 L CNN
F 1 "330n" H 4715 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4638 4100 50  0001 C CNN
F 3 "~" H 4600 4250 50  0001 C CNN
	1    4600 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3750 4600 4100
Wire Wire Line
	4600 4400 4600 4700
$Comp
L Device:C C?
U 1 1 6146AAB6
P 9000 4250
AR Path="/6146AAB6" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/6146AAB6" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/6146AAB6" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/6146AAB6" Ref="C?"  Part="1" 
AR Path="/5E27E78E/6146AAB6" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/6146AAB6" Ref="C?"  Part="1" 
AR Path="/60F74854/6146AAB6" Ref="C?"  Part="1" 
AR Path="/6144CC5A/6146AAB6" Ref="C8"  Part="1" 
F 0 "C8" H 9115 4296 50  0000 L CNN
F 1 "330n" H 9115 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 9038 4100 50  0001 C CNN
F 3 "~" H 9000 4250 50  0001 C CNN
	1    9000 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 4400 9000 4700
$Comp
L power:GND #PWR?
U 1 1 6147097E
P 4600 4700
AR Path="/60F74854/6147097E" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/6147097E" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 4600 4450 50  0001 C CNN
F 1 "GND" H 4605 4527 50  0000 C CNN
F 2 "" H 4600 4700 50  0001 C CNN
F 3 "" H 4600 4700 50  0001 C CNN
	1    4600 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61470F85
P 6200 4700
AR Path="/60F74854/61470F85" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/61470F85" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 6200 4450 50  0001 C CNN
F 1 "GND" H 6205 4527 50  0000 C CNN
F 2 "" H 6200 4700 50  0001 C CNN
F 3 "" H 6200 4700 50  0001 C CNN
	1    6200 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61471518
P 8100 4700
AR Path="/60F74854/61471518" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/61471518" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 8100 4450 50  0001 C CNN
F 1 "GND" H 8105 4527 50  0000 C CNN
F 2 "" H 8100 4700 50  0001 C CNN
F 3 "" H 8100 4700 50  0001 C CNN
	1    8100 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61471ABE
P 8550 4700
AR Path="/60F74854/61471ABE" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/61471ABE" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 8550 4450 50  0001 C CNN
F 1 "GND" H 8555 4527 50  0000 C CNN
F 2 "" H 8550 4700 50  0001 C CNN
F 3 "" H 8550 4700 50  0001 C CNN
	1    8550 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61472043
P 9000 4700
AR Path="/60F74854/61472043" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/61472043" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 9000 4450 50  0001 C CNN
F 1 "GND" H 9005 4527 50  0000 C CNN
F 2 "" H 9000 4700 50  0001 C CNN
F 3 "" H 9000 4700 50  0001 C CNN
	1    9000 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3750 4600 3750
Connection ~ 5000 3750
Wire Wire Line
	8550 3750 9000 3750
Wire Wire Line
	9000 3750 9000 4100
Connection ~ 8550 3750
Connection ~ 9000 3750
Wire Wire Line
	9000 3750 9300 3750
Wire Wire Line
	9300 3400 4400 3400
Wire Wire Line
	4400 3400 4400 3750
Wire Wire Line
	4400 3750 4600 3750
Connection ~ 4600 3750
Wire Wire Line
	4400 3750 4100 3750
Connection ~ 4400 3750
$Comp
L power:GND #PWR?
U 1 1 6149A551
P 3700 4700
AR Path="/60F74854/6149A551" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/6149A551" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 3700 4450 50  0001 C CNN
F 1 "GND" H 3705 4527 50  0000 C CNN
F 2 "" H 3700 4700 50  0001 C CNN
F 3 "" H 3700 4700 50  0001 C CNN
	1    3700 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 4350 3700 4500
Wire Wire Line
	3700 4500 3800 4500
Wire Wire Line
	3800 4500 3800 4350
Connection ~ 3700 4500
Wire Wire Line
	3700 4500 3700 4700
Wire Wire Line
	4100 3950 4200 3950
Wire Wire Line
	4100 4050 4200 4050
Wire Wire Line
	4100 4150 4200 4150
NoConn ~ 4200 3950
NoConn ~ 4200 4050
NoConn ~ 4200 4150
NoConn ~ 550  5000
Connection ~ 6200 4300
$Comp
L Device:C C?
U 1 1 614B9E5B
P 6500 4500
AR Path="/614B9E5B" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/614B9E5B" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/614B9E5B" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/614B9E5B" Ref="C?"  Part="1" 
AR Path="/5E27E78E/614B9E5B" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/614B9E5B" Ref="C?"  Part="1" 
AR Path="/60F74854/614B9E5B" Ref="C?"  Part="1" 
AR Path="/6144CC5A/614B9E5B" Ref="C9"  Part="1" 
F 0 "C9" H 6615 4546 50  0000 L CNN
F 1 "330n" H 6615 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6538 4350 50  0001 C CNN
F 3 "~" H 6500 4500 50  0001 C CNN
	1    6500 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 614B9E61
P 6950 4500
AR Path="/614B9E61" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/614B9E61" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/614B9E61" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/614B9E61" Ref="C?"  Part="1" 
AR Path="/5E27E78E/614B9E61" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/614B9E61" Ref="C?"  Part="1" 
AR Path="/60F74854/614B9E61" Ref="C?"  Part="1" 
AR Path="/6144CC5A/614B9E61" Ref="C10"  Part="1" 
F 0 "C10" H 7065 4546 50  0000 L CNN
F 1 "330n" H 7065 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6988 4350 50  0001 C CNN
F 3 "~" H 6950 4500 50  0001 C CNN
	1    6950 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4650 6500 4700
Wire Wire Line
	6950 4650 6950 4700
$Comp
L Device:C C?
U 1 1 614B9E6B
P 7400 4500
AR Path="/614B9E6B" Ref="C?"  Part="1" 
AR Path="/5DAEEEF4/614B9E6B" Ref="C?"  Part="1" 
AR Path="/5DD5C7F6/614B9E6B" Ref="C?"  Part="1" 
AR Path="/5DD5CD1D/614B9E6B" Ref="C?"  Part="1" 
AR Path="/5E27E78E/614B9E6B" Ref="C?"  Part="1" 
AR Path="/5F01FBEA/614B9E6B" Ref="C?"  Part="1" 
AR Path="/60F74854/614B9E6B" Ref="C?"  Part="1" 
AR Path="/6144CC5A/614B9E6B" Ref="C11"  Part="1" 
F 0 "C11" H 7515 4546 50  0000 L CNN
F 1 "330n" H 7515 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7438 4350 50  0001 C CNN
F 3 "~" H 7400 4500 50  0001 C CNN
	1    7400 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 4650 7400 4700
$Comp
L power:GND #PWR?
U 1 1 614B9E72
P 6500 4700
AR Path="/60F74854/614B9E72" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/614B9E72" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 6500 4450 50  0001 C CNN
F 1 "GND" H 6505 4527 50  0000 C CNN
F 2 "" H 6500 4700 50  0001 C CNN
F 3 "" H 6500 4700 50  0001 C CNN
	1    6500 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 614B9E78
P 6950 4700
AR Path="/60F74854/614B9E78" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/614B9E78" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 6950 4450 50  0001 C CNN
F 1 "GND" H 6955 4527 50  0000 C CNN
F 2 "" H 6950 4700 50  0001 C CNN
F 3 "" H 6950 4700 50  0001 C CNN
	1    6950 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 614B9E7E
P 7400 4700
AR Path="/60F74854/614B9E7E" Ref="#PWR?"  Part="1" 
AR Path="/6144CC5A/614B9E7E" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 7400 4450 50  0001 C CNN
F 1 "GND" H 7405 4527 50  0000 C CNN
F 2 "" H 7400 4700 50  0001 C CNN
F 3 "" H 7400 4700 50  0001 C CNN
	1    7400 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4350 6500 4300
Connection ~ 6500 4300
Wire Wire Line
	6500 4300 6200 4300
Wire Wire Line
	6950 4350 6950 4300
Connection ~ 6950 4300
Wire Wire Line
	6950 4300 6500 4300
Wire Wire Line
	7400 4350 7400 4300
Connection ~ 7400 4300
$EndSCHEMATC
