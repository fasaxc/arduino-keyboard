/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
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
  
  // make the pushbutton's pin an input:
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
  
  for (i = 0; i < 8; i++) {
    val = digitalRead(i+2);
    debounce[i] = (debounce[i] << 1) | val;
    if (debounce[i] == 0) {  // normally high.
      if (repeat[i] == 0){
        Serial.write(output_vals[i]);
        repeat[i] = 40;
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



