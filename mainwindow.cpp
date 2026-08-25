#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    firstNum = 0.0;
    currentOp = "";
    userTyping = false;

    QPushButton *numButtons[10] = {ui->btn_0, ui->btn_1, ui->btn_2, ui->btn_3, ui->btn_4, ui->btn_5, ui->btn_6, ui->btn_7, ui->btn_8, ui->btn_9};
    for(int i = 0; i < 10; ++i) {
        connect(numButtons[i], SIGNAL(clicked()), this, SLOT(numPressed()));
    }

    connect(ui->btn_add, SIGNAL(clicked()), this, SLOT(mathButtonPressed()));
    connect(ui->btn_sub, SIGNAL(clicked()), this, SLOT(mathButtonPressed()));
    connect(ui->btn_mul, SIGNAL(clicked()), this, SLOT(mathButtonPressed()));
    connect(ui->btn_div, SIGNAL(clicked()), this, SLOT(mathButtonPressed()));

    connect(ui->btn_eq, SIGNAL(clicked()), this, SLOT(equalButtonPressed()));
    connect(ui->btn_clear, SIGNAL(clicked()), this, SLOT(clearButtonPressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::numPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if (!userTyping) {
        ui->lineEdit->setText(butVal);
        userTyping = true;
    } else {
        ui->lineEdit->setText(ui->lineEdit->text() + butVal);
    }
}

void MainWindow::mathButtonPressed() {
    userTyping = false;
    currentOp = ((QPushButton *)sender())->text();
    firstNum = ui->lineEdit->text().toDouble();
}

void MainWindow::equalButtonPressed() {
    double secondNum = ui->lineEdit->text().toDouble();
    double result = 0.0;
    if (currentOp == "+") result = firstNum + secondNum;
    else if (currentOp == "-") result = firstNum - secondNum;
    else if (currentOp == "*") result = firstNum * secondNum;
    else if (currentOp == "/") result = firstNum / secondNum;

    ui->lineEdit->setText(QString::number(result));
    userTyping = false;
}

void MainWindow::clearButtonPressed() {
    firstNum = 0.0;
    currentOp = "";
    userTyping = false;
    ui->lineEdit->setText("");
}