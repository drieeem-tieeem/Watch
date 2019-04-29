//Libraries
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h>
#include <SPI.h>


#define TFT_CS         15
#define TFT_RST        12
#define TFT_DC         16 //RS
#define TFT_MOSI 4  // Data out /SDA
#define TFT_SCLK 5  // Clock out /SCL

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(9600);
  tft.initR(INITR_144GREENTAB); //initalize TFT ST7735 1.44"
  tft.fillScreen(ST77XX_BLACK);
  
  delay(1000);
  
  //tft.fillCircle(x,y,r,color);
  tft.fillCircle(64,28,18,ST7735_RED);
  delay(10);
  tft.fillCircle(64,100,18,ST7735_RED);
  delay(10);
  
  //tft.fillCircle(x,y,w,l,color);
  tft.fillRect(45,27,38,74,ST7735_BLUE);
}

void loop() {
  // put your main code here, to run repeatedly:

}
