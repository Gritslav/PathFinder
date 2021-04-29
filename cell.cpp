#include "functions.h"

Cell::Cell()
{

}

void Cell::Set_all(int x, int y, bool status, int H, int W, int cID)
{
    Cell::cell_x = x;
    Cell::cell_y = y;
    Cell::cell_status = status;
    Cell::ID = cID;

    if (!status)
    {
        Cell::way_left = false;
        Cell::way_right = false;
        Cell::way_up = false;
        Cell::way_down = false;
    } else {
        Cell::way_left = true;
        Cell::way_right = true;
        Cell::way_up = true;
        Cell::way_down = true;
        if (y == 0)
        {
            Cell::way_up = false;
        } else if (y == H-1)
        {
            Cell::way_down = false;
        }
        if (x == 0)
        {
            Cell::way_left = false;
        } else if (x == W-1)
        {
            Cell::way_right = false;
        }
    }

    /*QMessageBox::information(NULL,"info","x = " + QString::number(x) + " " + "y = " + QString::number(y) + "\n" +
                             "status = " + QString::number(status) + " " + "ID = " + QString::number(cID) + "\n" +
                             "l = " + QString::number(Cell::way_left) + " " + "r = " + QString::number(Cell::way_right) + "\n" +
                             "u = " + QString::number(Cell::way_up) + " " + "d = " + QString::number(Cell::way_down));*/
}
	
int Cell::Get_cell_x()
{
	return Cell::cell_x;
}
int Cell::Get_cell_y()
{
	return Cell::cell_y;
}
bool Cell::Get_cell_status()
{
	return Cell::cell_status;
}
bool Cell::Get_way_left()
{
	return Cell::way_left;
}
bool Cell::Get_way_right()
{
	return Cell::way_right;
}
bool Cell::Get_way_up()
{
	return Cell::way_up;
}
bool Cell::Get_way_down()
{
	return Cell::way_down;
}
void Cell::Set_way_left(bool left)
{
    Cell::way_left = left;
}
void Cell::Set_way_right(bool right)
{
    Cell::way_right = right;
}
void Cell::Set_way_up(bool up)
{
    Cell::way_up = up;
}
void Cell::Set_way_down(bool down)
{
    Cell::way_down = down;
}
int Cell::Get_prevID()
{
    return Cell::prevID;
}
void Cell::Set_prevID(int pID)
{
    Cell::prevID = pID;
}
