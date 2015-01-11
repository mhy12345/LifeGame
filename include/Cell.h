#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell();
    virtual ~Cell();
    void SetHp(int hp);
    static int GetColor(int hp);
    int GetColor();
    int GetHp();
protected:
private:
    int hp;
};

#endif // CELL_H
