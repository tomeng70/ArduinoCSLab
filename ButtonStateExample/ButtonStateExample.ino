/*
 * This sketch demonstrates how to use
 * state variables to track the state
 * of a system.
 */

#define LED1 6
#define BUTTON1 7

enum LED_STATE {OFF, ON, BLINKING};

LED_STATE currLED1;
bool prevButton1;
bool currButton1;

// in INPUT_PULLUP mode, if the signal is HIGH
// then the button is unpressed.
bool isPressed(int pin) {
  if (digitalRead(pin) == LOW) {
    return true;
  } else {
    return false;
  }
}

// this method checks the system to see 
// if its state should change.
void checkState() {
  // check button 1.
  currButton1 = isPressed(BUTTON1);
  if (currButton1 == true && prevButton1 == false) {
    // button 1 was just pressed (transitioned from unpressed to pressed).
    // update button state info.
    Serial.println("Button 1 was just pressed!");
    prevButton1 = currButton1;

    // change the state of the LED.
    if(currLED1 == OFF) {
      // switch from off to on.
      currLED1 = ON;
      Serial.println("LED1 switched to ON!");
    } else {
      // toggle to LED off.
      currLED1 = OFF;
      Serial.println("LED1 switched to OFF!");
    }
  } else if (currButton1 == false && currButton1 != prevButton1) {
    // button 1 was just released.
    // update button state info.
    prevButton1 = currButton1;
    Serial.println("Button 1 was just released!");
    Serial.println("");
  } 
}

void updateLEDs() {
  // check LED1.
  if (currLED1 == ON) {
    digitalWrite(LED1, ON);
  } else if (currLED1 == OFF) {
    digitalWrite(LED1, OFF);
  }
}

void setup() {
  // initialize pins.
  pinMode(LED1, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);

  // set the LEDs to off.
  digitalWrite(LED1, LOW);
  currLED1 = OFF;

  // check set initial state to unpressed.
  prevButton1 = false;

  // enable serial connection.
  Serial.begin(9600);
}

void loop() {
  // do we need to update the state of the system?
  checkState();

  // update the LEDs based on the state of the system.
  updateLEDs();
}
