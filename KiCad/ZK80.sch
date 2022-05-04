EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ZK80 With SD"
Date ""
Rev "Rev1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Display_Character:CA56-12EWA U1
U 1 1 6248B172
P 2200 1150
F 0 "U1" H 1400 1700 50  0000 C CNN
F 1 "OSL40562-IRA" H 2350 1700 50  0000 C CNN
F 2 "Display_7Segment:CA56-12EWA" H 2200 550 50  0001 C CNN
F 3 "http://www.kingbrightusa.com/images/catalog/SPEC/CA56-12EWA.pdf" H 1770 1180 50  0001 C CNN
	1    2200 1150
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:CC56-12EWA U2
U 1 1 6248BE52
P 5600 1150
F 0 "U2" H 4800 1700 50  0000 C CNN
F 1 "OSL40562-LRA" H 5650 1700 50  0000 C CNN
F 2 "Display_7Segment:CA56-12EWA" H 5600 550 50  0001 C CNN
F 3 "http://www.kingbrightusa.com/images/catalog/SPEC/CA56-12EWA.pdf" H 5170 1180 50  0001 C CNN
	1    5600 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 1250 3400 1250
Wire Wire Line
	3400 1250 3400 1850
Wire Wire Line
	3400 1850 6800 1850
Wire Wire Line
	6800 1850 6800 1250
Wire Wire Line
	6800 1250 6700 1250
Wire Wire Line
	3300 1350 3450 1350
Wire Wire Line
	3450 1350 3450 1900
Wire Wire Line
	3450 1900 6850 1900
Wire Wire Line
	6850 1900 6850 1350
Wire Wire Line
	6850 1350 6700 1350
Wire Wire Line
	3300 1450 3500 1450
Wire Wire Line
	3500 1450 3500 1950
Wire Wire Line
	3500 1950 6900 1950
Wire Wire Line
	6900 1950 6900 1450
Wire Wire Line
	6900 1450 6700 1450
Wire Wire Line
	3300 1550 3550 1550
Wire Wire Line
	3550 1550 3550 2000
Wire Wire Line
	3550 2000 6950 2000
Wire Wire Line
	6950 2000 6950 1550
Wire Wire Line
	6950 1550 6700 1550
Wire Wire Line
	1100 850  1000 850 
Wire Wire Line
	1000 850  1000 2050
Wire Wire Line
	1000 2050 4400 2050
Wire Wire Line
	4400 2050 4400 850 
Wire Wire Line
	4400 850  4500 850 
Wire Wire Line
	1100 950  950  950 
Wire Wire Line
	950  950  950  2100
Wire Wire Line
	950  2100 4350 2100
Wire Wire Line
	4350 2100 4350 950 
Wire Wire Line
	4350 950  4500 950 
Wire Wire Line
	1100 1050 900  1050
Wire Wire Line
	900  1050 900  2150
Wire Wire Line
	900  2150 4300 2150
Wire Wire Line
	4300 2150 4300 1050
Wire Wire Line
	4300 1050 4500 1050
Wire Wire Line
	1100 1150 850  1150
Wire Wire Line
	850  1150 850  2200
Wire Wire Line
	850  2200 4250 2200
Wire Wire Line
	4250 2200 4250 1150
Wire Wire Line
	4250 1150 4500 1150
Wire Wire Line
	1100 1250 800  1250
Wire Wire Line
	800  1250 800  2250
Wire Wire Line
	800  2250 4200 2250
Wire Wire Line
	4200 2250 4200 1250
Wire Wire Line
	4200 1250 4500 1250
Wire Wire Line
	1100 1350 750  1350
Wire Wire Line
	750  1350 750  2300
Wire Wire Line
	750  2300 4150 2300
Wire Wire Line
	4150 2300 4150 1350
Wire Wire Line
	4150 1350 4500 1350
Wire Wire Line
	1100 1450 700  1450
Wire Wire Line
	700  1450 700  2350
