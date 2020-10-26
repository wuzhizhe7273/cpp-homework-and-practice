#include<iostream>
#include<string>
#include<cassert>
#define Numerator 0
#define Denominator 1
#define Acurracy 1000
using namespace std;
class fraction;
class decimal;
class fraction
{
private:
    int Num[2];
public:
    friend class decimal;
    fraction(int _Numerator = 0, int _Denominator = 0)
    {
        Num[Numerator] = _Numerator;
        Num[Denominator] = _Denominator;
        Simpfy();
    }
    fraction(const decimal& shit);
    void Simpfy()
    {
        for (int i = 1; (i < Num[Numerator] / 2) && (i < Num[Denominator] / 2); i++)
        {
            if (Num[Numerator] % i == 0 && Num[Denominator] % i==0)
            {
                Num[Numerator] /= i;
                Num[Denominator] /= i;
                i = 1;
            }
        }
    }
    fraction& operator++()
    {
        Num[Numerator] += Num[Denominator];
        Simpfy();
        return *this;
    }
    fraction operator++(int)
    {
        fraction tmp(*this);
        operator++();
        return tmp;
    }
    fraction& operator+=(const fraction& shit)
    {
        Num[Numerator] = Num[Numerator] * shit.Num[Denominator] + shit.Num[Numerator] * Num[Denominator];
        Num[Denominator] *= shit.Num[Denominator];
        Simpfy();
        return *this;
    }
    friend fraction operator+(fraction lhs, const fraction& rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend ostream& operator<<(ostream& os, const fraction& obj)
    {
        os << obj.Num[Numerator] << "/" << obj.Num[Denominator];
        return os;
    }
};
class decimal
{
private:
    double Num;
public:
    friend class fraction;
    decimal(double _Num = 0) :Num(_Num) {};
    decimal(const fraction& shit)
    {
        Num = double(shit.Num[Numerator]) / double(shit.Num[Denominator]);
    }
    decimal& operator+=(const decimal& shit)
    {
        Num += shit.Num;
        return *this;
    }
    //隐式转换导致二义性
   /*friend decimal operator+(decimal lhs, const decimal& rhs)
    {
        lhs += rhs;
        return lhs;
    }*/
    decimal& operator++()
    {
        ++Num;
        return *this;
    }
    decimal operator++(int)
    {
        decimal tmp(*this);
        operator++();
        return tmp;
    }
    friend ostream& operator<<(ostream& os, const decimal& obj)
    {
        os << obj.Num;
        return os;
    }
};
fraction::fraction(const decimal& shit){
    Num[Numerator] = shit.Num * Acurracy;
    Num[Denominator] = Acurracy;
    Simpfy();
}
int main()
{
    fraction f1(1, 8);
    decimal d1(0.987);
    fraction f2= f1 + d1;
    decimal d2 = f1 + d1;
    cout << f2 << endl;
    cout << d2 << endl;
    f2++;
    d2++;
    cout << f2 << endl;
    cout << d2 << endl;
}
