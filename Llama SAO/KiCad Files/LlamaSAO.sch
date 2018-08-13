EESchema Schematic File Version 2
LIBS:leds
LIBS:74xgxx
LIBS:74xx
LIBS:ac-dc
LIBS:actel
LIBS:adc-dac
LIBS:allegro
LIBS:Altera
LIBS:analog_devices
LIBS:analog_switches
LIBS:atmel
LIBS:audio
LIBS:battery_management
LIBS:bbd
LIBS:bosch
LIBS:brooktre
LIBS:cmos_ieee
LIBS:cmos4000
LIBS:conn
LIBS:contrib
LIBS:cypress
LIBS:dc-dc
LIBS:device
LIBS:digital-audio
LIBS:diode
LIBS:display
LIBS:dsp
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:ftdi
LIBS:gennum
LIBS:graphic_symbols
LIBS:hc11
LIBS:infineon
LIBS:intel
LIBS:interface
LIBS:intersil
LIBS:ir
LIBS:Lattice
LIBS:LEM
LIBS:linear
LIBS:logic_programmable
LIBS:maxim
LIBS:mechanical
LIBS:memory
LIBS:microchip
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic24mcu
LIBS:microchip_pic32mcu
LIBS:microcontrollers
LIBS:modules
LIBS:motor_drivers
LIBS:motorola
LIBS:motors
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:opto
LIBS:Oscillators
LIBS:philips
LIBS:power
LIBS:Power_Management
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:regul
LIBS:relays
LIBS:rfcom
LIBS:RFSolutions
LIBS:sensors
LIBS:silabs
LIBS:siliconi
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:switches
LIBS:texas
LIBS:transf
LIBS:transistors
LIBS:triac_thyristor
LIBS:ttl_ieee
LIBS:valves
LIBS:video
LIBS:wiznet
LIBS:Worldsemi
LIBS:Xicor
LIBS:xilinx
LIBS:zetex
LIBS:Zilog
LIBS:badgelife_shitty_connector
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
L LED D1
U 1 1 5B5AA892
P 4700 3100
F 0 "D1" H 4700 3200 50  0000 C CNN
F 1 "LED" H 4700 3000 50  0000 C CNN
F 2 "ScrewdriverBadge:LED-SMD-BottomEntry-OSRAM-LS-T776" H 4700 3100 50  0001 C CNN
F 3 "" H 4700 3100 50  0001 C CNN
	1    4700 3100
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 5B5AA8DA
P 4700 3400
F 0 "D2" H 4700 3500 50  0000 C CNN
F 1 "LED" H 4700 3300 50  0000 C CNN
F 2 "ScrewdriverBadge:LED-SMD-BottomEntry-OSRAM-LS-T776" H 4700 3400 50  0001 C CNN
F 3 "" H 4700 3400 50  0001 C CNN
	1    4700 3400
	1    0    0    -1  
$EndComp
$Comp
L Badgelife_shitty_connector X1
U 1 1 5B5AA902
P 5550 4700
F 0 "X1" H 5650 4500 60  0000 C CNN
F 1 "Badgelife_shitty_connector" H 5550 5100 60  0000 C CNN
F 2 "LlamaSAO:Badgelife-Shitty-2x2" H 5550 4700 60  0001 C CNN
F 3 "" H 5550 4700 60  0001 C CNN
	1    5550 4700
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5B5AA952
P 5250 2850
F 0 "R1" V 5330 2850 50  0000 C CNN
F 1 "R" V 5250 2850 50  0000 C CNN
F 2 "ScrewdriverBadge:R_0603_Mid" V 5180 2850 50  0001 C CNN
F 3 "" H 5250 2850 50  0001 C CNN
	1    5250 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5B5AA9A5
P 4300 3550
F 0 "#PWR01" H 4300 3300 50  0001 C CNN
F 1 "GND" H 4300 3400 50  0000 C CNN
F 2 "" H 4300 3550 50  0001 C CNN
F 3 "" H 4300 3550 50  0001 C CNN
	1    4300 3550
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR02
U 1 1 5B5AA9C1
P 5250 2550
F 0 "#PWR02" H 5250 2400 50  0001 C CNN
F 1 "+3V3" H 5250 2690 50  0000 C CNN
F 2 "" H 5250 2550 50  0001 C CNN
F 3 "" H 5250 2550 50  0001 C CNN
	1    5250 2550
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR03
U 1 1 5B5AA9FD
P 5100 4550
F 0 "#PWR03" H 5100 4400 50  0001 C CNN
F 1 "+3V3" H 5100 4690 50  0000 C CNN
F 2 "" H 5100 4550 50  0001 C CNN
F 3 "" H 5100 4550 50  0001 C CNN
	1    5100 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5B5AAA14
P 5100 4850
F 0 "#PWR04" H 5100 4600 50  0001 C CNN
F 1 "GND" H 5100 4700 50  0000 C CNN
F 2 "" H 5100 4850 50  0001 C CNN
F 3 "" H 5100 4850 50  0001 C CNN
	1    5100 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2550 5250 2700
Wire Wire Line
	5250 3000 5250 3400
Wire Wire Line
	5250 3100 4850 3100
Wire Wire Line
	5250 3400 4850 3400
Connection ~ 5250 3100
Wire Wire Line
	4550 3400 4300 3400
Wire Wire Line
	4300 3100 4300 3550
Wire Wire Line
	4550 3100 4300 3100
Connection ~ 4300 3400
Wire Wire Line
	5200 4600 5100 4600
Wire Wire Line
	5100 4600 5100 4550
Wire Wire Line
	5200 4800 5100 4800
Wire Wire Line
	5100 4800 5100 4850
$EndSCHEMATC
