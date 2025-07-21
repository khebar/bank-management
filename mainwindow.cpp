#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    bankingSystem = BankingSystem::getInstance();
    bankingSystem->initializeSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}