#include "SED1335.h"
SED1335 lcd;

void setup() {
// Add your initialization code here
//Initializing LCD
lcd.GLCD_Initialize();
//lcd.setInverse(true);
lcd.GLCD_ClearGraphic();
lcd.GLCD_ClearText();
//Initializing SD
Serial.begin(9600);
while (!Serial);
Serial.println("STARTED");
pinMode(10, OUTPUT);
lcd.GLCD_TextGoTo(0, 0);
lcd.GLCD_WriteText("initialization done!");
}

// The loop function is called in an endless loop
void loop() {

// delay(1000);
// lcd.GLCD_Bitmap("240320/2.bmp", 0, 0, 240, 320);
// delay(1000);
// lcd.GLCD_Bitmap("240320/3.bmp", 0, 0, 240, 320);
// delay(1000);
// lcd.GLCD_Bitmap("240320/4.bmp", 0, 0, 240, 320);
// delay(1000);
// lcd.GLCD_Bitmap("240320/5.bmp", 0, 0, 240, 320);
// delay(1000);
}
