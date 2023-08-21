#include "mainwindow.h"
#include "testjetcolormap.h"
#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    TestJetColorMap test1;
    QTest::qExec(&test1, argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
