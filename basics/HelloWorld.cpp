

#include <iostream>

using namespace std;


class Box 
{
    public:
        double length;  //长度
        double breadth; //宽度
        double height;  //高度

        // 声明成员函数
        double getVolume(void);
        void setLength(double len) 
        {
            length = len;
        }
};

// 在类的外部使用范围解析运算符 :: 定义该函数
double Box::getVolume(void)
{
    return length * breadth * height;
}

int main() 
{
    Box Box1;
    Box Box2;
    double volume = 0.0;

    Box1.length = 5.0;
    Box1.breadth = 10.0;
    Box1.height = 12;


    volume = Box1.length * Box1.breadth * Box1.height;
    cout << "Box1 的体积:" << volume << endl;
    cout << "Box1 的体积:" << Box1.getVolume() << endl;
    return 0;
}