Wire Wire Line
	700  2350 4100 2350
Wire Wire Line
	4100 2350 4100 1450
Wire Wire Line
	4100 1450 4500 1450
Wire Wire Line
	1100 1550 650  1550
Wire Wire Line
	650  1550 650  2400
Wire Wire Line
	650  2400 4050 2400
Wire Wire Line
	4050 2400 4050 1550
Wire Wire Line
	4050 1550 4500 1550
$Comp
L Device:R R2
U 1 1 624AC392
P 3750 2850
F 0 "R2" V 3650 2750 50  0000 C CNN
F 1 "100" V 3650 2950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3680 2850 50  0001 C CNN
F 3 "~" H 3750 2850 50  0001 C CNN
	1    3750 2850
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 624AF6A0
P 3750 3050
F 0 "R3" V 3650 2950 50  0000 C CNN
F 1 "100" V 3650 3150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3680 3050 50  0001 C CNN
F 3 "~" H 3750 3050 50  0001 C CNN
	1    3750 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 624B0CC0
P 3750 3250
F 0 "R4" V 3650 3150 50  0000 C CNN
F 1 "100" V 3650 3350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3680 3250 50  0001 C CNN
F 3 "~" H 3750 3250 50  0001 C CNN
	1    3750 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 624B2411
P 3750 3450
F 0 "R5" V 3650 3350 50  0000 C CNN
F 1 "100" V 3650 3550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3680 3450 50  0001 C CNN
F 3 "~" H 3750 3450 50  0001 C CNN
	1    3750 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 1850 3400 2850
Wire Wire Line
	3400 2850 3600 2850
Connection ~ 3400 1850
Wire Wire Line
	3450 1900 3450 3050
Wire Wire Line
	3450 3050 3600 3050
Connection ~ 3450 1900
Wire Wire Line
	3500 1950 3500 3250
Wire Wire Line
	3500 3250 3600 3250
Connection ~ 3500 1950
Wire Wire Line
	3550 2000 3550 3450
Wire Wire Line
	3550 3450 3600 3450
Connection ~ 3550 2000
Wire Wire Line
	3900 2850 5150 2850
Wire Wire Line
	5150 2850 5150 4600
Wire Wire Line
	5150 4600 5800 4600
Wire Wire Line
	3900 3050 5100 3050
Wire Wire Line
	5100 3050 5100 4900
Wire Wire Line
	5100 4900 5800 4900
Wire Wire Line
	3900 3250 5050 3250
Wire Wire Line
	5050 3250 5050 5250
Wire Wire Line
	5050 5250 7200 5250
Wire Wire Line
	7200 5250 7200 4900
Wire Wire Line
	7200 4900 7100 4900
Wire Wire Line
	3900 3450 5000 3450
Wire Wire Line
	5000 3450 5000 5300
Wire Wire Line
	5000 5300 7250 5300
Wire Wire Line
	7250 5300 7250 4800
Wire Wire Line
	7250 4800 7100 4800
Wire Wire Line
	4100 2350 7200 2350
Connection ~ 4100 2350
Wire Wire Line
	4150 2300 7250 2300
Connection ~ 4150 2300
Wire Wire Line
	4200 2250 7300 2250
Connection ~ 4200 2250
Wire Wire Line
	4250 2200 7350 2200
Connection ~ 4250 2200
Wire Wire Line
	4300 2150 7400 2150
Connection ~ 4300 2150
Wire Wire Line
	4350 2100 7450 2100
Connection ~ 4350 2100
Wire Wire Line
	4400 2050 5200 2050
Connection ~ 4400 2050
$Comp
L Connector:Micro_SD_Card_Det J2
U 1 1 624914F2
P 9000 2050
F 0 "J2" H 8400 2750 50  0000 C CNN
F 1 "AE-MICRO-SD-DIP" H 9450 2750 50  0000 C CNN
F 2 "KUT_Connector:AE-MICRO-SD-DIP" H 11050 2750 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 9000 2150 50  0001 C CNN
	1    9000 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1750 7500 1750
