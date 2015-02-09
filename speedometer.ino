/*
  Speedometer
     To serve as a speedometer for any vehicle 
     with round wheels, given a specific circumference.
  
  Screen Info:
    1) microSD slot, must be formatted as FAT16 or FAT32
    2) 1.77" screen, 160x128 pixel resolution
    3) Runs on +5 VDC (Voltage Direct Current)
    4) LED backlight.
    
  Pin setup:
    +5V    ->  +5v
    CS_SD  ->  4
    RST    ->  8
    DC     ->  9
    CS_LD  ->  10
    MOSI   ->  11
    MISO   ->  12
    SCK    ->  13
    BL     ->  +5V
    GND    ->  GND
  
  by Rocky Quinn
*/

// SD.h  -  SD card Library
// TFT.h -  TFT (Thin-Film-Transistor) Library
// SPI.h -  SPI (Serial Peripheral Interface) Library
#include <SD.h>
#include <SPI.h>
#include <TFT.h>

//SD_CS  -  SD Chip Select
//LCD_CS -  LCD Chip select
//DC     -  Direct Current
//RESET  -  Reset button
//MISO   -  Master In Slave Out
//MOSI   -  Master Out Slave In
//SCLK   -  Serial Clock
//POWER  -  5V power pin
#define CS_LCD 10
#define CS_SD 4
#define DC 9
#define RESET 8
#define MOSI 11
#define MISO 12
#define SCK 13
TFT TFTScreen = TFT(CS_LCD, DC, RESET);
PImage imag;

void setup()
{
  //Initializes the screen
  TFTScreen.begin();
  TFTScreen.background(255, 255, 255);
  
  Serial.begin(9600);
  while(!Serial){;}
  
  //Initializes the microSD card so it can be accesed
  Serial.println("Initializing microSD card...");
  if(!SD.begin(CS_SD)) 
  {
    Serial.println("microSD card failed to initialize. Check connection.");
    return;
  }
  Serial.println("microSD card initialized.");
  
  //Loads the start up image.
  imag = TFTScreen.loadImage("start_up.bmp");
  if(!imag.isValid())
  {
    Serial.println("Error while loading image");
  }
  TFTScreen.image(imag,0,0);
}


void loop()
{
  //Loads the screen with a 0 on the screen
  //imag = TFTScreen.loadImage("spd_0.bmp");
  if(!imag.isValid())
  {
    Serial.println("Error while loading image");
  }
  
  PImage t1, t2;
  
  //Test 1
  t1 = TFTScreen.loadImage("spd_0.bmp");
  t2 = TFTScreen.loadImage("spd_0.bmp");
  TFTScreen.image(t1,0,0);
  TFTScreen.image(t2,80,0);
  
  delay(1000);
  
  //Test 2
  t2 = TFTScreen.loadImage("spd_1.bmp");
  TFTScreen.image(t2,80,0);
  
  delay(1000);
  
  //To clear screen use .background or .begin()
  //TFTScreen.image(imag, /*x*/0, /*y*/0);
}
