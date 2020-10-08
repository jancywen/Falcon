

#include <cassert>
#include <typeinfo>
#include <string>
#include <iostream>
#include <stdexcept>
#include <type_traits>


template<int N>
struct fib
{
    static_assert(N>=0, "N must be postive");
    static const int value = fib<N - 1>::value + fib<N - 2>::value;
};

template<>
struct fib<0>
{
    static const int value = 1;
};


template<>
struct fib<1>
{
    static const int value = 1;
};

#if __cplusplus >= 201402
constexpr int const_fib(int n)
{
    if (n <= 1) {
        return 1;
    }
    return const_fib(n - 1) + const_fib(n - 2);
}
#else
int const_fib(int n)
{
    return 42;
}
#endif

[[deprecated("deadline:2020-12-31")]]
int old_func()
{
    int value = 0;
    return value;
}

// [[constructor]]
void first_func()
{   
    // can not use cout
    printf("before main()\n");
}

// [[destructor]]
void last_func()
{
    // can not use cout
    printf("after main()\n");
}

_LIBCPP_ALWAYS_INLINE
int get_num()
{
    return 42;
}

_LIBCPP_NORETURN
int case1(bool flag)
{
    throw std::runtime_error("XXX");
}

void case2()
{
    using namespace std;
    __unused
    int nouse;

    cout << __FUNCTION__ << endl;
}


void case3()
{
    using namespace std;
    cout <<  __FUNCTION__ << endl;
}

void case4()
{
    static_assert(sizeof(int) == 4, "int must be 32bit");
    static_assert(sizeof(long) >= 8, "must run on x64");
}

template<typename T>
void check_type(T v)
{
    using namespace std;
    static_assert(is_integral<T>::value, "int");

    static_assert(is_integral_v<T>, "int");

    cout << "static_assert : " << typeid(v).name() <<endl;

    cout << is_void<void>::value <<endl;
    // is_void
}

void case5()
{
    int     i = 0;
    int     *p = &i;

    assert(i > 0 && "i must be greater than zero");
    assert(p != nullptr);

    std::string str = "hello";
    assert(!str.empty());

}

int main()
{
    using namespace std;

    cout << fib<2>::value <<endl;

    int f = old_func();
    case5();

    return 0;
}