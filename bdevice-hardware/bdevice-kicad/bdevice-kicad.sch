EESchema Schematic File Version 4
EELAYER 30 0
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
L MCU_Microchip_ATmega:ATmega328P-PU U1
U 1 1 5E0A9731
P 3650 4050
F 0 "U1" H 3006 4096 50  0000 R CNN
F 1 "ATmega328P-PU" H 3006 4005 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 3650 4050 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 3650 4050 50  0001 C CNN
	1    3650 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR0101
U 1 1 5E0ACEA6
P 3650 5850
F 0 "#PWR0101" H 3650 5600 50  0001 C CNN
F 1 "GNDREF" H 3655 5677 50  0000 C CNN
F 2 "" H 3650 5850 50  0001 C CNN
F 3 "" H 3650 5850 50  0001 C CNN
	1    3650 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 5550 3650 5600
Wire Wire Line
	4250 4350 4650 4350
Wire Wire Line
	4650 4350 4650 5600
Wire Wire Line
	4650 5600 3650 5600
Connection ~ 3650 5600
Wire Wire Line
	3650 5600 3650 5850
$Comp
L Device:CP1 C1
U 1 1 5E0B13BC
P 3350 2000
F 0 "C1" H 3465 2046 50  0000 L CNN
F 1 "CP1" H 3465 1955 50  0000 L CNN
F 2 "" H 3350 2000 50  0001 C CNN
F 3 "~" H 3350 2000 50  0001 C CNN
	1    3350 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 1850 3650 1850
$Comp
L power:+5V #PWR0102
U 1 1 5E0B52F3
P 2550 2600
F 0 "#PWR0102" H 2550 2450 50  0001 C CNN
F 1 "+5V" H 2565 2773 50  0000 C CNN
F 2 "" H 2550 2600 50  0001 C CNN
F 3 "" H 2550 2600 50  0001 C CNN
	1    2550 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2600 3350 2600
Wire Wire Line
	3350 2150 3650 2150
Wire Wire Line
	3650 2150 3650 2550
Wire Wire Line
	3350 2600 3350 2350
Wire Wire Line
	3350 2350 3150 2350
Wire Wire Line
	3150 2350 3150 1800
Wire Wire Line
	3150 1800 3650 1800
Wire Wire Line
	3650 1800 3650 1850
$EndSCHEMATC