Wire Wire Line
	7500 1750 7500 2450
Wire Wire Line
	7500 2450 5250 2450
Wire Wire Line
	5250 2450 5250 3700
Wire Wire Line
	5250 3700 5800 3700
Wire Wire Line
	8100 2050 7550 2050
Wire Wire Line
	7550 2050 7550 3800
Wire Wire Line
	7550 3800 7100 3800
Wire Wire Line
	8100 2250 7600 2250
Wire Wire Line
	7600 2250 7600 2500
Wire Wire Line
	7600 2500 5300 2500
Wire Wire Line
	5300 2500 5300 4700
Wire Wire Line
	5300 4700 5800 4700
Wire Wire Line
	8100 1850 7650 1850
Wire Wire Line
	7650 1850 7650 4700
Wire Wire Line
	7650 4700 7100 4700
$Comp
L power:+3.3V #PWR08
U 1 1 624AFBD8
P 7900 1300
F 0 "#PWR08" H 7900 1150 50  0001 C CNN
F 1 "+3.3V" H 7915 1473 50  0000 C CNN
F 2 "" H 7900 1300 50  0001 C CNN
F 3 "" H 7900 1300 50  0001 C CNN
	1    7900 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 1300 7900 1950
Wire Wire Line
	7900 1950 8100 1950
$Comp
L power:GND #PWR09
U 1 1 624B47B0
P 7900 2750
F 0 "#PWR09" H 7900 2500 50  0001 C CNN
F 1 "GND" H 7905 2577 50  0000 C CNN
F 2 "" H 7900 2750 50  0001 C CNN
F 3 "" H 7900 2750 50  0001 C CNN
	1    7900 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 2150 7900 2150
Wire Wire Line
	7900 2150 7900 2750
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 624BABC1
P 2150 4200
F 0 "J1" H 2250 4550 50  0000 C CNN
F 1 "ICSP" H 2050 4550 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Horizontal" H 2150 4200 50  0001 C CNN
F 3 "~" H 2150 4200 50  0001 C CNN
	1    2150 4200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2350 4000 2700 4000
Wire Wire Line
	2700 4000 2700 3600
Wire Wire Line
	2700 3600 3150 3600
$Comp
L power:+3.3V #PWR01
U 1 1 624C4195
P 2500 3150
F 0 "#PWR01" H 2500 3000 50  0001 C CNN
F 1 "+3.3V" H 2515 3323 50  0000 C CNN
F 2 "" H 2500 3150 50  0001 C CNN
F 3 "" H 2500 3150 50  0001 C CNN
	1    2500 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 4100 2500 4100
Wire Wire Line
	2350 4200 2500 4200
Wire Wire Line
	3250 4200 3250 4300
Wire Wire Line
	3250 4300 3550 4300
Wire Wire Line
	2350 4300 2800 4300
Wire Wire Line
	2800 4300 2800 3900
Wire Wire Line
	2350 4400 2850 4400
Wire Wire Line
	2850 4400 2850 4000
$Comp
L power:GND #PWR02
U 1 1 624E3DAF
P 2500 4600
F 0 "#PWR02" H 2500 4350 50  0001 C CNN
F 1 "GND" H 2505 4427 50  0000 C CNN
F 2 "" H 2500 4600 50  0001 C CNN
F 3 "" H 2500 4600 50  0001 C CNN
	1    2500 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 4600 2500 4200
Connection ~ 2500 4200
Wire Wire Line
	2500 4200 3250 4200
$Comp
L vsrAkizuki:MRUSB-2B-D14NI-S306 J3
U 1 1 624F16B1
P 1400 6400
F 0 "J3" H 1457 6867 50  0000 C CNN
F 1 "MRUSB-2B-D14NI-S306" H 1457 6776 50  0000 C CNN
F 2 "vsrAkizuki:MRUSB-2B-D14NI-S306" H 1550 6350 50  0001 C CNN
F 3 "" H 1550 6350 50  0001 C CNN
	1    1400 6400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 62515FB8
