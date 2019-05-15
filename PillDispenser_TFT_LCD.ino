//Libraries
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <SPI.h>

unsigned long timeNow = 0;
unsigned long timeLast = 0;

int startingHour = 12;

int seconds = 0;
int minutes = 33;
int hours = startingHour;
int days = 0;

int dailyErrorFast = 0;
int dailyErrorBehind = 0;
int correctedToday = 1;

#define TFT_CS         15
#define TFT_RST        12
#define TFT_DC         16 //RS
#define TFT_MOSI 4  // Data out /SDA
#define TFT_SCLK 5  // Clock out /SCL

int vibmotor1 = 13;
int vibmotor2 = 14;


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(9600);
  tft.initR(INITR_144GREENTAB); //initalize TFT ST7735 1.44"
  tft.fillScreen(ST77XX_WHITE);
  pinMode(vibmotor1, OUTPUT);
  pinMode(vibmotor2, OUTPUT);
  printtime();

}

void loop() {
  /*
  digitalWrite(vibmotor1, HIGH);
  delay(1000);
  digitalWrite(vibmotor1, LOW);
  delay(1000);
  digitalWrite(vibmotor2, HIGH);
  delay(1000);
    digitalWrite(vibmotor2, LOW);
  delay(1000);
  */
  tracktime();
  if(seconds == 0){
    printtime();
  }
  alarm(12, 34);
}

void pill(){

  tft.fillCircle(20,76,16,ST7735_RED);
  tft.fillCircle(108,76,16,ST7735_RED);
  
  //tft.fillCircle(x,y,w,l,color);
  tft.fillRect(20,60,88,33,ST7735_BLUE);

}

void printtime(){
  tft.setTextWrap(false);
  tft.setRotation(1);
  tft.fillRect(0,50,128,45,ST7735_WHITE);
  tft.setCursor(20, 85);
  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
  tft.setFont(&FreeSerifBold18pt7b);
  tft.print(hours);
  tft.print(":");
  tft.print(minutes);
  tft.setCursor(10, 35);
  if(days % 7 == 0){
    tft.print("Sunday");
  }
  if(days % 7 == 1){
    tft.print("Monday");
  }
  if(days % 7 == 2){
    tft.print("Tuesday");
  }
  if(days % 7 == 3){
    tft.print("Wednesday");
  }
  if(days % 7 == 4){
    tft.print("Thursday");
  }
  if(days % 7 == 5){
    tft.print("Friday");
  }
  if(days % 7 == 6){
    tft.print("Saturday");
  }  
  
  
}
void tracktime(){
  timeNow = millis()/1000;
  seconds = timeNow - timeLast;
  if(seconds == 60){
    timeLast = timeNow;
    minutes = minutes +1;
  }
  if(minutes == 60){
    minutes = 0;
    hours = hours +1;
  }
  if(hours == 24){
    hours = 0;
    days = days + 1;
    tft.fillScreen(ST7735_WHITE);
  }
  if(hours == (24 - startingHour) && correctedToday == 0){
    delay(dailyErrorFast*1000);
    seconds = seconds + dailyErrorBehind;
    correctedToday = 1;
  }
}

void alarm(int h, int m){
  if(hours == h && (minutes == m || minutes == m + 1 || minutes == m + 2)){
    if(seconds == 1){
      tft.fillRect(0,50,128,45,ST7735_WHITE);
      pill();
    }
  }
}
