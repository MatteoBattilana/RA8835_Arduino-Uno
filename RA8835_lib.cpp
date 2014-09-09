/*
 * RA8835_lib.c
 *
 *  Created on: 4 Sep 2014
 *      Author: Jianyuan
 */

#include "RA8835_lib.h"

SED1335::SED1335(){
	GLCD_InitializePorts();
}


void SED1335::n_delay(){
  volatile byte i;
  for(i = 0; i < (F_CPU/1000000); i++)
  {
	asm("nop");
  }
}

void SED1335::GLCD_InitializePorts() {	GLCD_DATA_DDR1 |= GLCD_DATA_MASK1;	GLCD_DATA_DDR2 |= GLCD_DATA_MASK2;
	GLCD_CTRL_DDR = ((1 << SED1335_A0) | (1 << SED1335_WR) | (1 << SED1335_RD) | (1 << SED1335_CS));
	GLCD_CTRL_PORT |= ((1 << SED1335_A0) | (1 << SED1335_WR) | (1 << SED1335_RD) | (1 << SED1335_CS));
}

void SED1335::GLCD_WriteCommand(byte command) {	GLCD_DATA_PORT1 &= ~GLCD_DATA_MASK1;	GLCD_DATA_PORT1 |= (command GLCD_DATA_SHIFT1);
	GLCD_DATA_PORT2 &= ~GLCD_DATA_MASK2;
	GLCD_DATA_PORT2 |= (command GLCD_DATA_SHIFT2);
	GLCD_CTRL_PORT &= ~((1 << SED1335_WR) | (1 << SED1335_CS));
	n_delay();
	GLCD_CTRL_PORT |= ((1 << SED1335_WR) | (1 << SED1335_CS));

}
void SED1335::GLCD_WriteData(byte data) {	GLCD_DATA_PORT1 &= ~GLCD_DATA_MASK1;	GLCD_DATA_PORT1 |= (data GLCD_DATA_SHIFT1);
	GLCD_DATA_PORT2 &= ~GLCD_DATA_MASK2;
	GLCD_DATA_PORT2 |= (data GLCD_DATA_SHIFT2);
	GLCD_CTRL_PORT &= ~((1 << SED1335_WR) | (1 << SED1335_A0) | (1 << SED1335_CS));
	n_delay();
	GLCD_CTRL_PORT |=((1 << SED1335_WR) |(1 << SED1335_A0)| (1 << SED1335_CS));
}

unsigned char SED1335::GLCD_ReadData(){
	byte tmp;
	GLCD_DATA_DDR1 &= ~GLCD_DATA_MASK1;
	GLCD_DATA_DDR2 &= ~GLCD_DATA_MASK2;
	GLCD_CTRL_PORT &= ~((1 << SED1335_RD) | (1 << SED1335_CS) );
	n_delay();
	tmp = (GLCD_DATA_PIN1 GLCD_DATA_RSHIFT1) | (GLCD_DATA_PIN2 GLCD_DATA_RSHIFT2);
	GLCD_CTRL_PORT |= ((1 << SED1335_RD) | (1 << SED1335_CS) );
	GLCD_DATA_DDR1 |= GLCD_DATA_MASK1;
	GLCD_DATA_DDR2 |= GLCD_DATA_MASK2;
	  return tmp;
}

