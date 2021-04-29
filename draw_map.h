#ifndef DRAW_MAP_H
#define DRAW_MAP_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QWheelEvent>

#include <QMessageBox>
#include <QString>
#include <cstdlib>
#include <vector>

#include "functions.h"

class Draw_map : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Draw_map(QWidget *parent = 0);
    void setScale(int s);
    int getScale();
    void addSquare(QGraphicsItemGroup*,QGraphicsScene);
    void SetTimer();
    void SetFirstClick(bool a);
    void SetSecondClick(bool a);
    bool GetFirstClick();
    bool GetSecondClick();
    void SetACoord(double x, double y);
    void SetBCoord(double x, double y);
    int GetA_x();
    int GetA_y();
    int GetB_x();
    int GetB_y();
    void Set_Path(std::vector<int>);
    bool Get_new_draw();
    void Set_new_draw(bool a);
    std::vector<int> Get_Path();

    static int H_main; // количество ячеек по высоте
    static int W_main; // количество ячеек по ширине
    static double Cell_Size; // размер ячейки карты
    static int scale; // Масштаб изображения
    static bool start_Draw; //флаг установки переметров при заполнении всех полей с данными
    static std::vector<std::vector<Cell>> cell_map; // массив всех клеток карты
    static int width_scale;
    static int height_scale;






signals:

private slots:
    void slotAlarmTimer();  // слот для обработчика переполнения таймера
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);


private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group;     // Объявляем группу элементов
    QTimer              *timer;     // Таймер для задержки отрисовки.
    bool first_click;
    bool second_click;
    int A_x;
    int A_y;
    int B_x;
    int B_y;
    bool new_draw;
    std::vector<int> path;

private:


    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);  // Удаление всех элементов из группы элементов

};

#endif // DRAW_MAP_H


