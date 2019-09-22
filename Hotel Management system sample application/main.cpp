#include "hotel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Hotel w;
    w.show();
    return a.exec();
}