//LCD functions
void SED1335::GLCD_Initialize(){
	GLCD_InitializePorts();

	GLCD_WriteCommand(SED1335_SYSTEM_SET);
	GLCD_WriteData(0x30);
	//GLCD_WriteData(SED1335_SYS_P2);
	GLCD_WriteData(0x87);
	GLCD_WriteData(0x07);
	GLCD_WriteData(SED1335_CR);
	GLCD_WriteData(SED1335_TCR);
	GLCD_WriteData(SED1335_LF);
	GLCD_WriteData(SED1335_APL);
	GLCD_WriteData(SED1335_APH);

	GLCD_WriteCommand(SED1335_SCROLL);
	GLCD_WriteData(SED1335_SAD1L);
	GLCD_WriteData(SED1335_SAD1H);
	GLCD_WriteData(SED1335_SL1);
	GLCD_WriteData(SED1335_SAD2L);
	GLCD_WriteData(SED1335_SAD2H);
	GLCD_WriteData(SED1335_SL2);
	GLCD_WriteData(SED1335_SAD3L);
	GLCD_WriteData(SED1335_SAD3H);
	GLCD_WriteData(SED1335_SAD4L);
	GLCD_WriteData(SED1335_SAD4H);

	GLCD_WriteCommand(SED1335_HDOT_SCR);
	GLCD_WriteData(SED1335_SCRD);

	GLCD_WriteCommand(SED1335_OVLAY);
	GLCD_WriteData(0x01);

	GLCD_WriteCommand(SED1335_DISP_OFF);
	GLCD_WriteData(SED1335_FLASH);

	GLCD_WriteCommand(SED1335_CSRFORM);
	GLCD_WriteData(SED1335_CRX);
	GLCD_WriteData(SED1335_CSRF_P2);

	GLCD_WriteCommand(SED1335_CGRAM_ADR);
	GLCD_WriteData(SED1335_SAGL);
	GLCD_WriteData(SED1335_SAGH);

	GLCD_WriteCommand(SED1335_CSRDIR_R);

	GLCD_WriteCommand(SED1335_DISP_ON);
	GLCD_WriteData(SED1335_FLASH);

}

