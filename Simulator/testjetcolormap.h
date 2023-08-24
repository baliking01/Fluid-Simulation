#ifndef TESTJETCOLORMAP_H
#define TESTJETCOLORMAP_H

#include <QObject>
#include <QtTest/QTest>

class TestJetColorMap : public QObject
{
    Q_OBJECT
public:
    explicit TestJetColorMap(QObject *parent = nullptr);

private slots:
    void toUpper();
};

#endif // TESTJETCOLORMAP_H