P 2800 6600
F 0 "C5" H 2915 6646 50  0000 L CNN
F 1 "10uF" H 2915 6555 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L4.0mm_W2.5mm_P2.50mm" H 2838 6450 50  0001 C CNN
F 3 "~" H 2800 6600 50  0001 C CNN
	1    2800 6600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 62516F30
P 3750 6600
F 0 "C6" H 3865 6646 50  0000 L CNN
F 1 "10uF" H 3865 6555 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L4.0mm_W2.5mm_P2.50mm" H 3788 6450 50  0001 C CNN
F 3 "~" H 3750 6600 50  0001 C CNN
	1    3750 6600
	1    0    0    -1  
$EndComp
$Comp
L Memory_RAM2:SLIDE_SWITCH_3P S2
U 1 1 6251FF27
P 2450 6100
F 0 "S2" H 2450 6165 50  0000 C CNN
F 1 "OFF    ON" H 2450 6074 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2450 6125 50  0001 C CNN
F 3 "" H 2450 6125 50  0001 C CNN
	1    2450 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 6300 2250 6300
Wire Wire Line
	2450 6450 2800 6450
Wire Wire Line
	2800 6450 2800 6300
Wire Wire Line
	2800 6300 2950 6300
Connection ~ 2800 6450
Wire Wire Line
	1700 6500 2000 6500
Wire Wire Line
	2000 6500 2000 6850
Wire Wire Line
	2000 6850 2800 6850
Wire Wire Line
	2800 6850 2800 6750
Wire Wire Line
	2800 6850 3250 6850
Wire Wire Line
	3250 6850 3250 6600
Connection ~ 2800 6850
Wire Wire Line
	3250 6850 3750 6850
Wire Wire Line
	3750 6850 3750 6750
Connection ~ 3250 6850
Wire Wire Line
	3550 6300 3750 6300
Wire Wire Line
	3750 6300 3750 6450
$Comp
L power:GND #PWR015
U 1 1 6255D9C5
P 3750 7050
F 0 "#PWR015" H 3750 6800 50  0001 C CNN
F 1 "GND" H 3755 6877 50  0000 C CNN
F 2 "" H 3750 7050 50  0001 C CNN
F 3 "" H 3750 7050 50  0001 C CNN
	1    3750 7050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR014
U 1 1 6255E105
P 3750 6150
F 0 "#PWR014" H 3750 6000 50  0001 C CNN
F 1 "+3.3V" H 3765 6323 50  0000 C CNN
F 2 "" H 3750 6150 50  0001 C CNN
F 3 "" H 3750 6150 50  0001 C CNN
	1    3750 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 6150 3750 6300
Connection ~ 3750 6300
Wire Wire Line
	3750 6850 3750 7050
Connection ~ 3750 6850
$Comp
L Device:Speaker LS1
U 1 1 6256C062
P 5750 5900
F 0 "LS1" H 5920 5896 50  0000 L CNN
F 1 "Speaker" H 5920 5805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-5-2" H 5750 5700 50  0001 C CNN
F 3 "~" H 5740 5850 50  0001 C CNN
	1    5750 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3800 5350 3800
Wire Wire Line
	5350 3800 5350 5900
Wire Wire Line
	5350 5900 5550 5900
$Comp
L power:GND #PWR07
U 1 1 6257C212
P 5350 6100
F 0 "#PWR07" H 5350 5850 50  0001 C CNN
F 1 "GND" H 5355 5927 50  0000 C CNN
F 2 "" H 5350 6100 50  0001 C CNN
F 3 "" H 5350 6100 50  0001 C CNN
	1    5350 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 6000 5350 6000
Wire Wire Line
	5350 6000 5350 6100
