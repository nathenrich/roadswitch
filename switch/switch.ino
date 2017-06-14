const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin1 = 3;      // the number of the LED pin
const int ledPin2 = 4;      // the number of the LED pin
const int ledPin3 = 0;      // the number of the LED pin
const int ledPin4 = 1;      // the number of the LED

// Variables will change:
int ledState1 = HIGH;         // the current state of the output pin
int ledState2 = LOW;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 80;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  // somthing extra

  // set initial LED state
  digitalWrite(ledPin1, ledState1);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState1 = !ledState1;
        ledState2 = !ledState2;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);

  digitalWrite(ledPin3, ledState1);
  digitalWrite(ledPin4, ledState2);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
