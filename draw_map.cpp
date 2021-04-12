#include "draw_map.h"

Draw_map::Draw_map(QWidget *parent)
    : QGraphicsView(parent)
{


    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);





    scene = new QGraphicsScene();
    this->setScene(scene);

	
    group = new QGraphicsItemGroup();
	

    scene->addItem(group);
    

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));
    timer->start(50);
}



void Draw_map::slotAlarmTimer()
{
    this->deleteItemsFromGroup(group);


    int width = (this->parentWidget()->width() - 20) + Draw_map::scale;
    int height = (this->parentWidget()->height() - 50) + Draw_map::scale;

    if ((Draw_map::H_main != 0) || (Draw_map::W_main != 0))
    {
        double blockH = (double)height/Draw_map::H_main;
        double blockW = (double)width/Draw_map::W_main;
        if (blockH < blockW)
        {
            Draw_map::Cell_Size = blockH;
        } else
        {
            Draw_map::Cell_Size = blockW;
        }
    }

    scene->setSceneRect(0,0,width,height);


    QPen penBlack(Qt::black);
    QPen penRed(Qt::red);


    int count = 0;
    int MaxCount = (Draw_map::W_main + Draw_map::H_main)/2;


    bool a = true;
    srand(time(0));
    std::vector<std::vector<Cell>> cell_map(Draw_map::Cell_Size, std::vector<Cell> (Draw_map::Cell_Size));
    for (int j = 0; j < Draw_map::W_main; j++)
    {
        for (int i = 0; i < Draw_map::H_main;i++)
        {

            if (!Draw_map::start_Draw)
            {
                a = true;
                int z =0;
                if (count <= MaxCount)
                {
                    z = rand()%100;

                    if (z <= 30)
                    {
                        a = false;
                        count++;
                    }
                }

                cell_map[i][j].Set_all(i, j, a, Draw_map::H_main, Draw_map::W_main, i * Draw_map::W_main + j);

                if ((i == (Draw_map::W_main - 1))&&(j == (Draw_map::H_main - 1)))
                {
                    Draw_map::start_Draw = true;
                }
            }

            group->addToGroup(scene->addLine(i*Draw_map::Cell_Size,
                                             j*Draw_map::Cell_Size,
                                             (i+1)*Draw_map::Cell_Size,
                                             j*Draw_map::Cell_Size, penBlack));
            group->addToGroup(scene->addLine((i+1)*Draw_map::Cell_Size,
                                             j*Draw_map::Cell_Size,
                                             (i+1)*Draw_map::Cell_Size,
                                             (j+1)*Draw_map::Cell_Size, penBlack));
            group->addToGroup(scene->addLine(i*Draw_map::Cell_Size,
                                             j*Draw_map::Cell_Size,
                                             i*Draw_map::Cell_Size,
                                             (j+1)*Draw_map::Cell_Size, penBlack));
            group->addToGroup(scene->addLine(i*Draw_map::Cell_Size,
                                             (j+1)*Draw_map::Cell_Size,
                                             (i+1)*Draw_map::Cell_Size,
                                             (j+1)*Draw_map::Cell_Size, penBlack));


        }
    }
    for (int j = 0; j < Draw_map::W_main; j++)
    {
        for (int i = 0; i < Draw_map::H_main;i++)
        {
            if (!cell_map[i][j].Get_cell_status())
            {
                if (i != 0) cell_map[i-1][j].Set_way_right(false);
                if (i != Draw_map::W_main - 1) cell_map[i+1][j].Set_way_left(false);
                if (j != 0) cell_map[i][j+1].Set_way_up(false);
                if (j != Draw_map::H_main - 1) cell_map[i][j-1].Set_way_down(false);

                double step = 0;
                step = Draw_map::Cell_Size / 10;
                for (int k = 1; k <= 10; k++)
                {
                    group->addToGroup(scene->addLine(i*Draw_map::Cell_Size + k*step,
                                                     j*Draw_map::Cell_Size,
                                                     i*Draw_map::Cell_Size + k*step,
                                                     (j+1)*Draw_map::Cell_Size, penBlack));
                    group->addToGroup(scene->addLine(i*Draw_map::Cell_Size,
                                                     j*Draw_map::Cell_Size + k*step,
                                                     (i+1)*Draw_map::Cell_Size,
                                                     j*Draw_map::Cell_Size + k*step, penBlack));
                }
            }
        }
    }





}


void Draw_map::resizeEvent(QResizeEvent *event)
{
    timer->start(50);
    QGraphicsView::resizeEvent(event);
}



void Draw_map::deleteItemsFromGroup(QGraphicsItemGroup *group)
{

    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}

void Draw_map::wheelEvent(QWheelEvent *event)
{
    timer->start(50);
    if (event->angleDelta().y() != 0)
    {

        Draw_map::scale+=event->angleDelta().y();


    }
}

void Draw_map::SetTimer()
{
    timer->start(50);
}