$Comp
L Device:R R6
U 1 1 62583A7A
P 5050 5900
F 0 "R6" V 4950 5800 50  0000 C CNN
F 1 "10k" V 4950 6000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4980 5900 50  0001 C CNN
F 3 "~" H 5050 5900 50  0001 C CNN
	1    5050 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 5900 5350 5900
Connection ~ 5350 5900
$Comp
L power:GND #PWR06
U 1 1 6258B274
P 4750 6100
F 0 "#PWR06" H 4750 5850 50  0001 C CNN
F 1 "GND" H 4755 5927 50  0000 C CNN
F 2 "" H 4750 6100 50  0001 C CNN
F 3 "" H 4750 6100 50  0001 C CNN
	1    4750 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5900 4750 5900
Wire Wire Line
	4750 5900 4750 6100
$Comp
L Device:C C3
U 1 1 625948B1
P 7950 3600
F 0 "C3" V 8202 3600 50  0000 C CNN
F 1 "0.1uF" V 8111 3600 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L4.0mm_W2.5mm_P2.50mm" H 7988 3450 50  0001 C CNN
F 3 "~" H 7950 3600 50  0001 C CNN
	1    7950 3600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 625AA2ED
P 7950 4400
F 0 "C4" V 7800 4550 50  0000 C CNN
F 1 "0.1uF" V 7800 4300 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L4.0mm_W2.5mm_P2.50mm" H 7988 4250 50  0001 C CNN
F 3 "~" H 7950 4400 50  0001 C CNN
	1    7950 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7100 3600 7750 3600
Wire Wire Line
	7100 3700 8100 3700
Wire Wire Line
	8100 3700 8100 3600
Wire Wire Line
	7100 4400 7800 4400
Wire Wire Line
	7100 4500 8100 4500
Wire Wire Line
	8100 4500 8100 4400
$Comp
L power:GND #PWR010
U 1 1 625DA01F
P 8300 3650
F 0 "#PWR010" H 8300 3400 50  0001 C CNN
F 1 "GND" H 8305 3477 50  0000 C CNN
F 2 "" H 8300 3650 50  0001 C CNN
F 3 "" H 8300 3650 50  0001 C CNN
	1    8300 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 625DA8C7
P 8300 5050
F 0 "#PWR011" H 8300 4800 50  0001 C CNN
F 1 "GND" H 8305 4877 50  0000 C CNN
F 2 "" H 8300 5050 50  0001 C CNN
F 3 "" H 8300 5050 50  0001 C CNN
	1    8300 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3600 8300 3600
Connection ~ 8100 3600
Wire Wire Line
	8100 4400 8300 4400
Connection ~ 8100 4400
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J4
U 1 1 625EBD3D
P 9200 4150
F 0 "J4" V 9296 3762 50  0000 R CNN
F 1 "KeyBoard ZK-80-KB" V 9205 3762 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x07_P2.54mm_Vertical" H 9200 4150 50  0001 C CNN
F 3 "~" H 9200 4150 50  0001 C CNN
	1    9200 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 4400 5400 4400
Wire Wire Line
	5400 4400 5400 5350
Wire Wire Line
	5400 5350 8900 5350
Wire Wire Line
	8900 5350 8900 4350
Wire Wire Line
	5800 4500 5450 4500
Wire Wire Line
	5450 4500 5450 5400
Wire Wire Line
	5450 5400 8750 5400
Wire Wire Line
	8750 5400 8750 3750
Wire Wire Line
	8750 3750 8900 3750
Wire Wire Line
	8900 3750 8900 3850
Wire Wire Line
	5800 4100 5500 4100
Wire Wire Line
	5500 4100 5500 5450
Wire Wire Line
	5500 5450 9000 5450
Wire Wire Line
	9000 5450 9000 4350
Wire Wire Line
	5750 4000 5750 3150
Wire Wire Line
	5750 3150 9000 3150
Wire Wire Line
	9000 3150 9000 3850
