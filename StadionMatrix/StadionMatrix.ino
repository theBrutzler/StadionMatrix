/* Derived from Adafruit RGB_matrix_Panel library */

// DIES IST EIN TEST HALLO

#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "FRITZ!Box";
const char* password = "2349363902948132";

// constructor with default pin wiring
P3RGB64x32MatrixPanel matrix;

// use this constructor for custom pin wiring instead of the default above
// these pins are an example, you may modify this according to your needs
//P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 23, 15, 32, 33, 12, 16, 17, 18);


unsigned int RES = 600;

unsigned char color_r(unsigned int count){
  if(count >= 0 && count < RES/3){
    return (int)(15*count/(RES/3));
  }
  else if (count >=(RES/3) && count < (2*RES/3)){
    return (int)(30-(15*count/(RES/3)));
  }
  else if(count >= RES && count < (RES+(RES/3))){
    return (int)(15*(count-RES)/(RES/3));
  }
  else if (count >=RES+(RES/3) && count <RES+(2*RES/3)){
    return (int)(30-(15*(count-RES)/(RES/3)));
  }
  else{
    return 0;
  }
  
}

unsigned char color_g(unsigned int count){
  
  if (count >=(RES/3) && count <(2*RES/3)){
    return (int)((15*(count-(RES/3))/(RES/3)));
  }
  else if (count >=(2*RES/3) && count <=(RES)){
    return (int)(30-(15*(count-(RES/3))/(RES/3)));
  }
  else if (count >=RES + (RES/3) && count <RES +(2*RES/3)){
    return (int)((15*(count-(RES/3)-RES)/(RES/3)));
  }
  else if (count >= RES + (2*RES/3) && count <= RES+ (RES)){
    return (int)(30-(15*(count-(RES/3)-RES)/(RES/3)));
  }
  else{
    return 0;
  }
  
}

