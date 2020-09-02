#include <iostream>

using namespace std;

void printBook( struct Books book);
void printPointerBook( struct Books *book);

typedef struct Car
{
    char    brand[20];
    double  price;
} Car;

void printCar(Car car);

struct Books
{
    char    title[50];
    char    author[50];
    char    subject[100];
    int     book_id;
};



void printBook(struct Books book) 
{
    cout << "书标题：" << book.title << endl;
}

void printPointerBook( struct Books *book)
{
    cout << "书的标题：" << book -> title << endl;
}

void printCar(Car car) 
{
    cout << car.brand << endl;
}


class Box 
{
    double width;
    protected:
        double height;

    public:
        double length;
        // 友元函数
        friend void printWidth(Box box);
        void setWidth( double wid);

        // 构造函数
        Box(double wid);
        // 拷贝构造函数
        Box(const Box &obj);
        // 析构函数
        ~Box();

        // 静态成员
        static int objectCount; 
        // 静态成员函数
        static int getCount()
        {
            return objectCount;
        }
};

// 构造函数
Box::Box(double wid)
{
    width = wid;
}
// 拷贝构造函数
Box::Box(const Box &obj) {

}
// 析构函数
Box::~Box(void) 
{

}

void Box::setWidth(double wid)
{
    width = wid;
}

void printWidth(Box box) 
{
    cout << "width of box:" << box.width <<endl;
}

// 初始化 静态成员
int Box:: objectCount = 0;


class D
{
    public:
        D(){cout << "D()" << endl;}
        ~D(){cout<< "~D()" << endl;}
    protected:
        int d;
};

class B: virtual public D
{
    public:
        B(){cout << "B()" << endl;}
        ~B(){cout<< "~B()" << endl;}
    protected:
        int b;
};

class A: virtual public D
{
    public:
        A(){cout << "A()" << endl;}
        ~A(){cout<< "~A()" << endl;}
    protected:
        int a;
};

class C: public A, public B
{
    public:
        C(){cout << "C()" << endl;}
        ~C(){cout<< "~C()" << endl;}
    protected:
        int c;
};

int main()
{

    Box box(12.0);
    box.setWidth(10.0);

    printWidth(box);

    cout << Box::getCount() << endl;
    

    Books Book1;
    strcpy(Book1.title, "C++");
    printBook(Book1);

    printPointerBook( &Book1);


    A a;

    cout << "**************" << endl;
    C c;
    cout << sizeof(c) << endl;

    return 0;
}