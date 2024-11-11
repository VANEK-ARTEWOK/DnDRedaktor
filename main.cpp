

#include "TXLib.h"
#include <fstream>

using namespace std;


struct Draw
{
 int x ;
 int y ;
 int w ;
 int h ;
 const char* text;

 void draw()
 {
  txSetColor(TX_WHITE);
  txSetFillColor(TX_GRAY);
  //win32::Round

 }
};
struct Pictures
{
 int x ;
 int y ;
 string adress;
 HDC image;
 int w ;
 int h ;
 int w_shr ;
 int h_shr ;
 string contegor;
 bool vizible;
 void draw()
 {

      if(vizible)  Win32::TransparentBlt(txDC(),x ,y  , w_shr, h_shr ,image, 0, 0, w ,h ,RGB(255, 0, 0));
 }
bool click()
  {
       return(txMouseButtons() == 1 && txMouseX()>x && txMouseX()<x+w_shr && txMouseY()>y && txMouseY()<y+h_shr );

  }


};


struct Button
{
 int x ;
 int y ;
 int w ;
 int h ;
 const char* text;
 string contegor;

 void draw()
 {
    txSetColor (TX_RED,10);

    txSetFillColor (TX_GRAY);
    Win32::RoundRect (txDC(),x, y, x+w, y+h,30,30);
    txSelectFont("Time New Roman",15);
    txDrawText(x, y, x+w, y+h,text);

 }

  bool click()
  {
       return(txMouseButtons()==1 && txMouseX()>x && txMouseX()<x+w && txMouseY()>y && txMouseY()<y+h);

  }
};

void drawWorkspase(int x,int y ,int w,int h)
{
txSetColor (TX_RED,10);
    txSetFillColor (TX_TRANSPARENT);
    txRectangle (x, y, x+w, y+h);

 }


