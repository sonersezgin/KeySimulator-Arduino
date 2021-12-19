# KeySimulator-Arduino
Key Simulator Arduino, button detect and serial send

It is intended to suport up to 8 pins but implementation is just for 2 pins
You may add more pins as you need.

Button press have states. IDLE, 1STPRESS, DEBOOUNCE, PRESSED
Serial char is sent by pressed, cancel is not possible once you press the button.

//Button definition
#define PIN1  12
#define PIN2  14

//Add buttons to array
BtPins[0] = PIN1;
BtPins[1] = PIN2;

//Input setup, if you have external pull up use only INPUT keyword.
pinMode(BtPins[0], INPUT_PULLUP);
pinMode(BtPins[0], INPUT_PULLUP);

//Serial send, change hex value depending on your pin configuration
Serial.write(0x01);