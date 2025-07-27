#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include <cmath>
#include <sstream>
#include <iomanip>

#include "data/types.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void HandlePushButtonPercentageClicked();
    void HandlePushButtonClearEntryClicked();
    void HandlePushButtonClearClicked();
    void HandlePushButtonBackSpaceClicked();

    void HandlePushButtonAddClicked();
    void HandlePushButtonSubtractClicked();
    void HandlePushButtonMultiplyClicked();
    void HandlePushButtonDivideClicked();
    void HandlePushButtonSquareClicked();
    void HandlePushButtonSquareRootClicked();
    void HandlePushButtonOneOverXClicked();

    void HandlePushButtonNumberClicked(int number);

    void HandlePushButtonSwitchSignClicked();
    void HandlePushButtonAddDecimalPointClicked();
    void HandlePushButtonEnterClicked();

private:

    std::string SplitNumbersIntoGroups(std::string numeric_string);
    std::string FormatNumber(double num);
    std::string OperationTypeToSign(OperationType operation_type);
    void ResolveCalculation();

    Ui::MainWindow *ui;

    QList<CalculationBlock> m_calculation_blocks;
    CalculationBlock m_active_calc_block;
    std::string m_current_display_string;

    bool can_change_second;

};
#endif // MAIN_WINDOW_H
