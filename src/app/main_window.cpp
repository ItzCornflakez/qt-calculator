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

    HandlePushButtonClearClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandlePushButtonPercentageClicked()
{
    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;
    OperationType& operation_type = m_active_calc_block.old_operation_type;

    if(first == NOT_SET)
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString("0"));
        ui->calculationTextBrowser->setText(QString::fromStdString("0"));
        m_current_display_string.clear();
        return;
    }

    std::string sign = OperationTypeToSign(operation_type);

    switch(operation_type)
    {
        case OperationType::Add:
            if(m_current_display_string.empty())
                second = first;
            else
                second = (first / 100) * std::stod(m_current_display_string);
            break;
        case OperationType::Subtract:
            if(m_current_display_string.empty())
                second = first;
            else
                second = (first / 100) * std::stod(m_current_display_string);
            break;
        case OperationType::Multiply:
            if(m_current_display_string.empty())
                second = 1;
            else
                second = std::stod(m_current_display_string) / 100;
            break;
        case OperationType::Divide:
            if(m_current_display_string.empty())
                second = 1;
            else
                second = std::stod(m_current_display_string) / 100;
            break;
        default:
            break;

    }

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + sign + FormatNumber(second)));
    ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(second)));

}

void MainWindow::HandlePushButtonClearEntryClicked()
{
    m_current_display_string.clear();
    ui->calculationTextBrowser->setText(QString::fromStdString("0"));
}

void MainWindow::HandlePushButtonClearClicked()
{
    m_active_calc_block.first_value = NOT_SET;
    m_active_calc_block.second_value = NOT_SET;
    m_active_calc_block.old_operation_type = OperationType::None;
    m_active_calc_block.new_operation_type = OperationType::None;

    can_change_second = true;

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
    m_active_calc_block.new_operation_type = OperationType::Add;
    can_change_second = true;

    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;

    if(m_current_display_string.empty())
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " +"));
        m_active_calc_block.old_operation_type = m_active_calc_block.new_operation_type;
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);
        ui->tempTextHistoryBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(m_current_display_string) + " +"));
        m_active_calc_block.old_operation_type = m_active_calc_block.new_operation_type;
        m_current_display_string.clear();
        return;
    }

    second = std::stod(m_current_display_string);

    ResolveCalculation();

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " +"));
    ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(first)));

}

void MainWindow::HandlePushButtonSubtractClicked()
{
    m_active_calc_block.new_operation_type = OperationType::Subtract;
    can_change_second = true;

    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;

    if(m_current_display_string.empty())
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " -"));
        m_active_calc_block.old_operation_type = m_active_calc_block.new_operation_type;
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);
        ui->tempTextHistoryBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(m_current_display_string)) + " -");
        m_active_calc_block.old_operation_type = m_active_calc_block.new_operation_type;
        m_current_display_string.clear();
        return;
    }

    second = std::stod(m_current_display_string);

    ResolveCalculation();

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " -"));
    ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(first)));
}

void MainWindow::HandlePushButtonMultiplyClicked()
{
    m_active_calc_block.new_operation_type = OperationType::Multiply;
    can_change_second = true;

    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;

    if(m_current_display_string.empty())
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " *"));
        m_active_calc_block.old_operation_type = m_active_calc_block.new_operation_type;
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);
        ui->tempTextHistoryBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(m_current_display_string) + " *"));
        m_active_calc_block.old_operation_type = m_active_calc_block.new_operation_type;
        m_current_display_string.clear();
        return;
    }

    second = std::stod(m_current_display_string);

    ResolveCalculation();

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " *"));
    ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(first)));
}

void MainWindow::HandlePushButtonDivideClicked()
{
    m_active_calc_block.new_operation_type = OperationType::Divide;
    can_change_second = true;

    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;

    if(m_current_display_string.empty())
    {
        ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " /"));
        m_active_calc_block.old_operation_type = m_active_calc_block.new_operation_type;
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);
        ui->tempTextHistoryBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(m_current_display_string) + " /"));
        m_active_calc_block.old_operation_type = m_active_calc_block.new_operation_type;
        m_current_display_string.clear();
        return;
    }

    second = std::stod(m_current_display_string);

    ResolveCalculation();

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " /"));
    ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(first)));
}

void MainWindow::HandlePushButtonSquareClicked()
{
    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;
    OperationType& operation_type = m_active_calc_block.old_operation_type;
    std::string sign = OperationTypeToSign(operation_type);

    if(m_current_display_string.empty() && first == NOT_SET)
    {
        if(ui->tempTextHistoryBrowser->toPlainText().toStdString().empty())
        {
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("sqr(0)"));
        }
        else
        {
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("sqr(" + ui->tempTextHistoryBrowser->toPlainText().toStdString() + ")"));
            ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(pow(first, 2))));
            first = pow(first, 2);
        }
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);

        ui->tempTextHistoryBrowser->setText(QString::fromStdString("sqr(" + FormatNumber(first) + ")"));
        ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(pow(first, 2))));

        first = pow(first, 2);
        m_current_display_string.clear();
        return;
    }

    if(m_current_display_string.empty())
        second = first;
    else
        second = std::stod(m_current_display_string);

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + sign + "sqr(" + FormatNumber(second) + ")"));
    ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(pow(second, 2))));

    second = pow(second, 2);
}

