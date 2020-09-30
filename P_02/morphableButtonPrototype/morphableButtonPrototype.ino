#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

const int buttonPin = 10;

const int rs = 12, en = 11, d4 = 8, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int rPin= 7;
int gPin = 6;
int bPin = 5;

int MAXPOINTS = 100;
int DELAYDURATION = 1000;

int points = 0;
int prevLevel = 0;



void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
 
  lcd.begin(16, 2);

  Serial.begin(9600);
}

void loop() {
  // When the button is being pressed, either held down or clicked rapidly, points will go up.
  // When the button is not being pressed for a period of time, the points will deteriorate.
  // In our final design, the button itself would morph its appearance to number of points/level the user has
  // This program simulates that by changing an LED's color

  int buttonVal = digitalRead(buttonPin);
  
  if(buttonVal == LOW){ // Since we are using an internal pull- up resistor, a press is LOW and a non-press is HIGH
    points = points + 5;
  }else{
    points = points - 5;
  }

  Serial.println(points);
  
  // Want it to go towards red when losing points, and towards blue when gaining points
  int rVal;
  int bVal;
  
  if(points < 0 ){
    rVal = map(0 - points, 0, MAXPOINTS, 150, 255);
    bVal = map(0 - points, 0, MAXPOINTS, 50, 0);
  }else {
    rVal = 0;
    bVal = map(points, 0, MAXPOINTS, 0, 255);
  }
  
  RGB_color(rVal, 0, bVal);

  lcd.setCursor(0,0);
  
  int currLevel = points / 20;
  if(currLevel > prevLevel){
    lcd.print("Level ");
    lcd.print(currLevel);
    lcd.print(" Unlocked          "); // Populate ends with whitespace  
  } else if (currLevel < prevLevel) {
    lcd.print("Dropped to ");
    lcd.print(currLevel);
    lcd.print("             "); // Populate ends with whitespace  
  }
  
  lcd.setCursor(0,1);
  lcd.print("Points: ");
  lcd.print(points);
  lcd.print("          "); // Populate ends with whitespace

  prevLevel = points / 20;

  delay(DELAYDURATION);

}

// RBG_color function from Aqib on Arduino Project Hub
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(rPin, red_light_value);
  analogWrite(gPin, green_light_value);
  analogWrite(bPin, blue_light_value);
}
