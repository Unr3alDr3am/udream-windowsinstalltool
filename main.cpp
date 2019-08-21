#include "splash.h"
#include <QApplication>
#include <QTextCodec>
#include <windows.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    splash w;
    w.show();

    return a.exec();
}
