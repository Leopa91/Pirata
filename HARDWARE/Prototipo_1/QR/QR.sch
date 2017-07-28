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
LIBS:mmbt2222l
LIBS:max232
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
L CONN_01X03 J1
U 1 1 595DE716
P 1450 1500
F 0 "J1" H 1450 1700 50  0000 C CNN
F 1 "SEL_POWER" V 1550 1500 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03_Pitch2.54mm" H 1450 1500 50  0001 C CNN
F 3 "" H 1450 1500 50  0001 C CNN
	1    1450 1500
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR01
U 1 1 595DE7D1
P 1900 1000
F 0 "#PWR01" H 1900 850 50  0001 C CNN
F 1 "+5V" H 1900 1140 50  0000 C CNN
F 2 "" H 1900 1000 50  0001 C CNN
F 3 "" H 1900 1000 50  0001 C CNN
	1    1900 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1000 1900 1400
Wire Wire Line
	1900 1400 1650 1400
$Comp
L +3.3V #PWR02
U 1 1 595DE7F2
P 2200 950
F 0 "#PWR02" H 2200 800 50  0001 C CNN
F 1 "+3.3V" H 2200 1090 50  0000 C CNN
F 2 "" H 2200 950 50  0001 C CNN
F 3 "" H 2200 950 50  0001 C CNN
	1    2200 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1600 2200 1600
Wire Wire Line
	2200 1600 2200 950 
Text Label 1650 1500 0    60   ~ 0
POWER
$Comp
L CONN_01X12 J7
U 1 1 595DE87F
P 7100 3900
F 0 "J7" H 7100 4550 50  0000 C CNN
F 1 "CAM" V 7200 3900 50  0000 C CNN
F 2 "Libreria:WR-FPC" H 7100 3900 50  0001 C CNN
F 3 "" H 7100 3900 50  0001 C CNN
	1    7100 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3550 6900 3550
Wire Wire Line
	5400 3550 5400 3750
$Comp
L GND #PWR03
U 1 1 595DE9D7
P 5400 3750
F 0 "#PWR03" H 5400 3500 50  0001 C CNN
F 1 "GND" H 5400 3600 50  0000 C CNN
F 2 "" H 5400 3750 50  0001 C CNN
F 3 "" H 5400 3750 50  0001 C CNN
	1    5400 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3650 6350 3650
Wire Wire Line
	6900 3750 6350 3750
Text Label 6350 3650 0    60   ~ 0
TX_QR
Text Label 6350 3750 0    60   ~ 0
RX_QR
NoConn ~ 6900 3350
Wire Wire Line
	6900 3450 6350 3450
Text Label 6350 3450 0    60   ~ 0
POWER
NoConn ~ 6900 3850
NoConn ~ 6900 3950
NoConn ~ 6900 4050
NoConn ~ 6900 4250
NoConn ~ 6900 4350
Wire Wire Line
	6900 4450 6350 4450
Text Label 6350 4450 0    60   ~ 0
TRIG
Wire Wire Line
	6900 4150 6350 4150
Text Label 6350 4150 0    60   ~ 0
PITO
$Comp
L CONN_01X02 J2
U 1 1 595DEEED
P 1450 2650
F 0 "J2" H 1450 2800 50  0000 C CNN
F 1 "Pulsador" V 1550 2650 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02_Pitch2.54mm" H 1450 2650 50  0001 C CNN
F 3 "" H 1450 2650 50  0001 C CNN
	1    1450 2650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR04
U 1 1 595DEFBB
P 1850 2900
F 0 "#PWR04" H 1850 2650 50  0001 C CNN
F 1 "GND" H 1850 2750 50  0000 C CNN
F 2 "" H 1850 2900 50  0001 C CNN
F 3 "" H 1850 2900 50  0001 C CNN
	1    1850 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 2900 1850 2700
Wire Wire Line
	1850 2700 1650 2700
$Comp
L R R2
U 1 1 595DEFE5
P 1850 2400
F 0 "R2" V 1930 2400 50  0000 C CNN
F 1 "1K" V 1850 2400 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1780 2400 50  0001 C CNN
F 3 "" H 1850 2400 50  0001 C CNN
	1    1850 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2600 2250 2600
