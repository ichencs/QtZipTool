#include "QtZipTool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtZipTool w;
    w.show();
    return a.exec();
}