Connection ~ 5750 4000
Wire Wire Line
	5750 4000 5800 4000
Wire Wire Line
	8700 3900 8700 4500
Wire Wire Line
	8700 4500 9100 4500
Wire Wire Line
	9100 4500 9100 4350
Wire Wire Line
	8300 3600 8300 3650
Wire Wire Line
	8650 4000 8650 3700
Wire Wire Line
	8650 3700 9100 3700
Wire Wire Line
	9100 3700 9100 3850
Wire Wire Line
	8650 4100 8650 4550
Wire Wire Line
	8650 4550 9200 4550
Wire Wire Line
	9200 4550 9200 4350
Wire Wire Line
	8600 4200 8600 3650
Wire Wire Line
	8600 3650 9200 3650
Wire Wire Line
	9200 3650 9200 3850
Wire Wire Line
	8600 4300 8600 4600
Wire Wire Line
	8600 4600 9300 4600
Wire Wire Line
	9300 4600 9300 4350
Wire Wire Line
	8300 4400 8300 5050
Wire Wire Line
	8550 4600 8550 3600
Wire Wire Line
	8550 3600 9300 3600
Wire Wire Line
	9300 3600 9300 3850
Wire Wire Line
	5700 3900 5700 3100
Wire Wire Line
	5700 3100 8500 3100
Wire Wire Line
	8500 3100 8500 4650
Wire Wire Line
	8500 4650 9400 4650
Wire Wire Line
	9400 4650 9400 4350
Connection ~ 5700 3900
Wire Wire Line
	5700 3900 5800 3900
Wire Wire Line
	5650 3600 5650 3050
Wire Wire Line
	5650 3050 9500 3050
Wire Wire Line
	9500 3050 9500 3850
Connection ~ 5650 3600
Wire Wire Line
	5650 3600 5800 3600
$Comp
L power:GND #PWR012
U 1 1 6275D7FE
P 9500 4750
F 0 "#PWR012" H 9500 4500 50  0001 C CNN
F 1 "GND" H 9505 4577 50  0000 C CNN
F 2 "" H 9500 4750 50  0001 C CNN
F 3 "" H 9500 4750 50  0001 C CNN
	1    9500 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 4350 9500 4750
$Comp
L Memory_RAM2:SLIDE_SWITCH_3P S1
U 1 1 6276B9BC
P 4400 4550
F 0 "S1" H 4400 4615 50  0000 C CNN
F 1 "STEP   AUTO" H 4400 4524 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4400 4575 50  0001 C CNN
F 3 "" H 4400 4575 50  0001 C CNN
	1    4400 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4200 4950 4200
Wire Wire Line
	4950 4200 4950 5050
Wire Wire Line
	4950 5050 4400 5050
Wire Wire Line
	4400 5050 4400 4900
$Comp
L power:GND #PWR05
U 1 1 6277A228
P 4100 4900
F 0 "#PWR05" H 4100 4650 50  0001 C CNN
F 1 "GND" H 4105 4727 50  0000 C CNN
F 2 "" H 4100 4900 50  0001 C CNN
F 3 "" H 4100 4900 50  0001 C CNN
	1    4100 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4750 4100 4750
Wire Wire Line
	4100 4750 4100 4900
$Comp
L Device:R R7
U 1 1 6278C7B4
P 9800 5050
F 0 "R7" V 9700 4950 50  0000 C CNN
F 1 "10k" V 9700 5150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9730 5050 50  0001 C CNN
F 3 "~" H 9800 5050 50  0001 C CNN
	1    9800 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 6278CAFE
P 10000 5050
F 0 "R8" V 9900 4950 50  0000 C CNN
F 1 "10k" V 9900 5150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9930 5050 50  0001 C CNN
F 3 "~" H 10000 5050 50  0001 C CNN
	1    10000 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 6278CB08
