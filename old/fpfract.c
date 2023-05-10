/*   _____                                 _____                                                                                                                
  __|   _ |__  ______  ______  ____     __| __  |__  ____  ____      ____  __   _  ____   _  ______  ____   _   ______  _____  _____   ____  ____   _  ______   
 \  \  //    ||   ___||   ___||    \   |  |/ /     ||    ||    |    |    ||  | | ||    \ | ||   ___||    \ | | |   ___|/     \|     \ |    ||    \ | ||   ___|  
 |\  \//     ||   ___| `-.`-. |     \  |     \     ||    ||    |_  _|    ||  |_| ||     \| ||   ___||     \| | |   |__ |     ||      \|    ||     \| ||   |  |  
 |_\__/    __||______||______||__|\__\ |__|\__\  __||____||______||______||______||__/\____||______||__/\____| |______|\_____/|______/|____||__/\____||______|  
    |_____|                               |_____|                                                                                                               
                                           _                                                                                                                    
  _____   __   _  ____  ______  __  __    / |  _____   ____  _____    __  __    _                                                                               
 /     \ |  | | ||    ||   ___||  |/ /   / /  |     \ |    ||     | _|  |_\ \  //                                                                               
 |     | |  |_| ||    ||   |__ |     \  |_/   |      \|    ||     \|_    _|\ \//                                                                                
 \___/\_\|______||____||______||__|\__\       |______/|____||__|\__\ |__|  /__/                                                                                 
                                                  _                                                                                                             
   __    _ ______  ______  __  __  _____  _____   / |______  ____  ____   _                                                                                     
  \  \  //|   ___||   ___||  |/ / /     \/     \ / /|   ___||    ||    \ | |                                                                                     
   \  \// |   ___||   ___||     \ |     ||     ||_/ |   ___||    ||     \| |                                                                                     
    \__/  |______||______||__|\__\\_____/\_____/    |___|   |____||__/\____|*/ 

/*----------------------------------------------------------------------+
 |                                                                      |
 |             fpfract.c -- demonstrate fractal in gfx                  |
 |                                                                      |
 +----------------------------------------------------------------------*/
 
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <gigatron/sys.h>
#include <gigatron/console.h>
#include <stdarg.h>

#define BSCALE 1.6 //brot
#define JSCALE 1.7 //julia
#define BSSCALE 2.1 //burnship
#define YSTEP 1
#define XSTEP 1
#define CX -0.8
#define CY 0.156

int readint(const char *prompt)
{
  char buffer[32];
  cprintf(prompt, strlen(prompt));
  console_readline(buffer, sizeof(buffer));
  return atoi(buffer);
}
  
int mandelbrot(float x, float y, int ITE) {
 float zz;
 float a;
 float b;
 float a2;
 float b2;
 float atemp;
 int i;
  
  a = 0;
  b = 0;  
  i = 0;
  while (i < ITE)
  {
    a2 = a * a;
    b2 = b * b;
    zz = a2 + b2;
    if(zz > 4) break;
    
    atemp = a2 - b2 + x;
    b = 2.0 * a * b + y;
    a = atemp;
    i++;
  }
  return i;
}

int julia(float x, float y, int ITE) {
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
  while (i < ITE)
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

int burnship(float x, float y, int ITE) {
 float zz;
 float a;
 float b;
 float a2;
 float b2;
 float atemp;
 int i;
  
  a = 0;
  b = 0;  
  i = 0;
  while (i < ITE)
  {
    a2 = a * a;
    b2 = b * b;
    zz = a2 + b2;
    if(zz > 4) break;
    
    atemp = a2 - b2 + x;
    b = abs(2.0 * a * b) + y;
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
  int x, y, data;
  int col;
  float sx, sy;
  int par, IT;
  int WIDTH; //26 //160
  int HEIGHT; //15 //120
  
  cprintf("Floating Point Fractals:\n");
  cprintf("#1 Mandelbrot\n"); 
  cprintf("#2 Julia\n");
  cprintf("#3 Burning Ship\n\n");  
  par=readint("Choose Fractal #1-3:");
  WIDTH=readint("Screen Size X #26-160:");
  HEIGHT=readint("Screen Size Y #15-120:");
  IT=readint("Iteration Count #2-63:");
  
  SYS_SetMode(3);
  
  for(y = 0; y < HEIGHT; y++ ) {
    for(x = 0; x < WIDTH; x++ ) {
      drawPixel(x,y,0);
    }
  } 
    
  for(y = 0; y < HEIGHT; y = y + YSTEP ) {
    for(x = 0; x < WIDTH; x = x + XSTEP ) {
      
      switch(par){    
      case 1:    
      //brot
      sx = -0.7 + (BSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (BSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = mandelbrot(sx, sy, IT);
      break;    
      case 2:    
      //julia
      sx = (JSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (JSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = julia(sx, sy, IT);
      break;
      case 3:    
      //burnship
      sx = -0.4 + (BSSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = -0.3 + (BSSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = burnship(sx, sy, IT);
      break;      
      default:
      //brot    
      sx = -0.7 + (BSCALE * (WIDTH/2.0 - x) / (WIDTH/2.0))*(-1);
      sy = (BSCALE * (HEIGHT/2.0 - y) / (HEIGHT/2.0))*(-0.75);
      data = mandelbrot(sx, sy, IT);
      }   
            
      col = IT - data;
      drawPixel(x,y,col);
    }
  }
  SYS_SetMode(0);
}