Wire Wire Line
	1850 2600 1850 2550
Wire Wire Line
	1850 2250 1850 1950
Text Label 1850 1950 0    60   ~ 0
POWER
Connection ~ 1850 2600
Text Label 2250 2600 0    60   ~ 0
TRIG
$Comp
L R R1
U 1 1 595DF363
P 1450 4250
F 0 "R1" V 1530 4250 50  0000 C CNN
F 1 "330" V 1450 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1380 4250 50  0001 C CNN
F 3 "" H 1450 4250 50  0001 C CNN
	1    1450 4250
	0    1    1    0   
$EndComp
$Comp
L MMBT2222L Q1
U 1 1 595DF43E
P 1950 4250
F 0 "Q1" H 2150 4325 50  0000 L CNN
F 1 "MMBT2222L" H 2150 4250 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 2150 4175 50  0001 L CIN
F 3 "" H 1950 4250 50  0001 L CNN
	1    1950 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 4250 1750 4250
$Comp
L LED D1
U 1 1 595DF55A
P 2050 3750
F 0 "D1" H 2050 3850 50  0000 C CNN
F 1 "LED" H 2050 3650 50  0000 C CNN
F 2 "LEDs:LED_0603" H 2050 3750 50  0001 C CNN
F 3 "" H 2050 3750 50  0001 C CNN
	1    2050 3750
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 J3
U 1 1 595DF6B1
P 2600 3750
F 0 "J3" H 2600 3900 50  0000 C CNN
F 1 "BUZZER" V 2700 3750 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02_Pitch2.54mm" H 2600 3750 50  0001 C CNN
F 3 "" H 2600 3750 50  0001 C CNN
	1    2600 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 4050 2050 3900
Wire Wire Line
	2050 4000 2400 4000
Wire Wire Line
	2400 4000 2400 3800
Connection ~ 2050 4000
Wire Wire Line
	2400 2900 2400 3700
Wire Wire Line
	2050 3500 2050 3600
$Comp
L R R3
U 1 1 595DF7DC
P 2050 3350
F 0 "R3" V 2130 3350 50  0000 C CNN
F 1 "1K" V 2050 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1980 3350 50  0001 C CNN
F 3 "" H 2050 3350 50  0001 C CNN
	1    2050 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3200 2050 3050
Wire Wire Line
	2050 3050 2400 3050
$Comp
L +5V #PWR05
U 1 1 595DFAA7
P 2400 2900
F 0 "#PWR05" H 2400 2750 50  0001 C CNN
F 1 "+5V" H 2400 3040 50  0000 C CNN
F 2 "" H 2400 2900 50  0001 C CNN
F 3 "" H 2400 2900 50  0001 C CNN
	1    2400 2900
	1    0    0    -1  
$EndComp
Connection ~ 2400 3050
Wire Wire Line
	1300 4250 1100 4250
Text Label 1100 4250 0    60   ~ 0
PITO
$Comp
L RJ45 J4
U 1 1 595E01F9
P 4900 1300
F 0 "J4" H 5100 1800 50  0000 C CNN
F 1 "RJ45" H 4750 1800 50  0000 C CNN
F 2 "RJ45-8p8c:8p8c-RJ45" H 4900 1300 50  0001 C CNN
F 3 "" H 4900 1300 50  0001 C CNN
	1    4900 1300
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR06
U 1 1 595E0426
P 5800 1750
F 0 "#PWR06" H 5800 1600 50  0001 C CNN
F 1 "+3.3V" H 5800 1890 50  0000 C CNN
F 2 "" H 5800 1750 50  0001 C CNN
F 3 "" H 5800 1750 50  0001 C CNN
	1    5800 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 1750 5800 1900
Wire Wire Line
	5800 1900 5250 1900
Wire Wire Line
	5250 1900 5250 1750
Text Label 4150 1900 0    60   ~ 0
TRIG
Wire Wire Line
	4550 1750 4550 1900
Wire Wire Line
	4550 1900 4150 1900
