#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include "stdafx.h"
#include "Game.h"
#define IDT_TIMER1 1
#define INIT_TIME_SINGLE_ROUND 1024
int TimeEachRound=INIT_TIME_SINGLE_ROUND;



/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    if (AllocConsole())
    {
        freopen("CONIN$","r",stdin);
        freopen("CONOUT$","w",stdout);
        freopen("CONOUT$","w",stderr);
    }

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    printf("Set Timer with time %d.\n",INIT_TIME_SINGLE_ROUND);
    ::SetTimer(hwnd,IDT_TIMER1,INIT_TIME_SINGLE_ROUND,NULL);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    extern Game game;
    switch (message)                  /* handle the messages */
    {
    case WM_TIMER:
        if (wParam==IDT_TIMER1)
        {
            printf("Run Game!\n");
            PAINTSTRUCT ps;
            HDC hdc;

            hdc=GetDCEx(hwnd,NULL,DCX_CACHE|DCX_NORESETATTRS);
            game.Run();
            game.OnPaint(hdc,10,10,327,327);
            ReleaseDC(hwnd,hdc);
        }
        break;
    case WM_PAINT:
        printf("On Paint\n");
        PAINTSTRUCT ps;
        HDC hdc;
        ps.fErase=true;
        hdc=::BeginPaint(hwnd,&ps);
        //game.Run();
        game.OnPaint(hdc,10,10,327,327);
        EndPaint(hwnd,&ps);
        break;
    case WM_CHAR:
        if (wParam=='\033')
        {
            PostQuitMessage(0);
            printf("Quit now!\n");
        }
        else if (wParam=='r')
        {
            game.Random();
            printf("Init Random Round!\n");
        }
        else if (wParam=='+' || wParam=='-')
        {
            if (wParam=='+')
            {
                TimeEachRound*=2;
            }
            else
            {
                if (TimeEachRound==128)break;
                TimeEachRound/=2;
            }
            KillTimer(hwnd,IDT_TIMER1);
            SetTimer(hwnd,IDT_TIMER1,TimeEachRound,NULL);
            printf("Set Rount time into %d\n",TimeEachRound);
        }
        else
        {
            printf("Char catched [%c]!\n",wParam);
        }
        break;
    case WM_DESTROY:
        printf("Start Destroy!\n");
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
