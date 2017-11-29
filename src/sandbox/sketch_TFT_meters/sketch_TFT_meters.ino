/*
 Example animated analogue meters using a HX8357 TFT LCD screen

 Originanally written for a 320 x 240 display, so only occupies half
 of a 480 x 320 display.

 Needs Font 2 (also Font 4 if using large centered scale label)

 */
// #include <avr/dtostrf.h> // Only needed by Due

#include <TFT_HX8357.h> // Hardware-specific library

TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library

#define TFT_GREY 0x5AEB

float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = 120, osy = 120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update
 
int old_analog =  -999; // Value last displayed
int old_digital = -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int old_value2[6] = { -1, -1, -1, -1, -1, -1};

int d = 0;

void setup(void) {
  tft.init();
  tft.setRotation(1);
  Serial.begin(9600); // For debug
  tft.fillScreen(TFT_BLACK);

  //analogMeter(); // Draw analogue meter
analogMeter_V2(0, "%HUM");  
analogMeter_V2(240, "%TEMP");
  // Draw 6 linear meters
  //byte d = 40;
  //int w = 36;
  byte d = 55;
  int w = 50;  
  plotLinear("PM 1 ", 0, 160, w);
  plotLinear("PM 2.5", 1 * d, 160, w);
  plotLinear("PM 10", 2 * d, 160, w);
//  plotLinear("A3", 3 * d, 160);
//  plotLinear("A4", 4 * d, 160);
//  plotLinear("A5", 5 * d, 160);

  updateTime = millis(); // Next update time


}

#define DISPLAY_STR_SIZE 15

char oldDisplayPm25[DISPLAY_STR_SIZE];
  
void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + 250; // Delay to limit speed of update

   

      Serial.println("Please enter v1: "); //Prompt User for input
      while (Serial.available()==0) {}
      // read the incoming byte:
      String input1 = Serial.readString();   
      Serial.print("I received: ");
      Serial.println(input1);

          Serial.println("Please enter v2: "); //Prompt User for input
      while (Serial.available()==0) {}
      // read the incoming byte:
      String input2 = Serial.readString();   
      Serial.print("I received: ");
      Serial.println(input2);

      Serial.println("Please enter v3: "); //Prompt User for input
      while (Serial.available()==0) {}
      // read the incoming byte:
      String input3 = Serial.readString();   
      Serial.print("I received: ");
      Serial.println(input3);

    value[0] = input1.toInt();
    value[1] = input2.toInt();
    value[2] = input3.toInt();

//    value[0] = 130;
//    value[1] = 999;
//    value[2] = 20;

 
    d += 4; if (d >= 360) d = 0;

    //value[0] = map(analogRead(A0), 0, 1023, 0, 100); // Test with value form Analogue 0
    //value[1] = map(analogRead(A1), 0, 1023, 0, 100); // Test with value form Analogue 1
    //value[2] = map(analogRead(A2), 0, 1023, 0, 100); // Test with value form Analogue 2
    //value[3] = map(analogRead(A3), 0, 1023, 0, 100); // Test with value form Analogue 3
    //value[4] = map(analogRead(A4), 0, 1023, 0, 100); // Test with value form Analogue 4
    //value[5] = map(analogRead(A5), 0, 1023, 0, 100); // Test with value form Analogue 5

    // Create a Sine wave for testing
//    value[0] = 50 + 50 * sin((d + 0) * 0.0174532925);
//    value[1] = 50 + 50 * sin((d + 60) * 0.0174532925);
//    value[2] = 50 + 50 * sin((d + 120) * 0.0174532925);
//    value[3] = 50 + 50 * sin((d + 180) * 0.0174532925);
//    value[4] = 50 + 50 * sin((d + 240) * 0.0174532925);
//    value[5] = 50 + 50 * sin((d + 300) * 0.0174532925);
    
    //unsigned long t = millis(); 
  float tempValue = 30.9;
  float humValue=70.6;
  tft.setTextColor(TFT_WHITE);
  tft.drawRightString("2017/9/10 23:59:59", 450, 150 , 4);
  tft.drawRightString("HUM : 70.6 %", 450, 180 , 4);
  tft.drawRightString("TEMP: 30.9 C", 450, 210 ,4);
  tft.drawRightString("ATM : 1000 hPa", 450, 240 ,4);
  
