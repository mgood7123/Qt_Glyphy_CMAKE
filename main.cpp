#include "GLWindow.h"

#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    GLWindow glWindow;
    glWindow.show();
    return a.exec();
}
