#include "mainwindow.h"

#include <QApplication>
#include "map.h"
#include "map_object.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
