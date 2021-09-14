# X27.186 Quad Driver Test with AX1201728SG and Arduino Uno

Small and basic .ino file for testing X27.186 Quad Driver Test with AX1201728SG Driver Controler using Arduino Uno. This was inspired from another project https://github.com/clearwater/SwitecX25/tree/X12 but I did myself this code just to have the base to operate with it.

"
X27 Quad Driver Test
Drive the motor forward and backwards through 315 degrees
at constant speed.

Model: X27.168
Axial Force Maximum: 150N
Axial Pull Force Maximum: 100N
Radial Force Maximum: 12N
Rotation Angle Maximum: 315°
Coil Resistance: 260 ohm
General Tolerance: ± 0.1 / ± 5°
Rotation Angle Maximum: ~315°
600 steps per 'rotation' (315 degree rotation)

AX1201728SG Driver Controler
1: VDD      15: VDD
2: CWCCW_B  16: CWCWW_D
3: Fscx_B   17: Fscx_D
4: OUT3_A   18: OUT3_C
5: OUT4_A   19: OUT4_C
6: OUT2_A   20: OUT2_C
7: OUT1_A   21: OUT1_C
8: OUT1_D   22: OUT1_B
9: OUT2_D   23: OUT2_B
10: OUT4_D  24: OUT4_B
11: OUT3_D  25: OUT3_B
12: VSS     26: RESET
13: CWCCW_C 27: CWCWW_A
14: Fscx_C  28: Fscx_A

Arduino Uno with Arduino 1.8.16 IDE

inspired from: https://guy.carpenter.id.au/gaugette/2017/04/29/switecx25-quad-driver-tests/
coded by: Leandro Silva, 12/09/2021
"
