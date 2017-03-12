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
LIBS:wemos_mini
LIBS:switch
LIBS:BrainBox-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Brain Box Premium"
Date "2017-03-12"
Rev "1.0"
Comp "BBC"
Comment1 "Jérôme Labidurie"
Comment2 "CC:BY-SA"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L WeMos_mini U2
U 1 1 58C5602E
P 6950 4150
F 0 "U2" H 6950 4650 60  0000 C CNN
F 1 "WeMos_mini" H 6950 3650 60  0000 C CNN
F 2 "" H 7500 3450 60  0000 C CNN
F 3 "" H 7500 3450 60  0000 C CNN
	1    6950 4150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 58C560DE
P 5500 4350
F 0 "R1" V 5580 4350 50  0000 C CNN
F 1 "1K" V 5500 4350 50  0000 C CNN
F 2 "" V 5430 4350 50  0000 C CNN
F 3 "" H 5500 4350 50  0000 C CNN
	1    5500 4350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 58C56133
P 5300 4350
F 0 "C1" H 5200 4450 50  0000 L CNN
F 1 "10n" H 5150 4250 50  0000 L CNN
F 2 "" H 5338 4200 50  0000 C CNN
F 3 "" H 5300 4350 50  0000 C CNN
	1    5300 4350
	1    0    0    -1  
$EndComp
$Comp
L Battery BT1
U 1 1 58C56163
P 6200 3400
F 0 "BT1" H 6300 3500 50  0000 L CNN
F 1 "Battery" V 6050 3300 50  0000 L CNN
F 2 "" V 6200 3460 50  0000 C CNN
F 3 "" V 6200 3460 50  0000 C CNN
	1    6200 3400
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 58C56553
P 5800 3350
F 0 "R2" V 5880 3350 50  0000 C CNN
F 1 "1K" V 5800 3350 50  0000 C CNN
F 2 "" V 5730 3350 50  0000 C CNN
F 3 "" H 5800 3350 50  0000 C CNN
	1    5800 3350
	-1   0    0    1   
$EndComp
$Comp
L PN2222A Q1
U 1 1 58C56607
P 5600 3050
F 0 "Q1" H 5800 3125 50  0000 L CNN
F 1 "PN2222A" H 5800 3050 50  0000 L CNN
F 2 "" H 5800 2975 50  0000 L CIN
F 3 "" H 5600 3050 50  0000 L CNN
	1    5600 3050
	-1   0    0    -1  
$EndComp
$Comp
L Switch U1
U 1 1 58C568DA
P 4200 3650
F 0 "U1" H 4200 3650 60  0000 C CNN
F 1 "Switch" H 4200 3350 60  0000 C CNN
F 2 "" H 4200 3650 60  0001 C CNN
F 3 "" H 4200 3650 60  0001 C CNN
	1    4200 3650
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 58C56AAC
P 5400 4500
F 0 "#PWR01" H 5400 4250 50  0001 C CNN
F 1 "GND" H 5400 4350 50  0000 C CNN
F 2 "" H 5400 4500 50  0000 C CNN
F 3 "" H 5400 4500 50  0000 C CNN
	1    5400 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 58C56AD3
P 6350 3900
F 0 "#PWR02" H 6350 3650 50  0001 C CNN
F 1 "GND" H 6350 3750 50  0000 C CNN
F 2 "" H 6350 3900 50  0000 C CNN
F 3 "" H 6350 3900 50  0000 C CNN
	1    6350 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4300 7550 4300
Wire Wire Line
	7550 4300 7550 4500
Wire Wire Line
	7550 4500 7450 4500
Wire Wire Line
	5800 3850 6250 3850
Wire Wire Line
	5500 4050 5500 4200
Wire Wire Line
	5500 4200 5300 4200
Wire Wire Line
	5300 4500 5500 4500
Wire Wire Line
	5500 4100 6200 4100
Wire Wire Line
	6200 4100 6200 4300
Wire Wire Line
	6200 4300 6450 4300
Connection ~ 5500 4100
Wire Wire Line
	6450 3900 6350 3900
Wire Wire Line
	6450 4200 6250 4200
Wire Wire Line
	6250 4200 6250 3850
Wire Wire Line
	6200 3200 6450 3200
Wire Wire Line
	6450 3200 6450 3800
Wire Wire Line
	6200 3600 6350 3600
Wire Wire Line
	6350 3600 6350 3900
Wire Wire Line
	5500 2850 7450 2850
Wire Wire Line
	7450 2850 7450 3800
Wire Wire Line
	5800 3850 5800 3500
Wire Wire Line
	5800 3200 5800 3050
NoConn ~ 7450 3900
NoConn ~ 7450 4000
NoConn ~ 7450 4100
NoConn ~ 7450 4200
NoConn ~ 7450 4400
NoConn ~ 6450 4000
NoConn ~ 6450 4100
NoConn ~ 6450 4400
NoConn ~ 6450 4500
Wire Wire Line
	5500 3250 4400 3250
Wire Wire Line
	4400 4050 5500 4050
Text Notes 4250 4300 1    60   ~ 0
Dispositif de détection\ndu courrier
Text Label 6200 3200 0    60   ~ 0
+4.5V
$Comp
L PWR_FLAG #FLG03
U 1 1 58C572EF
P 10800 950
F 0 "#FLG03" H 10800 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 10800 1130 50  0000 C CNN
F 2 "" H 10800 950 50  0000 C CNN
F 3 "" H 10800 950 50  0000 C CNN
	1    10800 950 
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 58C57339
P 10350 950
F 0 "#FLG04" H 10350 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 10350 1130 50  0000 C CNN
F 2 "" H 10350 950 50  0000 C CNN
F 3 "" H 10350 950 50  0000 C CNN
	1    10350 950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 58C5735B
P 10800 950
F 0 "#PWR05" H 10800 700 50  0001 C CNN
F 1 "GND" H 10800 800 50  0000 C CNN
F 2 "" H 10800 950 50  0000 C CNN
F 3 "" H 10800 950 50  0000 C CNN
	1    10800 950 
	1    0    0    -1  
$EndComp
Text Label 10350 950  0    60   ~ 0
+4.5V
$EndSCHEMATC
