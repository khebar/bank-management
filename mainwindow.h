#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bankingsystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //login slot
    void on_loginButton_clicked();
    //Admin slots
    void on_adminCreateCustomerButton_clicked();
    void on_adminCreateAdminButton_clicked();
    void on_adminCreateAccountButton_clicked();
    void on_adminViewCustomersButton_clicked();
    void on_adminViewAccountsButton_clicked();
    void on_adminViewAdminsButton_clicked();
    void on_adminLogoutButton_clicked();
    //Customer slots
    void on_customerViewAccountsButton_clicked();
    void on_customerChangeFirstPinButton_clicked();
    void on_customerChangeSecondPinButton_clicked();
    void on_customerGenerateDynamicPinButton_clicked();
    void on_customerTransferButton_clicked();
    void on_customerLogoutButton_clicked();

private:
    Ui::MainWindow *ui;
    BankingSystem* bankingSystem;
    
    void setupLoginPage();
    void setupAdminPage();
    void setupCustomerPage();
    void switchToLoginPage();
    void switchToAdminPage();
    void switchToCustomerPage();
    void refreshAccountList();
    void refreshCustomerList();
    void refreshAdminList();
    
};

#endif // MAINWINDOW_H