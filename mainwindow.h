#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QAction>
#include <QCloseEvent>
#include <QSettings>

#include "draw_map.h"
#define ORGANIZATION_NAME "Grigorii Tsokurenko"
#define APPLICATION_NAME "PathFinder"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	
protected:
	void closeEvent(QCloseEvent* event);

private slots:
    void on_Generator_clicked();


private:
    Ui::MainWindow *ui;
    Draw_map *map;
    void writeSettings();
    void readSettings();
};
#endif // MAINWINDOW_H
