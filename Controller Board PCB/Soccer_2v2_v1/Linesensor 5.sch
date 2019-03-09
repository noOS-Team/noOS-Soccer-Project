EESchema Schematic File Version 2
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
LIBS:My
LIBS:Soccer_2v2_v1-cache
EELAYER 25 0
EELAYER END
$Descr User 7874 5119
encoding utf-8
Sheet 11 21
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
L Q_Photo_NPN Q17
U 1 1 59FE47DE
P 3400 1000
F 0 "Q17" H 3600 1050 50  0000 L CNN
F 1 "KDT00030TR" H 3600 950 50  0000 L CNN
F 2 "MyFootprints:ChipLED" H 3600 1100 50  0001 C CNN
F 3 "" H 3400 1000 50  0001 C CNN
	1    3400 1000
	1    0    0    -1  
$EndComp
$Comp
L Q_Photo_NPN Q18
U 1 1 59FE47DF
P 4200 1000
F 0 "Q18" H 4400 1050 50  0000 L CNN
F 1 "KDT00030TR" H 4400 950 50  0000 L CNN
F 2 "MyFootprints:ChipLED" H 4400 1100 50  0001 C CNN
F 3 "" H 4200 1000 50  0001 C CNN
	1    4200 1000
	1    0    0    -1  
$EndComp
$Comp
L Q_Photo_NPN Q19
U 1 1 59FE47E0
P 5000 1000
F 0 "Q19" H 5200 1050 50  0000 L CNN
F 1 "KDT00030TR" H 5200 950 50  0000 L CNN
F 2 "MyFootprints:ChipLED" H 5200 1100 50  0001 C CNN
F 3 "" H 5000 1000 50  0001 C CNN
	1    5000 1000
	1    0    0    -1  
$EndComp
$Comp
L Q_Photo_NPN Q20
U 1 1 59FE47E1
P 5800 1000
F 0 "Q20" H 6000 1050 50  0000 L CNN
F 1 "KDT00030TR" H 6000 950 50  0000 L CNN
F 2 "MyFootprints:ChipLED" H 6000 1100 50  0001 C CNN
F 3 "" H 5800 1000 50  0001 C CNN
	1    5800 1000
	1    0    0    -1  
$EndComp
$Comp
L LED D30
U 1 1 59FE47E2
P 2000 1650
F 0 "D30" H 2000 1750 50  0000 C CNN
F 1 "VLMW41R1T1" H 2000 1500 50  0000 C CNN
F 2 "LEDs:LED_PLCC-2" H 2000 1650 50  0001 C CNN
F 3 "" H 2000 1650 50  0001 C CNN
	1    2000 1650
	0    -1   -1   0   
$EndComp
$Comp
L LED D28
U 1 1 59FE47E3
P 1200 1650
F 0 "D28" H 1200 1750 50  0000 C CNN
F 1 "VLMW41R1T1" H 1200 1500 50  0000 C CNN
F 2 "LEDs:LED_PLCC-2" H 1200 1650 50  0001 C CNN
F 3 "" H 1200 1650 50  0001 C CNN
	1    1200 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 700  3500 800 
Wire Wire Line
	5900 750  5900 800 
Wire Wire Line
	5100 750  5100 800 
Connection ~ 5100 750 
Wire Wire Line
	4300 800  4300 750 
Connection ~ 4300 750 
Wire Wire Line
	3500 750  5900 750 
Connection ~ 3500 750 
$Comp
L R R83
U 1 1 59FE47E4
P 3500 1450
F 0 "R83" V 3580 1450 50  0000 C CNN
F 1 "6.2K" V 3500 1450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3430 1450 50  0001 C CNN
F 3 "" H 3500 1450 50  0001 C CNN
	1    3500 1450
	1    0    0    -1  
$EndComp
$Comp
L R R84
U 1 1 59FE47E5
P 4300 1450
F 0 "R84" V 4380 1450 50  0000 C CNN
F 1 "6.2K" V 4300 1450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4230 1450 50  0001 C CNN
F 3 "" H 4300 1450 50  0001 C CNN
	1    4300 1450
	1    0    0    -1  
$EndComp
$Comp
L R R85
U 1 1 59FE47E6
P 5100 1450
F 0 "R85" V 5180 1450 50  0000 C CNN
F 1 "6.2K" V 5100 1450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5030 1450 50  0001 C CNN
F 3 "" H 5100 1450 50  0001 C CNN
	1    5100 1450
	1    0    0    -1  
