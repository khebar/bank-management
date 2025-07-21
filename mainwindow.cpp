#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVBoxLayout>
using namespace std;
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
    QStringList customers;
    const LinkedList<Customer*>& allCustomers = Admin::getAllCustomers();
    
    for (int i = 0; i < allCustomers.getSize(); i++) {
        Customer* customer = allCustomers.get(i);
        customers << QString("%1 %2 (%3)")
        .arg(QString::fromStdString(customer->getFirstName()))
        .arg(QString::fromStdString(customer->getLastName()))
        .arg(QString::fromStdString(customer->getUsername()));
    }
    
    bool ok;
    QString selectedCustomer = QInputDialog::getItem(this, "ایجاد حساب", 
                "انتخاب مشتری:", customers, 0, false, &ok);
    if (!ok || selectedCustomer.isEmpty()) return;
    
    int startPos = selectedCustomer.lastIndexOf('(') + 1;
    int endPos = selectedCustomer.lastIndexOf(')');
    QString username = selectedCustomer.mid(startPos, endPos - startPos);
    
    QStringList accountTypes;
    accountTypes << "حساب سپرده" << "حساب جاری" << "حساب قرض‌الحسنه";
    
    QString selectedType = QInputDialog::getItem(this, "ایجاد حساب", 
                "نوع حساب:", accountTypes, 0, false, &ok);
    if (!ok || selectedType.isEmpty()) return;
    
    double initialBalance = QInputDialog::getDouble(this, "ایجاد حساب", 
                "موجودی اولیه:", 0, 0, 1000000000, 2, &ok);
    if (!ok) return;
    
    double rate = 0;
    int term = 0;
    
    if (selectedType == "حساب سپرده") {
        rate = QInputDialog::getDouble(this, "ایجاد حساب", 
        "نرخ سود (٪):", 15, 0, 100, 2, &ok);
        if (!ok) return;
        
        term = QInputDialog::getInt(this, "ایجاد حساب", 
        "مدت (ماه):", 12, 1, 120, 1, &ok);
        if (!ok) return;
    } else if (selectedType == "حساب قرض‌الحسنه") {
        rate = QInputDialog::getDouble(this, "ایجاد حساب", 
        "نرخ کارمزد (٪):", 4, 0, 20, 2, &ok);
        if (!ok) return;
        
        term = QInputDialog::getInt(this, "ایجاد حساب", 
    "مدت بازپرداخت (ماه):", 12, 1, 120, 1, &ok);
        if (!ok) return;
    }

    string accountTypeStr;
    if (selectedType == "حساب سپرده") {
        accountTypeStr = "deposit";
    } else if (selectedType == "حساب جاری") {
        accountTypeStr = "current";
    } else {
        accountTypeStr = "qarz";
    }
    
    if (bankingSystem->createAccount(username.toStdString(), accountTypeStr, initialBalance, rate, term)) {
        QMessageBox::information(this, "موفق", "حساب با موفقیت ایجاد شد.");
        refreshAccountList();
    } else {
        QMessageBox::warning(this, "خطا", "خطا در ایجاد حساب.");
    }

    void MainWindow::on_adminViewCustomersButton_clicked()
{
    const LinkedList<Customer*>& customers = Admin::getAllCustomers();
    
    QDialog dialog(this);
    dialog.setWindowTitle("لیست مشتریان");
    dialog.setMinimumSize(600, 400);
    
    QTableWidget* table = new QTableWidget(&dialog);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "نام" << "نام خانوادگی" << "کد ملی" << "سن" << "نام کاربری");
    table->setRowCount(customers.getSize());
    
    for (int i = 0; i < customers.getSize(); i++) {
        Customer* customer = customers.get(i);
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(customer->getFirstName())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(customer->getLastName())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(customer->getNationalCode())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(customer->getAge())));
        table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(customer->getUsername())));
    }
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->addWidget(table);
    
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dialog.setLayout(layout);
    
    dialog.exec();
}

