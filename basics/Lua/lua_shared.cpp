// g++ lua_shared.cpp -std=c++11 -shared -fPIC -o liblua_shared.so

extern "C" {

int num = 10;
int my_add(int a, int b);

}

int my_add(int a, int b)
{
    return a + b;
}