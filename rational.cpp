#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
class rational
{
public:
    rational(int numerator, int denominator);
    rational(int numerator);
    rational();

    void output(ostream &stream, string rNum);
    void input(istream &stream);

    rational neg();
    rational add(rational frac);
    rational sub(rational frac);
    rational mul(rational frac);
    rational div(rational frac);
    bool less(rational frac);
    
    void simp();

private:
    int numerator;
    int denominator;
    int getNum() { return numerator; }
    int getDen() { return denominator; }
};

int gcd(int a, int b);

int main()
{
    rational r1(15, 4);
    rational r2(12, -3);

    r1.output(cout, "r1");
    r2.output(cout, "r2");

    rational r3 = r2.neg();
    r3.output(cout, "r3");

    rational r4 = r1.neg();
    r4.output(cout, "r4");

    cout << endl;
    ifstream in1;
    in1.open("inp1.txt");
    rational r5;
    cout << "r5 will get input from ifstream (connected to inp1.txt):" << endl;
    r5.input(in1);
    in1.close();
    r5.output(cout, "r5");
    cout << endl;

    rational r6 = r3.add(r1);
    r6.output(cout, "r6");

    rational r7 = r3.sub(r1);
    r7.output(cout, "r7");

    rational r8 = r6.mul(r7);
    r8.output(cout, "r8");

    rational r9 = r8.div(r5);
    r9.output(cout, "r9");
    cout << endl;

    cout << "r9 < r1: " << r9.less(r1) << endl;
    cout << "r4 < r5: " << r4.less(r5) << endl;
    cout << "r6 < r8: " << r6.less(r8) << endl;
    cout << "r1 < r3: " << r1.less(r3) << endl;

    cout << endl;
    rational y1(70);
    y1.output(cout, "y1");

    cout << endl;
    rational y2;
    y2.output(cout, "y2");

    cout << "y2 will now get input from cin: " << endl;
    y2.input(cin);
    // enter: 34/-6 (user input)
    y2.output(cout, "y2");

    cout << endl;
    ofstream ofs;
    ofs.open("log1.txt", ofstream::out); // ofstream::app
    r1.output(ofs, "r1");
    r2.output(ofs, "r2");
    r3.output(ofs, "r3");
    r4.output(ofs, "r4");
    r5.output(ofs, "r5");
    r6.output(ofs, "r6");
    r7.output(ofs, "r7");
    r8.output(ofs, "r8");
    r9.output(ofs, "r9");
    y1.output(ofs, "y1");
    y2.output(ofs, "y2");

    ofs.close();

    rational r10(18, 0);
    rational r11(12, 4);

    return 0;
}

// constructor for rational class
rational::rational(int numerator, int denominator)
{
    this->numerator = numerator;
    this->denominator = denominator;
    simp();
}

// constructor with only numerator
rational::rational(int numerator)
{
    this->numerator = numerator;
    denominator = 1;
}

// empty constructor
rational::rational() : numerator(0), denominator(1)
{
}

// prints fraction
void rational::output(ostream &stream, string rNum)
{
    stream << rNum << ": " << numerator << "/" << denominator << endl;
}

// makes fraction negative
rational rational::neg()
{
    return rational(numerator * -1, denominator);
}

// gets arguments from file
void rational::input(istream &stream)
{
    if (&stream == &cin)
    {
        cout << "enter numerator: ";
        cin >> numerator;
        cout << "enter denominator: ";
        cin >> denominator;
        simp();
    }
    else
    {
        int i = 0;
        string str;
        while (!stream.eof())
        {
            getline(stream, str);
            if (i == 0)
            {
                numerator = stoi(str);
            }
            if (i == 1)
            {
                denominator = stoi(str);
            }
            i++;
        }
        simp();
    }
}
int gcd(int a, int b){
    if (b == 0)
       return a;
    return gcd(b, a % b); 
}

// adds 2 rationals
rational rational::add(rational toAdd)
{
    return rational(numerator * toAdd.getDen() + denominator * toAdd.getNum(), denominator * toAdd.getDen());
}

// subtracts 2 rationals
rational rational::sub(rational toSub)
{
    return rational(numerator * toSub.getDen() - denominator * toSub.getNum(), denominator * toSub.getDen());
}

// multiplys 2 rationals
rational rational::mul(rational toMul)
{
    return rational(numerator * toMul.getNum(), denominator * toMul.getDen());
}

// divides 2 rationals
rational rational::div(rational toDiv)
{
    return rational(numerator * toDiv.getDen(), denominator * toDiv.getNum());
}

// determine if rational is smaller than another rational
bool rational::less(rational isLess)
{
    if (numerator * isLess.getDen() < isLess.getNum() * denominator)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void rational::simp()
{
    if (denominator == 0)
    {
        cout << "Denominator can\'t be 0";
    }
    int gc = gcd(numerator, denominator);
    numerator = numerator / gc;
    denominator = denominator / gc;
    if (denominator < 0)
    {
        numerator = numerator * -1;
        denominator = denominator * -1;
    }
}