void MainWindow::on_adminViewAccountsButton_clicked()
{
    const LinkedList<Account*>& accounts = Admin::getAllAccounts();
    
    QDialog dialog(this);
    dialog.setWindowTitle("لیست حساب‌ها");
    dialog.setMinimumSize(800, 400);
    
    QTableWidget* table = new QTableWidget(&dialog);
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels(QStringList() << "نوع حساب" << "شماره حساب" << "شماره کارت" << "شماره شبا" 
                                   << "تاریخ انقضا" << "CVV2" << "موجودی");
    table->setRowCount(accounts.getSize());
    
    for (int i = 0; i < accounts.getSize(); i++) {
        Account* account = accounts.get(i);
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(account->getAccountType())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(account->getAccountNumber())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(account->getCardNumber())));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(account->getIban())));
        table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(account->getExpirationDate())));
        table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(account->getCvv2())));
        table->setItem(i, 6, new QTableWidgetItem(QString::number(account->getBalance(), 'f', 0)));
    }
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->addWidget(table);
    
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dialog.setLayout(layout);
    
    dialog.exec();
}

void MainWindow::on_adminViewAdminsButton_clicked()
{
    const LinkedList<Admin*>& admins = Admin::getAllAdmins();
    
    QDialog dialog(this);
    dialog.setWindowTitle("لیست ادمین‌ها");
    dialog.setMinimumSize(600, 400);
    
    QTableWidget* table = new QTableWidget(&dialog);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "نام" << "نام خانوادگی" << "کد ملی" << "سن" << "نام کاربری");
    table->setRowCount(admins.getSize());
    
    for (int i = 0; i < admins.getSize(); i++) {
        Admin* admin = admins.get(i);
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(admin->getFirstName())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(admin->getLastName())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(admin->getNationalCode())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(admin->getAge())));
        table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(admin->getUsername())));
    }
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->addWidget(table);
    
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dialog.setLayout(layout);
    
    dialog.exec();
}
void MainWindow::on_customerViewAccountsButton_clicked()
{
    Customer* customer = dynamic_cast<Customer*>(bankingSystem->getCurrentUser());
    if (!customer) return;
    
    const LinkedList<Account*>& accounts = customer->getAccounts();
    
    QDialog dialog(this);
    dialog.setWindowTitle("حساب‌های من");
    dialog.setMinimumSize(800, 400);
    
    QTableWidget* table = new QTableWidget(&dialog);
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels(QStringList() << "نوع حساب" << "شماره حساب" << "شماره کارت" << "شماره شبا" 
                                   << "تاریخ انقضا" << "CVV2" << "موجودی");
    table->setRowCount(accounts.getSize());
    
    for (int i = 0; i < accounts.getSize(); i++) {
        Account* account = accounts.get(i);
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(account->getAccountType())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(account->getAccountNumber())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(account->getCardNumber())));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(account->getIban())));
        table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(account->getExpirationDate())));
        table->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(account->getCvv2())));
        table->setItem(i, 6, new QTableWidgetItem(QString::number(account->getBalance(), 'f', 0)));
    }
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->addWidget(table);
    
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dialog.setLayout(layout);
    
    dialog.exec();
}

