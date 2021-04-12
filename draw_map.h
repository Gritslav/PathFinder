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

#include "cell.h"
#include <vector>

class Draw_map : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Draw_map(QWidget *parent = 0);
    void setScale(int s);
    int getScale();
    void addSquare(QGraphicsItemGroup*,QGraphicsScene);
    void SetTimer();

    static int H_main; // количество ячеек по высоте
    static int W_main; // количество ячеек по ширине
    static double Cell_Size; // размер ячейки карты
    static int scale; // Масштаб изображения
    static bool start_Draw; //флаг установки переметров при заполнении всех полей с данными






signals:

private slots:
    void slotAlarmTimer();  // слот для обработчика переполнения таймера

private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group;     // Объявляем группу элементов
    QTimer              *timer;     // Таймер для задержки отрисовки.

private:

    void resizeEvent(QResizeEvent *event);

    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);  // Удаление всех элементов из группы элементов
    void wheelEvent(QWheelEvent *event);
};

#endif // DRAW_MAP_H