P 10200 5050
F 0 "R9" V 10100 4950 50  0000 C CNN
F 1 "10k" V 10100 5150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 10130 5050 50  0001 C CNN
F 3 "~" H 10200 5050 50  0001 C CNN
	1    10200 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 5350 9800 5350
Wire Wire Line
	9800 5350 9800 5200
Connection ~ 8900 5350
Wire Wire Line
	8750 5400 10000 5400
Wire Wire Line
	10000 5400 10000 5200
Connection ~ 8750 5400
Wire Wire Line
	9000 5450 10200 5450
Wire Wire Line
	10200 5450 10200 5200
Connection ~ 9000 5450
$Comp
L power:+3.3V #PWR013
U 1 1 627FEFD8
P 10200 4650
F 0 "#PWR013" H 10200 4500 50  0001 C CNN
F 1 "+3.3V" H 10215 4823 50  0000 C CNN
F 2 "" H 10200 4650 50  0001 C CNN
F 3 "" H 10200 4650 50  0001 C CNN
	1    10200 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 4650 10200 4800
Wire Wire Line
	10200 4800 10000 4800
Wire Wire Line
	10000 4800 10000 4900
Connection ~ 10200 4800
Wire Wire Line
	10200 4800 10200 4900
Wire Wire Line
	10000 4800 9800 4800
Wire Wire Line
	9800 4800 9800 4900
Connection ~ 10000 4800
$Comp
L Device:R R1
U 1 1 6282C0D9
P 2850 3450
F 0 "R1" V 2750 3350 50  0000 C CNN
F 1 "330" V 2750 3550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2780 3450 50  0001 C CNN
F 3 "~" H 2850 3450 50  0001 C CNN
	1    2850 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 3150 2500 3450
Wire Wire Line
	2700 3450 2500 3450
Connection ~ 2500 3450
Wire Wire Line
	2500 3450 2500 4100
Wire Wire Line
	3000 3450 3150 3450
Wire Wire Line
	3150 3450 3150 3600
Connection ~ 3150 3600
Wire Wire Line
	3150 3600 5650 3600
$Comp
L Device:C C2
U 1 1 628850DF
P 3550 5250
F 0 "C2" H 3665 5296 50  0000 L CNN
F 1 "0.1uF" H 3665 5205 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L4.0mm_W2.5mm_P2.50mm" H 3588 5100 50  0001 C CNN
F 3 "~" H 3550 5250 50  0001 C CNN
	1    3550 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 628866E3
P 2950 4950
F 0 "C1" H 3068 4996 50  0000 L CNN
F 1 "10uF" H 3068 4905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 2988 4800 50  0001 C CNN
F 3 "~" H 2950 4950 50  0001 C CNN
	1    2950 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3900 4050 3900
Wire Wire Line
	2500 4100 2950 4100
Wire Wire Line
	2950 4100 2950 4800
Connection ~ 2500 4100
Wire Wire Line
	3250 4300 3250 5200
Wire Wire Line
	3250 5200 2950 5200
Wire Wire Line
	2950 5200 2950 5100
Connection ~ 3250 4300
$Comp
L power:GND #PWR04
U 1 1 628EF2D4
P 3250 5300
F 0 "#PWR04" H 3250 5050 50  0001 C CNN
F 1 "GND" H 3255 5127 50  0000 C CNN
F 2 "" H 3250 5300 50  0001 C CNN
F 3 "" H 3250 5300 50  0001 C CNN
	1    3250 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5200 3250 5300
Connection ~ 3250 5200
Wire Wire Line
	3550 5100 3550 4300
Connection ~ 3550 4300
Wire Wire Line
	3550 4300 5800 4300
Wire Wire Line
	5800 4800 5150 4800
Wire Wire Line
	5150 4800 5150 5550
Wire Wire Line
	5150 5550 3550 5550
Wire Wire Line
	3550 5550 3550 5400