void MainWindow::on_customerChangeFirstPinButton_clicked()
{
    Customer* customer = dynamic_cast<Customer*>(bankingSystem->getCurrentUser());
    if (!customer) return;
    
    QStringList cardNumbers;
    const LinkedList<Account*>& accounts = customer->getAccounts();
    
    for (int i = 0; i < accounts.getSize(); i++) {
        Account* account = accounts.get(i);
        cardNumbers << QString("%1 (%2)")
                      .arg(QString::fromStdString(account->getCardNumber()))
                      .arg(QString::fromStdString(account->getAccountType()));
    }
    
    bool ok;
    QString selectedCard = QInputDialog::getItem(this, "تغییر رمز اول", 
                                               "انتخاب کارت:", cardNumbers, 0, false, &ok);
    if (!ok || selectedCard.isEmpty()) return;
    
    QString cardNumber = selectedCard.split(" ").first();
    
    QString oldPin = QInputDialog::getText(this, "تغییر رمز اول", 
                                         "رمز فعلی:", QLineEdit::Password, "", &ok);
    if (!ok || oldPin.isEmpty()) return;
    
    QString newPin = QInputDialog::getText(this, "تغییر رمز اول", 
                                         "رمز جدید (4 رقمی):", QLineEdit::Password, "", &ok);
    if (!ok || newPin.isEmpty()) return;
    
    if (newPin.length() != 4 || !newPin.toInt(&ok) || !ok) {
        QMessageBox::warning(this, "خطا", "رمز اول باید 4 رقم باشد.");
        return;
    }
    
    if (bankingSystem->changePin(cardNumber.toStdString(), oldPin.toStdString(), 
                               newPin.toStdString(), false)) {
        QMessageBox::information(this, "موفق", "رمز اول با موفقیت تغییر یافت.");
    } else {
        QMessageBox::warning(this, "خطا", "رمز فعلی اشتباه است یا عملیات با خطا مواجه شد.");
    }
}
void MainWindow::on_customerChangeSecondPinButton_clicked()
{
    Customer* customer = dynamic_cast<Customer*>(bankingSystem->getCurrentUser());
    if (!customer) return;
    
    QStringList cardNumbers;
    const LinkedList<Account*>& accounts = customer->getAccounts();
    
    for (int i = 0; i < accounts.getSize(); i++) {
        Account* account = accounts.get(i);
        cardNumbers << QString("%1 (%2)")
                      .arg(QString::fromStdString(account->getCardNumber()))
                      .arg(QString::fromStdString(account->getAccountType()));
    }
    
    bool ok;
    QString selectedCard = QInputDialog::getItem(this, "تغییر رمز دوم", 
                                               "انتخاب کارت:", cardNumbers, 0, false, &ok);
    if (!ok || selectedCard.isEmpty()) return;
    
    QString cardNumber = selectedCard.split(" ").first();
    
    QString oldPin = QInputDialog::getText(this, "تغییر رمز دوم", 
                                         "رمز فعلی:", QLineEdit::Password, "", &ok);
    if (!ok || oldPin.isEmpty()) return;
    
    QString newPin = QInputDialog::getText(this, "تغییر رمز دوم", 
                                         "رمز جدید (5 رقمی):", QLineEdit::Password, "", &ok);
    if (!ok || newPin.isEmpty()) return;
    
    if (newPin.length() != 5 || !newPin.toInt(&ok) || !ok) {
        QMessageBox::warning(this, "خطا", "رمز دوم باید 5 رقم باشد.");
        return;
    }
    
    if (bankingSystem->changePin(cardNumber.toStdString(), oldPin.toStdString(), 
                               newPin.toStdString(), true)) {
        QMessageBox::information(this, "موفق", "رمز دوم با موفقیت تغییر یافت.");
    } else {
        QMessageBox::warning(this, "خطا", "رمز فعلی اشتباه است یا عملیات با خطا مواجه شد.");
    }
}

void MainWindow::on_customerGenerateDynamicPinButton_clicked()
{
    Customer* customer = dynamic_cast<Customer*>(bankingSystem->getCurrentUser());
    if (!customer) return;
    
    QStringList cardNumbers;
    const LinkedList<Account*>& accounts = customer->getAccounts();
    
    for (int i = 0; i < accounts.getSize(); i++) {
        Account* account = accounts.get(i);
        cardNumbers << QString("%1 (%2)")
                      .arg(QString::fromStdString(account->getCardNumber()))
                      .arg(QString::fromStdString(account->getAccountType()));
    }
    
    bool ok;
    QString selectedCard = QInputDialog::getItem(this, "تولید رمز دوم پویا", 
                                               "انتخاب کارت:", cardNumbers, 0, false, &ok);
    if (!ok || selectedCard.isEmpty()) return;
    
    QString cardNumber = selectedCard.split(" ").first();
    
    std::string dynamicPin = bankingSystem->generateDynamicPin(cardNumber.toStdString());
    
    if (!dynamicPin.empty()) {
        QMessageBox::information(this, "رمز دوم پویا", 
                              QString("رمز دوم پویا: %1\nاین رمز فقط برای یک تراکنش معتبر است.")
                                .arg(QString::fromStdString(dynamicPin)));
    } else {
        QMessageBox::warning(this, "خطا", "خطا در تولید رمز دوم پویا.");
    }
}
}