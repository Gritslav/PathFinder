#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setApplicationName(APPLICATION_NAME);
	
    QApplication a(argc, argv);
    MainWindow w;

    w.setMinimumHeight(554);
    w.setMaximumHeight(554);
    w.setMinimumWidth(805);
    w.setMaximumWidth(805);
    w.show();
    return a.exec();
}
