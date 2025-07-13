#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

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

    Ui::MainWindow *ui;

    QList<CalculationBlock> m_calculation_blocks;
    CalculationBlock m_active_calculation_block;
    std::string m_current_display_string;
    int calc_index;
};
#endif // MAIN_WINDOW_H
