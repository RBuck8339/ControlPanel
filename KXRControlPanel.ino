#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define TOGGLE_BIT(button_state, bit) ((button_state) ^ (1 << bit))
// To Call: TOGGLE_BIT(0, 7)


const unsigned int checkInterval = 100;

/*
When reading in strings for OLED, config switches at the same time
if(emptry string) skip OLED
if that switch is hit, send "empty" to python and deal with it there
handle bitmasking in python instead
*/

// Stores previous button state for checking if there was an update
struct states{
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
  bool bt_one = 0;
  bool bt_two = 0;
  bool bt_three = 0;
  bool bt_four = 0;
  bool bt_five = 0;
};

// Stores associated commands for sending to Python
// String stores "empty" if no function
struct commands{
  String cmd_sw_one;
  String cmd_sw_two;
  String cmd_sw_three;
  String cmd_sw_four;
  String cmd_sw_five;
  String cmd_sw_six;
  String cmd_sw_seven;
  String cmd_sw_eight;
  String cmd_sw_nine;
  String cmd_sw_ten;
  String cmd_bt_one;
  String cmd_bt_two;
  String cmd_bt_three;
  String cmd_bt_four;
  String cmd_bt_five;
};

void setup(){
  Serial.begin(115200);

  // Wait until the serial becomes available
  while(!Serial){
    ; 
  }

  Serial.println("READY");
  delay(1000);

  configPanel();
  
}

void loop() {
  checkButtons()
}

// Writes strings to OLEDs for associated switches
// Modifies switches based on function
void configPanel(){
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Initializes object
  // do it again, name appropriately left to right 1-X

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // do it again
  
  // Clears old stuff
  display.display();
  display.clearDisplay();
  // Now do it again

  // Gets the new stuff
  commands.cmd_sw_one = Serial.readStringUntil('\n');
  (commands.cmd_sw_one).trim();

  if(commands.cmd_sw_one != "empty"){
    // Puts the new stuff on there
    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,0);
    display.print(commands.cmd_sw_one); 
    display.display();
  }
    

  // Now do it again

} // End configPanel()


void checkButtons(){
  
  /*
  if(switch one is hit)
    ser.println(commands.cmd_sw_one);
  */
  // See arduino change of state example

  */
  /*
  15 if-statements
    Also change the associated LED from Neopixel
  
  
} */

/*THOUGHTS
 * 2. Thinking of scrapping the config_arr idea
 * 3. Make a function dedicated to changing the light
 * 4. Make a python function dedicated to sending instruction
 * 5. Could just make a sample function for writing to serial on loop
 * 6. STM32 will only be doing sending, we are going to have a separate board for NeoPixels
 * 7. Apparently im reading a string to display to OLED
 * 8. IS AVIONICS EXISTING???

 2 different scripts:
  One sending data to LED control
  One for OLEDS and switches and avionics
  Then a python script for each

  LEDS get data from wanda

 */




  // This works, sends back b'This\r\n'
  /*
  String var = Serial.readString();
  var.trim();
  Serial.println(var);
  */