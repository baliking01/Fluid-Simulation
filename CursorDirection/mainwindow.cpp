#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , screen(new Screen(this))
{
    setCentralWidget(screen);
    resize(600, 600);
    //ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

