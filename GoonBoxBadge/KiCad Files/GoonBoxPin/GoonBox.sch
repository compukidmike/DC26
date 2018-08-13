EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
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
LIBS:GoonBox-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Battery_Cell BT1
U 1 1 5A91D2D7
P 4650 4050
F 0 "BT1" H 4750 4150 50  0000 L CNN
F 1 "Battery_Cell" H 4750 4050 50  0000 L CNN
F 2 "GoonBoxBadge:Linx-BAT-HLD-001" V 4650 4110 50  0001 C CNN
F 3 "" V 4650 4110 50  0001 C CNN
	1    4650 4050
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5A91D35C
P 5100 3050
F 0 "D1" H 5100 3150 50  0000 C CNN
F 1 "LED" H 5100 2950 50  0000 C CNN
F 2 "GoonBoxBadge:LED-5MM-SMT-FLAT" H 5100 3050 50  0001 C CNN
F 3 "" H 5100 3050 50  0001 C CNN
	1    5100 3050
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A91D407
P 5550 3050
F 0 "R1" V 5630 3050 50  0000 C CNN
F 1 "R" V 5550 3050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5480 3050 50  0001 C CNN
F 3 "" H 5550 3050 50  0001 C CNN
	1    5550 3050
	0    1    1    0   
$EndComp
$Comp
L TSOP331xx U1
U 1 1 5A91D482
P 4400 3050
F 0 "U1" H 4000 3350 50  0000 L CNN
F 1 "TSOP331xx" H 4000 2750 50  0000 L CNN
F 2 "GoonBoxBadge:TSOP332-IR-RCV" H 4350 2675 50  0001 C CNN
F 3 "" H 5050 3350 50  0001 C CNN
	1    4400 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5A91D50B
P 4650 4150
F 0 "#PWR01" H 4650 3900 50  0001 C CNN
F 1 "GND" H 4650 4000 50  0000 C CNN
F 2 "" H 4650 4150 50  0001 C CNN
F 3 "" H 4650 4150 50  0001 C CNN
	1    4650 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5A91D527
P 4800 3250
F 0 "#PWR02" H 4800 3000 50  0001 C CNN
F 1 "GND" H 4800 3100 50  0000 C CNN
F 2 "" H 4800 3250 50  0001 C CNN
F 3 "" H 4800 3250 50  0001 C CNN
	1    4800 3250
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR04
U 1 1 5A91EA59
P 4650 3750
F 0 "#PWR04" H 4650 3600 50  0001 C CNN
F 1 "+BATT" H 4650 3890 50  0000 C CNN
F 2 "" H 4650 3750 50  0001 C CNN
F 3 "" H 4650 3750 50  0001 C CNN
	1    4650 3750
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR05
U 1 1 5A91EA75
P 4900 2800
F 0 "#PWR05" H 4900 2650 50  0001 C CNN
F 1 "+BATT" H 4900 2940 50  0000 C CNN
F 2 "" H 4900 2800 50  0001 C CNN
F 3 "" H 4900 2800 50  0001 C CNN
	1    4900 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2850 5750 2850
Wire Wire Line
	4900 2850 4900 2800
Wire Wire Line
	4650 3850 4650 3750
Wire Wire Line
	4800 3050 4950 3050
Wire Wire Line
	5250 3050 5400 3050
Wire Wire Line
	5750 2850 5750 3050
Wire Wire Line
	5750 3050 5700 3050
Connection ~ 4900 2850
$EndSCHEMATC
