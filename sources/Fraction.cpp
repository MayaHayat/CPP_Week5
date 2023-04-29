#include "Fraction.hpp"
#include <iostream>
#include <cmath>

using namespace std;
namespace ariel{

Fraction :: Fraction(int numerator , int denominator){
    if (denominator == 0 && numerator != 0){
        throw (" Denominator can't be 0");
    }
    this -> numerator = numerator;
    this -> denominator = denominator;
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
        throw std :: invalid_argument ("This demoninator is illegal");
    }
    this -> denominator = denominator;
}

// -------------------- Help Function ---------------------------

    int Fraction :: getGCD (int numerator, int denominator){
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


Fraction Fraction::operator+(Fraction& frc) const{
    int num = (this -> numerator * frc.denominator) + (frc.numerator * this -> denominator);
    int den = this -> denominator * frc.denominator;
    return Fraction(num,den);
}

float Fraction::operator+(float num){
    float numerator = this -> numerator + num * this->denominator;
    return (numerator/this -> denominator);
}

Fraction operator+(float num, const Fraction &frac){
    return (double(frac.numerator)/frac.denominator) + (num);
}


Fraction Fraction::operator-(Fraction& frc) {
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


Fraction Fraction::operator*( Fraction& frc)  {
    int num = (this->numerator * frc.numerator);
    int den = this ->denominator * frc.denominator;
    return Fraction(num, den);
}

float Fraction::operator*(float num){
    
    return double(this->numerator * num)/this->denominator;
}

Fraction operator*(float num, const Fraction &frac){
    
    return (double(frac.numerator)/frac.denominator)*num;
}


Fraction Fraction::operator/( Fraction& frc)  {
    int num = this -> numerator * frc.denominator;
    int den = this -> denominator * frc.numerator;
    return Fraction(num, den);
}

float Fraction::operator/(float num){
    if (num == 0){
        throw ("Dividing by 0 is illegal!");
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
    if (this -> numerator == frc.numerator && this -> denominator == frc.denominator){
        return true;
    }
    return false;
}


bool Fraction :: operator!=(const Fraction& frc) const{
    if ((this ->numerator/this -> denominator) != (frc.numerator/frc.denominator)){
        return true;
    } 
    return false;
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

std::istream& operator>>(std::istream& in, Fraction& frc){
    int numerator, denominator;
    if (in.peek() == EOF){
        throw ("No numbers entred!");
    }
    in >> numerator;
    if (in.peek() == EOF){
        throw ("Please add another number");
    }
    in >> denominator;
    frc.setNumerator(numerator);
    frc.setDenominator(denominator);
	return in;
}

}





