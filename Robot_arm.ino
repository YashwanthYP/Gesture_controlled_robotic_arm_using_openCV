#include <Servo.h>
#define numofValsRec 5
#define digitsPerValRec 1

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numofValsRec];
int stringLength = numofValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;

void setup() {
  Serial.begin(9600);
  servoThumb.attach(5);
  servoIndex.attach(8);
  servoMiddle.attach(9);
  servoRing.attach(10);
  servoPinky.attach(6);
}

void receieveData() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '$') {
      counterStart = true;
    }
    if (counterStart) {
      if (counter < stringLength) {
        receivedString = String(receivedString + c);
        counter++;
      }
      if (counter >= stringLength) {
        for (int i = 0; i < numofValsRec; i++) {
          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void loop() {

  receieveData();
  if (valsRec[0] == 0) {
    servoThumb.write(180);
  } else {
    servoThumb.write(0);
  }
  if (valsRec[1] == 1) {
    servoIndex.write(180);
  } else {
    servoIndex.write(0);
  }
  if (valsRec[2] == 1) {
    servoMiddle.write(180);
  } else {
    servoMiddle.write(0);
  }
  if (valsRec[3] == 1) {
    servoRing.write(180);
  } else {
    servoRing.write(0);
  }
  if (valsRec[4] == 1) {
    servoPinky.write(180);
  } else {
    servoPinky.write(0);
  }
}
