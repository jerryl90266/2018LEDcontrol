/*
 * FRC Team 4201 LED State Switch 
 * 
  State change detection (edge detection)
  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.
  This example shows how to detect when a button or button changes from off to on
  and on to off.
  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10 kilohm resistor attached to pin 2 from ground
  - LED attached from pin 13 to ground (or use the built-in LED on most
    Arduino boards)
  created  27 Sep 2005
  modified 30 Aug 2011
  by Tom Igoe
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/ButtonStateChange
*/
// HARDWARE CONFIG
const int  buttonPin = 4;    // the pin that the pushbutton is attached to
const int ledBuiltin = 13;       // the pin that the LED is attached to
const int ledRed=3;
const int ledGreen=5;
const int ledBlue=6;
const int ledPin[6] = {3, 5, 6, 9, 10, 11};       // the pin that the LED is attached to
// STATES 
const int greenSolid=0;
const int redSolid=1;
const int blueSolid=2;
const int dark=3;

int ledState=dark;
int ledPrevState=dark;
int flashRate=0;
int intensity=128;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledBuiltin, OUTPUT);
  for(int i=0; i<6; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  ledState=dark;
  ledPrevState=dark;  
  flashRate=0;
  intensity=255;
  // initialize serial communication:
  Serial.begin(9600);
}

void setLED(int state) {
  if(state != ledPrevState) {
    Serial.println(state);
    ledPrevState=state;
  }
  switch(state) {
    case greenSolid:
      analogWrite(ledPin[ledRed], 0);
      analogWrite(ledPin[ledGreen], intensity);
      analogWrite(ledPin[ledBlue], 0);
      flashRate=0;
      break;
    case redSolid:
      analogWrite(ledPin[ledRed], intensity);
      analogWrite(ledPin[ledGreen], 0);
      analogWrite(ledPin[ledBlue], 0);
      flashRate=0;
      break;
    default:
      analogWrite(ledPin[ledRed], 0);
      analogWrite(ledPin[ledGreen], 0);
      analogWrite(ledPin[ledBlue], 0);
      flashRate=0;
      break;
  }
}

void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

  // turns on the builtin LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledBuiltin, HIGH);
    ledState=dark;
  } else {
    digitalWrite(ledBuiltin, LOW);
  }
  
  ledState = buttonPushCounter % 3;
  setLED(ledState);
    
}
