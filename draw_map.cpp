#include "functions.h"



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
    Draw_map::SetSecondClick(false);
    Draw_map::SetFirstClick(false);
    timer->start(50);
}



void Draw_map::slotAlarmTimer()
{
    this->deleteItemsFromGroup(group);

    int width;
    int height;
    Draw_map::width_scale = (this->parentWidget()->width() - 20);
    Draw_map::height_scale = (this->parentWidget()->height() - 50);

    width = (this->parentWidget()->width() - 20) + Draw_map::scale;
    height = (this->parentWidget()->height() - 50) + Draw_map::scale;
    if ((width < Draw_map::width_scale)||(height<Draw_map::height_scale))
    {
        width = Draw_map::width_scale;
        height = Draw_map::height_scale;
        Draw_map::scale = 0;
    }


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
    int MaxCount = (Draw_map::W_main * Draw_map::H_main)/2;


    bool a = true;
    srand(time(0));

    for (int i = 0; i < Draw_map::W_main; i++)
    {
        for (int j = 0; j < Draw_map::H_main;j++)
        {

            if (!Draw_map::start_Draw)
            {
                a = true;
                int z =0;
                if (count <= MaxCount)
                {
                    z = rand()%100;

                    if (z <= 20)
                    {
                        a = false;
                        count++;
                    }
                }

                Draw_map::cell_map[i][j].Set_all(i, j, a, Draw_map::H_main, Draw_map::W_main, j * Draw_map::H_main + i);

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
            if (!Draw_map::cell_map[i][j].Get_cell_status())
            {
                double step = 0;

                if ((Draw_map::H_main < 30)||(Draw_map::W_main < 30))
                {
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
                } else if ((Draw_map::H_main < 60)||(Draw_map::W_main < 60))
                {
                    step = Draw_map::Cell_Size / 3;
                    for (int k = 1; k <= 3; k++)
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
                } else
                {
                    step = Draw_map::Cell_Size / 2;
                    for (int k = 1; k <= 2; k++)
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


    if (Draw_map::GetSecondClick())
    {
        if (Draw_map::Get_new_draw())
        {
            Draw_map::Set_new_draw(false);
            Draw_map::Set_Path(PathFinder(Draw_map::cell_map,Draw_map::GetA_x(),Draw_map::GetA_y(),Draw_map::GetB_x(),Draw_map::GetB_y(),Draw_map::W_main));
        }


        for(int i = 0; i < Draw_map::Get_Path().size(); i++)
        {

			//дорожка к предыдущему
			if (i != 0)
			{

                if (Draw_map::Get_Path()[i-1] == Draw_map::Get_Path()[i] - 1)
				{

                    group->addToGroup(scene->addLine(Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main),
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,penRed));

													 
                } else if (Draw_map::Get_Path()[i-1] == Draw_map::Get_Path()[i] + 1)
				{
                    group->addToGroup(scene->addLine(Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,penRed));

					
                } else if (Draw_map::Get_Path()[i-1] == Draw_map::Get_Path()[i] - Draw_map::W_main)
				{
                    group->addToGroup(scene->addLine(Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main),
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,penRed));

                } else if (Draw_map::Get_Path()[i-1] == Draw_map::Get_Path()[i] + Draw_map::W_main)
				{
                    group->addToGroup(scene->addLine(Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,penRed));

				} 
			}
			//дорожка к следующему
            if (i != Draw_map::Get_Path().size() - 1)
            {

                if (Draw_map::Get_Path()[i+1] == Draw_map::Get_Path()[i] - 1)
				{
                    group->addToGroup(scene->addLine(Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main),
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,penRed));

													 
                } else if (Draw_map::Get_Path()[i+1] == Draw_map::Get_Path()[i] + 1)
				{
                    group->addToGroup(scene->addLine(Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,penRed));

					
                } else if (Draw_map::Get_Path()[i+1] == Draw_map::Get_Path()[i] - Draw_map::W_main)
				{
                    group->addToGroup(scene->addLine(Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main),
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,penRed));

                } else if (Draw_map::Get_Path()[i+1] == Draw_map::Get_Path()[i] + Draw_map::W_main)
				{
                    group->addToGroup(scene->addLine(Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]%Draw_map::W_main) + Draw_map::Cell_Size/2,
                                                      Draw_map::Cell_Size*(Draw_map::Get_Path()[i]/Draw_map::W_main) + Draw_map::Cell_Size/2,penRed));

				} 
            }
        }
    }
}

void Draw_map::Set_Path(std::vector<int> PATH_TO_B)
{
    Draw_map::path = PATH_TO_B;
}
std::vector<int> Draw_map::Get_Path()
{
    return Draw_map::path;
}

