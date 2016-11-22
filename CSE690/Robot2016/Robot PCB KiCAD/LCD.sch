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
Sheet 4 5
Title "CSE398 Robot LCD SCH"
Date "2016-02-26"
Rev "1"
Comp "Syracuse University"
Comment1 "Philip D. Geramian"
Comment2 "Duane Marcy"
Comment3 "Designed By:"
Comment4 ""
$EndDescr
$Comp
L LCD U9
U 1 1 56C785D3
P 7300 3100
F 0 "U9" H 7200 4050 60  0000 C CNN
F 1 "LCD" V 7400 3150 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16" H 6950 2600 60  0001 C CNN
F 3 "" H 6950 2600 60  0000 C CNN
	1    7300 3100
	1    0    0    -1  
$EndComp
$Comp
L MCP23017 U8
U 1 1 56C78654
P 5700 3650
F 0 "U8" H 5450 4550 60  0000 C CNN
F 1 "MCP23017" V 5700 3650 60  0000 C CNN
F 2 "SMD_Packages:SOIC-28" H 5700 3650 60  0001 C CNN
F 3 "" H 5700 3650 60  0000 C CNN
	1    5700 3650
	1    0    0    -1  
$EndComp
Text HLabel 5150 3000 0    60   Input ~ 0
SCL
Text HLabel 5150 3100 0    60   Input ~ 0
SDA
$Comp
L C C10
U 1 1 56C89BF4
P 4400 4100
F 0 "C10" H 4425 4200 50  0000 L CNN
F 1 "0.1uF" H 4425 4000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4438 3950 30  0001 C CNN
F 3 "" H 4400 4100 60  0000 C CNN
	1    4400 4100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR026
U 1 1 56C89CC2
P 5700 2250
F 0 "#PWR026" H 5700 2100 50  0001 C CNN
F 1 "+3.3V" H 5700 2390 50  0000 C CNN
F 2 "" H 5700 2250 60  0000 C CNN
F 3 "" H 5700 2250 60  0000 C CNN
	1    5700 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 56C89CE5
P 5700 4900
F 0 "#PWR027" H 5700 4650 50  0001 C CNN
F 1 "GND" H 5700 4750 50  0000 C CNN
F 2 "" H 5700 4900 60  0000 C CNN
F 3 "" H 5700 4900 60  0000 C CNN
	1    5700 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2400 4400 3950
Wire Wire Line
	4400 2400 6900 2400
Wire Wire Line
	5700 2250 5700 2600
Connection ~ 5700 2400
Wire Wire Line
	5700 4700 5700 4900
Wire Wire Line
	4400 4250 4400 4800
Wire Wire Line
	4400 4800 6700 4800
Connection ~ 5700 4800
Wire Wire Line
	5150 3700 4400 3700
Connection ~ 4400 3700
Wire Wire Line
	5150 3500 4400 3500
Connection ~ 4400 3500
Wire Wire Line
	5150 3400 4400 3400
Connection ~ 4400 3400
Wire Wire Line
	5150 3300 4400 3300
Connection ~ 4400 3300
Wire Wire Line
	6250 3600 6900 3600
Wire Wire Line
	6250 3500 6900 3500
Wire Wire Line
	6250 3400 6900 3400
Wire Wire Line
	6250 3300 6900 3300
Wire Wire Line
	6250 3200 6900 3200
Wire Wire Line
	6250 3100 6900 3100
Wire Wire Line
	6250 3000 6900 3000
Wire Wire Line
	6250 2900 6900 2900
Wire Wire Line
	6250 3700 6500 3700
Wire Wire Line
	6500 3700 6500 2800
Wire Wire Line
	6500 2800 6900 2800
Wire Wire Line
	6250 3800 6400 3800
Wire Wire Line
	6400 3800 6400 2600
Wire Wire Line
	6400 2600 6900 2600
Wire Wire Line
	5900 2400 5900 2400
Wire Wire Line
	6900 2300 6700 2300
Wire Wire Line
	6700 2300 6700 4800
Wire Wire Line
	6900 2700 6700 2700
Connection ~ 6700 2700
Wire Wire Line
	6900 3800 6700 3800
Connection ~ 6700 3800
Wire Wire Line
	6250 3900 6600 3900
Wire Wire Line
	6600 3900 6600 3700
Wire Wire Line
	6600 3700 6900 3700
$EndSCHEMATC