$EndComp
$Comp
L R R86
U 1 1 59FE47E7
P 5900 1450
F 0 "R86" V 5980 1450 50  0000 C CNN
F 1 "6.2K" V 5900 1450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5830 1450 50  0001 C CNN
F 3 "" H 5900 1450 50  0001 C CNN
	1    5900 1450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0120
U 1 1 59FE47E8
P 3500 1700
F 0 "#PWR0120" H 3500 1450 50  0001 C CNN
F 1 "GND" H 3500 1550 50  0000 C CNN
F 2 "" H 3500 1700 50  0001 C CNN
F 3 "" H 3500 1700 50  0001 C CNN
	1    3500 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1600 3500 1700
Wire Wire Line
	4300 1600 4300 1650
Wire Wire Line
	5100 1650 5100 1600
Wire Wire Line
	5900 1650 5900 1600
Wire Wire Line
	3500 1200 3500 1300
Wire Wire Line
	4300 1200 4300 1300
Wire Wire Line
	5100 1200 5100 1300
Wire Wire Line
	5900 1200 5900 1300
Text HLabel 5050 2000 2    60   Input ~ 0
VREF_black
Text HLabel 5050 2200 2    60   Input ~ 0
VREF_white
Text HLabel 5050 2100 2    60   Input ~ 0
line5_white
Wire Wire Line
	3500 1250 3650 1250
Connection ~ 3500 1250
Wire Wire Line
	4450 1250 4300 1250
Connection ~ 4300 1250
Wire Wire Line
	5250 1250 5100 1250
Connection ~ 5100 1250
Wire Wire Line
	6050 1250 5900 1250
Connection ~ 5900 1250
$Comp
L TLV1704 U32
U 1 1 59FE47E9
P 4100 2700
F 0 "U32" H 4100 3100 60  0000 C CNN
F 1 "TLV1704" H 4100 2300 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-14_4.4x5mm_Pitch0.65mm" H 4100 2700 60  0001 C CNN
F 3 "" H 4100 2700 60  0001 C CNN
	1    4100 2700
	1    0    0    -1  
$EndComp
Text Label 3650 1250 0    60   ~ 0
Photo1
Text Label 4450 1250 0    60   ~ 0
Photo2
Text Label 5250 1250 0    60   ~ 0
Photo3
Text Label 6050 1250 0    60   ~ 0
Photo4
$Comp
L TLV1704 U33
U 1 1 59FE47EA
P 6150 2700
F 0 "U33" H 6150 3100 60  0000 C CNN
F 1 "TLV1704" H 6150 2300 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-14_4.4x5mm_Pitch0.65mm" H 6150 2700 60  0001 C CNN
F 3 "" H 6150 2700 60  0001 C CNN
	1    6150 2700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR0121
U 1 1 59FE47EB
P 3500 700
F 0 "#PWR0121" H 3500 550 50  0001 C CNN
F 1 "+5V" H 3500 840 50  0000 C CNN
F 2 "" H 3500 700 50  0001 C CNN
F 3 "" H 3500 700 50  0001 C CNN
	1    3500 700 
	1    0    0    -1  
$EndComp
Text HLabel 5050 1900 2    60   Input ~ 0
line5_black
$Comp
L LED D31
U 1 1 59FE47ED
P 2400 1650
F 0 "D31" H 2400 1750 50  0000 C CNN
F 1 "VLMW41R1T1" H 2400 1500 50  0000 C CNN
F 2 "LEDs:LED_PLCC-2" H 2400 1650 50  0001 C CNN
F 3 "" H 2400 1650 50  0001 C CNN
	1    2400 1650
	0    -1   -1   0   
$EndComp
$Comp
L LED D29
U 1 1 59FE47EE
P 1600 1650
F 0 "D29" H 1600 1750 50  0000 C CNN
F 1 "VLMW41R1T1" H 1600 1500 50  0000 C CNN
F 2 "LEDs:LED_PLCC-2" H 1600 1650 50  0001 C CNN
F 3 "" H 1600 1650 50  0001 C CNN
	1    1600 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 1650 5900 1650
