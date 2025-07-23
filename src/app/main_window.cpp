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

    m_active_calculation_block.first_value = NOT_SET;
    m_active_calculation_block.second_value = NOT_SET;
    m_active_calculation_block.operation_type = OperationType::None;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandlePushButtonPercentageClicked()
{
    double& first = m_active_calculation_block.first_value;
    double& second = m_active_calculation_block.second_value;
    OperationType& operation_type = m_active_calculation_block.operation_type;

    if(first == NOT_SET)
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("0"));
        ui->calculationTextBrowser->setText(QString::fromStdString("0"));
        m_current_display_string.clear();
        return;
    }

    std::string sign;

    switch(operation_type)
    {
        case OperationType::Add:
            sign = " + ";
            if(m_current_display_string.empty())
                second = first;
            else
                second = (first / 100) * std::stod(m_current_display_string);
            break;
        case OperationType::Subtract:
            sign = " - ";
            if(m_current_display_string.empty())
                second = first;
            else
                second = (first / 100) * std::stod(m_current_display_string);
            break;
        case OperationType::Multiply:
            sign = " * ";
            if(m_current_display_string.empty())
                second = 1;
            else
                second = std::stod(m_current_display_string) / 100;
            break;
        case OperationType::Divide:
            sign = " / ";
            if(m_current_display_string.empty())
                second = 1;
            else
                second = std::stod(m_current_display_string) / 100;
            break;
        default:
            break;

    }

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(FormatNumber(first)) + sign + SplitNumbersIntoGroups(FormatNumber(second))));
    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(FormatNumber(second))));

    m_current_display_string.clear();

}

void MainWindow::HandlePushButtonClearEntryClicked()
{
    m_current_display_string.clear();
    ui->calculationTextBrowser->setText(QString::fromStdString("0"));
}

void MainWindow::HandlePushButtonClearClicked()
{
    m_active_calculation_block.first_value = NOT_SET;
    m_active_calculation_block.second_value = NOT_SET;
    m_active_calculation_block.operation_type = OperationType::None;

    m_current_display_string.clear();
    ui->tempTextHistoryBrowser->setText(QString::fromStdString(""));
    ui->calculationTextBrowser->setText(QString::fromStdString("0"));

}

void MainWindow::HandlePushButtonBackSpaceClicked()
{
    if(m_current_display_string.empty())
        return;

    m_current_display_string = m_current_display_string.substr(0, m_current_display_string.size()-1);

    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(m_current_display_string)));
}

void MainWindow::HandlePushButtonAddClicked()
{
    m_active_calculation_block.operation_type = OperationType::Add;

    double& first = m_active_calculation_block.first_value;
    double& second = m_active_calculation_block.second_value;

    if(m_current_display_string.empty())
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("+ " + SplitNumbersIntoGroups(FormatNumber(first))));
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("+ " + SplitNumbersIntoGroups(m_current_display_string)));
        m_current_display_string.clear();
        return;
    }

    second = std::stod(m_current_display_string);

    ui->tempTextHistoryBrowser->setText(QString::fromStdString("+ " + SplitNumbersIntoGroups(FormatNumber(first+second))));
    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(FormatNumber(first+second))));
    m_current_display_string.clear();

    first = first+second;
    second = NOT_SET;

}

void MainWindow::HandlePushButtonSubtractClicked()
{
    m_active_calculation_block.operation_type = OperationType::Subtract;

    double& first = m_active_calculation_block.first_value;
    double& second = m_active_calculation_block.second_value;

    if(m_current_display_string.empty())
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("- " + SplitNumbersIntoGroups(FormatNumber(first))));
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("- " + SplitNumbersIntoGroups(m_current_display_string)));
        m_current_display_string.clear();
        return;
    }

    second = std::stod(m_current_display_string);

    ui->tempTextHistoryBrowser->setText(QString::fromStdString("- " + SplitNumbersIntoGroups(FormatNumber(first-second))));
    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(FormatNumber(first-second))));
    m_current_display_string.clear();

    first = first-second;
    second = NOT_SET;
}

void MainWindow::HandlePushButtonMultiplyClicked()
{
    m_active_calculation_block.operation_type = OperationType::Multiply;

    double& first = m_active_calculation_block.first_value;
    double& second = m_active_calculation_block.second_value;

    if(m_current_display_string.empty())
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("* " + SplitNumbersIntoGroups(FormatNumber(first))));
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("* " + SplitNumbersIntoGroups(m_current_display_string)));
        m_current_display_string.clear();
        return;
    }

    second = std::stod(m_current_display_string);

    ui->tempTextHistoryBrowser->setText(QString::fromStdString("* " + SplitNumbersIntoGroups(FormatNumber(first*second))));
    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(FormatNumber(first*second))));
    m_current_display_string.clear();

    first = first*second;
    second = NOT_SET;
}

