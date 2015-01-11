#ifndef GAME_H
#define GAME_H
#include "Cell.h"
class Game
{
public:
    static const int maxlen=40;
    Game();
    virtual ~Game();
    void ObtainFromFile(FILE *fin);
    void OnPaint(HDC hdc,int xStart,int yStart,int xEnd,int yEnd);
    void Run();
    void Random();
protected:
private:
    Cell *cell[maxlen][maxlen];
    int len;
};

#endif // GAME_H
