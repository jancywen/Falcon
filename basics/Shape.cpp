#include <iostream>
using namespace std;


enum shape_type{
    triangle,
    rectangle
};

class Shape
{
    protected:
        int width, height;
    public:
        Shape(int a = 0, int b = 0);
        virtual ~Shape(){cout << __FUNCTION__ <<endl;}
        // 纯虚函数
        virtual int area()  = 0;
        
};

Shape::Shape(int a , int b ):width(a), height(b){}


class Rectangle: public Shape
{   
    public:
        Rectangle(int a = 0, int b = 0):Shape(a, b){}
        ~Rectangle(){cout << __FUNCTION__ <<endl;}
        int area()
        {
            cout << "Rectangle class area:" <<endl;
            return (width*height);
        }
};

class Triangle: public Shape {
    public:
        Triangle( int a = 0, int b = 0): Shape(a, b){}
        ~Triangle(){cout << __FUNCTION__ <<endl;}
        int area()
        {
            cout << "Triangle class area:"<< endl;
            return (width*height/2);
        }
};

Shape * create_shape(shape_type type, int w, int h) {
    switch (type)   
    {
    case triangle:
        
        return new Triangle(w, h);
        break;
    
    case rectangle:
        return new Rectangle(w, h);
        break;
    }
}

class shape_wrapper {
    public:
        explicit shape_wrapper(Shape *ptr = nullptr):ptr_(ptr){}
        ~shape_wrapper()
        {
            cout << __FUNCTION__ << endl;
            delete ptr_;
        }
        Shape * get() const {return ptr_;}
    private:
        Shape * ptr_;
};

int main() 
{
    // Shape *shape;
    // Rectangle rec(10, 7);
    // Triangle tri(10, 5);

    // shape = &rec;
    // cout<< shape ->area() << endl;

    // shape = &tri;
    // cout << shape->area() << endl;
    // clog << "clog 打印"<< endl;

    enum shape_type type;
    type = triangle;
    
    shape_wrapper ptr_wrapper(create_shape(triangle, 10, 7));

    cout << ptr_wrapper.get()->area() << endl;

    return 0;
}