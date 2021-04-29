#include "mainwindow.h"
#include "ui_mainwindow.h"





int Draw_map::H_main = 0;
int Draw_map::W_main = 0;
double Draw_map::Cell_Size = 0;
int Draw_map::scale = 0;
bool Draw_map::start_Draw = false;
std::vector<std::vector<Cell>> Draw_map::cell_map (1, std::vector<Cell> (1));
int Draw_map::width_scale = 0;
int Draw_map::height_scale = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    map = new Draw_map();

    ui->group->addWidget(map,1,Qt::Alignment());
    MainWindow::readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::readSettings()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.beginGroup("POSITION");
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
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
            Draw_map::cell_map.resize(Draw_map::W_main);
            for (int i = 0; i < Draw_map::W_main; i++)
            {
                Draw_map::cell_map[i].resize(Draw_map::H_main);
            }


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

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.beginGroup("POSITION");
    settings.setValue("pos", pos());
    settings.endGroup();
    QMainWindow::closeEvent(event);
}

