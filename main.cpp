#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel label("سیستم مدیریت بانکداری");
    label.show();
    return a.exec();
}