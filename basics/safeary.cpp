#include <iostream>

using namespace std;
const int SIZE  = 10;


class safeary 
{
    private:
        int arr[SIZE];
    public:
        safeary() 
        {
            for(int i = 0; i< SIZE; i++) 
            {
                arr[i] = i;
            }
        }

        int& operator [](int i)
        {
            if (i> SIZE)
            {
                cout << "索引值超过最大" << endl;
                return arr[0];
            }
            return arr[i];
        }
};


int main()
{
    safeary A;
    cout << "A[2] 的值:" << A[2] <<endl;
    cout << "A[12]的值" << A[12] << endl;

    return 0;
}