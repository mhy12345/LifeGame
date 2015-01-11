#include "stdafx.h"
#include "Cell.h"

Cell::Cell()
{
    hp=-1;
    //ctor
}

Cell::~Cell()
{
    //dtor
}
int Cell::GetColor(int hp)
{
    if (hp>=70)return 0x66ff00;
    else if (hp>=1)return 0xcc6600;
    else if (hp==0)return 0xffffff;
    return -1;
}
int Cell::GetColor()
{
    if (hp>=70)return 0x66ff00;
    else if (hp>=1)return 0xcc6600;
    else if (hp==0)return 0xffffff;
    return -1;
}
void Cell::SetHp(int hp)
{
    this->hp=hp;
}
int Cell::GetHp()
{
    return hp;
}
