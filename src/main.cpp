#include "mainwindow.h"

#include <QApplication>
#include "map.h"
#include "map_object.h"
#include "map_grid.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Map map;
    w.show();
    SquareGrid grid(map.map);
    grid.show();
    return a.exec();
}
