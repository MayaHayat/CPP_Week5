#include "Fraction.hpp"
#include <iostream>
#include <cmath>
#include <climits>
#include <cstdlib>

using namespace std;
namespace ariel{


Fraction :: Fraction(){
    this -> numerator = 0;
    this -> denominator = 1;
}

Fraction :: Fraction(int numerator , int denominator){
    if (denominator == 0 && numerator != 0){
        throw std::invalid_argument(" Denominator can't be 0");
    }
    if (numerator > INT_MAX || denominator > INT_MAX){
        throw std::overflow_error("Num is too large, should be an int");
    }
    if (denominator < 0){
        this ->numerator = -1* numerator;
        this ->denominator = -1 * denominator;
    }
    else{
        this -> numerator = numerator;
        this -> denominator = denominator;
    }
    reduce();

}

Fraction::Fraction(float numerator) {
    this -> numerator = std :: round(numerator*1000);
    this -> denominator = 1000;
    reduce();
}

// ----------- Getters & Setters------------

int Fraction :: getNumerator() const{
    return this -> numerator;
}

int Fraction :: getDenominator() const{
    return this -> denominator;
}

void Fraction :: setNumerator(int numerator){
    this -> numerator = numerator;
}

void Fraction :: setDenominator(int denominator){
    if (denominator == 0){
        throw std :: runtime_error ("This denominator is illegal");
    }
    this -> denominator = denominator;
}

// -------------------- Help Function ---------------------------

    int Fraction :: getGCD (int numerator, int denominator){
        if (numerator < 0){
            numerator = abs(numerator);
        }
        if (denominator < 0){
            denominator = abs(denominator);
        }
        if (denominator == 0){
            return numerator;
        }
        return (this -> getGCD(denominator, numerator%denominator));
    }