NoConn ~ 4650 1750
$Comp
L GND #PWR07
U 1 1 595E04F7
P 4750 1950
F 0 "#PWR07" H 4750 1700 50  0001 C CNN
F 1 "GND" H 4750 1800 50  0000 C CNN
F 2 "" H 4750 1950 50  0001 C CNN
F 3 "" H 4750 1950 50  0001 C CNN
	1    4750 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1750 4750 1950
Wire Wire Line
	5050 1750 5050 2050
Wire Wire Line
	5050 2050 6150 2050
Wire Wire Line
	6150 2050 6150 1750
$Comp
L +5V #PWR08
U 1 1 595E0702
P 6150 1750
F 0 "#PWR08" H 6150 1600 50  0001 C CNN
F 1 "+5V" H 6150 1890 50  0000 C CNN
F 2 "" H 6150 1750 50  0001 C CNN
F 3 "" H 6150 1750 50  0001 C CNN
	1    6150 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1750 4850 2400
Wire Wire Line
	4950 1750 4950 2150
Text Label 4850 2400 0    60   ~ 0
A
Text Label 4950 2150 0    60   ~ 0
B
$Comp
L Max232 U1
U 1 1 595E0A57
P 9100 2150
F 0 "U1" H 8450 3150 118 0000 C CNN
F 1 "Max232" H 8750 2050 118 0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 8700 1950 118 0001 C CNN
F 3 "" H 8700 1950 118 0001 C CNN
	1    9100 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2050 9850 2050
Text Label 9850 2050 0    60   ~ 0
RX_MAX
Text Label 7750 2050 0    39   ~ 0
RX
Wire Wire Line
	8150 2050 7750 2050
Wire Wire Line
	9300 1950 9750 1950
Wire Wire Line
	9750 1950 9750 1850
Text Label 9750 1850 0    60   ~ 0
TX_MAX
Wire Wire Line
	8150 1950 7750 1950
Text Label 7750 1950 0    60   ~ 0
TX
$Comp
L CONN_01X03 J8
U 1 1 595E20C0
P 9250 2950
F 0 "J8" H 9250 3150 50  0000 C CNN
F 1 "SEL_TX_CAM" V 9350 2950 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03_Pitch2.54mm" H 9250 2950 50  0001 C CNN
F 3 "" H 9250 2950 50  0001 C CNN
	1    9250 2950
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 J9
U 1 1 595E2257
P 9250 3700
F 0 "J9" H 9250 3900 50  0000 C CNN
F 1 "SEL_RX_CAM" V 9350 3700 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03_Pitch2.54mm" H 9250 3700 50  0001 C CNN
F 3 "" H 9250 3700 50  0001 C CNN
	1    9250 3700
	-1   0    0    1   
$EndComp
Text Label 9450 2850 0    60   ~ 0
TX_MAX
Text Label 9450 3050 0    60   ~ 0
RX_MAX
Text Label 9450 2950 0    60   ~ 0
TX_QR
Text Label 9450 3600 0    60   ~ 0
TX_MAX
Text Label 9450 3800 0    60   ~ 0
RX_MAX
Text Label 9450 3700 0    60   ~ 0
RX_QR
$Comp
L CONN_01X03 J5
U 1 1 595E3195
P 6750 1500
F 0 "J5" H 6750 1700 50  0000 C CNN
F 1 "SEL_TX" V 6850 1500 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03_Pitch2.54mm" H 6750 1500 50  0001 C CNN
F 3 "" H 6750 1500 50  0001 C CNN
	1    6750 1500
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 J6
U 1 1 595E33CE
P 6750 2150
F 0 "J6" H 6750 2350 50  0000 C CNN
F 1 "SEL_RX" V 6850 2150 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03_Pitch2.54mm" H 6750 2150 50  0001 C CNN
F 3 "" H 6750 2150 50  0001 C CNN
	1    6750 2150
	-1   0    0    1   
