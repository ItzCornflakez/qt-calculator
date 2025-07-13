#include "main_window.h"
#include "ui_main_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonPercentage, &QPushButton::clicked, this, &MainWindow::HandlePushButtonPercentageClicked);
    connect(ui->pushButtonClearEntry, &QPushButton::clicked, this, &MainWindow::HandlePushButtonClearEntryClicked);
    connect(ui->pushButtonClear, &QPushButton::clicked, this, &MainWindow::HandlePushButtonClearClicked);
    connect(ui->pushButtonBackSpace, &QPushButton::clicked, this, &::MainWindow::HandlePushButtonBackSpaceClicked);

    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &MainWindow::HandlePushButtonAddClicked);
    connect(ui->pushButtonSubtract, &QPushButton::clicked, this, &MainWindow::HandlePushButtonSubtractClicked);
    connect(ui->pushButtonMultiply, &QPushButton::clicked, this, &MainWindow::HandlePushButtonMultiplyClicked);
    connect(ui->pushButtonDivide, &QPushButton::clicked, this, &MainWindow::HandlePushButtonDivideClicked);
    connect(ui->pushButtonSquare, &QPushButton::clicked, this, &MainWindow::HandlePushButtonSquareClicked);
    connect(ui->pushButtonSquareRoot, &QPushButton::clicked, this, &MainWindow::HandlePushButtonSquareRootClicked);
    connect(ui->pushButtonOneOverX, &QPushButton::clicked, this, &MainWindow::HandlePushButtonOneOverXClicked);

    connect(ui->pushButton0, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(0); });
    connect(ui->pushButton1, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(1); });
    connect(ui->pushButton2, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(2); });
    connect(ui->pushButton3, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(3); });
    connect(ui->pushButton4, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(4); });
    connect(ui->pushButton5, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(5); });
    connect(ui->pushButton6, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(6); });
    connect(ui->pushButton7, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(7); });
    connect(ui->pushButton8, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(8); });
    connect(ui->pushButton9, &QPushButton::clicked, this, [this]() { HandlePushButtonNumberClicked(9); });

    connect(ui->pushButtonSwitchSign, &QPushButton::clicked, this, &MainWindow::HandlePushButtonSwitchSignClicked);
    connect(ui->pushButtonAddDecimalPoint, &QPushButton::clicked, this, &MainWindow::HandlePushButtonAddDecimalPointClicked);
    connect(ui->pushButtonEnter, &QPushButton::clicked, this, &MainWindow::HandlePushButtonEnterClicked);


    double default_value = 0.0;
    m_active_calculation_block.values.append(default_value);
    m_active_calculation_block.operationTypes.append(OperationType::None);
    calc_index = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandlePushButtonPercentageClicked()
{
    ui->calculationTextBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonClearEntryClicked()
{
    ui->calculationTextBrowser->setText(QString::fromStdString("0"));
}

void MainWindow::HandlePushButtonClearClicked()
{
    ui->calculationTextBrowser->setText(QString::fromStdString("0"));
}

void MainWindow::HandlePushButtonBackSpaceClicked()
{
    ui->calculationTextBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonAddClicked()
{

    m_active_calculation_block.operationTypes.replace(calc_index, OperationType::Add);
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("+ " + SplitNumbersIntoGroups(m_current_display_string)));
}

void MainWindow::HandlePushButtonSubtractClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonMultiplyClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonDivideClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonSquareClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonSquareRootClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonOneOverXClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonNumberClicked(int number)
{
    m_current_display_string += std::to_string(number);

    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(m_current_display_string)));
}

void MainWindow::HandlePushButtonSwitchSignClicked()
{
    ui->calculationTextBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonAddDecimalPointClicked()
{
    ui->calculationTextBrowser->setText(QString::fromStdString("20"));
}

void MainWindow::HandlePushButtonEnterClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("= " + SplitNumbersIntoGroups(m_current_display_string)));
}

std::string MainWindow::SplitNumbersIntoGroups(std::string numeric_string)
{
    std::string result;

    int length = numeric_string.length();

    // We'll process the string from right to left
    for (int i = length - 1, count = 0; i >= 0; i--, count++) {
        // Insert space after every 3 digits (except the first group)
        if (count != 0 && count % 3 == 0) {
            result += ' ';
        }
        result += numeric_string[i];
    }

    // Reverse the string to get the correct order
    std::reverse(result.begin(), result.end());

    return result;
}


