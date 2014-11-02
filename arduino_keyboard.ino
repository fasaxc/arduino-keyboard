/*
Reads digital inputs 2-9, debounces them using a shift register.  Outputs
char codes '0' - '7' on the serial line when the buttons are pushed.

Expects SPST pushbuttons connected between digital pins 2-9 and ground.
Uses the internal pull ups.
 */

unsigned int debounce[8] = {1,1,1,1, 1,1,1,1};
unsigned int repeat[8] = {0,0,0,0, 0,0,0,0};
byte output_vals[8] = {
  48,49,50,51,
  52,53,54,55
};


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // Enable internal pull-ups on the inputs.
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}


// the loop routine runs over and over again forever:
void loop() {
  int i;
  int val;
  
  // Loop over the pins, read them each in turn.
  for (i = 0; i < 8; i++) {
    val = digitalRead(i+2); // +2 because pins 0-1 are used for serial.
    
    // Shift register debouncer, feed 1-bit value in from the right.  Only
    // trigger a key press once the debouncer is full of 0s.
    debounce[i] = (debounce[i] << 1) | val;
    if (debounce[i] == 0) {  // Button down for whole debounce period.
      if (repeat[i] == 0){  
        Serial.write(output_vals[i]);
        repeat[i] = 40;  // Auto-repeat every 200 msec or so.
      }
      else
      {
        repeat[i] -= 1; 
      }
    }
    else
    {
      repeat[i] = 0;
    }
  }
  delay(6);
}