$EndComp
Text Label 6950 1400 0    60   ~ 0
TX
Text Label 6950 1600 0    60   ~ 0
RX
Text Label 6950 2050 0    60   ~ 0
TX
Text Label 6950 2250 0    60   ~ 0
RX
Text Label 6950 1500 0    60   ~ 0
A
Text Label 6950 2150 0    60   ~ 0
B
Text Label 9300 1350 0    60   ~ 0
POWER
$Comp
L GND #PWR09
U 1 1 595E4BA1
P 10300 1500
F 0 "#PWR09" H 10300 1250 50  0001 C CNN
F 1 "GND" H 10300 1350 50  0000 C CNN
F 2 "" H 10300 1500 50  0001 C CNN
F 3 "" H 10300 1500 50  0001 C CNN
	1    10300 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1450 10300 1450
Wire Wire Line
	10300 1450 10300 1500
NoConn ~ 9300 1550
NoConn ~ 9300 1650
NoConn ~ 9300 1750
NoConn ~ 9300 1850
$Comp
L CP1 C4
U 1 1 595E5058
P 7850 1450
F 0 "C4" H 7875 1550 50  0000 L CNN
F 1 "CP1" H 7875 1350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7850 1450 50  0001 C CNN
F 3 "" H 7850 1450 50  0001 C CNN
	1    7850 1450
	0    1    1    0   
$EndComp
Text Label 7600 1200 0    60   ~ 0
POWER
Wire Wire Line
	7600 1200 7600 1450
Wire Wire Line
	7600 1450 7700 1450
Wire Wire Line
	8000 1450 8150 1450
$Comp
L CP1 C1
U 1 1 595E5290
P 7400 1350
F 0 "C1" H 7425 1450 50  0000 L CNN
F 1 "CP1" H 7425 1250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7400 1350 50  0001 C CNN
F 3 "" H 7400 1350 50  0001 C CNN
	1    7400 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 1350 8050 1350
Wire Wire Line
	8050 1350 8050 1000
Wire Wire Line
	8050 1000 7400 1000
Wire Wire Line
	7400 1000 7400 1200
Wire Wire Line
	7400 1500 7400 1650
Wire Wire Line
	7400 1650 8000 1650
Wire Wire Line
	8000 1650 8000 1550
Wire Wire Line
	8000 1550 8150 1550
Wire Wire Line
	8150 1650 8050 1650
Wire Wire Line
	8050 1650 8050 1700
Wire Wire Line
	8050 1700 7400 1700
Wire Wire Line
	7400 1700 7400 1750
$Comp
L CP1 C2
U 1 1 595E53CA
P 7400 1900
F 0 "C2" H 7425 2000 50  0000 L CNN
F 1 "CP1" H 7425 1800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7400 1900 50  0001 C CNN
F 3 "" H 7400 1900 50  0001 C CNN
	1    7400 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2050 7400 2150
Wire Wire Line
	7400 2150 7600 2150
Wire Wire Line
	7600 2150 7600 1750
Wire Wire Line
	7600 1750 8150 1750
Wire Wire Line
	8150 1850 7650 1850
Wire Wire Line
	7650 1850 7650 2200
Wire Wire Line
	7650 2200 7400 2200
Wire Wire Line
	7400 2200 7400 2250
$Comp
L CP1 C3
U 1 1 595E54D6
P 7400 2400
F 0 "C3" H 7425 2500 50  0000 L CNN
F 1 "CP1" H 7425 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 7400 2400 50  0001 C CNN
F 3 "" H 7400 2400 50  0001 C CNN
	1    7400 2400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR010
U 1 1 595E561A
P 7400 2600
F 0 "#PWR010" H 7400 2350 50  0001 C CNN
F 1 "GND" H 7400 2450 50  0000 C CNN
F 2 "" H 7400 2600 50  0001 C CNN
F 3 "" H 7400 2600 50  0001 C CNN
	1    7400 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2550 7400 2600
$Comp
L GND #PWR011
U 1 1 595E6D0B
P 2050 4750
F 0 "#PWR011" H 2050 4500 50  0001 C CNN
F 1 "GND" H 2050 4600 50  0000 C CNN
F 2 "" H 2050 4750 50  0001 C CNN
F 3 "" H 2050 4750 50  0001 C CNN
	1    2050 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 4450 2050 4750
NoConn ~ 5450 950 
NoConn ~ 5150 1750
$EndSCHEMATC