tft.setTextColor(TFT_BLACK, TFT_BLACK);
tft.drawRightString(oldDisplayPm25, 450, 270 ,4);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  
 
  char displayPm25[DISPLAY_STR_SIZE];
    unsigned int PM25_STR_SIZE = 4;
  char pm2_5Str[PM25_STR_SIZE];
  memset(pm2_5Str, ' ', PM25_STR_SIZE);
  dtostrf(value[1], 3, 0, pm2_5Str);
   strcpy(displayPm25,  "  PM 2.5 : ");
   strcat(displayPm25, pm2_5Str);
   strcat(displayPm25, " ug/m3");
  tft.drawRightString(displayPm25, 450, 270 ,4);
  //tft.drawRightString("    PM 2.5 : 25 ug/m3", 450, 270 ,4);

Serial.println(String(displayPm25));

//strcpy(displayPm25,oldDisplayPm25);
memcpy( oldDisplayPm25, displayPm25, DISPLAY_STR_SIZE*sizeof(char) );
Serial.println(String(oldDisplayPm25));
    
    plotPointer(); // It takes aout 3.5ms to plot each gauge for a 1 pixel move, 21ms for 6 gauges     
    plotNeedle(tempValue, 0,240, "%TEMP"); // It takes between 2 and 12ms to replot the needle with zero delay
    plotNeedle(humValue, 0,0, "%HUM"); // It takes between 2 and 12ms to replot the needle with zero delay

 // plotNeedle(26.5, 0,0); // It takes between 2 and 12ms to replot the needle with zero delay
    //Serial.println(millis()-t); // Print time taken for meter update
  }
}

