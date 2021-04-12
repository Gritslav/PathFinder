#ifndef CELL_H
#define CELL_H

#include <QGraphicsItemGroup>

class Cell
{
private:
	int cell_x;
	int cell_y;
	bool cell_status;
	bool way_left;
	bool way_right;
	bool way_up;
	bool way_down;
    int ID;
    int prevID;
	QGraphicsItemGroup  *cell_group;
public:
    Cell();
    void Set_all(int x, int y, bool status, int H, int W, int ID);
	int Get_cell_x();
	int Get_cell_y();
	bool Get_cell_status();
	bool Get_way_left();
	bool Get_way_right();
	bool Get_way_up();
	bool Get_way_down();
    void Set_way_left(bool left);
    void Set_way_right(bool right);
    void Set_way_up(bool up);
    void Set_way_down(bool down);
    int Get_prevID();
    void Set_prevID(int ID);
};

#endif // CELL_H
