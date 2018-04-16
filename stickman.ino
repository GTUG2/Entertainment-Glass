#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display
Adafruit_SSD1306 display;  // Create display
SoftwareSerial BTserial(8, 9); // RX | TX
//Adafruit_SSD1306.h -> line 73 128x32yi 128x64 olarak degistirdik.
const long baudRate = 9600; 
int x = 64;
int y = 32;
void setup() {
    Serial.begin(9600);    
    BTserial.begin(baudRate);  
    delay(100);  // This delay is needed to let the display to initialize
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C 
    display.clearDisplay();  // Clear the buffer
    display.setTextColor(WHITE);  // Set color of the text
    display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3
    display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                                 // To override this behavior (so text will run off the right side of the display - useful for
                                 // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                                 // with setTextWrap(true).
                                 
    display.dim(0);  //Set brightness (0 is maximum and 1 is a little dim)
    
    
}
void hareket(int x,int y)
{
    display.drawLine(x+10,y+40,x+0,y+50,WHITE); //sol ayak
    display.drawLine(x+10,y+40,x+20,y+50,WHITE); // sag ayak
    delay(50);
}
void drawStickMan(int x,int y)
{
    if(x % 2 == 0)
    {
      hareket(x-1,y);
    }
    else{
      hareket(x+1,y);
    }
    display.drawCircle(x+10, y+10, 10, WHITE); //kafa
    display.drawFastVLine(x+10,y+20,20,WHITE); //govde
    
    display.drawLine(x+10,y+20,x+0,y+30,WHITE); //sol kol
    display.drawLine(x+10,y+20,x+20,y+30,WHITE); //sag kol
    display.drawPixel(x+7,y+7,WHITE); //sol goz
    display.drawPixel(x+13,y+7,WHITE); //sag goz

    display.drawPixel(x+10,y+10,WHITE); //burun

    display.drawFastHLine(x+7,y+13,7,WHITE); //govde
    display.display();
}

void loop() {
  display.clearDisplay();
  drawStickMan(x++,y);
  if(x > 128){
    y=64;
    x=-20;  }
  if(y > 15)
    y--;  
}
