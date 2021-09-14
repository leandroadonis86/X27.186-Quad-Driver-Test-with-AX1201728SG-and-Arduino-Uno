/*
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
*/

typedef struct {
  int DIR;   // pin for CW/CCW, diretion
  int STEP;  // pin for f(scx), last and new position
  int ANGLE; // of 315 available
  int RANGE; // range operation, recommend: ANGLE * 3 * 4;
  int DELAY; // μs between steps
} mySteppers;

// stepper configs by default
const mySteppers stepper = {
  9, 8, 270, 270 * 3 * 4, 250
};

// get external analog values to process.
const int INPUTLEVEL = A5;

const int LED = 13; // Arduino embedded led blick check
const int RESET = 10; // pin for RESET

// must
int val;
int lastPos;
bool updating;

// only for istesting()
int steps;
bool testing;
bool forward;

void setup() {
    Serial.begin(9600);
  
    pinMode(stepper.DIR, OUTPUT);
    pinMode(stepper.STEP, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(RESET, OUTPUT);
  
    digitalWrite(RESET, LOW);
    digitalWrite(LED, HIGH);
    digitalWrite(stepper.STEP, LOW);
    digitalWrite(stepper.DIR, HIGH);
    delay(1);  // keep reset low min 1ms
    digitalWrite(RESET, HIGH);
  
    steps = 0;
    val = 0;
    lastPos = val;
    forward = true;
    testing = true;
    updating = true;
}

void loop() {
    // nice to have a test 1st if everything check and ok.
    istesting();
  
    getAnaloginput();
  
    // if input value had change from the last update.
    if (val != lastPos) {
      updating = true;
    } else {
      updating = false;
    }
  
    gofoward();
}

void gofoward() {
    // New inputlevel, need to move from last to new position.
    if (updating) {
      if (val > lastPos) {
        lastPos++;
        dorefresh(HIGH);
      }
      if (val < lastPos) {
        lastPos--;
        dorefresh(LOW);
      }
      // Delaying beetween steps.
      delayMicroseconds(stepper.DELAY);
    }
}

void dorefresh(int state) {
    // Refresh X27 positions. state: direction needed.
    digitalWrite(stepper.STEP, LOW);
    digitalWrite(stepper.DIR, state ? LOW : HIGH);
    digitalWrite(stepper.STEP, HIGH);
}

void istesting() {
    // Testing start.
    if (testing) {
      digitalWrite(stepper.STEP, LOW);
      
      steps++;
      if (steps > stepper.RANGE) {
        forward = !forward;
        steps = 0;
        digitalWrite(stepper.DIR, forward ? LOW : HIGH);
        digitalWrite(LED, forward ? HIGH : LOW);
        testing = false; // if true no stop for testing.
      }
      digitalWrite(stepper.STEP, HIGH);
      delayMicroseconds(stepper.DELAY);
    }
}

void getAnaloginput() {
    // Get input level from external and process it.
    val = analogRead(INPUTLEVEL);
    val = val * 3; // Exact calc for 10k resistence range.
    
    if (val < 0) val = 0;
    if (val > stepper.RANGE) val = stepper.RANGE;
    // Serial.println show the values but slow the updating speed. Use only for debug.
    //Serial.println(val);
}