$Comp
L power:+3.3V #PWR03
U 1 1 6293CF99
P 2650 5350
F 0 "#PWR03" H 2650 5200 50  0001 C CNN
F 1 "+3.3V" H 2665 5523 50  0000 C CNN
F 2 "" H 2650 5350 50  0001 C CNN
F 3 "" H 2650 5350 50  0001 C CNN
	1    2650 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 5350 2650 5550
Wire Wire Line
	2650 5550 3550 5550
Connection ~ 3550 5550
NoConn ~ 2650 6300
NoConn ~ 9400 3850
NoConn ~ 8100 2350
NoConn ~ 8100 2450
NoConn ~ 8100 2550
NoConn ~ 9800 2550
NoConn ~ 4600 4750
NoConn ~ 8100 1650
NoConn ~ 2350 4500
$Comp
L power:+3.3V #PWR0101
U 1 1 624B9E0E
P 7750 3400
F 0 "#PWR0101" H 7750 3250 50  0001 C CNN
F 1 "+3.3V" H 7765 3573 50  0000 C CNN
F 2 "" H 7750 3400 50  0001 C CNN
F 3 "" H 7750 3400 50  0001 C CNN
	1    7750 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3400 7750 3600
Connection ~ 7750 3600
Wire Wire Line
	7750 3600 7800 3600
$Comp
L Memory_RAM2:PIC32MX170F256B U3
U 1 1 625FE804
P 6450 4600
F 0 "U3" H 6450 5967 50  0000 C CNN
F 1 "PIC32MX150F128B" H 6450 5876 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm_LongPads" H 6600 6050 50  0001 L CNN
F 3 "" H 6450 4400 50  0001 C CNN
	1    6450 4600
	1    0    0    -1  
$EndComp
$Comp
L Memory_RAM2:7333-A U4
U 1 1 62645E33
P 3250 6300
F 0 "U4" H 3250 6542 50  0000 C CNN
F 1 "7333-A" H 3250 6451 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 3275 6150 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 3250 6250 50  0001 C CNN
	1    3250 6300
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6264958B
P 2800 5950
F 0 "#FLG0101" H 2800 6025 50  0001 C CNN
F 1 "PWR_FLAG" H 2800 6123 50  0000 C CNN
F 2 "" H 2800 5950 50  0001 C CNN
F 3 "~" H 2800 5950 50  0001 C CNN
	1    2800 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 5950 2800 6300
Connection ~ 2800 6300
Wire Wire Line
	2850 4000 5200 4000
Wire Wire Line
	4050 2400 4050 3900
Connection ~ 4050 2400
Connection ~ 4050 3900
Wire Wire Line
	4050 3900 5700 3900
Wire Wire Line
	5200 2050 5200 4000
Connection ~ 5200 4000
Wire Wire Line
	5200 4000 5750 4000
Wire Wire Line
	7100 3900 7450 3900
Wire Wire Line
	7200 2350 7200 4600
Wire Wire Line
	7200 4600 7100 4600
Connection ~ 7200 4600
Wire Wire Line
	7200 4600 8550 4600
Wire Wire Line
	7450 2100 7450 3900
Connection ~ 7450 3900
Wire Wire Line
	7450 3900 8700 3900
Wire Wire Line
	7100 4000 7400 4000
Wire Wire Line
	7250 2300 7250 4300
Connection ~ 7250 4300
Wire Wire Line
	7250 4300 7100 4300
Wire Wire Line
	7250 4300 8600 4300
Wire Wire Line
	7400 2150 7400 4000
Connection ~ 7400 4000
Wire Wire Line
	7400 4000 8650 4000
Wire Wire Line
	7100 4200 7300 4200
Wire Wire Line
	7100 4100 7350 4100
Wire Wire Line
	7300 2250 7300 4200
Connection ~ 7300 4200
Wire Wire Line
	7300 4200 8600 4200
Wire Wire Line
	7350 2200 7350 4100
Connection ~ 7350 4100
Wire Wire Line
	7350 4100 8650 4100
$EndSCHEMATC
