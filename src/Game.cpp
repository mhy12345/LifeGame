#include "stdafx.h"
#include "Game.h"
#include "Cell.h"
Game game;

Game::Game()
{
    len=maxlen;
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            cell[i][j]=new Cell();
    ObtainFromFile(fopen("input.txt","r"));
}

Game::~Game()
{
    //dtor
}

void Game::OnPaint(HDC hdc,int xStart,int yStart,int xEnd,int yEnd)
{
    PAINTSTRUCT ps;
    HBRUSH hBrush=::CreateSolidBrush(RGB(220,255,255));
    HBRUSH hOldBrush=(HBRUSH)::SelectObject(hdc,hBrush);
    xStart+=5;
    yStart+=5;
    xEnd-=5;
    yEnd-=5;
    int xLen=(xEnd-xStart+1)/len;
    int yLen=(yEnd-yStart+1)/len;
    int xRange=xLen;
    xRange-=xRange/4;
    xRange=(xRange-xRange%2)/2;
    int yRange=yLen;
    yRange-=yRange/4;
    yRange=(yRange-yRange%2)/2;
    int xCent=xLen/2,yCent=yLen/2;
    xEnd=xStart+xLen*len;
    yEnd=yStart+yLen*len;
    ::Rectangle(hdc,xStart-5,yStart-5,xEnd+5,yEnd+5);
    for (int i=0; i<len; i++)
    {
        for (int j=0; j<len; j++)
        {
            HBRUSH hNowBrush=::CreateSolidBrush(cell[i][j]->GetColor());
            //printf("Print cell[%d,%d],whose HP is [%d] RGB is [%x]\n",i,j,cell[i][j]->GetHp(),cell[i][j]->GetColor());
            ::SelectObject(hdc,hNowBrush);
            ::RoundRect(hdc,
                        xStart+xLen*i+xCent-xRange,
                        yStart+yLen*j+yCent-yRange,
                        xStart+xLen*i+xCent+xRange,
                        yStart+yLen*j+yCent+yRange,
                        xRange/2,yRange/2);
            ::DeleteObject(hNowBrush);
            ::SelectObject(hdc,hOldBrush);
        }
    }
    ::SelectObject(hdc,hOldBrush);
    ::DeleteObject(hBrush);
}

void Game::ObtainFromFile(FILE *fin=fopen("input.txt","r"))
{
    fscanf(fin,"%d",&len);
    int hp;
    for (int i=0; i<len; i++)
    {
        for (int j=0; j<len; j++)
        {
            fscanf(fin,"%d",&hp);
            cell[j][i]->SetHp(hp);
        }
    }
}
void Game::Random()
{
    for (int i=0; i<len; i++)
    {
        for (int j=0; j<len; j++)
        {
            cell[i][j]->SetHp(rand()%2?100:0);
        }
    }
}
void Game::Run()
{
    int hp[maxlen][maxlen];
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            hp[i][j]=cell[i][j]->GetHp();
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
        {
            int x=0;
            for (int k=0; k<8; k++)
            {
                if (i+mov[k][0]<len && i+mov[k][0]>=0 && j+mov[k][1]<len && j+mov[k][1]>=0)
                    x+=hp[i+mov[k][0]][j+mov[k][1]]!=0;
            }
            if (x==3)cell[i][j]->SetHp(100);
            else if (x==2)cell[i][j]->SetHp(hp[i][j]?100:0);
            else cell[i][j]->SetHp(0);
        }
}
