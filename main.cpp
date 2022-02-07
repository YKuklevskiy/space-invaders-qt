#include "mainwindow.h"

#include <QApplication>
#include <chrono>
#include <random>

int main(int argc, char *argv[])
{
    std::srand(std::chrono::system_clock::now().time_since_epoch().count()*7215215); // seed
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
