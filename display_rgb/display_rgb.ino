#include <Arduino_GFX_Library.h>

Arduino_DataBus *bus = new Arduino_HWSPI(9 /* DC */, 10 /* CS */);
Arduino_GFX *gfx = new Arduino_ST7796(bus, 8 /* RESET */,0,true);

/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/
void setup(void)
{
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  
  // Serial.setDebugOutput(true);
  // while(!Serial);
  Serial.println("Arduino_GFX Hello World example");

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  // Init Display
  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BLACK);

  gfx->setCursor(10, 10);
  gfx->setTextColor(PURPLE);
  gfx->setTextSize(3, 3);
  gfx->println("Hello World!");

  gfx->setCursor(10, 50);
  gfx->setTextColor(NAVY);
  gfx->setTextSize(3, 3);
  gfx->println("5");

  gfx->setCursor(30, 50);
  gfx->setTextColor(DARKGREEN);
  gfx->setTextSize(3, 3);
  gfx->println("2");

  gfx->setCursor(50, 50);
  gfx->setTextColor(DARKCYAN);
  gfx->setTextSize(3, 3);
  gfx->println("P");

  gfx->setCursor(70, 50);
  gfx->setTextColor(MAROON);
  gfx->setTextSize(3, 3);
  gfx->println("i");

  // Draw the box (if 1pix is a line)
  gfx->fillRect(115,65,10,10,WHITE);

  // It's equal to draw a line
  gfx->fillRect(150,0,1,240,WHITE);
  gfx->fillRect(0,100,240,1,WHITE);

  // Draw a circle
  gfx->drawEllipse(120,70,20,20,MAGENTA);
}

void loop()
{
  delay(1000); // 1 second
}
