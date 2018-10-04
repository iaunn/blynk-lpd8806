#define BLYNK_PRINT Serial

#include "LPD8806.h"
#include "SPI.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int nLEDs = 32;
int dataPin  = D1;
int clockPin = D2;
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

char auth[] = "blynk token";

char ssid[] = "wifi";
char pass[] = "pass";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  strip.begin();
  strip.show();
}
int ledEnable;
int ledSlide;
int r,g,b;
int ledPosition;
int ledPosLength;

BLYNK_WRITE(V0)
{
  r = param[0].asInt();
  g = param[2].asInt();
  b = param[1].asInt();

  Serial.print("V0 Slider value is: r: ");
  Serial.print(r);
  Serial.print(" g: ");
  Serial.print(g);
  Serial.print(" b: ");
  Serial.println(b);
  updateColor();
}


BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
  ledEnable = pinValue;
  updateColor();
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  Serial.print("V2 Slider value is: ");
  Serial.println(pinValue);
  ledSlide = pinValue;
  updateColor();
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt();
  Serial.print("V3 Slider value is: ");
  Serial.println(pinValue);
  ledPosition = pinValue;
  updateColor();
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt();
  Serial.print("V4 Slider value is: ");
  Serial.println(pinValue);
  ledPosLength = pinValue;
  updateColor();
}

void loop() {
  Blynk.run();
}

void updateColor() {
  Serial.print("led enable ");
  Serial.println(ledEnable);

  Serial.print("led slide Enable ");
  Serial.println(ledSlide);

  Serial.print("led Pixel Position ");
  Serial.println(ledPosition);

  Serial.print("led Pixel Position ");
  Serial.println(ledPosition);

  Serial.print("led Pixel Position Length");
  Serial.println(ledPosLength);

  Serial.print("r");
  Serial.println(r);
  Serial.print("g");
  Serial.println(g);
  Serial.print("b");
  Serial.println(b);


  if (ledEnable == 0){
    setColor(strip.Color(0,  0,  0), 0, strip.numPixels());
  } else {
    if ( ledSlide == 0) {
      setColor(strip.Color(r,  g,  b), 0, strip.numPixels());
    } else {
      int realPos = ledPosition + ledPosLength;

      if ( realPos > ( strip.numPixels() -1)) {
          realPos = strip.numPixels();
      }
      
      Serial.print("Real Pos");
      Serial.println(realPos);
      setColor(strip.Color(r,  g,  b), ledPosition, realPos);
    }
  }
}

// Chase one dot down the full strip.  Good for testing purposes.
void setColor(uint32_t c, int ledStart, int ledStop) {
  int i;
  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
  
  // set all pixels with color:
  for(i=ledStart; i<ledStop; i++) strip.setPixelColor(i, c);
  strip.show();
}

