#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <QObject>
#include <QWidget>

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);

signals:

};

#endif // SCREEN_HPP
