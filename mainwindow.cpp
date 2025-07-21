#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

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
void MainWindow::on_adminCreateCustomerButton_clicked()
{
    QString firstName = QInputDialog::getText(this, "ایجاد مشتری", "نام:");
    if (firstName.isEmpty()) return;
    
    QString lastName = QInputDialog::getText(this, "ایجاد مشتری", "نام خانوادگی:");
    if (lastName.isEmpty()) return;
    
    QString nationalCode = QInputDialog::getText(this, "ایجاد مشتری", "کد ملی:");
    if (nationalCode.isEmpty()) return;
    
    bool ok;
    int age = QInputDialog::getInt(this, "ایجاد مشتری", "سن:", 18, 18, 120, 1, &ok);
    if (!ok) return;
    
    QString username = QInputDialog::getText(this, "ایجاد مشتری", "نام کاربری:");
    if (username.isEmpty()) return;
    
    QString password = QInputDialog::getText(this, "ایجاد مشتری", "رمز عبور:", QLineEdit::Password);
    if (password.isEmpty()) return;
    
    if (bankingSystem->createCustomer(firstName.toStdString(), lastName.toStdString(),
                                    nationalCode.toStdString(), age,
                                    username.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "موفق", "مشتری با موفقیت ایجاد شد.");
        refreshCustomerList();
    } else {
        QMessageBox::warning(this, "خطا", "خطا در ایجاد مشتری. نام کاربری یا کد ملی تکراری است.");
    }
}

void MainWindow::on_adminCreateAdminButton_clicked()
{
    QString firstName = QInputDialog::getText(this, "ایجاد ادمین", "نام:");
    if (firstName.isEmpty()) return;
    
    QString lastName = QInputDialog::getText(this, "ایجاد ادمین", "نام خانوادگی:");
    if (lastName.isEmpty()) return;
    
    QString nationalCode = QInputDialog::getText(this, "ایجاد ادمین", "کد ملی:");
    if (nationalCode.isEmpty()) return;
    
    bool ok;
    int age = QInputDialog::getInt(this, "ایجاد ادمین", "سن:", 18, 18, 120, 1, &ok);
    if (!ok) return;
    
    QString username = QInputDialog::getText(this, "ایجاد ادمین", "نام کاربری:");
    if (username.isEmpty()) return;
    
    QString password = QInputDialog::getText(this, "ایجاد ادمین", "رمز عبور:", QLineEdit::Password);
    if (password.isEmpty()) return;
    
    if (bankingSystem->createAdmin(firstName.toStdString(), lastName.toStdString(),
                                 nationalCode.toStdString(), age,
                                 username.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "موفق", "ادمین با موفقیت ایجاد شد.");
        refreshAdminList();
    } else {
        QMessageBox::warning(this, "خطا", "خطا در ایجاد ادمین. نام کاربری تکراری است.");
    }
}