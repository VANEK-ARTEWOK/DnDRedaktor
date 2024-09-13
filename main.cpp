

#include "TXLib.h"











struct Button
{
 int x ;
 int y ;
 int width ;
 int height ;

 void draw()
 {
    txSetColor (TX_RED,10);
    txSetFillColor (TX_TRANSPARENT);
    Win32::RoundRect (txDC(),x+3, y+3, x+width+3, y+height+3,30,30);
    txSelectFont("Time New Roman",15);
    txDrawText(x, y, x+width, y+height,"Раса");
 }
};



void drawWorkspase(int x,int y ,int width,int height)
{
txSetColor (TX_RED,10);
    txSetFillColor (TX_TRANSPARENT);
    txRectangle (x, y, x+width, y+height);

 }
int main()
    {
    txCreateWindow (1540, 800);
    txTextCursor (false);

     Button but1={55,55,150,35};



   while(!GetAsyncKeyState (VK_ESCAPE))
   {
    drawWorkspase(440,220 , 800, 500);

    but1.draw();







    txSleep(10);
   }


    txDisableAutoPause();
    return 0;
    }

