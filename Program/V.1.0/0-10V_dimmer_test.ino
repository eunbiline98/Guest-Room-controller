#include <TM1637Display.h>

#define CLK 3
#define DIO 2

int upDim = 4;
int downDim = 5;
int upVal;
int downVal;
int pwmout = 9;
int bright = 17;
int fade = 150;

int percent = 0;

unsigned int angka = 0;
TM1637Display display(CLK, DIO);

void setup()
{
  display.setBrightness(0x0f);
  pinMode(upDim, INPUT_PULLUP);
  pinMode(downDim, INPUT_PULLUP);
  pinMode(pwmout, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int val = 1;
  upVal = digitalRead(upDim);
  downVal = digitalRead(downDim);
  delay(fade);
  if (upVal == 0)
  {
    bright = bright + val;
  }
  if (downVal == 0)
  {
    bright = bright - val;
  }
  if (bright > 255)
  {
    bright = 255;
  }
  if (bright < 0)
  {
    bright = 0;
  }

  percent = ((bright / 255.00) * 100);

  analogWrite(pwmout, bright);
  Serial.print("percentage = ");
  Serial.print(percent);
  Serial.println("%\n\n");
  display.showNumberDec(percent);
}