Connection ~ 3500 1650
Connection ~ 5100 1650
Connection ~ 4300 1650
$Comp
L R R82
U 1 1 59FE47EF
P 2000 1250
F 0 "R82" V 2080 1250 50  0000 C CNN
F 1 "160" V 2000 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1930 1250 50  0001 C CNN
F 3 "" H 2000 1250 50  0001 C CNN
	1    2000 1250
	1    0    0    -1  
$EndComp
$Comp
L R R81
U 1 1 59FE47F0
P 1200 1250
F 0 "R81" V 1280 1250 50  0000 C CNN
F 1 "160" V 1200 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1130 1250 50  0001 C CNN
F 3 "" H 1200 1250 50  0001 C CNN
	1    1200 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 1400 2000 1500
Wire Wire Line
	1200 1400 1200 1500
$Comp
L GND #PWR0122
U 1 1 59FE47F1
P 2400 2000
F 0 "#PWR0122" H 2400 1750 50  0001 C CNN
F 1 "GND" H 2400 1850 50  0000 C CNN
F 2 "" H 2400 2000 50  0001 C CNN
F 3 "" H 2400 2000 50  0001 C CNN
	1    2400 2000
	1    0    0    -1  
$EndComp
Text Label 3750 2900 2    60   ~ 0
Photo1
Text Label 3750 2700 2    60   ~ 0
Photo2
Text Label 4450 2900 0    60   ~ 0
Photo1
Text Label 6500 2800 0    60   ~ 0
Photo3
Text Label 4450 2700 0    60   ~ 0
Photo2
Text Label 5800 2800 2    60   ~ 0
Photo3
Text Label 5800 3000 2    60   ~ 0
Photo4
Text Label 6500 3000 0    60   ~ 0
Photo4
Wire Wire Line
	3750 2800 3700 2800
Wire Wire Line
	3700 2800 3700 3150
Wire Wire Line
	3700 3000 3750 3000
Wire Wire Line
	4450 2800 5450 2800
Wire Wire Line
	4500 2800 4500 3000
Wire Wire Line
	4500 3000 4450 3000
Wire Wire Line
	4450 2500 4500 2500
Wire Wire Line
	4500 2500 4500 2400
Wire Wire Line
	4450 2400 5800 2400
Wire Wire Line
	3700 2500 3750 2500
Wire Wire Line
	3700 2250 3700 2500
Wire Wire Line
	3700 2400 3750 2400
Wire Wire Line
	5450 2900 5800 2900
Wire Wire Line
	5750 2900 5750 2700
Wire Wire Line
	5750 2700 5800 2700
Wire Wire Line
	6500 2900 6550 2900
Wire Wire Line
	6550 3150 6550 2700
Wire Wire Line
	6550 2700 6500 2700
Wire Wire Line
	5800 2500 5750 2500
Wire Wire Line
	5750 2500 5750 2400
Wire Wire Line
	6550 2500 6500 2500
Wire Wire Line
	6550 2250 6550 2500
Wire Wire Line
	6550 2400 6500 2400
Wire Wire Line
	5450 2800 5450 2900
Connection ~ 4500 2800
Connection ~ 5750 2900
Wire Wire Line
	3700 3150 6550 3150
Connection ~ 6550 2900
Connection ~ 3700 3000
Connection ~ 4500 2400
Connection ~ 5750 2400
Wire Wire Line
	3700 2250 6550 2250
Connection ~ 6550 2400
Connection ~ 3700 2400
Wire Wire Line
	4450 2600 4700 2600
Wire Wire Line
	4700 2600 4700 3400
Wire Wire Line
	6500 2600 6750 2600
Wire Wire Line
	5800 2600 5700 2600
Wire Wire Line
	3750 2600 3650 2600
$Comp
L GND #PWR0123
U 1 1 59FE47F2
P 4300 3400
F 0 "#PWR0123" H 4300 3150 50  0001 C CNN
F 1 "GND" H 4300 3250 50  0000 C CNN
F 2 "" H 4300 3400 50  0001 C CNN
F 3 "" H 4300 3400 50  0001 C CNN
	1    4300 3400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR0124
U 1 1 59FE47F4
P 3900 3400
F 0 "#PWR0124" H 3900 3250 50  0001 C CNN
F 1 "+5V" H 3900 3540 50  0000 C CNN
F 2 "" H 3900 3400 50  0001 C CNN
F 3 "" H 3900 3400 50  0001 C CNN
	1    3900 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2200 5000 2200
