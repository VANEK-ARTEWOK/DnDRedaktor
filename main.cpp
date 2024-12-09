

#include "TXLib.h"
#include <fstream>
#include <dirent.h>
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
struct Menu_Button
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
int get_w(string adress)
 {
  FILE *f1 = fopen(adress.c_str(), "rb");
  unsigned char header[54];
  fread(header,sizeof(unsigned char), 54 , f1);
  int w = *(int*)&header[18];
  return w ;
 }
int get_h(string adress)
 {
  FILE*f1 = fopen(adress.c_str(), "rb");
  unsigned char header[54];
  fread(header,sizeof(unsigned char), 54 , f1);
  int h = *(int*)&header[22];
  return h ;
 }

int ReadFromDir(string adressDir,Pictures pic[],int countFile)
{
    DIR *dir;
    struct dirent *ent;
    int X = 10;
    int Y = 100;

    if ((dir = opendir(adressDir.c_str())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            if((string)ent->d_name != "." && (string)ent->d_name != ".." )
            {
                pic[countFile].x = X;
                pic[countFile].y = Y;
                pic[countFile].adress = adressDir + (string)ent->d_name;

                countFile++;
                Y+=100 ;

                if(Y>=650)
                {
                    X = 150;
                    Y = 100;
                }
            }

        }

        closedir(dir);
    }

    return countFile;
}



inline int GetFilePointer(HANDLE FileHandle)
{
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height)
{
    bool Success=0;
    HBITMAP OffscrBmp=NULL;
    HDC OffscrDC=NULL;
    LPBITMAPINFO lpbi=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return 0;
    if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
        return 0;
    HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
    BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return 0;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(OffscrDC, OldBmp);
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        return 0;
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((BmpFile = CreateFile(filename,
                        GENERIC_WRITE,
                        0, NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL)) == INVALID_HANDLE_VALUE)
        return 0;
    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return 0;
    if (Written < sizeof(BITMAPINFOHEADER))
        return 0;
    int PalEntries;
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
                      (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
    if(lpbi->bmiHeader.biClrUsed)
    PalEntries = lpbi->bmiHeader.biClrUsed;
    if(PalEntries){
    if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
        return 0;
        if (Written < PalEntries * sizeof(RGBQUAD))
            return 0;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
        return 0;
    if (Written < lpbi->bmiHeader.biSizeImage)
        return 0;
    bmfh.bfSize = GetFilePointer(BmpFile);
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;

    CloseHandle (BmpFile);

    delete [] (char*)lpvBits;
    delete [] lpbi;

    DeleteDC (OffscrDC);
    DeleteObject (OffscrBmp);


    return 1;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename, HWND hwnd)
{
    HDC hDC = GetDC(hwnd);
    HDC hDc = CreateCompatibleDC(hDC);

    HBITMAP hBmp = CreateCompatibleBitmap(hDC, width, height);

    HGDIOBJ old= SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, hDC, x, y, SRCCOPY);

    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);

    SelectObject(hDc, old);

    DeleteObject(hBmp);

    DeleteDC (hDc);
    ReleaseDC (hwnd, hDC);

    return ret;
}

