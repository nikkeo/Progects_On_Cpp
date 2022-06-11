#include <iostream>
#include <stdexcept>
#include <string>
#include <assert.h>

using namespace std;

constexpr int pow(int x, int n){
    int sum = 1;

    for (int i = 0; i < n; ++i){
        sum *= x;
    }

    return sum;
}

template <class... Targs>
constexpr int func(int x, const Targs& ...args)
{
    int Args[] {args...};
    int sum = 0, i = 0;

    for (auto &p: Args){
        sum += p * pow(x, i);
        ++i;
    }

    return sum;
}


int main()
{

    constexpr int a = func(2, 1, 2, 10, 12);
    cout << a;
    static_assert(func(2, 1, 2, 10, 12) == 141, "None");
    static_assert(func(2, 1, 2, 10, 12));

    return 0;
}