    void Fraction :: reduce(){
        int gcd = this->getGCD(this -> numerator, this -> denominator);
        this -> numerator /= gcd;
        this -> denominator /= gcd;
    }



// --------------- Requested functions ------------------


Fraction Fraction::operator+(const Fraction& frc) const{
    long check1 = (long(this -> numerator) * frc.denominator) + (long(frc.numerator) * this -> denominator);
    long check2 = long(this->denominator) * frc.denominator;
     if (check1 > INT_MAX || check2 > INT_MAX ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    int num = (this -> numerator * frc.denominator) + (frc.numerator * this -> denominator);
    int den = this -> denominator * frc.denominator;
    return Fraction(num,den);
}

Fraction Fraction::operator+(float num){
    Fraction ans(num);
    Fraction result(*this+ans);
    return result;
}

Fraction operator+(float num, const Fraction &frac){
    return (double(frac.numerator)/frac.denominator) + (num);
}


Fraction Fraction::operator-(const Fraction& frc) {
    long check1 = (long(this -> numerator) * frc.denominator) - (long(frc.numerator) * this -> denominator);
    long check2 = long(this->denominator) * frc.denominator;
     if (check1 > INT_MAX || check2 > INT_MAX ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    int num = (this-> numerator * frc.denominator) - (frc.numerator * this -> denominator);
    int den = this -> denominator * frc.denominator;
    return Fraction(num, den);
}

float Fraction::operator-(float num){
    float numerator = this -> numerator - num * this->denominator;
    return ((numerator)/this -> denominator);
}

Fraction operator-(float num, const Fraction &frac){
    return (num) - (double(frac.numerator)/frac.denominator);
}

Fraction operator-(const Fraction &frac, float num){
    return (double(frac.numerator)/frac.denominator) - num;
}


Fraction Fraction::operator*(const Fraction& frc){
    long check1 = long(this->numerator) * frc.numerator;
    long check2 = long(this->denominator) * frc.denominator;
     if (check1 > INT_MAX || check2 > INT_MAX ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    int num = (this->numerator * frc.numerator);
    int den = this ->denominator * frc.denominator;
    return Fraction(num, den);
}

float Fraction::operator*(float num){
    double numer = double(this->numerator)*num;
    return numer/this->denominator;
}


Fraction operator*(float num, const Fraction &frac){
    return (double(frac.numerator)/frac.denominator)*num;
}


Fraction operator*(const Fraction &frac , float num){
    return (double(frac.numerator)/frac.denominator)*num;
}

Fraction Fraction::operator/(const Fraction& frc)  {
    if (frc.numerator == 0){
        throw std::runtime_error("Dividing by 0 is illegal!");
    }
    long check1 = long(this->numerator) * frc.denominator;
    long check2 = long(this->denominator) * frc.numerator;
     if (check1 > INT_MAX || check2 > INT_MAX ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    int num = this -> numerator * frc.denominator;
    int den = this -> denominator * frc.numerator;
    return Fraction(num, den);
}

float Fraction::operator/(float num){
    if (num == 0){
        throw std::runtime_error("Dividing by 0 is illegal!");
    }
    Fraction number(num);
    float current = double(numerator)/denominator;
    float frc = double(number.numerator)/number.denominator;
    float ans = double(current)/frc;
    return ans;
}

Fraction operator/(float num, const Fraction &frac){
    return num/(double(frac.numerator)/frac.denominator);
}


bool Fraction :: operator==(const Fraction& frc) const{
    if (this ->numerator == 0 && frc.numerator == 0){
        return true;
    }
    double ans1 = std::round(double(this->numerator)/this->denominator * 1000) / 1000.0;
    double ans2 = std::round(double(frc.numerator)/frc.denominator * 1000) / 1000.0;
    if (ans1 == ans2){
        return true;
    }
    return false;
}

bool Fraction :: operator==(const float& num) const{
    double ans1 = std::round(double(this->numerator)/this->denominator*1000) / 1000.0;
    double ans2 = std::round(num *1000)/1000.0;
    if (ans1 != ans2){
        return false;
    }
    return true;
}



bool Fraction :: operator<=(const Fraction& frc) const{
    if ((this -> numerator* frc.denominator) <= (frc.numerator*this -> denominator)){
        return true;
    } 
    return false;
}

bool Fraction :: operator<=(float num) const{
    if (this -> numerator <= num*this -> denominator){
        return true;
    } 
    return false;
}

bool operator<=(const float &num, const Fraction &frc){
    return frc >= num;
}

bool Fraction :: operator<(const Fraction& frc) const{
    if ((this -> numerator* frc.denominator) < (frc.numerator*this -> denominator)){
        return true;
    } 
    return false;
}

bool Fraction :: operator<(float num) const{
    if (this -> numerator < num*this -> denominator){
        return true;
    } 
    return false;
}

bool operator<(const float& num, const Fraction& frac){
    return frac > num;
}


bool Fraction :: operator>=(const Fraction& frc) const{ 
    if ((this -> numerator* frc.denominator) >= (frc.numerator*this -> denominator)){
        return true;
    } 
    return false;
}

bool Fraction :: operator>=(float num) const{
    if (this -> numerator >= num * this -> denominator){
        return true;
    } 
    return false;
}


bool operator>=(const float &num, const Fraction &frc){
    return frc <= num;
}

bool Fraction :: operator>(const Fraction& frc) const{
    if ((this -> numerator* frc.denominator) > (frc.numerator*this -> denominator)){
        return true;
    } 
    return false;
}

bool Fraction :: operator>(float num) const{
    if (this -> numerator > num* this->denominator){
        return true;
    } 
    return false;
}

bool operator>(const float &num, const Fraction &frc){
    return frc < num;
}



Fraction& Fraction ::operator++(){
    this -> numerator += this -> denominator;
    return *this;
}


Fraction Fraction::operator++(int) { 
    Fraction frc(*this); // shouldn't change
    this -> numerator += this -> denominator;
    return frc;
}


Fraction& Fraction ::operator--(){
    this -> numerator -= this -> denominator;
    return *this;
}

Fraction Fraction::operator--(int) { 
    Fraction frc(*this); // shouldn't change
    this -> numerator -= this -> denominator;
    return frc;
}


std::ostream& operator<<(std::ostream& output, const Fraction& fraction){
    return (output << fraction.numerator<< '/' << fraction.denominator);
}

std::istream& operator>>(std::istream& inpt, Fraction& frc){
    int numerator, denominator;
    if (inpt.peek() == EOF){
        throw std::runtime_error ("No numbers entred!");
    }
    inpt >> numerator;
    if (inpt.peek() == EOF){
        throw std::runtime_error ("Please add another number");
    }
    inpt >> denominator;
    if (denominator < 0){
        numerator = -1* numerator;
        denominator = -1 * denominator;
    }
    frc.setNumerator(numerator);
    frc.setDenominator(denominator);
	return inpt;
}

}





