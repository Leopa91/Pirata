EESchema Schematic File Version 2
LIBS:74hc125
LIBS:4052
LIBS:rj11
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
LIBS:microreader
LIBS:pin_3
LIBS:tps5622
LIBS:max232
LIBS:Prototipo_1-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
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
L GND #PWR061
U 1 1 594B26DC
P 4200 4950
F 0 "#PWR061" H 4200 4700 50  0001 C CNN
F 1 "GND" H 4200 4800 50  0000 C CNN
F 2 "" H 4200 4950 50  0001 C CNN
F 3 "" H 4200 4950 50  0001 C CNN
	1    4200 4950
	1    0    0    -1  
$EndComp
$Comp
L 74HC125 U5
U 1 1 594C2001
P 4100 4100
F 0 "U5" H 3900 4800 60  0000 C CNN
F 1 "74HC125" H 4450 3550 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 4100 4100 60  0001 C CNN
F 3 "" H 4100 4100 60  0001 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR062
U 1 1 594C23F7
P 4200 3100
F 0 "#PWR062" H 4200 2950 50  0001 C CNN
F 1 "+5V" H 4200 3240 50  0000 C CNN
F 2 "" H 4200 3100 50  0001 C CNN
F 3 "" H 4200 3100 50  0001 C CNN
	1    4200 3100
	1    0    0    -1  
$EndComp
Connection ~ 2400 4000
Wire Wire Line
	2400 4200 3500 4200
Connection ~ 2400 3800
Wire Wire Line
	2400 4000 3500 4000
Wire Wire Line
	2400 3200 2400 4200
Wire Wire Line
	2400 3600 3500 3600
Wire Wire Line
	4200 3200 4200 3100
Wire Wire Line
	4200 4850 4200 4950
Wire Wire Line
	4950 4200 5250 4200
Wire Wire Line
	4950 4000 5250 4000
Wire Wire Line
	4950 3800 5250 3800
Wire Wire Line
	4950 3600 5250 3600
Wire Wire Line
	2250 3900 2400 3900
Connection ~ 2400 3900
$Comp
L GND #PWR063
U 1 1 594C28E2
P 3400 2800
F 0 "#PWR063" H 3400 2550 50  0001 C CNN
F 1 "GND" H 3400 2650 50  0000 C CNN
F 2 "" H 3400 2800 50  0001 C CNN
F 3 "" H 3400 2800 50  0001 C CNN
	1    3400 2800
	1    0    0    -1  
$EndComp
$Comp
L 74HC125 U4
U 1 1 594C28EC
P 3300 1950
F 0 "U4" H 3100 2650 60  0000 C CNN
F 1 "74HC125" H 3650 1400 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 3300 1950 60  0001 C CNN
F 3 "" H 3300 1950 60  0001 C CNN
	1    3300 1950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR064
U 1 1 594C28F2
P 3400 950
F 0 "#PWR064" H 3400 800 50  0001 C CNN
F 1 "+5V" H 3400 1090 50  0000 C CNN
F 2 "" H 3400 950 50  0001 C CNN
F 3 "" H 3400 950 50  0001 C CNN
	1    3400 950 
	1    0    0    -1  
$EndComp
Connection ~ 1600 1850
Wire Wire Line
	1600 2050 2700 2050
Connection ~ 1600 1650
Wire Wire Line
	1600 1850 2700 1850
Wire Wire Line
	1600 1150 1600 2050
Wire Wire Line
	1600 1450 2700 1450
Wire Wire Line
	3400 1050 3400 950 
Wire Wire Line
	3400 2700 3400 2800
Wire Wire Line
	4150 2050 4450 2050
Wire Wire Line
	4150 1850 4450 1850
Wire Wire Line
	4150 1650 4450 1650
Wire Wire Line
	4150 1450 4450 1450
Wire Wire Line
	1450 1750 1600 1750
Connection ~ 1600 1750
Wire Wire Line
	2700 1550 2150 1550
Wire Wire Line
	2700 1750 2150 1750
Wire Wire Line
	2700 1950 2150 1950
Wire Wire Line
	2700 2150 2150 2150
$Comp
L GND #PWR065
U 1 1 594C38A3
P 8600 2750
F 0 "#PWR065" H 8600 2500 50  0001 C CNN
F 1 "GND" H 8600 2600 50  0000 C CNN
F 2 "" H 8600 2750 50  0001 C CNN
F 3 "" H 8600 2750 50  0001 C CNN
	1    8600 2750
	1    0    0    -1  
