#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;


const int MAX = 3;

void getSeconds(unsigned long *par);
// 函数模板
template <typename T>
inline T const& Max(T const& a, T const& b)
{
    return a < b ? b : a;
}

// 类模板
template <class T>
class Stack
{
private:
    vector <T> elems;
public:
    void push(T const&);
    void pop();
    T top() const;
    void desc();
    bool empty() const{
        return elems.empty();
    }
};

template <class T>
void Stack<T>::push(T const& elem)
{
    elems.push_back(elem);
}

template <class T>
void Stack<T>::pop() 
{
    if (elems.empty())
    {
        throw out_of_range("Stack<>::pop(): empty stack");
    }
    elems.pop_back();
}

template <class T>
T Stack<T>::top() const
{
    if (elems.empty())
    {
        throw out_of_range("Stack<>::top(): empty stack");
    }
    return elems.back();
}

template <class T>
void Stack<T>::desc()
{
    //for
    for (int i = 0; i < elems.size(); i++)
    {
      cout << "value of elems [" << i << "] = " << elems[i] << endl;
    }
}

int main()
{

    int var1;
    char var2[10];

    cout << "var1 变量的地址：" << &var1 << endl;
    cout << "var2 变量的地址：" << &var2 << endl;

    cout <<"\n\n" << endl;

    
    int var[MAX] = {10, 20, 30};
    int *ptr = NULL;
    ptr = var;
    for (int i = 0; i< MAX; i++) 
    {
        cout<<"Address of var[" << i << "] = " ;
        cout << ptr <<endl;

        cout << "Value of var["<< i <<"] = ";
        cout << *ptr <<endl;

        ptr++;
    }

    for (int i = MAX; i > 0; i--)
    {
        cout<<"Address of var[" << i << "] = " ;
        cout << ptr <<endl;

        cout << "Value of var["<< i <<"] = ";
        cout << *ptr <<endl;

        ptr--;
    }

    cout << var[0] << endl;

    for (int i = 0; i < MAX ; i++)
    {
        *var = i;
        cout << &var <<endl;
        cout<<var[0] << endl;
        cout<< var[1] <<endl;
    }

    cout << "\n\n******************\n\n" << endl;

    const char *names[MAX] = {"Eval", "Wdnd", "Jhon"};
    for (int i = 0; i< MAX; i++)
    {
        cout << "value of name["<< i << "] = " << names[i] << endl;

        cout << "地址：" << &names[i] <<endl;
    }


    cout << "\n\n******************\n\n" << endl;



    unsigned long sec;

    getSeconds(&sec);

    cout << sec << endl;

    
cout << "\n\n******************\n\n" << endl;
    // unsigned long *sec_pointer;
    // getSeconds(sec_pointer);
    // cout << sec_pointer << endl;
    // cout << *sec_pointer <<endl;

    int array[MAX] = {10, 23, 43};
    int *int_pointer;
    int_pointer = array;

    for (int i = 0; i < MAX; i ++) {
        cout << *int_pointer << endl;
        int_pointer++;
    }

cout << "\n\n******************\n\n" << endl;

    try 
    {
        Stack<int> intStack;
        Stack<string> stringStack;

        intStack.push(7);
        intStack.desc();
    }
    catch (exception const& e)
    {
        cerr<< "Exception: " <<e.what() <<endl;
    }

cout << "\n\n******************\n\n" << endl;

    vector<int> vec;
    vec.push_back(10);
    // 迭代器
    vector<int>::iterator v = vec.begin();
    while (v!=vec.end())
    {   
        cout << "value of v = " << *v <<endl;
        v++;
    }
    

    return 0;
}


void getSeconds(unsigned long *par)
{
    *par = time(NULL);
    return;
}