void MainWindow::HandlePushButtonDivideClicked()
{
    m_active_calculation_block.operation_type = OperationType::Divide;

    double& first = m_active_calculation_block.first_value;
    double& second = m_active_calculation_block.second_value;

    if(m_current_display_string.empty())
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("/ " + SplitNumbersIntoGroups(FormatNumber(first))));
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("/ " + SplitNumbersIntoGroups(m_current_display_string)));
        m_current_display_string.clear();
        return;
    }

    second = std::stod(m_current_display_string);

    ui->tempTextHistoryBrowser->setText(QString::fromStdString("/ " + SplitNumbersIntoGroups(FormatNumber(first/second))));
    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(FormatNumber(first/second))));
    m_current_display_string.clear();

    first = first/second;
    second = NOT_SET;
}

void MainWindow::HandlePushButtonSquareClicked()
{
    m_active_calculation_block.operation_type = OperationType::Square;

    double& first = m_active_calculation_block.first_value;
    double& second = m_active_calculation_block.second_value;

    std::string temp_history_output;
    std::string calculation_output;

    if(m_current_display_string.empty())
    {
        if(ui->tempTextHistoryBrowser->toPlainText().toStdString().empty())
        {
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("sqr(0)"));
        }
        else
        {
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("sqr(" + ui->tempTextHistoryBrowser->toPlainText().toStdString() + ")"));
        }
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);

        ui->tempTextHistoryBrowser->setText(QString::fromStdString("sqr(" + SplitNumbersIntoGroups(FormatNumber(first)) + ")"));
        ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(FormatNumber(pow(first, 2)))));
        return;
    }

    if(second == NOT_SET)
        second = std::stod(m_current_display_string);



    if(std::floor(first/second) == first/second)
    {
        temp_history_output = "/ " + SplitNumbersIntoGroups(std::to_string(static_cast<int>(first/second)));
        calculation_output = SplitNumbersIntoGroups(std::to_string(static_cast<int>(first/second)));
    }
    else
    {
        temp_history_output = "/ " + SplitNumbersIntoGroups(std::to_string(first/second));
        calculation_output = SplitNumbersIntoGroups(std::to_string(first/second));
    }


    ui->tempTextHistoryBrowser->setText(QString::fromStdString(temp_history_output));
    ui->calculationTextBrowser->setText(QString::fromStdString(calculation_output));
    m_current_display_string.clear();

    first = first/second;
    second = NOT_SET;
}

void MainWindow::HandlePushButtonSquareRootClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("sqrt() " + SplitNumbersIntoGroups(m_current_display_string)));
    m_current_display_string = "";
}

void MainWindow::HandlePushButtonOneOverXClicked()
{
    ui->tempTextHistoryBrowser->setText(QString::fromStdString("1/ " + SplitNumbersIntoGroups(m_current_display_string)));
    m_current_display_string = "";
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
    /*
    m_active_calculation_block.values.append(std::stod(m_current_display_string));

    std::string temp_history_output;
    std::string calculation_output;
    double calculation_output_value;

    if(m_active_calculation_block.values.size() == 1)
    {
        double firstNumber = m_active_calculation_block.values.first();
        if(std::floor(firstNumber) == firstNumber)
        {
            temp_history_output = SplitNumbersIntoGroups(std::to_string((static_cast<int>(firstNumber)))) +
                                  " + " + SplitNumbersIntoGroups(std::to_string((static_cast<int>(firstNumber))));
        }
        else
        {
            temp_history_output = SplitNumbersIntoGroups(std::to_string((firstNumber))) +
                                  " + " + SplitNumbersIntoGroups(std::to_string((firstNumber)));
        }

        calculation_output_value += firstNumber*2;
    }
    else
    {
        for(int i = 0; i < m_active_calculation_block.values.size(); i++)
        {
            double value = m_active_calculation_block.values.at(i);
            if(std::floor(value) == value)
            {
                if(i != 0)
                    temp_history_output += "+" + SplitNumbersIntoGroups(std::to_string(static_cast<int>(value)));
                else
                    temp_history_output += SplitNumbersIntoGroups(std::to_string(static_cast<int>(value)));
            }
            else
            {
                temp_history_output += "+" + SplitNumbersIntoGroups(std::to_string((value)));
            }

            calculation_output_value += value;
        }
    }

    switch (m_active_calculation_block.operation_type) {
    case OperationType::Add:
        break;
    default:
        break;
    }


    if(std::floor(calculation_output_value) == calculation_output_value)
        calculation_output = std::to_string(static_cast<int>(calculation_output_value));
    else
        calculation_output = std::to_string((calculation_output_value));

    ui->tempTextHistoryBrowser->setText(QString::fromStdString("= " + temp_history_output));
    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(calculation_output)));
    m_current_display_string = "";
    m_active_calculation_block = {};
    m_active_calculation_block.operation_type = OperationType::None;

    */
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

std::string MainWindow::FormatNumber(double num)
{
    std::ostringstream oss;
    oss << std::defaultfloat << std::setprecision(6); // 6 digits max, no trailing zeros
    oss << num;
    return oss.str();
}


