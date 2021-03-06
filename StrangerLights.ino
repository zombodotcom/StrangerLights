//original neopixels version https://create.arduino.cc/projecthub/3Derp/programmable-stranger-things-light-wall-costume-eaa668
// original code by Michael Barretta
//Edited for FastLED, Optimized and Added Numbers.
//Created by Zombodotcom

#include <FastLED.h>
#define DATA_PIN 3
#define COLOR_ORDER RGB

#define ONDELAY 750
#define OFFDELAY 500
#define NUM_LEDS 60
int mode=0;


String txtMsg = "/";    // Initialize default string for incoming text
CRGB leds[NUM_LEDS];

// Array to transpose incoming ascii positions to corresponding positions in light fixture
const int charPos[36] {
  6, //A
  7, //B
  8, //C
  9, //D
  10, //E
  11, //F
  12, //G
  13, //H
  22, //I
  21, //J
  20, //K
  19, //L
  18, //M
  17, //N
  16, //O
  15, //P
  14, //Q
  23, //R
  24, //S
  25, //T
  26, //U
  27, //V
  28, //W
  29, //X
  30, //Y
  31, //z


};
// number array 
const int numPos[11] {
  32,//0
  33,//1
  34,//2
  35,//3
  36,//4
  37,//5
  38,//6
  39,//7
  40,//8
  41,//9
  0// space

};

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); //setting up the FastLED
  FastLED.clear();
  FastLED.show();
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

// Program to step through string character by character and perform an action
void printChar(String input) {
  
  for (int i = 0; i < input.length(); i++) {
    //find the value of the character
    int let = ((int)input[i]);

    //if it is a space , go to the space position of the LEDS in this first draft it is in the numPos Array at 10  
    if (let == 32) {
    leds[numPos[10]] = CHSV(random8(), 255, 255); // chsv random 8 makes it a random color each time
      FastLED.show();
      delay(ONDELAY);
      leds[numPos[10]] = CRGB::Black; // turn the space led off
      FastLED.show();
      delay(OFFDELAY);
    }
  // check to see if it is a letter if it is use the charPos array for the led
    if (let >= 97 && let <= 122) {
    int let1 = let - 97;
    leds[charPos[let1]] = CHSV(random8(), 255, 255);
      FastLED.show();
      delay(ONDELAY);
      // leds[charPos[pos]].setRGB(0,0,0);
      leds[charPos[let1]] = CRGB::Black;
      FastLED.show();
      delay(OFFDELAY);
    }
    //check to see if it is a number, if it is use the numpos array for the led
    if (let >= 48 && let <= 57) {
    int numa = let - 48;
    leds[numPos[numa]] = CHSV(random8(), 255, 255);
      FastLED.show();
      delay(ONDELAY);
      // leds[charPos[pos]].setRGB(0,0,0);
      leds[numPos[numa]] = CRGB::Black;
      FastLED.show();
      delay(OFFDELAY);
    }
  }
}



void blinkConst(void) {

  int blinkCount = 0;
  int i;

  while (blinkCount < 3) {
    for (i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(random8(), 255, 255);;
    }
    FastLED.show();
    delay(ONDELAY);
    for (i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(0, 0, 0);;
    }
    FastLED.show();
    delay(OFFDELAY);
    blinkCount++;
  }
}

// Function to blink all lights at variable speed
void blinkVar(int speed) {

  int i;

  for (i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(random8(), 255, 255);
  }
  FastLED.show();
  delay(speed);
  for (i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();
  delay(speed);
}

// Function to blink all lights randomly
void blinkRandom(int speed) {

  int i, randomNum;

  for (i = 0; i <= NUM_LEDS; i++) {
    randomNum = random(NUM_LEDS);
    leds[randomNum] = CHSV(random8(), 255, 255);
    FastLED.show();
    delay(speed);
    leds[randomNum] = CHSV(0, 0, 0);
    FastLED.show();
    delay(speed);
  }
}

// Function to blink all lights in a row
void blinkRow(int speed) {

  int i;

  for (i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(random8(), 255, 255);
    FastLED.show();
    delay(speed);
  }
  for (i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();
}


// Main program body, loop checks for new serial input and runs functions based on character input or default print function
void loop() {
//   Set string to incoming text
   delay(10);
   FastLED.show();
  while (Serial.available() > 0) {
    delay(50);
    char inChar = Serial.read();
    if (inChar == '*') { // Clear string using '*' input
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      txtMsg = "";
      // erase the string so it doesnt print anything 
      //set all the leds off
    }
    else if (inChar == '/') { // Clear string using '*' input
    mode=1;
    }
    else if (inChar == ':') { // set the mode to zero and turn all the leds off 
    mode=0; // set the mode to zero and turn all the leds off 
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    }
    else if (inChar == '%') { // Run other functions using specified inputs
      blinkConst();
    }
    else if (inChar == '&') { // Run other functions using specified inputs
      for (int i = 500; i >= 50; i -= 50)
      {
        blinkVar(i);
      }
    }
    else if (inChar == '$') { // Run other functions using specified inputs
      blinkRandom(50);
    }
    else if (inChar == '#') { // Run other functions using specified inputs
      blinkRow(50);
    }
    else {  // Other wise add input serial character to cleared string
      txtMsg += inChar;
    }
  }
  switch (mode) {
    case 1:  //run when var = 1
      pride();
      FastLED.show();
      break;
    case 2:  //run when var = 2
      blinkConst();
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }
  //blinkBlink();
  printChar(txtMsg);
  
}


void pride()
{

  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  for ( uint16_t i = 0 ; i < NUM_LEDS; i++) {

    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    CRGB newcolor = CHSV( hue8, sat8, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS - 1) - pixelnumber;

    nblend( leds[pixelnumber], newcolor, 64);

  }

}
