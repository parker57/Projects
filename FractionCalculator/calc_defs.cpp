#include "std_lib_facilities.h"
#include "frac_calc_decs.h"


namespace Rational
{
    Fraction::Fraction()
        :n{0}, d{1} {}
    Fraction::Fraction(int num)
        :n{num}, d{1} {}
    Fraction::Fraction(int num,int den)
        :n{num}, d{den} { normalise(); }

    void Fraction::normalise()
    {
        if (d==0)
            error("Denominator is zero, Zero Division ERROR.");
        if (d<0)
        {
            d*=-1;
            n*=-1;
        }
        if (gcd(n,d)>1)
        {
            int divisor = gcd(n,d);
            n/=divisor;
            d/=divisor;
        }
    }

    void Fraction::set_f(int nn, int dd)
    {
        n=nn;
        d=dd;
    }

    vector<int> Fraction::view_frac() const
    {
        vector<int> fraction;
        fraction.push_back(n);
        fraction.push_back(d);
        return fraction;

    }

    int gcd (int a, int b) //Euclidean Algorithm for Greatest common divisor
    {
        int t;
        while (b!=0)
        {
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    Fraction reciprocal (const Fraction& f1)
    {
        vector<int> recip_fraction = f1.view_frac();
        Fraction rf{recip_fraction[1],recip_fraction[0]};
        return rf;
    }

    ostream& operator << (ostream& os, const Fraction& f)
    {
        vector <int> vf = f.view_frac();
        if ((abs(vf[0])==abs(vf[1])) || vf[1]==1)
            return os<<vf[0];
        return os<<vf[0]<<"/"<<vf[1];
    }

    Fraction operator + (const Fraction& f1, const Fraction& f2)
    {
        vector<int> frac1 = f1.view_frac();
        vector<int> frac2 = f2.view_frac();

        int common_denom = frac1[1]*frac2[1];
        int numerator = (frac1[0]*frac2[1])+(frac2[0]*frac1[1]);
        Fraction added{numerator,common_denom};
        return added;
    }

    Fraction operator - (const Fraction& f1, const Fraction& f2)
    {
        vector<int> frac1 = f1.view_frac();
        vector<int> frac2 = f2.view_frac();

        int common_denom = frac1[1]*frac2[1];
        int numerator = (frac1[0]*frac2[1])-(frac2[0]*frac1[1]);
        Fraction added{numerator,common_denom};
        return added;
    }

    Fraction operator * (const Fraction& f1, const Fraction& f2)
    {
        vector<int> frac1 = f1.view_frac();
        vector<int> frac2 = f2.view_frac();

        int n_num = frac1[0]*frac2[0];
        int n_dom = frac1[1]*frac2[1];

        Fraction n_frac{n_num, n_dom};
        return n_frac;
    }

    Fraction operator / (const Fraction& f1, const Fraction& f2)
    {
        vector<int> frac1 = f1.view_frac();
        Fraction recip_of_f2 = reciprocal(f2);
        vector<int> frac2 = recip_of_f2.view_frac();

        int n_num = frac1[0]*frac2[0];
        int n_dom = frac1[1]*frac2[1];

        Fraction n_frac{n_num, n_dom};
        return n_frac;
    }



    Token::Token(char k)
        :kind{k} {}
    Token::Token(char k, int v)
        :kind{k}, value{v} {}
    Token::Token(char k, Fraction f)
        :kind{k}, frac{f} {}

    Token_Stream::Token_Stream()
        :full(false), buffer(0) {}
    void Token_Stream::putback( Token t)
    {
        if (full) error("putback() into a full buffer");
        buffer = t;
        full = true;
    }

    Token Token_Stream::get()
    {
        if (full)
        {
            full=false;
            return buffer;
        }

        char ch;
        cin>>ch;
        switch (ch)
        {
        //Need to think about the grammar, how do we interpret negative numbers.

        case '!':   // for factorials
        case '(': case ')': case '+': case '-': case '*': case '/':
        case '{': case '}': case '=':
            return Token(ch);


        case '.':
            error("This program only takes integers to construct fractions.");
            break;
        case 'f':
            error("No NUMERATOR defined?");
            break;

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            {
                cin.putback(ch);
                int val;
                cin>>val;
                char f_test;
                cin>>f_test;
                if (f_test=='f')
                {
                    int val2;
                    cin>>val2;
                    return Token ('f',Fraction{val,val2});
                }
                else
                {
                    cin.putback(f_test);
                    return Token('f',Fraction(val));
                }
                //return Token ('8', val); //Letting 8 represent a number/ integer.
            }
        default:
            cout<<ch<<" is an undefined character."<<endl;
            error(" UNKNOWN INPUT");
            break;
        }
    }


}

