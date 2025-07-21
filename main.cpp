#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFontDatabase>
#include <QFont>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Load the Persian/Arabic font
    int fontId = QFontDatabase::addApplicationFont(":/font/Vazirmatn.ttf");
    if (fontId != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.empty()) {
            QFont font(fontFamilies.first(), 10);
            a.setFont(font);
        }
    }

    // Set right-to-left layout for Persian text
    a.setLayoutDirection(Qt::RightToLeft);

    MainWindow w;
    w.show();
    return a.exec();
}