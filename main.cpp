#include <QApplication>
#include <QLabel>
#include <QLocale>
#include <QTranslator>
#include <QFontDatabase>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel label("سیستم مدیریت بانکداری");
    label.show();
    return a.exec();
    //
    QFontDatabase::addApplicationFont(":/fonts/Vazir.ttf");
    QFont font("Vazir", 10);
    a.setFont(font);

    a.setLayoutDirection(Qt::RightToLeft);

    MainWindow w;
    w.show();
    return a.exec();
}