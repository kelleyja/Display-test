// For a connection via I2C using the Arduino Wire include:
#include <Wire.h>               
#include "HT_SSD1306Wire.h"
#include "images.h"

SSD1306Wire  display(0x3c, 500000, SDA, SCL, GEOMETRY_128_64, GPIO10); // addr , freq , SDA, SCL, resolution , rst

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  delay(100);

  // Initialising the UI will init the display too.
  display.init();

  display.setFont(ArialMT_Plain_10);
  display.clear();

}

void drawFontFaceDemo() {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
}

void drawTextFlowDemo() {
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128,
      "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
}

void drawTextAlignmentDemo() {
  // Text alignment demo
  char str[30];
  int x = 0;
  int y = 0;
  display.setFont(ArialMT_Plain_10);
  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(x, y, "Left aligned (0,0)");

  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  x = display.width()/2;
  y = display.height()/2-5;
  sprintf(str,"Center aligned (%d,%d)",x,y);
  display.drawString(x, y, str);

  // The coordinates define the right end of the text
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  x = display.width();
  y = display.height()-12;
  sprintf(str,"Right aligned (%d,%d)",x,y);
  display.drawString(x, y, str);
}

void drawRectDemo() {
      // Draw a pixel at given position
    for (int i = 0; i < 10; i++) {
      display.setPixel(i, i);
      display.setPixel(10 - i, i);
    }
    display.drawRect(12, 12, 20, 20);

    // Fill the rectangle
    display.fillRect(14, 14, 17, 17);

    // Draw a line horizontally
    display.drawHorizontalLine(0, 40, 20);

    // Draw a line horizontally
    display.drawVerticalLine(40, 0, 20);
}

void drawCircleDemo() {
  for (int i=1; i < 8; i++) {
    display.setColor(WHITE);
    display.drawCircle(32, 32, i*3);
    if (i % 2 == 0) {
      display.setColor(BLACK);
    }
    display.fillCircle(96, 32, 32 - i* 3);
  }
}

void drawProgressBarDemo() {
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}



void VextON(void)
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) //Vext default OFF
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, HIGH);
}


Demo demos[] = {drawFontFaceDemo, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawCircleDemo, drawProgressBarDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;

void loop() {
  display.clear();
  
  // draw the current demo method
  display.drawString(0, 0, "this is a test");
  delay(100);
  display.display();

  delay(500);
  display.clear();
  drawProgressBarDemo();
  delay(500);
  display.display();
  }
  
