#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void duplicate(int&a, int&b, int&c);

int main()
{

    int a;
    float f = 3.4;

    a = (int)f;
    cout << a << endl;

    int d;
    d = int(f);
    cout << d << endl;

    f = (float)a;
    cout << f << endl;

    string mystr("1024");
    int myint;
    stringstream(mystr) >> myint;
    cout << myint << endl;

    cout << "dd 1234 to int" << endl;
    mystr = "dd 1234 ";
    stringstream(mystr) >> myint;
    cout << myint << endl;


    float price;
    int quantity;

    cout << "Enter price:";

    getline(cin, mystr);

    stringstream(mystr) >> price;

    cout << "Enter quantity: ";
    getline(cin, mystr);
    stringstream(mystr) >>quantity;

    cout << "Total price: " << price * quantity << endl;


    cout << "goto "<< endl;
    int n = 10;
    some:
    cout << n << ",";
    --n;
    if (n > 0) goto some;
    cout << "fire";


    int xint ;
    switch (xint)  
    {
    case 1:
    case 2:
    case 3:
    cout << "xint id 1,2 or 3" << endl;
        break;
    default:
        cout << "xint is not 1, 2 or 3" << endl;
    }

    int x = 1, y = 2, z = 3;
    duplicate(x, y, z);

    cout << x <<"," << y << "," << z << endl;

    return 0;
}



// 地址入参
void duplicate(int&a, int&b, int&c)
{
    a*=2;
    b*=3;
    c*=4;
}

// 递归

void testFactorial() {
    int i;
    cout << "Input a number: ";
    cin >> i;
    cout << i << "! = " << factorial(i);
}

int factorial(int a) 
{
    if (a > 1)
    {
        return a * factorial(a-1);
    }else {
        return 1;
    }
}