void SED1335::GLCD_SetPixel(unsigned int x,unsigned int y, int color){
	unsigned char tmp = 0;
	GLCD_GraphicGoTo(x,y);
	//unsigned int address = SED1335_GRAPHICSTART + (40 * y) + (x/8);
	//GLCD_SetCursorAddress(address);

	GLCD_WriteCommand(SED1335_MREAD);
	tmp = GLCD_ReadData();

	if(color)
	  tmp |= (1 << (SED1335_FX - (x % 8)));
	else
	  tmp &= ~(1 << (SED1335_FX - (x % 8)));

	GLCD_GraphicGoTo(x,y);
	GLCD_WriteCommand(SED1335_MWRITE);
	GLCD_WriteData(tmp);

}
void SED1335::GLCD_WriteText(char * text){
	GLCD_WriteCommand(SED1335_MWRITE);
	while(*text)
		GLCD_WriteData(*text++);
}
void SED1335::GLCD_SetCursorAddress(unsigned int address){
	GLCD_WriteCommand(SED1335_CSRW);
	GLCD_WriteData((unsigned char)(address & 0xFF));
	GLCD_WriteData((unsigned char)(address >> 8));

}
void SED1335::GLCD_GraphicGoTo(unsigned int x, unsigned int y)
{
	GLCD_SetCursorAddress(SED1335_GRAPHICSTART + (y * 40) + x/8);
}
void SED1335::GLCD_TextGoTo(unsigned char x, unsigned char y)
{
	GLCD_SetCursorAddress((y * 40) + x);
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void SED1335::GLCD_ClearText(void)
{
	int i;
	GLCD_TextGoTo(0,0);
	GLCD_WriteCommand(SED1335_MWRITE);
	for(i = 0; i < 1200; i++)
		GLCD_WriteData(' ');
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void SED1335::GLCD_ClearGraphic(void)
{
	unsigned int i;
	GLCD_SetCursorAddress(SED1335_GRAPHICSTART);
	GLCD_WriteCommand(SED1335_MWRITE);
	for(i = 0; i < (40 * 240); i++)
		GLCD_WriteData(0x00);
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/*void SED1335::GLCD_Bitmap(prog_uchar * bmp, int x, int y, int width, int height)
{
	byte bitmap;
	int j=0;
	for(int h = 0; h < height; h++)
	{
		GLCD_GraphicGoTo(x,y+h);
		GLCD_WriteCommand(SED1335_MWRITE);
		 for(int i = 0; i < width; i++)     //(PIXELS PER LINE/FONT WIDTH * NUMBER OF LINES)
		 {
		   bitmap = pgm_read_byte_near(bmp+(i+j));
		   GLCD_WriteData(GLCD_ReadByteFromROMMemory(bmp+j+i));
		 }
	 j=j+width;
	}
}*/
void SED1335::GLCD_Bitmap(unsigned char * bmp, int x, int y, int width, int height)
{
unsigned int i, j;
for(i = 0; i < height ; i++)
	{
	GLCD_GraphicGoTo(x, y+i);
	GLCD_WriteCommand(SED1335_MWRITE);
	for(j = 0; j < width/8; j++)
		GLCD_WriteData(GLCD_ReadByteFromROMMemory(bmp+j+(40*i)));
	}
}
unsigned char SED1335::GLCD_ReadByteFromROMMemory(unsigned char * ptr)
{
	return pgm_read_byte_near(ptr);
}

void SED1335::GLCD_createLine(int x0,int y0,int x1,int y1,int color){
	 boolean steep = abs(y1 - y0) > abs(x1 - x0);
	  if(steep){
	    //swap(x0, y0)
	    //swap(x1, y1)
	    int tmp=x0;
	    x0=y0;
	    y0=tmp;
	    tmp=x1;
	    x1=y1;
	    y1=tmp;
	  }
	  if(x0 > x1){
	    //swap(x0, x1)
	    //swap(y0, y1)
	    int tmp=x0;
	    x0=x1;
	    x1=tmp;
	    tmp=y0;
	    y0=y1;
	    y1=tmp;
	  }
	  int deltax = x1 - x0;
	  int deltay = abs(y1 - y0);
	  int error = deltax / 2;
	  int ystep=-1;
	  int y = y0;
	  if(y0 < y1){ystep= 1;}
	  for(int x =x0;x<=x1;x++){
	    if(steep){GLCD_SetPixel(y,x,color);}else{GLCD_SetPixel(x,y,color);}
	    error = error - deltay;
	    if(error < 0){
	      y = y + ystep;
	      error = error + deltax;
	    }
	  }
}

void SED1335::GLCD_drawRect(int x,int y,int height,int wight,int color){
	  int j;
	  for (j = 0; j < height; j++) {
		  GLCD_SetPixel(x, y + j, color);
		  GLCD_SetPixel(x + wight - 1, y + j, color);
		}
	  // Draw horizontal lines
	  for (j = 0; j < wight; j++)	{
		  GLCD_SetPixel(x + j, y, color);
		  GLCD_SetPixel(x + j, y + height - 1, color);
		}

}

void SED1335::GLCD_fillRect(int x1, int y1, int x2, int y2, int color){
	for (int i = y1; i <= y2; i++)
		GLCD_createLine(x1, i, x2, i, color);

}

void SED1335::GLCD_createCircle(int x0, int y0, int radius, int color){
	int16_t f = 1 - radius;
	  int16_t ddF_x = 1;
	  int16_t ddF_y = -2 * radius;
	  int16_t x = 0;
	  int16_t y = radius;

	  GLCD_SetPixel(x0, y0+radius, color);
	  GLCD_SetPixel(x0, y0-radius, color);
	  GLCD_SetPixel(x0+radius, y0, color);
	  GLCD_SetPixel(x0-radius, y0, color);

	  while (x<y) {
	    if (f >= 0) {
	      y--;
	      ddF_y += 2;
	      f += ddF_y;
	    }
	    x++;
	    ddF_x += 2;
	    f += ddF_x;

	    GLCD_SetPixel(x0 + x, y0 + y, color);
	    GLCD_SetPixel(x0 - x, y0 + y, color);
	    GLCD_SetPixel(x0 + x, y0 - y, color);
	    GLCD_SetPixel(x0 - x, y0 - y, color);
	    GLCD_SetPixel(x0 + y, y0 + x, color);
	    GLCD_SetPixel(x0 - y, y0 + x, color);
	    GLCD_SetPixel(x0 + y, y0 - x, color);
	    GLCD_SetPixel(x0 - y, y0 - x, color);

	  }
}