//
//// #########################################################################
////  Draw the analogue meter on the screen
//// #########################################################################
//void analogMeter()
//{
//  // Meter outline
//  tft.fillRect(0, 0, 239, 126, TFT_GREY);
//  tft.fillRect(5, 3, 230, 119, TFT_WHITE);
//
//  tft.setTextColor(TFT_BLACK);  // Text colour
//
//  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
//  for (int i = -50; i < 51; i += 5) {
//    // Long scale tick length
//    int tl = 15;
//
//    // Coodinates of tick to draw
//    float sx = cos((i - 90) * 0.0174532925);
//    float sy = sin((i - 90) * 0.0174532925);
//    uint16_t x0 = sx * (100 + tl) + 120;
//    uint16_t y0 = sy * (100 + tl) + 140;
//    uint16_t x1 = sx * 100 + 120;
//    uint16_t y1 = sy * 100 + 140;
//
//    // Coordinates of next tick for zone fill
//    float sx2 = cos((i + 5 - 90) * 0.0174532925);
//    float sy2 = sin((i + 5 - 90) * 0.0174532925);
//    int x2 = sx2 * (100 + tl) + 120;
//    int y2 = sy2 * (100 + tl) + 140;
//    int x3 = sx2 * 100 + 120;
//    int y3 = sy2 * 100 + 140;
//
//    // Yellow zone limits
//    //if (i >= -50 && i < 0) {
//    //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
//    //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
//    //}
//
//    // Green zone limits
//    if (i >= 0 && i < 25) {
//      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_GREEN);
//      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
//    }
//
//    // Orange zone limits
//    if (i >= 25 && i < 50) {
//      tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_ORANGE);
//      tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_ORANGE);
//    }
//
//    // Short scale tick length
//    if (i % 25 != 0) tl = 8;
//
//    // Recalculate coords incase tick lenght changed
//    x0 = sx * (100 + tl) + 120;
//    y0 = sy * (100 + tl) + 140;
//    x1 = sx * 100 + 120;
//    y1 = sy * 100 + 140;
//
//    // Draw tick
//    tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
//
//    // Check if labels should be drawn, with position tweaks
//    if (i % 25 == 0) {
//      // Calculate label positions
//      x0 = sx * (100 + tl + 10) + 120;
//      y0 = sy * (100 + tl + 10) + 140;
//      switch (i / 25) {
//        case -2: tft.drawCentreString("0", x0, y0 - 12, 2); break;
//        case -1: tft.drawCentreString("25", x0, y0 - 9, 2); break;
//        case 0: tft.drawCentreString("50", x0, y0 - 6, 2); break;
//        case 1: tft.drawCentreString("75", x0, y0 - 9, 2); break;
//        case 2: tft.drawCentreString("100", x0, y0 - 12, 2); break;
//      }
//    }
//
//    // Now draw the arc of the scale
//    sx = cos((i + 5 - 90) * 0.0174532925);
//    sy = sin((i + 5 - 90) * 0.0174532925);
//    x0 = sx * 100 + 120;
//    y0 = sy * 100 + 140;
//    // Draw scale arc, don't draw the last part
//    if (i < 50) tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
//  }
//
//  tft.drawString("", 5 + 230 - 40, 119 - 20, 2); // Units at bottom right
//  tft.drawCentreString("%HUM", 120, 70, 4); // Comment out to avoid font 4
//  tft.drawRect(5, 3, 230, 119, TFT_BLACK); // Draw bezel line
//
//  plotNeedle(0, 0, 0); // Put meter needle at 0
//}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################
void plotNeedle(float value, byte ms_delay, int x_adj, char* header)
{
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  char buf[8]; dtostrf(value, 4, 1, buf);
  tft.drawRightString(buf, 40+x_adj, 119 - 20, 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle util new value reached
//  while (!(value == old_analog)) {
//    if (old_analog < value) old_analog++;
//    else old_analog--;
//
//    if (ms_delay == 0) old_analog = value; // Update immediately id delay is 0

    float sdeg = map(value, -10, 110, -150, -30); // Map value to angle
    // Calcualte tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    tft.drawLine(120 + 20 * ltx - 1+x_adj, 140 - 20, osx - 1+x_adj, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx + x_adj, 140 - 20, osx+x_adj, osy, TFT_WHITE);
    tft.drawLine(120 + 20 * ltx + 1 + x_adj, 140 - 20, osx + 1+x_adj, osy, TFT_WHITE);

    // Re-plot text under needle
    tft.setTextColor(TFT_BLACK);
    tft.drawCentreString(header, 120 + x_adj, 70, 4); // // Comment out to avoid font 4

    // Store new needle end coords for next erase
    ltx = tx;
    osx = sx * 98 + 120;
    osy = sy * 98 + 140;

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    tft.drawLine(120 + 20 * ltx - 1+x_adj , 140 - 20, osx - 1 +x_adj, osy, TFT_RED);
    tft.drawLine(120 + 20 * ltx +x_adj, 140 - 20 , osx +x_adj, osy, TFT_MAGENTA);
    tft.drawLine(120 + 20 * ltx + 1 +x_adj , 140 - 20, osx + 1 +x_adj, osy, TFT_RED);

//    tft.drawLine(120 + (x_adj+20) * ltx - 1 + x_adj, 140 - 20, osx - 1+x_adj, osy, TFT_RED);
//    tft.drawLine(120 + (x_adj+20) * ltx + x_adj, 140 - 20 , osx+x_adj, osy, TFT_MAGENTA);
//    tft.drawLine(120 + (x_adj+20) * ltx + 1 + x_adj, 140 - 20, osx + 1+x_adj, osy, TFT_RED);

    // Slow needle down slightly as it approaches new postion
//    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;
//
//    // Wait before next update
//    delay(ms_delay);
//  }
}

// #########################################################################
//  Draw a linear meter on the screen
// #########################################################################
void plotLinear(char *label, int x, int y, int w)
{
  //int w = 36;
  tft.drawRect(x, y, w, 155, TFT_GREY);
  tft.fillRect(x+2, y + 19, w-3, 155 - 38, TFT_WHITE);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawCentreString(label, x + w / 2, y + 2, 2);

  for (int i = 0; i < 110; i += 10)
  {
    tft.drawFastHLine(x + 20, y + 27 + i, 6, TFT_BLACK);
  }

  for (int i = 0; i < 110; i += 50)
  {
    tft.drawFastHLine(x + 20, y + 27 + i, 9, TFT_BLACK);
  }
  
  tft.fillTriangle(x+3, y + 127, x+3+16, y+127, x + 3, y + 127 - 5, TFT_RED);
  tft.fillTriangle(x+3, y + 127, x+3+16, y+127, x + 3, y + 127 + 5, TFT_RED);
  
  tft.drawCentreString("    ", x + w / 2, y + 155 - 18, 2);
}

// #########################################################################
//  Adjust 6 linear meter pointer positions
// #########################################################################
void plotPointer(void)
{
  int dy = 187;
  byte pw = 16;

  int w = 55;
  
  
  // Move the 6 pointers one pixel towards new value
   tft.setTextColor(TFT_BLACK, TFT_BLACK);
  for (int i = 0; i < 3; i++)
  {
    if ( old_value2 >=0 ){
      char buf[8]; dtostrf(old_value2[i], 4, 0, buf);
      tft.drawRightString(buf, i * w + 36 - 5, 187 - 27 + 155 - 18, 2);
     
      old_value2[i] = value[i];
    }
  }

tft.setTextColor(TFT_GREEN, TFT_BLACK);
  // Move the 6 pointers one pixel towards new value
  for (int i = 0; i < 3; i++)
  {
    char buf[8]; dtostrf(value[i], 4, 0, buf);
    tft.drawRightString(buf, i * w + 36 - 5, 187 - 27 + 155 - 18, 2);

    int dx = 3 + w * i;
    if (value[i] < 0) value[i] = 0; // Limit value to emulate needle end stops
    if (value[i] > 100) value[i] = 100;

    while (!(value[i] == old_value[i])) {
      dy = 187 + 100 - old_value[i];
      if (old_value[i] > value[i])
      {
        tft.drawLine(dx, dy - 5, dx + pw, dy, TFT_WHITE);
        old_value[i]--;
        tft.drawLine(dx, dy + 6, dx + pw, dy + 1, TFT_RED);
      }
      else
      {
        tft.drawLine(dx, dy + 5, dx + pw, dy, TFT_WHITE);
        old_value[i]++;
        tft.drawLine(dx, dy - 6, dx + pw, dy - 1, TFT_RED);
      }
    }
  }
}


void analogMeter_V2(int x_adj, char* header)
{
  // Meter outline
  tft.fillRect(0+x_adj, 0, 239, 126, TFT_GREY);   // X, Y, width, height
  tft.fillRect(5+x_adj, 3, 230, 119, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (100 + tl) + 120;
    uint16_t y0 = sy * (100 + tl) + 140;
    uint16_t x1 = sx * 100 + 120;
    uint16_t y1 = sy * 100 + 140;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (100 + tl) + 120;
    int y2 = sy2 * (100 + tl) + 140;
    int x3 = sx2 * 100 + 120;
    int y3 = sy2 * 100 + 140;

    // Yellow zone limits
    //if (i >= -50 && i < 0) {
    //  tft.fillTriangle(x0, y0, x1, y1, x2, y2, TFT_YELLOW);
    //  tft.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_YELLOW);
    //}

    // Green zone limits
    if (i >= 0 && i < 25) {
      tft.fillTriangle(x0+x_adj, y0, x1+x_adj, y1, x2+x_adj, y2, TFT_GREEN);
      tft.fillTriangle(x1+x_adj, y1, x2+x_adj, y2, x3+x_adj, y3, TFT_GREEN);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      tft.fillTriangle(x0+x_adj, y0, x1+x_adj, y1, x2+x_adj, y2, TFT_ORANGE);
      tft.fillTriangle(x1+x_adj, y1, x2+x_adj, y2, x3+x_adj, y3, TFT_ORANGE);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords incase tick lenght changed
    x0 = sx * (100 + tl) + 120;
    y0 = sy * (100 + tl) + 140;
    x1 = sx * 100 + 120;
    y1 = sy * 100 + 140;

    // Draw tick
    tft.drawLine(x0+x_adj, y0, x1+x_adj, y1, TFT_BLACK);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions
      x0 = sx * (100 + tl + 10) + 120;
      y0 = sy * (100 + tl + 10) + 140;
      switch (i / 25) {
        case -2: tft.drawCentreString("0", x0+x_adj, y0 - 12, 2); break;
        case -1: tft.drawCentreString("25", x0+x_adj, y0 - 9, 2); break;
        case 0: tft.drawCentreString("50", x0+x_adj, y0 - 6, 2); break;
        case 1: tft.drawCentreString("75", x0+x_adj, y0 - 9, 2); break;
        case 2: tft.drawCentreString("100", x0+x_adj, y0 - 12, 2); break;
      }
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * 100 + 120;
    y0 = sy * 100 + 140;
    // Draw scale arc, don't draw the last part
    if (i < 50) tft.drawLine(x0+x_adj, y0, x1+x_adj, y1, TFT_BLACK);
  }


  tft.drawCentreString(header, 120+x_adj, 70, 4); // Comment out to avoid font 4
  tft.drawRect(5+x_adj, 3, 230, 119, TFT_BLACK); // Draw bezel line

  plotNeedle(0, 0,240,header); // Put meter needle at 0
}



