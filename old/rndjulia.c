/*                                                                                                                     
  __    _ ______  ______  __  __  _____  _____  ______  ____  ____   _   ______  _____  _____   ____  ____   _  ______  
 \  \  //|   ___||   ___||  |/ / /     \/     \|   ___||    ||    \ | | |   ___|/     \|     \ |    ||    \ | ||   ___| 
  \  \// |   ___||   ___||     \ |     ||     ||   ___||    ||     \| | |   |__ |     ||      \|    ||     \| ||   |  | 
   \__/  |______||______||__|\__\\_____/\_____/|___|   |____||__/\____| |______|\_____/|______/|____||__/\____||______| 
                                                                                                                        
                                                                                                                        */ 
/*----------------------------------------------------------------------+
 |                                                                      |
 |             rndjulia.c -- demonstrate fractal in gfx                 |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
// Standard includes
#include <stdlib.h>
#include <time.h>
#include <gigatron/sys.h>

#define HEIGHT 120
#define WIDTH 160
#define SCALE 1.7
#define YSTEP 1
#define XSTEP 1
#define CX -0.8
#define CY 0.156

static unsigned char sm[HEIGHT][WIDTH];

int julia(float x, float y) {
 float zz;
 float a;
 float b;
 float a2;
 float b2;
 float atemp;
 int i;
  
  a = x;
  b = y;  
  i = 0;
  while (i < 15)
  {
    a2 = a * a;
    b2 = b * b;
    zz = a2 + b2;
    if(zz > 4) break;
    
    atemp = a2 - b2 + CX;
    b = 2.0 * a * b + CY;
    a = atemp;
    i++;
  }
  return i;
}

void drawPixel(int x, int y, int color)
{
  screenMemory[y][x] = color;
}

void main(void) {
  int x, y, data, n;
  int col[16];
  float sx, sy;

  srand(time(0));
  
  SYS_SetMode(3);
 
  col[14] = 0x01;
  col[13] = 0x02;
  col[12] = 0x03;
  col[11] = 0x07;
  col[10] = 0x0b;
  col[9] = 0x0f;
  col[8] = 0x0e;
  col[7] = 0x0d;
  col[6] = 0x0c;
  col[5] = 0x3c;
  col[4] = 0x38;
  col[3] = 0x34;
  col[2] = 0x30;
  col[1] = 0x20;
  col[0] = 0x10;
  col[15] = 0x00;

  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      drawPixel(x,y,col[15]);
    }
  } 
 
  for(n = 0; n < 19200; n = n + 1 ) {
    y = rand() % HEIGHT;
    x = rand() % WIDTH;
    
    if(sm[y][x] == 'y') n--;
    
    if(sm[y][x] != 'y') { 
      sx = (SCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (SCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = julia(sx, sy);
      drawPixel(x,y,col[data]);
      sm[y][x] = 'y';
    }
  }
  SYS_SetMode(0);
}
