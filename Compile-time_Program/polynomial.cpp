#include <iostream>
#include <stdexcept>
#include <string>
#include <assert.h>
#include <vector>

using namespace std;


template <class... Targs>
class polynomial
{
private:
    int x_;
    vector <int> ve_;

public:
    polynomial(int x, const Targs& ...args) : x_(x){
        int Args[] {args...};
        for (auto &p: {args...}){
            ve_.push_back(p);
        }
    }

    int getArgs(const int i) const{
    	return ve_[i];
    }

    int getX() const{
    	return x_;
    }

    int ArgsSize() const{
    	return ve_.size();
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

int main(){
    polynomial pol(2, 1, 2, 3, 7);

    cout << pol;
    return 0;
}
