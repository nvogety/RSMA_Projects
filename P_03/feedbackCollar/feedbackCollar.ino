int incomingByte = 0;
const int buzzer = 9;

int runningSum = 0;
int skip = 0;
int interval = 4;

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    
    // read the incoming byte:
    incomingByte = Serial.read();
    
    if(incomingByte == 112 || incomingByte == 110){ // otherwise, Read would register a '0' automatically so have to prune
      
      if(incomingByte == 112){ // code for 'p'
        runningSum += 1;
        Serial.println("Positive vote recieved");
      }else{ // code for 'n'
        runningSum -= 1;
        Serial.println("Negative vote recieved");
      }
      
      skip += 1;
 
      if(skip == interval){
        if(runningSum < 0) {
          Serial.println("Majority negative votes....ZAP!");
          tone(buzzer, 1000);
          delay(1000);
          noTone(buzzer); 
          delay(500);
          runningSum = 0;
        }
        skip = 0;
      }
    }
    

    delay(500);
    
  }
}
