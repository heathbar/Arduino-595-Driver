// 595 SHIFT REGISTER TEST

const int dataPin = 4;
const int latchPin = 5;
const int clockPin = 6;
const int resetPin = 7;
const int num_outputs = 20;  // number of 595 pins that are connected to some output (LEDs)
unsigned long out_data = 0; // each bit holds the status of an output pin, so if you have more outputs than there are bits in a long you will have a problem


void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(dataPin, OUTPUT);  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  
  digitalWrite(resetPin, HIGH);
  Serial.begin(9600);
  Serial.println("reset");
}

void loop() {
  
  for (int i=0; i<3; i++){
    for (int j=0; j<num_outputs; j++){
      setHigh(j);
      update();
      delay(300);      
    }
    for (int j=0; j<num_outputs; j++){
      setLow(j);
      update();
      delay(300);      
    }
  }
}


void setHigh(int bitpos){
  out_data |= ((long)1 << bitpos);
}

void setLow(int bitpos){
  out_data &= ~((long)1 << bitpos);
}



// This method sends bits to the shift register:
void update() {


  for (int i=0; i < num_outputs; i++){
 
    digitalWrite(dataPin, (out_data >> (num_outputs - i)) & 1);
    
    // pulse the clock
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    
  }
  
  // pulse low to latch the data
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);

}
