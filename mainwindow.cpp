#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    bankingSystem = BankingSystem::getInstance();
    bankingSystem->initializeSystem();
    setupLoginPage();
    setupAdminPage();
    setupCustomerPage();
    
    switchToLoginPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupLoginPage()
{
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
}

void MainWindow::setupAdminPage()
{
    connect(ui->adminCreateCustomerButton, &QPushButton::clicked, this, &MainWindow::on_adminCreateCustomerButton_clicked);
    connect(ui->adminCreateAdminButton, &QPushButton::clicked, this, &MainWindow::on_adminCreateAdminButton_clicked);
    connect(ui->adminCreateAccountButton, &QPushButton::clicked, this, &MainWindow::on_adminCreateAccountButton_clicked);
    connect(ui->adminViewCustomersButton, &QPushButton::clicked, this, &MainWindow::on_adminViewCustomersButton_clicked);
    connect(ui->adminViewAccountsButton, &QPushButton::clicked, this, &MainWindow::on_adminViewAccountsButton_clicked);
    connect(ui->adminViewAdminsButton, &QPushButton::clicked, this, &MainWindow::on_adminViewAdminsButton_clicked);
    connect(ui->adminLogoutButton, &QPushButton::clicked, this, &MainWindow::on_adminLogoutButton_clicked);
}

void MainWindow::setupCustomerPage()
{
    connect(ui->customerViewAccountsButton, &QPushButton::clicked, this, &MainWindow::on_customerViewAccountsButton_clicked);
    connect(ui->customerChangeFirstPinButton, &QPushButton::clicked, this, &MainWindow::on_customerChangeFirstPinButton_clicked);
    connect(ui->customerChangeSecondPinButton, &QPushButton::clicked, this, &MainWindow::on_customerChangeSecondPinButton_clicked);
    connect(ui->customerGenerateDynamicPinButton, &QPushButton::clicked, this, &MainWindow::on_customerGenerateDynamicPinButton_clicked);
    connect(ui->customerTransferButton, &QPushButton::clicked, this, &MainWindow::on_customerTransferButton_clicked);
    connect(ui->customerLogoutButton, &QPushButton::clicked, this, &MainWindow::on_customerLogoutButton_clicked);
}

void MainWindow::switchToLoginPage()
{
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle("بانکداری - ورود");
    
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
}

void MainWindow::switchToAdminPage()
{
    ui->stackedWidget->setCurrentIndex(1);
    setWindowTitle("بانکداری - پنل مدیریت");
    refreshCustomerList();
    refreshAccountList();
    refreshAdminList();
}

void MainWindow::switchToCustomerPage()
{
    ui->stackedWidget->setCurrentIndex(2);
    setWindowTitle("بانکداری - پنل مشتری");
    refreshAccountList();
}
void MainWindow::refreshAccountList() {}
void MainWindow::refreshCustomerList() {}
void MainWindow::refreshAdminList() {}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    
    if (bankingSystem->login(username.toStdString(), password.toStdString())) {
        User* user = bankingSystem->getCurrentUser();
        if (user->getUserType() == "ادمین") {
            switchToAdminPage();
        } else {
            switchToCustomerPage();
        }
    } else {
        QMessageBox::warning(this, "خطا", "نام کاربری یا رمز عبور اشتباه است.");
    }
}

void MainWindow::on_adminLogoutButton_clicked()
{
    bankingSystem->logout();
    switchToLoginPage();
}

void MainWindow::on_customerLogoutButton_clicked()
{
    bankingSystem->logout();
    switchToLoginPage();
}