void Draw_map::SetFirstClick(bool a)
{
    Draw_map::first_click = a;
}
void Draw_map::SetSecondClick(bool a)
{
    Draw_map::second_click = a;
}
bool Draw_map::GetFirstClick()
{
    return Draw_map::first_click;
}
bool Draw_map::GetSecondClick()
{
    return Draw_map::second_click;
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
        if (event->angleDelta().y() > 0)
        {
            Draw_map::scale+=20;
        } else
        {
            Draw_map::scale-=20;
        }


    }
}

void Draw_map::SetACoord(double x, double y)
{
    if ((x > Draw_map::Cell_Size) && (x!=Draw_map::W_main*Draw_map::Cell_Size))
    {
        Draw_map::A_x = (int)(x/Draw_map::Cell_Size);
    } else if (x <= Draw_map::Cell_Size){
        Draw_map::A_x = 0;
    } else {
         Draw_map::A_x = Draw_map::W_main - 1;
    }
    if ((y > Draw_map::Cell_Size)&&(y!=Draw_map::H_main*Draw_map::Cell_Size))
    {
        Draw_map::A_y = (int)(y/Draw_map::Cell_Size);
    } else if (y <= Draw_map::Cell_Size){
        Draw_map::A_y = 0;
    } else {
         Draw_map::A_y = Draw_map::H_main - 1;
    }

}
void Draw_map::SetBCoord(double x, double y)
{
    if ((x > Draw_map::Cell_Size) && (x!=Draw_map::W_main*Draw_map::Cell_Size))
    {
        Draw_map::B_x = (int)(x/Draw_map::Cell_Size);
    } else if (x <= Draw_map::Cell_Size){
        Draw_map::B_x = 0;
    } else {
         Draw_map::B_x = Draw_map::W_main - 1;
    }
    if ((y > Draw_map::Cell_Size)&&(y!=Draw_map::H_main*Draw_map::Cell_Size))
    {
        Draw_map::B_y = (int)(y/Draw_map::Cell_Size);
    } else if (y <= Draw_map::Cell_Size){
        Draw_map::B_y = 0;
    } else {
         Draw_map::B_y = Draw_map::H_main - 1;
    }


}
int Draw_map::GetA_x()
{
    return Draw_map::A_x;
}
int Draw_map::GetA_y()
{
    return Draw_map::A_y;
}
int Draw_map::GetB_x()
{
    return Draw_map::B_x;
}
int Draw_map::GetB_y()
{
    return Draw_map::B_y;
}
void Draw_map::mousePressEvent(QMouseEvent *event)
{

    if (!Draw_map::GetFirstClick())
    {

        Draw_map::SetFirstClick(true);

        Draw_map::SetACoord(Draw_map::mapToScene(event->pos()).x(),Draw_map::mapToScene(event->pos()).y());



    } else if (!Draw_map::GetSecondClick())
    {
        Draw_map::Set_new_draw(true);
        Draw_map::SetSecondClick(true);

        Draw_map::SetBCoord(Draw_map::mapToScene(event->pos()).x(),Draw_map::mapToScene(event->pos()).y());

        timer->start(10);
    } else if ((Draw_map::GetFirstClick())&&(Draw_map::GetSecondClick()))
    {
         Draw_map::SetSecondClick(false);
         Draw_map::Set_new_draw(true);
         Draw_map::SetACoord(Draw_map::mapToScene(event->pos()).x(),Draw_map::mapToScene(event->pos()).y());
    }
}
/*
void Draw_map::mouseMoveEvent(QMouseEvent *event)
{
    if (Draw_map::GetFirstClick())
    {
        Draw_map::SetSecondClick(true);
        Draw_map::SetBCoord(event->pos().x(), event->pos().y());
    }


    if ((event->pos().x() <= Draw_map::GetA_x()*Draw_map::Cell_Size) ||
            (event->pos().x() > Draw_map::GetA_x()*Draw_map::Cell_Size + Draw_map::Cell_Size)||
            (event->pos().y() <= Draw_map::GetA_y()*Draw_map::Cell_Size)||
            (event->pos().y() > Draw_map::GetA_y()*Draw_map::Cell_Size + Draw_map::Cell_Size))
    {
        QMessageBox::information(NULL,"", "111");

    }
    timer->start(10);
}*/
void Draw_map::SetTimer()
{
    timer->start(50);
}

void Draw_map::Set_new_draw(bool a)
{
    Draw_map::new_draw = a;
}

bool Draw_map::Get_new_draw()
{
    return Draw_map::new_draw;
}


