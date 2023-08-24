#include "testjetcolormap.h"
#include <QString>

TestJetColorMap::TestJetColorMap(QObject *parent)
    : QObject{parent}
{
}

void TestJetColorMap::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}