void MainWindow::HandlePushButtonSquareRootClicked()
{
    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;
    OperationType& operation_type = m_active_calc_block.old_operation_type;
    std::string sign = OperationTypeToSign(operation_type);

    if(m_current_display_string.empty() && first == NOT_SET)
    {
        if(ui->tempTextHistoryBrowser->toPlainText().toStdString().empty())
        {
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("√(0)"));
        }
        else
        {
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("√(" + ui->tempTextHistoryBrowser->toPlainText().toStdString() + ")"));
            ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(pow(first, 0.5))));
            first = pow(first, 0.5);
        }
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);

        ui->tempTextHistoryBrowser->setText(QString::fromStdString("√(" + FormatNumber(first) + ")"));
        ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(pow(first, 0.5))));

        first = pow(first, 0.5);
        m_current_display_string.clear();
        return;
    }

    if(m_current_display_string.empty())
        second = first;
    else
        second = std::stod(m_current_display_string);

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + sign + "√(" + FormatNumber(second) + ")"));
    ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(pow(second, 0.5))));

    second = pow(second, 0.5);
}

void MainWindow::HandlePushButtonOneOverXClicked()
{
    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;
    OperationType& operation_type = m_active_calc_block.old_operation_type;
    std::string sign = OperationTypeToSign(operation_type);

    if(m_current_display_string.empty() && first == NOT_SET)
    {
        if(ui->tempTextHistoryBrowser->toPlainText().toStdString().empty())
        {
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("1/(0)"));
            ui->calculationTextBrowser->setText(QString::fromStdString("Cannot divide by zero"));
        }
        else
        {
            qDebug() << ui->tempTextHistoryBrowser->toPlainText().toStdString();
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("1/(" + ui->tempTextHistoryBrowser->toPlainText().toStdString() + ")"));
            ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(1.0/first)));
            first = 1.0 / first;
        }
        return;
    }

    if(first == NOT_SET)
    {
        first = std::stod(m_current_display_string);

        ui->tempTextHistoryBrowser->setText(QString::fromStdString("1/(" + FormatNumber(first) + ")"));
        ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(1.0/first)));

        first = 1.0 / first;
        m_current_display_string.clear();
        return;
    }

    if(m_current_display_string.empty())
        second = first;
    else
        second = std::stod(m_current_display_string);

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + sign + "1/(" + FormatNumber(second) + ")"));
    ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(1.0/second)));

    second = 1.0 / second;
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
    if(m_current_display_string.back() == '.')
        return;

    m_current_display_string += ".";

    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(m_current_display_string)));
}

void MainWindow::HandlePushButtonEnterClicked()
{
    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;
    OperationType& operation_type = m_active_calc_block.old_operation_type;
    std::string sign = OperationTypeToSign(operation_type);

    if(first == NOT_SET)
    {
        if(m_current_display_string.empty())
        {
            ui->tempTextHistoryBrowser->setText(QString::fromStdString("0 ="));
            ui->calculationTextBrowser->setText(QString::fromStdString("0"));
            m_current_display_string.clear();
        }
        else
        {
            first = std::stod(m_current_display_string);
            ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + " ="));
            ui->calculationTextBrowser->setText(QString::fromStdString(FormatNumber(first)));
            m_current_display_string.clear();
        }

        return;
    }
    if(operation_type == OperationType::None)
        return;

    if(can_change_second)
    {
        if(m_current_display_string.empty())
            second = first;
        else
            second = std::stod(m_current_display_string);
        can_change_second = false;
    }

    ui->tempTextHistoryBrowser->setText(QString::fromStdString(FormatNumber(first) + sign + FormatNumber(second) + " ="));

    ResolveCalculation();

    ui->calculationTextBrowser->setText(QString::fromStdString(SplitNumbersIntoGroups(FormatNumber(first))));

}

std::string MainWindow::SplitNumbersIntoGroups(std::string numeric_string)
{
    std::string result;
    size_t decimal_point = numeric_string.find('.');

    // Extract the integer part
    std::string integer_part;
    if (decimal_point == std::string::npos) {
        integer_part = numeric_string;
    } else {
        integer_part = numeric_string.substr(0, decimal_point);
    }

    // Check if the integer part is >= 1000 (at least 4 digits)
    if (integer_part.length() >= 4) {
        // Process the integer part with grouping
        int length = integer_part.length();
        for (int i = length - 1, count = 0; i >= 0; i--, count++) {
            if (count != 0 && count % 3 == 0) {
                result += ' ';
            }
            result += integer_part[i];
        }
        std::reverse(result.begin(), result.end());

        // Add the decimal part if it exists
        if (decimal_point != std::string::npos) {
            result += numeric_string.substr(decimal_point);
        }
    } else {
        // Return the original string if less than 1000
        result = numeric_string;
    }

    return result;
}

std::string MainWindow::FormatNumber(double num)
{
    std::ostringstream oss;
    oss << std::defaultfloat << std::setprecision(16); // 6 digits max, no trailing zeros
    oss << num;
    return SplitNumbersIntoGroups(oss.str());
}

std::string MainWindow::OperationTypeToSign(OperationType operation_type)
{
    std::string sign;

    switch(operation_type)
    {
    case OperationType::Add:
        sign = " + ";
        break;
    case OperationType::Subtract:
        sign = " - ";
        break;
    case OperationType::Multiply:
        sign = " * ";
        break;
    case OperationType::Divide:
        sign = " / ";
        break;
    default:
        break;

    }

    return sign;
}

void MainWindow::ResolveCalculation()
{
    double& first = m_active_calc_block.first_value;
    double& second = m_active_calc_block.second_value;
    OperationType& old_operation_type = m_active_calc_block.old_operation_type;
    OperationType& new_operation_type = m_active_calc_block.new_operation_type;
    std::string sign = OperationTypeToSign(old_operation_type);

    switch(old_operation_type)
    {
    case OperationType::Add:
        first = first+second;
        break;
    case OperationType::Subtract:
        first = first-second;
        break;
    case OperationType::Multiply:
        first = first*second;
        break;
    case OperationType::Divide:
        first = first/second;
        break;
    default:
        break;

    }

    old_operation_type = new_operation_type;

    m_current_display_string.clear();

}