unsigned char color_b(unsigned int count){
  if(count >= 0 && count < (RES/3)){
    return (int)(15-(15*count/(RES/3)));
  }
  else if (count >=(2*RES/3) && count <(RES)){
    return (int)((15*(count-(2*RES/3))/(RES/3)));
  }
  else if(count >= RES && count < RES+(RES/3)){
    return (int)(15-(15*(count-RES)/(RES/3)));
  }
  else if (count >=RES +(2*RES/3) && count <2*(RES)){
    return (int)((15*(count-(2*RES/3)-RES)/(RES/3)));
  }
  
  else{
    return 0;
  }
  
}
void setup() {
  
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    matrix.begin();
    matrix.setCursor(0, 0);
    matrix.setTextColor(matrix.color444(3,3,3));
    matrix.fillScreen(matrix.color444(0, 0, 0));
    matrix.setTextSize(1);     // size 1 == 8 pixels high
    matrix.print("Failed");
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

/*
  // draw a pixel in solid white
  matrix.drawPixel(0, 0, matrix.color444(15, 15, 15));
  delay(500);

  // fix the screen with green
  matrix.fillRect(0, 0, matrix.width(), matrix.height(), matrix.color444(0, 15, 0));
  delay(500);

  // draw a box in yellow
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.color444(15, 15, 0));
  delay(500);

  // draw an 'X' in red
  matrix.drawLine(0, 0, matrix.width() - 1, matrix.height() - 1, matrix.color444(15, 0, 0));
  matrix.drawLine(matrix.width() - 1, 0, 0, matrix.height() - 1, matrix.color444(15, 0, 0));
  delay(500);

  // draw a blue circle
  matrix.drawCircle(10, 10, 10, matrix.color444(0, 0, 15));
  delay(500);

  // fill a violet circle
  matrix.fillCircle(40, 21, 10, matrix.color444(15, 0, 15));
  delay(500);

  // fill the screen with 'black'
  matrix.fillScreen(matrix.color444(0, 0, 0));

  // draw some text!
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves

  matrix.setCursor(8, 0);    // start at top left, with 8 pixel of spacing
  uint8_t w = 0;
  char *str = "P3indoorSMDDisplay";
  for (w = 0; w < 8; w++) {
    matrix.setTextColor(Wheel(w));
    matrix.print(str[w]);
  }
  matrix.setCursor(2, 8);    // next line
  for (w = 8; w < 18; w++) {
    matrix.setTextColor(Wheel(w));
    matrix.print(str[w]);
  }
  matrix.println();
  //matrix.setTextColor(matrix.Color333(4,4,4));
  //matrix.println("Industries");
  matrix.setTextColor(matrix.color444(15, 15, 15));
  matrix.println("LED MATRIX!");

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.color444(15, 3, 0));
  matrix.print('3');
  matrix.setTextColor(matrix.color444(15, 4, 0));
  matrix.print('2');
  matrix.setTextColor(matrix.color444(15, 15, 0));
  matrix.print('x');
  matrix.setTextColor(matrix.color444(8, 15, 0));
  matrix.print('6');
  matrix.setTextColor(matrix.color444(0, 15, 0));
  matrix.print('4');
  matrix.setCursor(34, 24);
  matrix.setTextColor(matrix.color444(0, 15, 15));
  matrix.print("*");
  matrix.setTextColor(matrix.color444(0, 8, 15));
  matrix.print('R');
  matrix.setTextColor(matrix.color444(0, 0, 15));
  matrix.print('G');
  matrix.setTextColor(matrix.color444(8, 0, 15));
  matrix.print("B");
  matrix.setTextColor(matrix.color444(15, 0, 8));
  matrix.println("*");

  matrix.println("Restart")
  delay(1000);*/
  ArduinoOTA.setHostname("LED_MATRIX");
  ArduinoOTA
    .onStart([]() {
      matrix.stop();
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      matrix.begin();
      matrix.setCursor(0, 0);
      matrix.setTextColor(matrix.color444(3,3,3));
      matrix.fillScreen(matrix.color444(0, 0, 0));
      matrix.setTextSize(1);     // size 1 == 8 pixels high
      matrix.println("Flashing");
      int value = progress / (total / 100);
      matrix.print(value);
      matrix.stop();
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
  
  matrix.begin();
  matrix.setCursor(0, 0);
  matrix.setTextColor(matrix.color444(3,3,3));
  matrix.fillScreen(matrix.color444(0, 0, 0));
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.print("Connected");
  matrix.println(" ");
  delay(1000);

  matrix.fillScreen(matrix.color444(0, 0, 0));
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  //Cycle(255);
  // whew!
}
uint16_t bundt = 0;
bool count_up = true;
void loop() {
  
  //Cycle(bundt++,0);
  Schatz(bundt);
  //delay(100);
  if(bundt>=720)
    count_up=false;
  if(bundt<=0)
    count_up=true;
  if(count_up)
    bundt++;
  else
    bundt--;
  ArduinoOTA.handle();
    
  //Cycle(bundt+2,32);
  //delay(100);


  // do nothing
}

void Schatz(uint16_t colore){
    //char *str = "Der Plati-   nenmacher    ist un-     schlagbar!";
  //char *str = " Hi Schatz    Lieb dir    du bist     mein Herz!";
  char *str = "theBrutzler  unstoppable follow on   twitch.tv  ";
  
  //char *str = "Hi Lucy      Lieb dich   du bist     die Beste!";

  matrix.setCursor(0, 0);    // next line
  for (int w = 0; w < 48; w++) {
    matrix.setTextColor(matrix.color444(color_r(colore+(w*5)), color_g(colore+(w*5)), color_b(colore+(w*5))));
    matrix.print(str[w]);
    if (w == 12 || w == 24 || w == 36)
      matrix.println(' ');
  }
  
}

void Cycle(uint16_t colore, int xext){
  
  int      x, y, hue;
  float    dx, dy, d;
  uint8_t  sat, val;
  uint16_t c;
  for (y = 0; y < matrix.width(); y++) {
    dy = 15.5 - (float)y;
    for (x=xext; x < matrix.height(); x++) {
      dx = 15.5 - (float)x;
      d  = dx * dx + dy * dy;
      if (d <= (16.5 * 16.5)) { // Inside the circle(ish)?
        hue = (int)((atan2(-dy, dx) + PI) * 1536.0 / (PI * 2.0));
        d = sqrt(d);
        if (d > 15.5) {
          // Do a little pseudo anti-aliasing along perimeter
          sat = 255;
          val = (int)((1.0 - (d - 15.5)) * 255.0 + 0.5);
        } else
        {
          // White at center
          sat = (int)(d / 15.5 * 255.0 + 0.5);
          val = 255;
        }
        c = matrix.color444(color_r(colore), color_g(colore), color_b(colore));
      } else {
        c = 0;
      }
      matrix.drawPixel(x, y, c);
    }
  }
}


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if (WheelPos < 8) {
    return matrix.color444(15 - WheelPos * 2, WheelPos * 2, 0);
  } else if (WheelPos < 16) {
    WheelPos -= 8;
    return matrix.color444(0, 15 - WheelPos * 2, WheelPos * 2);
  } else {
    WheelPos -= 16;
    return matrix.color444(0, WheelPos * 2, 7 - WheelPos * 2);
  }
}
