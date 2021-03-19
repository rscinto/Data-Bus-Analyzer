#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



//Main Bus
//GPIO pin 5
int firstBit = 5;
//GPIO pin 4
int secondBit = 4;
//GPIO pin 3
int thirdBit = 3;
//GPIO pin 2
int fourthBit = 2;

//pin:  11, 10,  9,  8
//bits: 1st 2nd 3rd 4th
//Subsytem Data Bus
//GPIO pin 11
int firstSUBBit = 11;
//GPIO pin 10
int secondSUBBit = 10;
//GPIO pin 9
int thirdSUBBit = 9;
//GPIO pin 8
int fourthSUBBit = 8;



int busValue(int bitzero, int bitone, int bittwo, int bitthree)
{
  int state0 = bitzero;
  int state1 = bitone;
  int state2 = bittwo;
  int state3 = bitthree;

  int output = 0;

  if(state0)
  {
    output+=1;
  }

  if(state1)
  {
    output+=2;
  }

  if(state2)
  {
    output+=4;
  }

  if(state3)
  {
    output+=8;
  }

  return output;
}


void setup() 
{
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);    
  }

  //pins for Bus
  pinMode(firstBit, INPUT);
  pinMode(secondBit, INPUT);
  pinMode(thirdBit, INPUT);
  pinMode(fourthBit, INPUT);

  //pins for Sub
  pinMode(firstSUBBit, INPUT);
  pinMode(secondSUBBit, INPUT);
  pinMode(thirdSUBBit, INPUT);
  pinMode(fourthSUBBit, INPUT);
   
 
}

void loop() 
{
  int mainBus = busValue(digitalRead(firstBit),digitalRead(secondBit),digitalRead(thirdBit),digitalRead(fourthBit));
  int subBus  = busValue(digitalRead(firstSUBBit),digitalRead(secondSUBBit),digitalRead(thirdSUBBit),digitalRead(fourthSUBBit));
  
  //delay(100);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("");
  display.println("Bus Value");
  display.println("Main: ");
  display.println(mainBus);
  display.println("SubB: ");
  display.println(subBus);
  display.display();
  
  

}
