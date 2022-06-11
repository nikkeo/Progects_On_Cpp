#include <iostream>
#include <stdexcept>
#include <string>
#include <assert.h>
#include <vector>

using namespace std;

constexpr int pow(int x, int n){
    int sum = 1;

    for (int i = 0; i < n; ++i){
        sum *= x;
    }

    return sum;
}

template <class... Targs>
class polynomial
{
private:
    int x_;
    vector <int> ve_;
    int size_;
    
public:
    polynomial(int x, const Targs& ...args) : x_(x){
        int Args[] {args...};
        for (auto &p: {args...}){
            ve_.push_back(p);
        }
        size_ = ve_.size();
    }

    int getArgs(const int i) const{
        return ve_[i];
    }

    int getX() const{
        return x_;
    }

    constexpr int ArgsSize() const{
        return size_;
    }

    ~polynomial(){}
};

template <class... Targs>
ostream& operator<<(ostream &os, const polynomial<Targs ...>& pol){
        string q;
        
        for (int i = 0; i < pol.ArgsSize(); ++i){
            if (pol.getArgs(i) != 0){
                if (i != 0){
                    q += '+';
                }
                q += to_string(pol.getArgs(i));
                q += "x^";
                q += to_string(i);
            }
        }

        os << q;
        os << endl;
        return os;
}

template <class... Targs>
constexpr int func(const polynomial<Targs ...> pol)
{
    int sum = 0;

    for (int i = 0; i < pol.ArgsSize(); ++i){
        sum += pol.getArgs(i) * pow(pol.getX(), i);
    }

    return sum;
}


int main()
{
    polynomial pol(2, 1, 2, 10, 12);
    cout << func(pol);

    cout << endl << pol;

    return 0;
}