Wire Wire Line
	5000 2200 5000 2800
Connection ~ 5000 2800
Wire Wire Line
	4950 2100 4950 2400
Connection ~ 4950 2400
Wire Wire Line
	5050 2000 4900 2000
Wire Wire Line
	4900 2000 4900 3150
Connection ~ 4900 3150
Wire Wire Line
	4850 1900 4850 2250
Connection ~ 4850 2250
Wire Wire Line
	4850 1900 5050 1900
Wire Wire Line
	5050 2100 4950 2100
Wire Wire Line
	1200 1800 1200 1950
Wire Wire Line
	1200 1950 2400 1950
Wire Wire Line
	2400 1800 2400 2000
Connection ~ 2400 1950
Wire Wire Line
	2000 1800 2000 1950
Connection ~ 2000 1950
Wire Wire Line
	1600 1800 1600 1950
Connection ~ 1600 1950
$Comp
L R R137
U 1 1 5A079608
P 1600 1250
F 0 "R137" V 1680 1250 50  0000 C CNN
F 1 "160" V 1600 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1530 1250 50  0001 C CNN
F 3 "" H 1600 1250 50  0001 C CNN
	1    1600 1250
	1    0    0    -1  
$EndComp
$Comp
L R R138
U 1 1 5A07965D
P 2400 1250
F 0 "R138" V 2480 1250 50  0000 C CNN
F 1 "160" V 2400 1250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2330 1250 50  0001 C CNN
F 3 "" H 2400 1250 50  0001 C CNN
	1    2400 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 1000 1200 1100
Wire Wire Line
	1200 1050 2400 1050
Wire Wire Line
	2400 1050 2400 1100
Connection ~ 1200 1050
Wire Wire Line
	1600 1050 1600 1100
Connection ~ 1600 1050
Wire Wire Line
	2000 1050 2000 1100
Connection ~ 2000 1050
Wire Wire Line
	1600 1400 1600 1500
Wire Wire Line
	2400 1400 2400 1500
$Comp
L +5V #PWR0125
U 1 1 5A19C474
P 1200 1000
F 0 "#PWR0125" H 1200 850 50  0001 C CNN
F 1 "+5V" H 1200 1140 50  0000 C CNN
F 2 "" H 1200 1000 50  0001 C CNN
F 3 "" H 1200 1000 50  0001 C CNN
	1    1200 1000
	1    0    0    -1  
$EndComp
$Comp
L C C104
U 1 1 5A2217FB
P 4100 3400
F 0 "C104" H 4125 3500 50  0000 L CNN
F 1 "100n" H 4125 3300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4138 3250 50  0001 C CNN
F 3 "" H 4100 3400 50  0001 C CNN
	1    4100 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 3400 3950 3400
Wire Wire Line
	3650 2600 3650 3400
Connection ~ 3900 3400
Wire Wire Line
	4700 3400 4250 3400
Connection ~ 4300 3400
Wire Wire Line
	6750 2600 6750 3400
$Comp
L GND #PWR0126
U 1 1 5A225E94
P 6350 3400
F 0 "#PWR0126" H 6350 3150 50  0001 C CNN
F 1 "GND" H 6350 3250 50  0000 C CNN
F 2 "" H 6350 3400 50  0001 C CNN
F 3 "" H 6350 3400 50  0001 C CNN
	1    6350 3400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR0127
U 1 1 5A225E9A
P 5950 3400
F 0 "#PWR0127" H 5950 3250 50  0001 C CNN
F 1 "+5V" H 5950 3540 50  0000 C CNN
F 2 "" H 5950 3400 50  0001 C CNN
F 3 "" H 5950 3400 50  0001 C CNN
	1    5950 3400
	1    0    0    -1  
$EndComp
$Comp
L C C105
U 1 1 5A225EA0
P 6150 3400
F 0 "C105" H 6175 3500 50  0000 L CNN
F 1 "100n" H 6175 3300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6188 3250 50  0001 C CNN
F 3 "" H 6150 3400 50  0001 C CNN
	1    6150 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 3400 6000 3400
Wire Wire Line
	5700 2600 5700 3400
Connection ~ 5950 3400
Wire Wire Line
	6750 3400 6300 3400
Connection ~ 6350 3400
$EndSCHEMATC
