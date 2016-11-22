EESchema Schematic File Version 2
LIBS:CSE398_Robot-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Robot_Library
LIBS:CSE398_Robot-cache
EELAYER 25 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 5 5
Title "CSE398 Robot Motor SCH"
Date "2016-02-26"
Rev "1"
Comp "Syracuse University"
Comment1 "Philip D. Geramian"
Comment2 "Duane Marcy"
Comment3 "Designed By:"
Comment4 ""
$EndDescr
$Comp
L DRV8835 U10
U 1 1 56C7BDDA
P 4900 3300
F 0 "U10" H 4750 3700 60  0000 C CNN
F 1 "DRV8835" V 4900 3300 60  0000 C CNN
F 2 "Robot_Footprints:DRV8835" H 4900 3300 60  0001 C CNN
F 3 "" H 4900 3300 60  0000 C CNN
	1    4900 3300
	1    0    0    -1  
$EndComp
$Comp
L Magnet_Encoder U11
U 1 1 56C7BE3D
P 7200 2800
F 0 "U11" H 7100 3200 60  0000 C CNN
F 1 "Magnet_Encoder" V 7300 2800 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 7300 2800 60  0001 C CNN
F 3 "" H 7300 2800 60  0000 C CNN
	1    7200 2800
	1    0    0    -1  
$EndComp
$Comp
L Magnet_Encoder U12
U 1 1 56C7BEB6
P 7200 4050
F 0 "U12" H 7100 4450 60  0000 C CNN
F 1 "Magnet_Encoder" V 7300 4050 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 7300 4050 60  0001 C CNN
F 3 "" H 7300 4050 60  0000 C CNN
	1    7200 4050
	1    0    0    -1  
$EndComp
Text HLabel 4400 3250 0    60   Input ~ 0
B_En
Text HLabel 4400 3350 0    60   Input ~ 0
B_Ph
Text HLabel 4400 3450 0    60   Input ~ 0
A_En
Text HLabel 4400 3550 0    60   Input ~ 0
A_Ph
Text HLabel 6800 2750 0    60   Input ~ 0
E_B0
Text HLabel 6800 2650 0    60   Input ~ 0
E_B1
Text HLabel 6800 4000 0    60   Input ~ 0
E_A0
Text HLabel 6800 3900 0    60   Input ~ 0
E_A1
$Comp
L GND #PWR028
U 1 1 56C96E0E
P 6450 4700
F 0 "#PWR028" H 6450 4450 50  0001 C CNN
F 1 "GND" H 6450 4550 50  0000 C CNN
F 2 "" H 6450 4700 60  0000 C CNN
F 3 "" H 6450 4700 60  0000 C CNN
	1    6450 4700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR029
U 1 1 56C96E28
P 6350 2300
F 0 "#PWR029" H 6350 2150 50  0001 C CNN
F 1 "+3.3V" H 6350 2440 50  0000 C CNN
F 2 "" H 6350 2300 60  0000 C CNN
F 3 "" H 6350 2300 60  0000 C CNN
	1    6350 2300
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR030
U 1 1 56C96F68
P 3900 2600
F 0 "#PWR030" H 3900 2450 50  0001 C CNN
F 1 "+3.3V" H 3900 2740 50  0000 C CNN
F 2 "" H 3900 2600 60  0000 C CNN
F 3 "" H 3900 2600 60  0000 C CNN
	1    3900 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3250 5800 3250
Wire Wire Line
	5800 3250 5800 2950
Wire Wire Line
	5800 2950 6800 2950
Wire Wire Line
	5400 3350 5900 3350
Wire Wire Line
	5900 3350 5900 3050
Wire Wire Line
	5900 3050 6800 3050
Wire Wire Line
	5400 3450 5900 3450
Wire Wire Line
	5900 3450 5900 4200
Wire Wire Line
	5900 4200 6800 4200
Wire Wire Line
	5400 3550 5800 3550
Wire Wire Line
	5800 3550 5800 4300
Wire Wire Line
	5800 4300 6800 4300
Wire Wire Line
	6450 2550 6450 4700
Wire Wire Line
	6450 2550 6800 2550
Wire Wire Line
	6350 2300 6350 4100
Wire Wire Line
	6350 4100 6800 4100
Wire Wire Line
	6800 2850 6350 2850
Connection ~ 6350 2850
Wire Wire Line
	6800 3800 6450 3800
Connection ~ 6450 3800
Wire Wire Line
	3900 3650 4400 3650
Wire Wire Line
	3900 2600 3900 3650
$Comp
L GND #PWR031
U 1 1 56C96FB8
P 4000 3850
F 0 "#PWR031" H 4000 3600 50  0001 C CNN
F 1 "GND" H 4000 3700 50  0000 C CNN
F 2 "" H 4000 3850 60  0000 C CNN
F 3 "" H 4000 3850 60  0000 C CNN
	1    4000 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3850 4000 3050
Wire Wire Line
	4000 3050 4400 3050
Wire Wire Line
	4400 3150 3900 3150
Connection ~ 3900 3150
$Comp
L GND #PWR032
U 1 1 56C97012
P 5600 3850
F 0 "#PWR032" H 5600 3600 50  0001 C CNN
F 1 "GND" H 5600 3700 50  0000 C CNN
F 2 "" H 5600 3850 60  0000 C CNN
F 3 "" H 5600 3850 60  0000 C CNN
	1    5600 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3850 5600 3050
Wire Wire Line
	5600 3050 5400 3050
$Comp
L +BATT #PWR033
U 1 1 56C9706E
P 5500 2600
F 0 "#PWR033" H 5500 2450 50  0001 C CNN
F 1 "+BATT" H 5500 2740 50  0000 C CNN
F 2 "" H 5500 2600 60  0000 C CNN
F 3 "" H 5500 2600 60  0000 C CNN
	1    5500 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2600 5500 3150
Wire Wire Line
	5500 3150 5400 3150
$EndSCHEMATC
