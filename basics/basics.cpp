#include <iostream>
using namespace std;


const int MAX = 3;

void getSeconds(unsigned long *par);

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


    return 0;
}


void getSeconds(unsigned long *par)
{
    *par = time(NULL);
    return;
}