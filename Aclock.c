/** @file
  Aclock is an analog clock program for text mode console displays, terminals, or terminal emulators.
  This program is obviously absolutely useless, except for turning your old, expensive mainframe or
  supercomputer into a wall clock.

  Copyright (c) 1994-2016 Antoni Sawicki <as@tenoware.com>
  Copyright (c) 2016 Natalia Portillo <claunia@claunia.com>
**/

#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>

#include <math.h>
#include <unistd.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define FontWH_Ratio 2

// Global variables
SIMPLE_TEXT_OUTPUT_INTERFACE *ConOut;
EFI_SYSTEM_TABLE *eST;

void draw_circle(int hand_max, int sYcen, int sXcen){
    int x,y,r;
    char c;

    for(r=0;r<60;r++){
        x=cos(r*M_PI/180*6)*hand_max*FontWH_Ratio+sXcen;
        y=sin(r*M_PI/180*6)*hand_max+sYcen;
        switch (r) {
            case 0:
            case 5:
            case 10:
            case 15:
            case 20:
            case 25:
            case 30:
            case 35:
            case 40:
            case 45:
            case 50:
            case 55:
                c='o';
                break;
            default:
                c='.';
                break;
        }
        ConOut->SetCursorPosition(ConOut, x, y);
        Print(L"%c", c);
    }
}

void draw_hand(int minute, int hlenght, char c, int sXcen, int sYcen){
    int x,y,n;
    float r=(minute-15)*(M_PI/180)*6;

    for(n=1; n<hlenght; n++){
        x=cos(r)*n*FontWH_Ratio+sXcen;
        y=sin(r)*n+sYcen;
        ConOut->SetCursorPosition(ConOut, x, y);
        Print(L"%c", c);
    }
}

/**
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    ConOut = SystemTable->ConOut;
    eST = SystemTable;
    EFI_TIME ltime;

    /*char INFO[]="Copyright (c) 1994-2016 Antoni Sawicki <as@tenoware.com>\n"
                "Copyright (c) 2016 Natalia Portillo <claunia@claunia.com>\n"
                "Version 1.0 (efi); Canary Islands, May 2016\n";*/
    int sXmax, sYmax, smax, hand_max, sXcen, sYcen;

    sXmax=sYmax=hand_max=sXcen=sYcen=0;
    ConOut->ClearScreen(ConOut);

    while(1){
        eST->RuntimeServices->GetTime(&ltime, NULL);

	UINTN Columns, Rows;
        ConOut->QueryMode(ConOut, ConOut->Mode->Mode, &Columns, &Rows);
        sYmax = (int)Rows;
        sXmax = (int)Columns;

        if(sXmax/FontWH_Ratio<=sYmax)
            smax=sXmax/FontWH_Ratio;
        else
            smax=sYmax;

        hand_max = (smax/2)-1;

        sXcen = sXmax/2;
        sYcen = sYmax/2;

        ConOut->ClearScreen(ConOut);
        draw_circle(hand_max, sYcen, sXcen);

        draw_hand((ltime.Hour*5)+(ltime.Minute/10), 2*hand_max/3, 'h', sXcen, sYcen);
        draw_hand(ltime.Minute, hand_max-2, 'm', sXcen, sYcen);
        draw_hand(ltime.Second, hand_max-1, '.', sXcen, sYcen);

        ConOut->SetCursorPosition(ConOut, sXcen-5, sYcen-(3*hand_max/5));
        Print(L".:ACLOCK:.");
        ConOut->SetCursorPosition(ConOut, sXcen-5, sYcen+(3*hand_max/5));
        Print(L"[%02d:%02d:%02d]", ltime.Hour, ltime.Minute, ltime.Second);

        sleep(1);
    }

    return EFI_SUCCESS;
}

