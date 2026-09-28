#pragma once
#include "calculator.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void OnDigitClicked();
    void on_tb_negate_clicked();
    void on_tb_backspace_clicked();
    void on_tb_ms_clicked();
    void on_tb_mr_clicked();
    void on_tb_mc_clicked();

private:
    Ui::MainWindow* ui;
    Calculator calculator_;
    QString input_number_ = "";
    Number active_number_ = 0.0;
    Number memory_value_ = 0.0;
    bool has_memory_ = false;

    enum class Operation {
        NO_OPERATION,
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        POWER
    };
    Operation current_operation_ = Operation::NO_OPERATION;

    QString RemoveTrailingZeroes(const QString &text);
    QString NormalizeNumber(const QString &text);
    void AddText(const QString& suffix);
    void SetOperation(Operation operation_to_symbol_);
    QString OperationToSymbol(Operation operation_to_symbol_);
    void CalculateResult();
    void ResetCalculator();
    void SetInputText(const QString& text);
    void SetResultText(Number value);
    QString FormatNumber(Number value) const;
};
