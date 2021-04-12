#include "mainwindow.h"
#include "ui_mainwindow.h"





int Draw_map::H_main = 0;
int Draw_map::W_main = 0;
double Draw_map::Cell_Size = 0;
int Draw_map::scale = 0;
bool Draw_map::start_Draw = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    map = new Draw_map();

    ui->group->addWidget(map,1,Qt::Alignment());
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_Generator_clicked()
{
    MainWindow::map->SetTimer();
    if ((ui->H_line != NULL) && (ui->W_line != NULL))
    {
        bool ok = true;
        Draw_map::H_main = ui->H_line->text().toInt(&ok);
        Draw_map::W_main = ui->W_line->text().toInt(&ok);
        if (ok)
        {
            return;
        } else
        {
            QMessageBox::critical(this,"Error!","Введены неверные значения!");
        }
    } else
    {
        QMessageBox::critical(this,"Error!","Значения не введены!");
    }
}


