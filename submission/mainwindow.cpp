#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_memory->setText("");
    ui->l_formula->setText("");
    SetInputText("0");
    connect(ui->tb_one, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_two, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_three, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_four, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_five, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_six, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_seven, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_eight, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_nine, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_zero, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
    connect(ui->tb_add, &QPushButton::clicked, this, [this]() {SetOperation(Operation::ADDITION);});
    connect(ui->tb_substract, &QPushButton::clicked, this, [this]() {SetOperation(Operation::SUBTRACTION);});
    connect(ui->tb_multiplicate, &QPushButton::clicked, this, [this]() {SetOperation(Operation::MULTIPLICATION);});
    connect(ui->tb_divide, &QPushButton::clicked, this, [this]() {SetOperation(Operation::DIVISION);});
    connect(ui->tb_power, &QPushButton::clicked, this, [this]() {SetOperation(Operation::POWER);});
    connect(ui->tb_equal, &QPushButton::clicked, this, [this]() {CalculateResult();});
    connect(ui->tb_reset, &QPushButton::clicked, this, [this]() {ResetCalculator(); });
    connect(ui->tb_comma, &QPushButton::clicked, this, [this]() {AddText(".");});
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::OnDigitClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        AddText(button->text());
    }
}

QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text == "-0" || text == "-") {
        return "0";
    }
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        QString normalizedRest = NormalizeNumber(text.mid(1));
        if (normalizedRest == "0") {
            return "0";
        }
        return "-" + normalizedRest;
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

QString MainWindow::OperationToSymbol(Operation operation_to_symbol_) {
    switch(operation_to_symbol_) {
        case Operation::ADDITION: return "+";
        case Operation::SUBTRACTION: return "−";
        case Operation::MULTIPLICATION: return "×";
        case Operation::DIVISION: return "÷";
        case Operation::POWER: return "^";
        default: return "";
    }
}

void MainWindow::SetOperation(Operation new_operation) {
    if (current_operation_ != Operation::NO_OPERATION && !input_number_.isEmpty()) {
        QString operation_symbol = OperationToSymbol(new_operation);
        QString formula_text = QString("%1 %2").arg(FormatNumber(calculator_.GetNumber())).arg(operation_symbol);
        ui->l_formula->setText(formula_text);
        current_operation_ = new_operation;
        return;
    }
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }
    current_operation_ = new_operation;
    QString operation_symbol = OperationToSymbol(new_operation);
    QString formula_text = QString("%1 %2").arg(FormatNumber(calculator_.GetNumber())).arg(operation_symbol);
    ui->l_formula->setText(formula_text);
    input_number_ = "";
    ui->l_result->setText("");
}

void MainWindow::CalculateResult() {
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }
    QString operation_symbol = OperationToSymbol(current_operation_);
    Number second_operand = 0.0;
    if (!input_number_.isEmpty()) {
        second_operand = input_number_.toDouble();
    } else {
        second_operand = active_number_;
    }
    QString formula_text = QString("%1 %2 %3 =")
                               .arg(FormatNumber(calculator_.GetNumber()))
                               .arg(operation_symbol)
                               .arg(FormatNumber(second_operand));
    ui->l_formula->setText(formula_text);
    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(second_operand);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(second_operand);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(second_operand);
        break;
    case Operation::DIVISION:
        calculator_.Div(second_operand);
        break;
    case Operation::POWER:
        calculator_.Pow(second_operand);
        break;
    default:
        break;
    }
    Number result = calculator_.GetNumber();
    active_number_ = result;
    SetResultText(result);
    current_operation_ = Operation::NO_OPERATION;
    input_number_ = "";
}

void MainWindow::ResetCalculator () {
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->clear();
    SetInputText("0");
}

void MainWindow::on_tb_negate_clicked() {
    if (input_number_.isEmpty()) {
        return;
    }
    if (input_number_.startsWith('-')) {
        input_number_ = input_number_.mid(1);
    } else {
        input_number_ = "-" + input_number_;
    }
    SetInputText(input_number_);
}

void MainWindow::on_tb_backspace_clicked() {
    if (input_number_.isEmpty()) {
        return;
    }
    input_number_.chop(1);
    if(input_number_.isEmpty()) {
        SetInputText("0");
    } else {
        SetInputText(input_number_);
    }
}

void MainWindow::on_tb_ms_clicked() {
    memory_value_ = active_number_;
    has_memory_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::on_tb_mr_clicked() {
    if (!has_memory_) {
        return;
    }
    active_number_ = memory_value_;
    SetResultText(active_number_);
    input_number_ = "";
}

void MainWindow::on_tb_mc_clicked() {
    has_memory_ = false;
    memory_value_ = 0.0;
    ui->l_memory->setText("");
}

void MainWindow::SetInputText(const QString& text) {
    QString normalized = NormalizeNumber(text);
    input_number_ = normalized;
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::SetResultText(Number value) {
    QString str = QString::number(value, 'g', 10);
    input_number_ = str;
    active_number_ = value;
    ui->l_result->setText(str);
}

QString MainWindow::FormatNumber(Number value) const {
    return QString::number(value, 'g', 10);
}

void MainWindow::AddText(const QString& suffix) {
    if (current_operation_ == Operation::NO_OPERATION) {
        ui->l_formula->clear();
    }
    if (suffix == "." && input_number_.contains('.')) {
        return;
    }
    input_number_ += suffix;
    SetInputText(input_number_);
}
