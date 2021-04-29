#include "functions.h"


std::vector<int> PathFinder (std::vector<std::vector<Cell>> Cell_map, int x1, int y1, int x2, int y2, int W)
{
    std::vector<int> explored;
    std::vector<int> next_in_line = {x1+y1*W};
    std::vector<int> result;
	int aim_id = x2+y2*W;
	int position = x1+y1*W;
	int indPosition = 0;

    while ((position != aim_id) && (next_in_line.size() != 0))
	{


		bool ok_left = true;
		bool ok_right = true;
		bool ok_up = true;
		bool ok_down = true;
        if (explored.size() != 0)
        {

            for (int i = 0; i<explored.size();i++)
            {

                if (explored[i] == position - 1)
                {
                    ok_left = false;
                }
                if (explored[i] == position + 1)
                {
                    ok_right = false;
                }
                if (explored[i] == position - W)
                {
                    ok_up = false;
                }
                if (explored[i] == position + W)
                {
                    ok_down = false;
                }
            }
        }

        if(Cell_map[position%W][position/W].Get_way_left())
        {

			if (ok_left)
			{
                bool ok_next = true;
                for (int i = 0; i < next_in_line.size(); i++)
                {
                    if (next_in_line[i] == position - 1)
                    {
                        ok_next = false;
                        break;
                    }
                }
                if (ok_next)
                {
                    next_in_line.push_back(position - 1);
                    Cell_map[position%W - 1][position/W].Set_prevID(position);
                }
			}
		}

        if(Cell_map[position%W][position/W].Get_way_right())
		{

			if (ok_right)
			{
                bool ok_next = true;
                for (int i = 0; i < next_in_line.size(); i++)
                {
                    if (next_in_line[i] == position + 1)
                    {
                        ok_next = false;
                        break;
                    }
                }
                if (ok_next)
                {
                    next_in_line.push_back(position + 1);
                    Cell_map[position%W + 1][position/W].Set_prevID(position);
                }
			}
		}

        if(Cell_map[position%W][position/W].Get_way_up())
		{

			if (ok_up)
			{
                bool ok_next = true;
                for (int i = 0; i < next_in_line.size(); i++)
                {
                    if (next_in_line[i] == position - W)
                    {
                        ok_next = false;
                        break;
                    }
                }
                if (ok_next)
                {
                    next_in_line.push_back(position - W);
                    Cell_map[position%W][position/W - 1].Set_prevID(position);
                }
			}
		}

        if(Cell_map[position%W][position/W].Get_way_down())
		{

			if (ok_down)
			{
                bool ok_next = true;
                for (int i = 0; i < next_in_line.size(); i++)
                {
                    if (next_in_line[i] == position + W)
                    {
                        ok_next = false;
                        break;
                    }
                }
                if (ok_next)
                {
                    next_in_line.push_back(position + W);
                    Cell_map[position%W][position/W + 1].Set_prevID(position);
                }
			}
		}

		explored.push_back(position);
		next_in_line.erase(next_in_line.begin() + indPosition);
       // QString s;
        //QString s1;




        indPosition = rand()%next_in_line.size();
        position = next_in_line[indPosition];
       /* for (int k = 0; k < explored.size(); k++)
        {
            s += QString::number(explored[k]) + " ";
        }
        for (int k = 0; k < next_in_line.size(); k++)
        {
            s1 += QString::number(next_in_line[k]) + " ";
        }
        QMessageBox::information(NULL,"info","explored: " + s+"\n"+"next_in_line: " + s1+"\n"+
                                 "position: " + QString::number(position)+"\n"+"indPosition: " + QString::number(indPosition) + "\n" +
                                 "aim_id: " + QString::number(aim_id));*/
	}
	if (position == aim_id)
	{
		while (position != x1+y1*W)
		{
            result.push_back(position);
            position = Cell_map[position%W][(double)position/W].Get_prevID();
		}
        result.push_back(position);
	} 
    /*QString s;
    for (int k = 0; k < result.size(); k++)
    {
        s += QString::number(result[k]) + " ";
    }
    QMessageBox::information(NULL, "", s);*/
	return result;
}
