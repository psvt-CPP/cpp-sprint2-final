
#pragma once
#include <cmath>

using Number = double;

class Calculator {
public:
    Calculator (Number init = 0) : number_(init) {}

    void Set(Number n) { number_ = n;} //Устанавливаю число

    Number GetNumber() const {return number_;} //Получаю текущее число

    void Add(Number r) {number_ += r;}
    void Sub(Number r) {number_ -= r;}
    void Mul(Number r) {number_ *= r;}     //Операции
    void Div(Number r) {number_ /= r;}
    void Pow(Number r) {number_ = std::pow(number_, r);}
private:
    Number number_;
};

