#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

using namespace std;


namespace ariel {}
class Fraction{

    private: 
        int numerator;
        int denominator;

    public:

    Fraction(): numerator(1), denominator(1){}

    Fraction(int numerator, int denominator);

    Fraction(float number);
    
    void setNumerator(int);
    void setDenominator(int);

    int getNumerator() const;
    int getDenominator() const;
        
    
    // ----------------- Requested functions ---------------------

    Fraction operator+(const Fraction& other) const;

    Fraction operator+(float num);

    friend Fraction operator+(float num, const Fraction &frac);


    Fraction operator-(const Fraction& other);

    float operator-(float num);

    friend Fraction operator-(float num, const Fraction &frac);


    Fraction operator*(const Fraction& other);

    float operator*(float num);
    
    
    friend Fraction operator*(float num, const Fraction &frac);
    

    Fraction operator/(const Fraction& other);

    float operator/(float num);
    
    friend Fraction operator/(float num, const Fraction &frac);
    

    bool operator==(const Fraction& other) const;

    bool operator==(const float& num) const;
    

    bool operator<(const Fraction& other) const;

    bool operator<(float num) const;

    friend bool operator<(const float& num, const Fraction& frc);

    friend bool operator>(const float& num, const Fraction& frc);

    bool operator>(const Fraction& other) const;
    
    bool operator>(float num) const;
    
    bool operator<=(const Fraction& other) const;

    bool operator<=(float num) const;

    friend bool operator<=(const float& num, const Fraction& frc);

    friend bool operator>=(const float& num, const Fraction& frc);
    
    bool operator>=(const Fraction& other) const;
    
    bool operator>=(float num) const;
    
    Fraction& operator++();
    
    Fraction& operator--();
    
    Fraction operator++(int);
    
    Fraction operator--(int);
    
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
    
    friend std::istream& operator>>(std::istream& inpt, Fraction& fraction);


    // -------------------- Help Function ---------------------------

    int getGCD (int num1, int num2);

    void reduce();


};

#endif