#include "std_lib_facilities.h"


namespace Rational
{
    class Fraction
    {
    public:
        Fraction();
        Fraction(int);
        Fraction(int,int);

        void normalise();
        vector <int> view_frac() const;

        void set_f (int, int ); //Needed for = operator overload.

    private:
        int n;
        int d;
    };

    int gcd (int a, int b);
    ostream& operator << (ostream& os, const Fraction& f);

    Fraction reciprocal (const Fraction& f1);

    Fraction operator + (const Fraction& f1, const Fraction& f2);
    Fraction operator - (const Fraction& f1, const Fraction& f2);
    Fraction operator * (const Fraction& f1, const Fraction& f2);
    Fraction operator / (const Fraction& f1, const Fraction& f2);


    class Token
    {
    public:
        char kind;
        int value;
        Fraction frac;
        Token (char);
        Token (char, int);
        Token (char, Fraction);
    };

    class Token_Stream
    {
    public:
        Token_Stream(); //Creates a token stream to read from cin. (Constructor defined in main.cpp)
        Token get(); //Get a token from buffer or cin.
        void putback( Token );
    private:
        bool full;
        Token buffer;
    };

    //The Parser functions are defined in the file with main();
}