string DialogFile(bool isSave)
{
 string  filename = "";
  OPENFILENAME ofn = {0};
  TCHAR szFile[260]={0};
  ZeroMemory(&ofn,sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = txWindow();
  ofn.lpstrFile = szFile;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter =("Text\0*.TXT\0");
  ofn.nFilterIndex = 1;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir =NULL;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if(isSave)
   {
    if(GetSaveFileName(&ofn) == TRUE)
     {
      filename = ofn.lpstrFile;
      filename = filename + ".txt";
     }
   }
   else
   {
     if(GetOpenFileName(&ofn) == TRUE)
      {
       filename = ofn.lpstrFile;
      }
   }

  return filename;
}

int main()
{
txCreateWindow (1500, 760);
txTextCursor (false);

     int count_pic = 19;
     int count_butn = 7;
     int nCentrPic = 0;

     char str[50];

     Button butn[count_butn];
     butn[0]={55,55,150,35,"–аса","–аса"};
     butn[1]={255,55,150,35," лассы"," лассы"};
     butn[2]={455,55,150,35,"одежда","одежда"};
     butn[3]={655,55,150,35,"питомцы","питомцы"};
     butn[4]={855,55,150,35,"оружее","оружее"};
     butn[5]={1200,75,210,35,"сахранить","сахранение"};
     butn[6]={1150,105,210,35,"загрузить","загрузка"};
     HDC Fon =txLoadImage ("картинки/фон.bmp");
     //HDC Bnt =txLoadImage ("кнопка.bmp");

     int butn_save = count_butn -2;
     int butn_load = count_butn -1;


     Pictures pic[count_pic];
     pic[0]={10,100,"картинки/расы/кенку.bmp",txLoadImage ("картинки/расы/кенку.bmp"),564,729,80,100,"–аса"};
     pic[1]={10,200,"картинки/расы/орк.bmp",txLoadImage ("картинки/расы/орк.bmp"),216,281,80,100,"–аса"};
     pic[2]={10,300,"картинки/расы/дварф.bmp",txLoadImage ("картинки/расы/дварф.bmp"),184,274,80,100,"–аса"};
     pic[3]={10,400,"картинки/расы/кот.bmp",txLoadImage ("картинки/расы/кот.bmp"),209,241,80,100,"–аса"};
     pic[4]={10,500,"картинки/расы/гоблин.bmp",txLoadImage ("картинки/расы/гоблин.bmp"),216,497,80,100,"–аса"};
     pic[5]={10,600,"картинки/расы/грунг.bmp",txLoadImage ("картинки/расы/грунг.bmp"),184,274,80,100,"–аса"};
     pic[6]={10,700,"картинки/расы/ааракана.bmp",txLoadImage ("картинки/расы/ааракана.bmp"),216,208,80,100,"–аса"};
     pic[7]={60,100,"картинки/расы/автогном.bmp",txLoadImage ("картинки/расы/автогном.bmp"),216,324,80,100,"–аса"};
     pic[8]={60,200,"картинки/расы/плазмоид.bmp",txLoadImage ("картинки/расы/плазмоид.bmp"),209,241,80,100,"–аса"};
     pic[9]={60,300,"картинки/расы/кованый.bmp",txLoadImage ("картинки/расы/кованый.bmp"),287,512,80,100,"–аса"};

     pic[10]={10,100,"картинки/брон€/шл€па.bmp",txLoadImage ("картинки/брон€/шл€па.bmp"),225,225,80,100,"одежда"};
     pic[11]={10,200,"картинки/брон€/нагрудник.bmp",txLoadImage ("картинки/брон€/нагрудник.bmp"),225,225,80,100,"одежда"};
     pic[12]={10,300,"картинки/брон€/маска.bmp",txLoadImage ("картинки/брон€/маска.bmp"),194,257,80,100,"одежда"};
     pic[13]={10,400,"картинки/брон€/чума.bmp",txLoadImage ("картинки/брон€/чума.bmp"),225,225,80,100,"одежда"};
     pic[14]={10,500,"картинки/брон€/шлем.bmp",txLoadImage ("картинки/брон€/шлем.bmp"),219,230,80,100,"одежда"};
     pic[15]={10,600,"картинки/брон€/ковбой.bmp",txLoadImage ("картинки/брон€/ковбой.bmp"),225,225,80,100,"одежда"};

     pic[16]={10,100,"картинки/питомцы/акулака.bmp",txLoadImage ("картинки/питомцы/акулака.bmp"),169,110,100,80,"питомцы"};
     pic[17]={10,200,"картинки/питомцы/курица.bmp",txLoadImage ("картинки/питомцы/курица.bmp"),300,300,100,100,"питомцы"};
     pic[18]={10,300,"картинки/питомцы/дракон.bmp",txLoadImage ("картинки/питомцы/дракон.bmp"),215,117,100,80,"питомцы"};

    // pic[19]={10,100,,txLoadImage ("картинки/брон€/маска.bmp"),194,257,80,100,false,"оружее"};
     //pic[20]={10,200,,txLoadImage ("картинки/брон€/чума.bmp"),225,225,80,100,false,"оружее"};
     //pic[21]={10,300,,txLoadImage ("картинки/брон€/шлем.bmp"),219,230,80,100,false,"оружее"};
     //pic[22]={10,400,,txLoadImage ("картинки/брон€/ковбой.bmp"),225,225,80,100,false,"оружее"};

       for(int i=0;i< count_butn;i++)
       {
        pic[i].vizible = false;
       }



     int vybor = 1;
     bool mause_down = false ;

     Pictures centr_pic[100];


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor(TX_BLACK);
        txClear();
        txBegin();

        Win32::TransparentBlt(txDC(),0 ,0  , 1540, 800 ,Fon, 0, 0, 1540 ,800 ,RGB(255, 0, 0));
        //Win32::TransparentBlt(txDC(),1200 ,45 , 200, 77 ,Bnt, 0, 0, 200 ,77 ,RGB(255, 0, 0));
        drawWorkspase(440,220 , 800, 500);


        for(int i=0;i<7;i++)
        {
            butn[i].draw();

        }

        for(int i=0;i<count_pic;i++)
        {
            pic[i].draw();
        }

        for(int i=0;i<nCentrPic;i++)
        {
            centr_pic[i].draw();
        }


        for(int nbutn=0;nbutn<4;nbutn++)
        {
            if(butn[nbutn].click())
            {
                for(int npic=0;npic<count_pic;npic++)
                {
                    pic[npic].vizible = false;
                    if(pic[npic].contegor==butn[nbutn].contegor)
                    {
                        pic[npic].vizible = true;
                    }
                }
            }
        }

        for(int npic=0; npic<count_pic; npic++)
        {
            if(pic[npic].click() && pic[npic].vizible)
            {
                while(txMouseButtons() == 1)
                {
                    txSleep(10);
                }
                centr_pic[nCentrPic] = {900,
                                        500,
                                        pic[npic].adress,
                                        pic[npic].image,
                                        pic[npic].w,
                                        pic[npic].h,
                                        pic[npic].w_shr,
                                        pic[npic].h_shr,
                                        pic[npic].contegor,
                                        pic[npic].vizible
                                        };
                nCentrPic++;
            }
        }

        sprintf(str, "C_Centr_pic = %d", nCentrPic);
        txTextOut(0, 0, str);


         for(int npic =0;npic<nCentrPic; npic++ )
          {
           if(centr_pic[npic].click()&&centr_pic[npic].vizible)
           {
            vybor= npic;
            mause_down = false ;
           }
          }

           if(vybor>=0)
             {
               if(txMouseButtons()==1 && !mause_down)
               {
                 centr_pic[vybor].x=txMouseX() -centr_pic[vybor].w/2;
                 centr_pic[vybor].y=txMouseY() -centr_pic[vybor].h/2;
               }
               else
               {
                if(txMouseButtons()!=1)
                 {
                   mause_down = true;

                 }


               }
              }


           if(vybor>=0)
             {
              if(txMouseButtons() == 1 && !mause_down)
               {
                centr_pic[vybor].x = txMouseX() - centr_pic[vybor].w_shr/2;
                centr_pic[vybor].y = txMouseY() - centr_pic[vybor].w_shr/2;
               }
               else
               {
               if(txMouseButtons() != 1)
                {
                mause_down = true;
                }

               }


              if(GetAsyncKeyState (VK_UP))
               {
                centr_pic[vybor].y -= 5;
               }
             if(GetAsyncKeyState (VK_DOWN))
               {
                centr_pic[vybor].y += 5;
                }
             if(GetAsyncKeyState (VK_LEFT))
               {
                centr_pic[vybor].x -= 5;
                }
             if(GetAsyncKeyState (VK_RIGHT))
               {
                centr_pic[vybor].x += 5;
               }
            if(GetAsyncKeyState (VK_OEM_PLUS))
               {
                centr_pic[vybor].w_shr = centr_pic[vybor].w_shr*1.15;
                centr_pic[vybor].h_shr = centr_pic[vybor].h_shr*1.15;
               }
              if(GetAsyncKeyState (VK_OEM_MINUS))
               {
                centr_pic[vybor].w_shr = centr_pic[vybor].w_shr*0.95;
                centr_pic[vybor].h_shr = centr_pic[vybor].h_shr*0.95;
               }



               }
           if(vybor>=0 && GetAsyncKeyState (VK_DELETE))
            {
             centr_pic[vybor] = centr_pic[ nCentrPic-1];
             nCentrPic--;
            }
            if(butn[butn_save].click())
             {
               string filename =  DialogFile(true);

               ofstream fileout;
               fileout.open(filename);
               if(fileout.is_open())
                {
                for(int i=0;i<nCentrPic;i++)
                {
                 fileout << centr_pic[i].x << endl;
                 fileout << centr_pic[i].y << endl;
                 fileout << centr_pic[i].adress << endl;
                 fileout << centr_pic[i].w_shr << endl;
                 fileout << centr_pic[i].h_shr << endl;
                }
              }

             fileout.close();
             }

             if(butn[butn_load].click())
             {
                string filename =  DialogFile(false);

               char buff[50];
               ifstream filein(filename);
                while(filein.good())
                {
                 filein.getline(buff,50);
                 int x = atoi(buff);
                 filein.getline(buff,50);
                 int y = atoi(buff);
                 filein.getline(buff,50);
                 string adress = buff;
                 filein.getline(buff,50);
                 int w_shr = atoi(buff);
                 filein.getline(buff,50);
                 int h_shr = atoi(buff);


                 for(int i=0; i<count_pic; i++)
                  {
                   if(pic[i].adress == adress)
                   {
                       centr_pic[nCentrPic] = { x,
                                                y,
                                                adress,
                                                pic[i].image,
                                                pic[i].w,
                                                pic[i].h,
                                                w_shr,
                                                h_shr,
                                                pic[i].contegor,
                                                true
                                            };
                        nCentrPic++;
                   }

                  }
                }
              filein.close();
             }
























        txEnd();
        txSleep(10);
    }

txDisableAutoPause();
return 0;
}