$EndComp
$Comp
L 74HC125 U6
U 1 1 594C38AD
P 8500 1900
F 0 "U6" H 8300 2600 60  0000 C CNN
F 1 "74HC125" H 8850 1350 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 8500 1900 60  0001 C CNN
F 3 "" H 8500 1900 60  0001 C CNN
	1    8500 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 1000 8600 900 
Wire Wire Line
	8600 2650 8600 2750
Wire Wire Line
	7900 1500 7350 1500
Wire Wire Line
	7900 1700 7350 1700
Wire Wire Line
	7900 1900 7350 1900
Wire Wire Line
	7900 2100 7350 2100
Wire Wire Line
	7900 1400 7350 1400
Wire Wire Line
	7900 1600 7350 1600
Wire Wire Line
	7900 1800 7350 1800
Wire Wire Line
	7900 2000 7350 2000
$Comp
L +3.3V #PWR066
U 1 1 594C4259
P 8600 900
F 0 "#PWR066" H 8600 750 50  0001 C CNN
F 1 "+3.3V" H 8600 1040 50  0000 C CNN
F 2 "" H 8600 900 50  0001 C CNN
F 3 "" H 8600 900 50  0001 C CNN
	1    8600 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 2000 9350 2000
Wire Wire Line
	9700 1400 9700 2000
Wire Wire Line
	9700 1400 9350 1400
Wire Wire Line
	9350 1600 9700 1600
Connection ~ 9700 1600
Wire Wire Line
	9350 1800 9700 1800
Connection ~ 9700 1800
Wire Wire Line
	9950 1700 9700 1700
Connection ~ 9700 1700
$Comp
L GND #PWR067
U 1 1 594DBD07
P 9100 4900
F 0 "#PWR067" H 9100 4650 50  0001 C CNN
F 1 "GND" H 9100 4750 50  0000 C CNN
F 2 "" H 9100 4900 50  0001 C CNN
F 3 "" H 9100 4900 50  0001 C CNN
	1    9100 4900
	1    0    0    -1  
$EndComp
$Comp
L 74HC125 U7
U 1 1 594DBD0D
P 9000 4050
F 0 "U7" H 8800 4750 60  0000 C CNN
F 1 "74HC125" H 9350 3500 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 9000 4050 60  0001 C CNN
F 3 "" H 9000 4050 60  0001 C CNN
	1    9000 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3150 9100 3050
Wire Wire Line
	9100 4800 9100 4900
Wire Wire Line
	8400 3650 7850 3650
Wire Wire Line
	8400 3850 7850 3850
Wire Wire Line
	8400 4050 7850 4050
Wire Wire Line
	8400 4250 7850 4250
Wire Wire Line
	8400 3550 7850 3550
Wire Wire Line
	8400 3750 7850 3750
Wire Wire Line
	8400 3950 7850 3950
Wire Wire Line
	8400 4150 7850 4150
$Comp
L +3.3V #PWR068
U 1 1 594DBD21
P 9100 3050
F 0 "#PWR068" H 9100 2900 50  0001 C CNN
F 1 "+3.3V" H 9100 3190 50  0000 C CNN
F 2 "" H 9100 3050 50  0001 C CNN
F 3 "" H 9100 3050 50  0001 C CNN
	1    9100 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 4150 9850 4150
Wire Wire Line
	10200 3550 10200 4150
Wire Wire Line
	10200 3550 9850 3550
Wire Wire Line
	9850 3750 10200 3750
Connection ~ 10200 3750
Wire Wire Line
	9850 3950 10200 3950
Connection ~ 10200 3950
Wire Wire Line
	10450 3850 10200 3850
Connection ~ 10200 3850
Wire Wire Line
	3500 3700 3050 3700
Wire Wire Line
	3500 3900 3050 3900
Wire Wire Line
	3500 4100 3050 4100
Wire Wire Line
	3500 4300 3050 4300
