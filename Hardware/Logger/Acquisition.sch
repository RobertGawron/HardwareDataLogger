EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_Coaxial J?
U 1 1 60F47948
P 3500 1750
AR Path="/60F47948" Ref="J?"  Part="1" 
AR Path="/60F455B3/60F47948" Ref="J1"  Part="1" 
F 0 "J1" H 3600 1725 50  0000 L CNN
F 1 "Conn_Coaxial" H 3600 1634 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Molex_73251-2200_Horizontal" H 3500 1750 50  0001 C CNN
F 3 " ~" H 3500 1750 50  0001 C CNN
	1    3500 1750
	-1   0    0    -1  
$EndComp
Text Notes 3450 1400 0    71   ~ 14
GM detector
Text Notes 3150 2700 0    71   ~ 14
semiconductor \nradioactivity detector
Text Notes 3300 3850 0    71   ~ 14
for future use
$Comp
L power:GND #PWR013
U 1 1 60F4B5D1
P 3500 2000
F 0 "#PWR013" H 3500 1750 50  0001 C CNN
F 1 "GND" H 3505 1827 50  0000 C CNN
F 2 "" H 3500 2000 50  0001 C CNN
F 3 "" H 3500 2000 50  0001 C CNN
	1    3500 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1950 3500 2000
$Comp
L Device:R R?
U 1 1 60F4F614
P 3900 1750
AR Path="/60F4F614" Ref="R?"  Part="1" 
AR Path="/60F39CF0/60F4F614" Ref="R?"  Part="1" 
AR Path="/60F455B3/60F4F614" Ref="R9"  Part="1" 
F 0 "R9" V 4107 1750 50  0000 C CNN
F 1 "1k" V 4016 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3830 1750 50  0001 C CNN
F 3 "~" H 3900 1750 50  0001 C CNN
	1    3900 1750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 1750 3750 1750
$Comp
L Connector:Conn_Coaxial J?
U 1 1 60F5159A
P 3500 3000
AR Path="/60F5159A" Ref="J?"  Part="1" 
AR Path="/60F455B3/60F5159A" Ref="J2"  Part="1" 
F 0 "J2" H 3600 2975 50  0000 L CNN
F 1 "Conn_Coaxial" H 3600 2884 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Molex_73251-2200_Horizontal" H 3500 3000 50  0001 C CNN
F 3 " ~" H 3500 3000 50  0001 C CNN
	1    3500 3000
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 60F515A0
P 3500 3250
F 0 "#PWR014" H 3500 3000 50  0001 C CNN
F 1 "GND" H 3505 3077 50  0000 C CNN
F 2 "" H 3500 3250 50  0001 C CNN
F 3 "" H 3500 3250 50  0001 C CNN
	1    3500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3200 3500 3250
$Comp
L Device:R R?
U 1 1 60F515A7
P 3900 3000
AR Path="/60F515A7" Ref="R?"  Part="1" 
AR Path="/60F39CF0/60F515A7" Ref="R?"  Part="1" 
AR Path="/60F455B3/60F515A7" Ref="R10"  Part="1" 
F 0 "R10" V 4107 3000 50  0000 C CNN
F 1 "1k" V 4016 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3830 3000 50  0001 C CNN
F 3 "~" H 3900 3000 50  0001 C CNN
	1    3900 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 3000 3750 3000
$Comp
L Connector:Conn_Coaxial J?
U 1 1 60F51C28
P 3500 4150
AR Path="/60F51C28" Ref="J?"  Part="1" 
AR Path="/60F455B3/60F51C28" Ref="J3"  Part="1" 
F 0 "J3" H 3600 4125 50  0000 L CNN
F 1 "Conn_Coaxial" H 3600 4034 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Molex_73251-2200_Horizontal" H 3500 4150 50  0001 C CNN
F 3 " ~" H 3500 4150 50  0001 C CNN
	1    3500 4150
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 60F51C2E
P 3500 4400
F 0 "#PWR015" H 3500 4150 50  0001 C CNN
F 1 "GND" H 3505 4227 50  0000 C CNN
F 2 "" H 3500 4400 50  0001 C CNN
F 3 "" H 3500 4400 50  0001 C CNN
	1    3500 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4350 3500 4400
$Comp
L Device:R R?
U 1 1 60F51C35
P 3900 4150
AR Path="/60F51C35" Ref="R?"  Part="1" 
AR Path="/60F39CF0/60F51C35" Ref="R?"  Part="1" 
AR Path="/60F455B3/60F51C35" Ref="R11"  Part="1" 
F 0 "R11" V 4107 4150 50  0000 C CNN
F 1 "1k" V 4016 4150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3830 4150 50  0001 C CNN
F 3 "~" H 3900 4150 50  0001 C CNN
	1    3900 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 4150 3750 4150
Text Notes 3300 4950 0    71   ~ 14
for future use
$Comp
L Connector:Conn_Coaxial J?
U 1 1 60F715EB
P 3500 5250
AR Path="/60F715EB" Ref="J?"  Part="1" 
AR Path="/60F455B3/60F715EB" Ref="J4"  Part="1" 
F 0 "J4" H 3600 5225 50  0000 L CNN
F 1 "Conn_Coaxial" H 3600 5134 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Molex_73251-2200_Horizontal" H 3500 5250 50  0001 C CNN
F 3 " ~" H 3500 5250 50  0001 C CNN
	1    3500 5250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 60F715F1
P 3500 5500
F 0 "#PWR016" H 3500 5250 50  0001 C CNN
F 1 "GND" H 3505 5327 50  0000 C CNN
F 2 "" H 3500 5500 50  0001 C CNN
F 3 "" H 3500 5500 50  0001 C CNN
	1    3500 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5450 3500 5500
$Comp
L Device:R R?
U 1 1 60F715F8
P 3900 5250
AR Path="/60F715F8" Ref="R?"  Part="1" 
AR Path="/60F39CF0/60F715F8" Ref="R?"  Part="1" 
AR Path="/60F455B3/60F715F8" Ref="R12"  Part="1" 
F 0 "R12" V 4107 5250 50  0000 C CNN
F 1 "1k" V 4016 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3830 5250 50  0001 C CNN
F 3 "~" H 3900 5250 50  0001 C CNN
	1    3900 5250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 5250 3750 5250
$Comp
L Connector:DB9_Female_MountingHoles J7
U 1 1 60F515C7
P 2200 6500
F 0 "J7" H 2380 6502 50  0000 L CNN
F 1 "DB9_Female_MountingHoles" H 2380 6411 50  0000 L CNN
F 2 "Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.84mm_EdgePinOffset4.94mm_Housed_MountingHolesOffset7.48mm" H 2200 6500 50  0001 C CNN
F 3 " ~" H 2200 6500 50  0001 C CNN
	1    2200 6500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