int main()
{
txCreateWindow (1500, 760);
txTextCursor (false);

     string PAGE = "menu";



     int count_pic = 0;
     int count_butn = 9;
     int nCentrPic = 0;
     int count_menu_butn = 4;
     int butn_save = count_butn -5;
     int butn_load = count_butn -4;
     int butn_ckrin = count_butn -3;
     int butn_exit = count_butn -2;
     int butn_help = count_butn -1;
     int menu_butn_start = count_menu_butn -3;
     int menu_butn_help = count_menu_butn -2;

     int menu_butn_exit =  count_menu_butn -1;




     char str[300];

     Button menu_butn[count_menu_butn];
     menu_butn[0]={670,440,150,35,"автор"};
     menu_butn[1]={670,180,150,35,"начать"};                     //count_pic
     menu_butn[2]={670,260,150,35,"помощь"};
     menu_butn[3]={670,380,150,35,"выход"};


     Button butn[count_butn];
     butn[0]={55,55,150,35,"расы","расы"};                     //count_pic
     butn[1]={255,55,150,35,"Классы","Классы"};
     butn[2]={455,55,150,35,"одежда","одежда"};
     butn[3]={655,55,150,35,"питомцы","питомцы"};
     butn[4]={1200,75,210,35,"сахранить"};
     butn[5]={1200,120,210,35,"загрузить"};
     butn[6]={1260,630,210,35,"скриншот"};
     butn[7]={1260,550,210,35,"выход"};
     butn[8]={1260,500,210,35,"помощь"};
     HDC Fon =txLoadImage ("картинки/фон.bmp");
     HDC Menu =txLoadImage ("картинки/МЕНЮ.bmp");
     HDC Exit =txLoadImage ("картинки/выход.bmp");
     HDC Help =txLoadImage ("картинки/ХЕЛП.bmp");

     Pictures pic[1000];



    count_pic = ReadFromDir("картинки/расы/", pic, count_pic);
    count_pic = ReadFromDir("картинки/Классы/", pic, count_pic);
    count_pic = ReadFromDir("картинки/одежда/", pic, count_pic);
    count_pic = ReadFromDir("картинки/питомцы/", pic, count_pic);
    count_pic = ReadFromDir("картинки/инструменты/", pic, count_pic);

       for(int i=0;i< count_pic;i++)
       {
        pic[i].vizible = false;

       int pos1 = pic[i].adress.find("/");
       int pos2 = pic[i].adress.find("/",pos1+1);
       pic[i].contegor = pic[i].adress.substr(pos1+1,pos2-(pos1+1));

       pic[i].w = get_w(pic[i].adress);
       pic[i].h = get_h(pic[i].adress);

       if(pic[i].contegor ==  "расы" || pic[i].contegor ==  "оружее" )
         {
          pic[i].w_shr = pic[i].w/4;
          pic[i].h_shr = pic[i].h/4;
         }
         else
         {
          pic[i].w_shr = pic[i].w/4;
          pic[i].h_shr = pic[i].h/4;
         }
        pic[i].image = txLoadImage(pic[i].adress.c_str());

       }


     int vybor = 1;
     bool mause_down = false ;

     Pictures centr_pic[600];

    while(PAGE != "exit")
    {

        txSetFillColor(TX_BLACK);
        txClear();
        txBegin();

    if(PAGE == "menu")

     {


       Win32::TransparentBlt(txDC(),0 ,0  , 1540, 800 ,Menu, 0, 0, 1540 ,800 ,RGB(255, 0, 0));
        for(int i=0;i<count_menu_butn;i++)
        {
            menu_butn[i].draw();

        }
      if(menu_butn[menu_butn_help].click())
        {
         PAGE ="help";

        }
     if(menu_butn[menu_butn_start].click())
        {
           PAGE ="work";

        }
     if(menu_butn[menu_butn_exit].click())
        {
           PAGE ="exit";

        }






     }

    if(PAGE == "help")
     {
     Win32::TransparentBlt(txDC(),0 ,0  , 1540, 800 ,Help, 0, 0, 1540 ,800 ,RGB(255, 242, 0));
      if(GetAsyncKeyState (VK_ESCAPE))
          {
                PAGE = "menu";
          }

     }








    if(PAGE == "work" )
    {

        Win32::TransparentBlt(txDC(),0 ,0  , 1540, 800 ,Fon, 0, 0, 1540 ,800 ,RGB(255, 0, 0));

        //Win32::TransparentBlt(txDC(),1200 ,45 , 200, 77 ,Bnt, 0, 0, 200 ,77 ,RGB(255, 0, 0));
        drawWorkspase(440,220 , 800, 500);


        for(int i=0;i<8;i++)
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

        if(butn[butn_ckrin].click())
        {
            ScreenCapture(440,220 , 800, 500, "скрин.bmp", txWindow());
                        txMessageBox("Это тебе ;3  оно в скрин.bmp");

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
             if(butn[butn_help].click())
              {
               PAGE = "help";
              }
              if(butn[butn_exit].click())
              {
               PAGE = "menu";
              }
    }
        txEnd();
        txSleep(10);

    }
txDisableAutoPause();
return 0;
}