Text GLabel 1450 1750 0    60   Input ~ 0
UART0_TX
Text GLabel 2150 1550 0    60   Input ~ 0
SEL_TAG
Text GLabel 2150 1750 0    60   Input ~ 0
SEL_RFID
Text GLabel 2150 1950 0    60   Input ~ 0
SEL_QR
Text GLabel 2150 2150 0    60   Input ~ 0
SEL_TAR
Text GLabel 4450 1450 2    60   Input ~ 0
TAG_TX_1
Text GLabel 4450 1650 2    60   Input ~ 0
RFID_TX_1
Text GLabel 4450 1850 2    60   Input ~ 0
QR_TX_1
Text GLabel 4450 2050 2    60   Input ~ 0
TAR_TX_1
Text GLabel 2250 3900 0    60   Input ~ 0
UART1_TX
Text GLabel 3050 3700 0    60   Input ~ 0
SEL_TAG_2
Text GLabel 3050 3900 0    60   Input ~ 0
SEL_RFID_2
Text GLabel 3050 4100 0    60   Input ~ 0
SEL_QR_2
Text GLabel 3050 4300 0    60   Input ~ 0
SEL_TAR_2
Text GLabel 5250 3600 2    60   Input ~ 0
TAG_TX_2
Text GLabel 5250 3800 2    60   Input ~ 0
RFID_TX_2
Text GLabel 5250 4000 2    60   Input ~ 0
QR_TX_2
Text GLabel 5250 4200 2    60   Input ~ 0
TAR_TX_2
Text GLabel 7350 1400 0    60   Input ~ 0
TAG_RX_1
Text GLabel 7350 1500 0    60   Input ~ 0
SEL_TAG
Text GLabel 7350 1600 0    60   Input ~ 0
RFID_RX_1
Text GLabel 7350 1700 0    60   Input ~ 0
SEL_RFID
Text GLabel 7350 1800 0    60   Input ~ 0
QR_RX_1
Text GLabel 7350 1900 0    60   Input ~ 0
SEL_QR
Text GLabel 7350 2000 0    60   Input ~ 0
TAR_RX_1
Text GLabel 7350 2100 0    60   Input ~ 0
SEL_TAR
Text GLabel 9950 1700 2    60   Input ~ 0
USART0_RX
Text GLabel 7850 3550 0    60   Input ~ 0
TAG_RX_2
Text GLabel 7850 3650 0    60   Input ~ 0
SEL_TAG_2
Text GLabel 7850 3750 0    60   Input ~ 0
RFID_RX_2
Text GLabel 7850 3850 0    60   Input ~ 0
SEL_RFID_2
Text GLabel 7850 3950 0    60   Input ~ 0
QR_RX_2
Text GLabel 7850 4050 0    60   Input ~ 0
SEL_QR_2
Text GLabel 7850 4150 0    60   Input ~ 0
TAR_RX_2
Text GLabel 7850 4250 0    60   Input ~ 0
SEL_TAR_2
Text GLabel 10450 3850 2    60   Input ~ 0
USART1_RX
$Comp
L CONN_01X03 J7
U 1 1 59548ECE
P 1100 1050
F 0 "J7" H 1100 1250 50  0000 C CNN
F 1 "CONN_01X03" V 1200 1050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 1100 1050 50  0001 C CNN
F 3 "" H 1100 1050 50  0001 C CNN
	1    1100 1050
	-1   0    0    1   
$EndComp
Wire Wire Line
	2700 1650 2300 1650
Text Label 2300 1650 0    39   ~ 0
2A
Wire Wire Line
	1300 1050 1600 1050
Text Label 1600 1050 0    39   ~ 0
2A
Wire Wire Line
	1600 1150 1300 1150
Connection ~ 1600 1450
Text GLabel 1450 950  2    39   Input ~ 0
AUX_1
Wire Wire Line
	1450 950  1300 950 
$Comp
L CONN_01X03 J8
U 1 1 5954F63F
P 1450 3100
F 0 "J8" H 1450 3300 50  0000 C CNN
F 1 "CONN_01X03" V 1550 3100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 1450 3100 50  0001 C CNN
F 3 "" H 1450 3100 50  0001 C CNN
	1    1450 3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	1650 3100 1950 3100
Text Label 1950 3100 0    39   ~ 0
2A_TX
Wire Wire Line
	1650 3200 2400 3200
Text GLabel 1800 3000 2    39   Input ~ 0
AUX_1
Wire Wire Line
	1800 3000 1650 3000
Text Label 3300 3800 0    39   ~ 0
2A_TX
Wire Wire Line
	3500 3800 3300 3800
Connection ~ 2400 3600
$EndSCHEMATC
