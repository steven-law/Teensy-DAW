#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define CS_PIN  8
#define TFT_DC  9
#define TFT_CS 10
// MOSI=11, MISO=12, SCK=13

XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  2

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 180
#define TS_MINY 260
#define TS_MAXX 3730
#define TS_MAXY 3800

#define STEP_FRAME_W 15
#define STEP_FRAME_H 20
int step_Frame_X;
int step_Frame_Y;
int touchX;
int touchY;

int dSteps;
int dTrack;

bool drumbeat[8][16] {
  {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
};
void setup() {
  Serial.begin(38400);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(3);
  while (!Serial && (millis() <= 1000));


  tft.fillScreen(ILI9341_DARKGREY);
  for (int i = 0; i < 17; i++) {   //vert Lines
    step_Frame_X = i * STEP_FRAME_W;
    tft.drawFastVLine(step_Frame_X + STEP_FRAME_W, 20, 160, ILI9341_WHITE); //(x, y-start, length, color)

  }
  for (int i = 0; i < 9; i++) {   //hor lines
    step_Frame_Y = i * 20;
    tft.drawFastHLine(15, step_Frame_Y + STEP_FRAME_H, 240, ILI9341_WHITE); //(x-start, y, length, color)
    tft.setCursor(270, step_Frame_Y + 25);
    tft.setTextColor(step_Frame_Y * 36751);
    tft.print("Drum ");
    tft.setCursor(300, step_Frame_Y + 25);
    tft.setTextColor(step_Frame_Y * 36751);
    tft.print(i + 1);
  }
}

boolean wastouched = true;


void loop() {
  boolean istouched = ts.touched();
  TS_Point p = ts.getPoint();
  tft.fillRect(0, 190, 300, 240, ILI9341_DARKGREY);
  tft.setTextColor(ILI9341_GREEN);
  tft.setFont(Arial_10);
  tft.setCursor(20, 200);
  tft.print("X = ");
  tft.print(touchX);
  tft.setCursor(100, 200);
  tft.print("Y = ");
  tft.print(touchY);

  if (istouched) {
    touchX = map(p.x, 180, 3730, 0, 320);
    touchY = map(p.y, 260, 3760, 0, 240);
    if (touchX > 15 && touchX < 255 && touchY > 20 && touchY < 188) {

      dTrack = (touchX > (dSteps * STEP_FRAME_W) + 15 && (touchX < (dSteps * STEP_FRAME_H) + STEP_FRAME_H) + 15);
      dSteps = (touchY > (dTrack * STEP_FRAME_H) + 20 && (touchY < (dTrack * STEP_FRAME_W) + STEP_FRAME_W) + 20);

      if (drumbeat[dTrack][dSteps] == LOW) {
        drumbeat[dTrack][dSteps] = HIGH;
        tft.fillCircle(dSteps * STEP_FRAME_W + 22, dTrack * STEP_FRAME_H + 30, 5, ILI9341_RED);  //draw the active step circles
      }
      else if (drumbeat[dTrack][dSteps] == HIGH) {
        drumbeat[dTrack][dSteps] = LOW;
        tft.fillCircle(dSteps * STEP_FRAME_W + 22, dTrack * STEP_FRAME_H + 30, 5, ILI9341_DARKGREY);  //draw the active step circles



      }
    }
    delay(100);
  }
}
