#include <NewPing.h>
#include <FastLED.h>

// Set all USR pins
#define TRIGGER_PIN_1  12  
#define ECHO_PIN_1     11
#define TRIGGER_PIN_2  10  
#define ECHO_PIN_2     9
#define TRIGGER_PIN_3  8  
#define ECHO_PIN_3     7  
#define MAX_DISTANCE 90
#define ESTIMATED_MAX 10

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);

// Set all LED Pins
// To add more rows, define new pins for each row and increase NUM_STRIPS
// This example would show a 2x9 LED matrix
#define LED_PIN_1     6
#define LED_PIN_2     5
#define NUM_STRIPS 2
#define NUM_LEDS_PER_STRIP 9
#define COLOR_ORDER   GRB
#define BRIGHTNESS  150
#define LED_TYPE    WS2811
#define UPDATES_PER_SECOND 100
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;



void setup() {
  // Must add a new FastLED.addLeds for every new row added
  FastLED.addLeds<LED_TYPE, LED_PIN_1, COLOR_ORDER>(leds[0], NUM_LEDS_PER_STRIP).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN_2, COLOR_ORDER>(leds[1], NUM_LEDS_PER_STRIP).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowStripeColors_p;
  currentBlending = NOBLEND;
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
}

void loop() {
  int ping1 = sonar1.ping_cm();
  int ping2 = sonar2.ping_cm();
  int ping3 = sonar3.ping_cm();
  Serial.println("Ping 1:");
  Serial.println(ping1);
  Serial.println("Ping 2:");
  Serial.println(ping2);
  Serial.println("Ping 3:");
  Serial.println(ping3);

  int ping1Color = map(ping1 % ESTIMATED_MAX, 0, ESTIMATED_MAX, 10, 255);
  int ping2Color = map(ping2 % ESTIMATED_MAX, 0, ESTIMATED_MAX, 10, 255);
  int ping3Color = map(ping3 % ESTIMATED_MAX, 0, ESTIMATED_MAX, 10, 255);

  for(int i = 0; i < NUM_STRIPS; i++){
    fill_gradient(leds[i],0,CHSV(ping1Color,ping2Color,ping3Color), NUM_LEDS_PER_STRIP,CHSV(255 - ping1Color,255 - ping2Color,255 - ping3Color),SHORTEST_HUES); 
  }

  FastLED.show();
  delay(2000);
}
