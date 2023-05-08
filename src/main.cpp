/**
 * @file main.cpp
 * @authors Created with qtcreator
 * @brief Main file of the game, that setups mainwindow.
 * @date 2023-05-08
*/
#include "mainwindow.h"

#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
