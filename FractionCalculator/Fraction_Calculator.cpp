#include "frac_calc_decs.h"
#include "std_lib_facilities.h"

/*
    A more comprehensive solution to exercise 13, chapter  9 of Programming Principles and practice using C++ (2nd Edition),
    A parser has been developed using the techniques laid out in chapter 6 & 7, Writing and Completing a Program respectively.

    Owing to the exhaustive constructors for the Fraction data-type in namespace Rational, numbers in the input stream will only processed as fractions.
    The parser, and simple grammar permits addition, subtraction, multiplication and division of Fractions.

*/

using namespace Rational;

Token_Stream ts;

Fraction primary()
{
    Token t = ts.get();
    Fraction d;
    switch (t.kind) {
    case 'f':
        d = t.frac;
        break;
    case '-':
        d = (Fraction(-1)*primary());
        break;
    case '+':
        d = primary();
        break;
    default:
        error("primary expected");
    }

    return d;
}

Fraction term()
{
    Fraction left = primary();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left = (left * primary());
            t = ts.get();
            break;
        case '/':
        {
            Fraction d = primary();
            vector <int> view_d = d.view_frac();

            if (view_d[0] == 0)
                error("Fraction division by zero");

            left = (left / d);
            t = ts.get();
            break;
        }

        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

Fraction equate()
{
    Fraction left = term();
    Token t = ts.get();

    while (true) {
        switch (t.kind) {
        case '+':
            left = (left + term());
            t = ts.get();
            break;
        case '-':
            left = (left - term());
            t = ts.get();
            break;
        case '=':
            return left;
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

void fraction_calculate()
{
    cout<<"FRACTION CALCULATOR: use 'f' to input fraction ( 5f3 == 5/3 )"<<endl
    <<" The '/' symbol is reserved for division. "<<endl
    <<" This calculator only works with integer values. "<<endl
    <<">";

    cout<<equate()<<endl<<endl;
}

int main()
{
    try
    {
        while (true)
            fraction_calculate();

        return 0;
    }
    catch (exception& e)
    {
        cerr<<"EXCEPTION: "<<e.what()<<endl;

        return 1;
    }

    catch (...)
    {
        cerr<<"EXCEPTION\n";

        return 2;
    }

}
