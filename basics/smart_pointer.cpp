#include <iostream>
using namespace std;

enum shape_type 
{
    triangle,
    rectangle
};

class shape {
    private:
        int width,height;
    public:
        shape(int a = 0, int b = 0):width(a), height(b){};
        virtual ~shape(){cout << __FUNCTION__ <<endl;};
    
};

class triangle_shap: public shape {

    public:
        triangle_shap(int a , int b):shape(a, b){};
        ~triangle_shap() {cout << __FUNCTION__ << endl;}
};

class rectangle_shape: public shape {
    public:
    rectangle_shape(int a, int b): shape(a, b){};
    ~rectangle_shape(){cout << __FUNCTION__<< endl;}
};

shape * create_shape(shape_type type, int w, int h)
{
    switch (type)   
    {
    case triangle:
        return new triangle_shap(w, h);
        break;
    
    case rectangle:
        return new rectangle_shape(w, h);
        break;
    }
}

class shape_wrapper{
    public:
        explicit shape_wrapper(shape* ptr = nullptr){}
        ~shape_wrapper()
        {
            cout << __FUNCTION__ <<endl;
            delete ptr_;
        }

        shape * get() const {return ptr_;}
    private:
        shape * ptr_;
};



template <typename T>
class  smart_ptr
{
public:
    smart_ptr(T* ptr = nullptr): ptr_(ptr){};
    ~ smart_ptr()
    {
        cout << __FUNCTION__ << endl;
        delete ptr_;
    };
    // 重载
    T& operator *() const {return *ptr_;}
    T* operator ->() const {return ptr_;}
    // 类型转换
    operator bool() const {return ptr_;}
    // 禁止拷贝
    smart_ptr(const smart_ptr&) = delete;
    // smart_ptr& operator=(const smart_ptr&) = delete;

    smart_ptr(smart_ptr& other) 
    { 
        ptr_ = other.release(); 
    } 
    smart_ptr& operator=(smart_ptr& rhs) 
    { 
        smart_ptr(rhs).swap(*this); 
        return *this;
    }
private:
    T* ptr_;
    
    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    void swap(smart_ptr& rhs)
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }

};


int main()
{
    smart_ptr<shape> ptr1{create_shape(triangle, 10, 7)};
    smart_ptr<shape> ptr2 = ptr1;
    return 0;
}