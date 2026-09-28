
#pragma once

using Number = double;

class Calculator {
public:
    Calculator (Number init = 0) : number_(init) {}

    void Set(Number number);
    Number GetNumber() const;
    void Add(Number operand);
    void Sub(Number operand);
    void Mul(Number operand);
    void Div(Number operand);
    void Pow(Number operand);
private:
    Number number_;
};

