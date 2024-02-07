#include <Adafruit_NeoPixel.h> // Header for Neopixel library
//#include "ButtonControl.h"

#define LED_PIN 1 // What pin on arduino is connected to NeoPixels

#define LED_COUNT 50 // Number of NeoPixels attached

#define BRIGHTNESS 255 // max = 255


// structs

// If i can just store that as a bytearray I can just document it in a comment

// Stores states of switches (10)
struct swState{
  bool sw_one = 0;
  bool sw_two = 0;
  bool sw_three = 0;
  bool sw_four = 0;
  bool sw_five = 0;
  bool sw_six = 0;
  bool sw_seven = 0;
  bool sw_eight = 0;
  bool sw_nine = 0;
  bool sw_ten = 0;
} swState; // Do I even need this?

// Stores states of buttons (5)
struct btState{
  bool bt_one = 0;
  bool bt_two = 0;
  bool bt_three = 0;
  bool bt_four = 0;
  bool bt_five = 0;
} btState; // Do I even need this?

// Stores NeoPixel pin numbers for each button and switch
struct ledPin{
  // 10 switches
  int pix_swone = 1;
  int pix_swtwo = 2;
  int pix_swthree = 3;
  int pix_swfour = 4;
  int pix_swfive = 5;
  int pix_swsix = 6;
  int pix_swseven = 7;
  int pix_sweight = 8;
  int pix_swnine = 9;
  int pix_swten = 10;

  // 5 buttons
  int pix_btone = 11;
  int pix_bttwo = 12;
  int pix_btthree = 13;
  int pix_btfour = 14;
  int pix_btfive = 15;
} ledPin;


const unsigned int checkInterval = 100;

int incomingByte = 0;


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW);// Defines an object

void setup(){
  Serial.begin(115200);
  // So serial is reading in 240?

  strip.begin(); // Initializes the strip object
  strip.show(); // Turns off pixels
  strip.setBrightness(BRIGHTNESS); 

  initColor(strip.Color(255, 0, 0)); // color is Red

  while(!Serial){
    ; // Wait until the serial becomes available
  }

  configPanel();
}


void loop() {
  
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      //Serial.print("I received: ");
      Serial.println(incomingByte, DEC);

      // Thinking of adding a function to actually do the stuff with the data
      //foo(incomingByte);
  }
  //int data_raw = Serial.read(); // server.py line 59
  
  // Serial.println(thing);

}

// Sets all pixels to a designated color
void initColor(uint32_t color){
  // Iterates over each pixel in the strip
  for(int i = 0; i <strip.numPixels(); i++){
    strip.setPixelColor(i, color); // Built in function
    strip.show(); // Updates strip to match edit
  }
}

// Could return true if the panel configuration was successful
// Reads in input fron Python to configure the buttons
void configPanel(){
  bool config_arr[16]; // might need to change to integer array
  for(int i = 0; i < 16; i++){
    config_arr[i] = Serial.read(size = 1);
  }

  // Thinking of just making a boolean array
  // This boolean array will be used in making buttons work or not work in the if statements
  /* Example:
      arr[i] = true; means button is in use
      arr[i] = false; means button not in use
      if(ChangeOfState && arr[correspondingIndexNum]){
        do thing
      }
  */
} // End configPanel()

// Things below here aren't as easily testable

void checkButtons(){
  /*
  15 if-statements
    If ChangeOfState detected, set the value to 1 with bitmask
    Also change the associated LED from Neopixel
    Also call sendSerial();
  */
}

// Sends serial instruction to Python, called within checkButtons()
void sendSerial(){
  instruction = createInstruction();
  sendInstruction(instruction);
}

int createInstruction(){

  // What I would like to do is just have a 16-bit string as global variable
  // Then bitmask this whenever there is a change of state
  // Would prob just bitmask an OR of 0000 0000 0010 0000 to just change the state of that index to on
  // Then for a turn off bitmask an AND of 1111 1111 1101 1111
  // Example:
    /*
     * if(changeInButton){
         bitmask to the associated thing
         send this state
       }
     */

  // So this is one possibility, albeit not a good one
  int new_instruction = 0;

  new_instruction += swState.sw_one * 1;
  new_instruction += swState.sw_two * 2;
  new_instruction += swState.sw_three * 4;
  new_instruction += swState.sw_four * 8;
  new_instruction += swState.sw_five * 16;
  new_instruction += swState.sw_six * 32;
  new_instruction += swState.sw_seven * 64;
  new_instruction += swState.sw_eight * 128;
  new_instruction += swState.sw_nine * 256;
  new_instruction += swState.sw_ten * 512;

  new_instruction += btState.bt_one * 1024;
  new_instruction += btState.bt_two * 2048;
  new_instruction += btState.bt_three * 4096;
  new_instruction += btState.bt_four * 8192;
  new_instruction += btState.bt_five * 16384;

  return new_instruction;
}

void sendInstruction(instruction){
  // send instruction to socket
}

/*THOUGHTS
 * tbh i prob need a header file cuz holy shit this is getting long
 * 1. Make a header file with a cpp file to reference
 *    This will have the controls for the buttons and what each input does
 * 2. Make a function dedicated to reading serial
 * 3. Make a function dedicated to changing the light
 * 4. Make a python function dedicated to sending instruction
 * 5. Could just make a sample function for writing to serial on loop
 * 
 *

 * Test this
uint32_t number = 123456789; // the integer to send
Serial.write((uint8_t*)&number, sizeof(number)); // write the bytes of the number

 */