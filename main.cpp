#include "widget.h"
#include "pixel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    //w.show();
    pixel w;
    a.setWindowIcon(QIcon("box.ico"));
    return a.exec();
}
