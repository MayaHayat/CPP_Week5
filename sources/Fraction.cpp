#include "Fraction.hpp"
#include <iostream>
#include <cmath>
#include <climits>
#include <cstdlib>

using namespace std;




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


// *this (frc1) +frc
Fraction Fraction::operator+(const Fraction& frc) const{
    
    //cout << "1" << endl;
    long check1 = (long(this -> numerator) * frc.denominator) + (long(frc.getNumerator()) * this -> denominator);
    long check2 = long(this->denominator) * frc.denominator;
     if (check1 > INT_MAX || check2 > INT_MAX ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    int num = (this -> numerator * frc.denominator) + (frc.getNumerator() * this -> denominator);
    int den = this -> denominator * frc.denominator;
    return Fraction(num,den);
}

// *this (frc1) +num
Fraction Fraction::operator+(float num){
    
   // cout << "2" << endl;
    Fraction ans(num);
    Fraction result(*this+ans);
    return result;
}

// num + frc
Fraction operator+(float num, const Fraction &frc){
    //cout << "3" << endl;
    return (double(frc.getNumerator())/frc.getDenominator()) + (num);
}


//*this (frc1) + frc
Fraction Fraction::operator-(const Fraction& frc) {
    //cout << "5" << endl;
    long check1 = (long(this -> numerator) * frc.getDenominator()) - (long(frc.getNumerator()) * this -> denominator);
    long check2 = long(this->denominator) * frc.getDenominator();
     if (check1 > INT_MAX || check2 > INT_MAX ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    int num = (this-> numerator * frc.getDenominator()) - (frc.getNumerator() * this -> denominator);
    int den = this -> denominator * frc.getDenominator();
    return Fraction(num, den);
}

// *this -num
float Fraction::operator-(float num){
    //cout << "6" << endl;
    float numerator = this -> numerator - num * this->denominator;
    return ((numerator)/this -> denominator);
}

// num - frc
Fraction operator-(float num, const Fraction &frc){
    //cout << "7" << endl;
    return (num) - (double(frc.getNumerator())/frc.getDenominator());
}

// *this(frc1)* frc
Fraction Fraction::operator*(const Fraction& frc){
    //cout << "8" << endl;
    long check1 = long(this->numerator) * frc.getNumerator();
    long check2 = long(this->denominator) * frc.getDenominator();
    if (check1 > INT_MAX || check2 > INT_MAX ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    int num = (this->numerator * frc.getNumerator());
    int den = this ->denominator * frc.getDenominator();
    return Fraction(num, den);
}

// *this (frc) *num
float Fraction::operator*(float num){
    //cout << "9" << endl;
    long check1 = long(this->numerator) *num;
    long check2 = long(this->denominator);
    if (check1  > INT_MAX *check2 ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    double numer = double(this->numerator)*num;
    return numer/this->denominator;
}

//num*frc
Fraction operator*(float num, const Fraction &frc){
    //cout << "10" << endl;
    long check1 = long(frc.numerator) *num;
    long check2 = long(frc.denominator);
    if (check1  > INT_MAX *check2 ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    return (double(frc.getNumerator())/frc.getDenominator())*num;
}

// *this/frc
Fraction Fraction::operator/(const Fraction& frc)  {
    //cout << "11" << endl;
    if (frc.getNumerator() == 0){
        throw std::runtime_error("Dividing by 0 is illegal!");
    }
    long check1 = long(this->numerator) * frc.getDenominator();
    long check2 = long(this->denominator) * frc.getNumerator();
     if (check1 > INT_MAX || check2 > INT_MAX ||  check1 < INT_MIN || check2 < INT_MIN){
        throw std::overflow_error (" Note we're using INTEGERS");
    }
    int num = this -> numerator * frc.denominator;
    int den = this -> denominator * frc.getNumerator();
    return Fraction(num, den);
}

// *this/num
float Fraction::operator/(float num){
    //cout << "12" << endl;
    if (num == 0){
        throw std::runtime_error("Dividing by 0 is illegal!");
    }
    Fraction number(num);
    float current = double(numerator)/denominator;
    float frc = double(number.getNumerator())/number.getDenominator();
    float ans = double(current)/frc;
    return ans;
}


// num/frc
Fraction operator/(float num, const Fraction &frc){
    //cout << "13" << endl;
    return num/(double(frc.getNumerator())/frc.getDenominator());
}


//*this == frc
bool Fraction :: operator==(const Fraction& frc) const{
    //cout << "14" << endl;
    if (this ->numerator == 0 && frc.getNumerator() == 0){
        return true;
    }
    double ans1 = std::round(double(this->numerator)/this->denominator * 1000) / 1000.0;
    double ans2 = std::round(double(frc.getNumerator())/frc.getDenominator() * 1000) / 1000.0;
    if (ans1 == ans2){
        return true;
    }
    return false;
}

// *this == num
bool Fraction :: operator==(const float& num) const{
    //cout << "15" << endl;
    double ans1 = std::round(double(this->numerator)/this->denominator*1000) / 1000.0;
    double ans2 = std::round(num *1000)/1000.0;
    if (ans1 != ans2){
        return false;
    }
    return true;
    
}


// *this <= frc
bool Fraction :: operator<=(const Fraction& frc) const{
    //cout << "16" << endl;
    if ((this -> numerator* frc.getDenominator()) <= (frc.getNumerator()*this -> denominator)){
        return true;
    } 
    return false;
}

//*this <= num
bool Fraction :: operator<=(float num) const{
    //cout << "17" << endl;

    return (operator==(num) || operator<(num));
}

// num <= frc
bool operator<=(const float &num, const Fraction &frc){
    //cout << "18" << endl;
    return frc >= num;
}

// *this < frc
bool Fraction :: operator<(const Fraction& frc) const{
    //cout << "19" << endl;
    return !(operator>=(frc));
}

// *this  < num
bool Fraction :: operator<(float num) const{
    //cout << "20" << endl;
    return !(operator>=(num));
}

// num < frc
bool operator<(const float& num, const Fraction& frc){
    //cout << "21" << endl;
    return !(operator>=(num,frc));
}

// *this >= frc
bool Fraction :: operator>=(const Fraction& frc) const{ 
    //cout << "22" << endl;
    if ((this -> numerator* frc.getDenominator()) >= (frc.getNumerator()*this -> denominator)){
        return true;
    } 
    return false;
}

//*this >= num
bool Fraction :: operator>=(float num) const{
    //cout << "23" << endl;
    if (this -> numerator >= num * this -> denominator){
        return true;
    } 
    return false;
}

// num >= frc
bool operator>=(const float &num, const Fraction &frc){
    //cout << "24" << endl;
    return frc <= num;
}

// *this > frc
bool Fraction :: operator>(const Fraction& frc) const{
    //cout << "25" << endl;
    return !(operator<=(frc));
}


// *this > num
bool Fraction :: operator>(float num) const{
    //cout << "26" << endl;
    return !(operator<=(num));
}


//
bool operator>(const float &num, const Fraction &frc){
    //cout << "27" << endl;
    return !(operator<=(num, frc));

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


std::ostream& operator<<(std::ostream& output, const Fraction& frction){
    return (output << frction.numerator<< '/' << frction.denominator);
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






