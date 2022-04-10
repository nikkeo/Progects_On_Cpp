#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <vector>
#include <queue>
const int SIZE = 10000;


using namespace std;


class polynomial{
private:
	double arr[SIZE];
	vector <int> ve;
public:
	polynomial(){}


	void show(){
		for (int i = 0; i < ve.size(); ++i){
			cout << ve[i] << " " << arr[ve[i]] << "  ";
		}
		cout << endl;
	}
	// x = коэффициент, y = степень x

	bool exists(int y){
		for (int i = 0; i < ve.size(); ++i){
			if (ve[i] == y){
				return 1;
			}
		}
		return 0;
	}

	void changeMonomial(double x, int y){
		arr[y] += x;
	}

	void addNewMonomial(double x, int y){
		for (int i = 0; i < ve.size(); ++i){
			if (y == ve[i]){
				arr[y] += x;
				return;
			}
		}
		arr[y] = x;
		ve.push_back(y);
	}

	void reset(){
		while (ve.size() > 0){
			ve.pop_back();
		}
	}

	void operator=(const polynomial &equating){
		while (ve.size() > 0){
			ve.pop_back();
		}
		for (int i = 0; i < equating.ve.size(); ++i){
			ve.push_back(equating.ve[i]);
			arr[ve[i]] = equating.arr[ve[i]];
		}
	}

	bool operator==(const polynomial& comparison){
		bool final = 1;
		for (int i = 0; i < ve.size(); ++i){
			bool b = 0;
			for (int j = 0; j < comparison.ve.size(); ++j){
				if (ve[i] == comparison.ve[j]){
					if (arr[ve[i]] == comparison.arr[comparison.ve[j]]){
						b = 1;
					}
					else{
						break;
					}
				}
			}

			if (!b){
				final = 0;
				break;
			}
		}

		for (int j = 0; j < comparison.ve.size(); ++j){
			bool b = 0;
			for (int i = 0; i < ve.size(); ++i){
				if (ve[i] == comparison.ve[j]){
					if (arr[ve[i]] == comparison.arr[comparison.ve[j]]){
						b = 1;
					}
					else{
						break;
					}
				}
			}
			
			if (!b){
				final = 0;
				break;
			}
		}

		return final;
	}

	bool operator!=(const polynomial& comparison){
		bool final = 1;
		for (int i = 0; i < ve.size(); ++i){
			bool b = 0;
			for (int j = 0; j < comparison.ve.size(); ++j){
				if (ve[i] == comparison.ve[j]){
					if (arr[ve[i]] == comparison.arr[comparison.ve[j]]){
						b = 1;
					}
					else{
						break;
					}
				}
			}

			if (!b){
				final = 0;
				break;
			}
		}

		for (int j = 0; j < comparison.ve.size(); ++j){
			bool b = 0;
			for (int i = 0; i < ve.size(); ++i){
				if (ve[i] == comparison.ve[j]){
					if (arr[ve[i]] == comparison.arr[comparison.ve[j]]){
						b = 1;
					}
					else{
						break;
					}
				}
			}
			
			if (!b){
				final = 0;
				break;
			}
		}

		return (!final);
	}

	polynomial operator+(const polynomial& addition){
		polynomial newone;

		for (int i = 0; i < addition.ve.size(); ++i){
			newone.addNewMonomial(addition.ve[i], addition.arr[addition.ve[i]]);
		}
		for (int i = 0; i < ve.size(); ++i){
			if (newone.exists(ve[i])){
				newone.changeMonomial(ve[i], arr[ve[i]]);
			}
			else{
				newone.addNewMonomial(ve[i], arr[ve[i]]);
			}
		}

		return newone;
	}

	void operator+=(const polynomial& addition){
		polynomial newone;

		for (int i = 0; i < addition.ve.size(); ++i){
			newone.addNewMonomial(addition.ve[i], addition.arr[addition.ve[i]]);
		}
		for (int i = 0; i < ve.size(); ++i){
			if (newone.exists(ve[i])){
				newone.changeMonomial(ve[i], arr[ve[i]]);
			}
			else{
				newone.addNewMonomial(ve[i], arr[ve[i]]);
			}
		}

		while (ve.size() > 0){
			ve.pop_back();
		}
		for (int i = 0; i < newone.ve.size(); ++i){
			ve.push_back(newone.ve[i]);
			arr[ve[i]] = newone.arr[ve[i]];
		}
	}

	polynomial operator-(const polynomial& subtraction){
		bool final = 1;
		for (int i = 0; i < ve.size(); ++i){
			bool b = 0;
			for (int j = 0; j < subtraction.ve.size(); ++j){
				if (ve[i] == subtraction.ve[j]){
					if (arr[ve[i]] == subtraction.arr[subtraction.ve[j]]){
						b = 1;
					}
					else{
						break;
					}
				}
			}

			if (!b){
				final = 0;
				break;
			}
		}

		for (int j = 0; j < subtraction.ve.size(); ++j){
			bool b = 0;
			for (int i = 0; i < ve.size(); ++i){
				if (ve[i] == subtraction.ve[j]){
					if (arr[ve[i]] == subtraction.arr[subtraction.ve[j]]){
						b = 1;
					}
					else{
						break;
					}
				}
			}
			
			if (!b){
				final = 0;
				break;
			}
		}

		polynomial newone;

		if (final == 0){
			cout << "ERROR:They are not same" << endl;
			return newone;
		}

		for (int i = 0; i < subtraction.ve.size(); ++i){
			newone.addNewMonomial(subtraction.ve[i], arr[ve[i]] - subtraction.arr[subtraction.ve[i]]);
		}

		return newone;
	}

	void operator-=(const polynomial& subtraction){
		bool final = 1;
		for (int i = 0; i < ve.size(); ++i){
			bool b = 0;
			for (int j = 0; j < subtraction.ve.size(); ++j){
				if (ve[i] == subtraction.ve[j]){
					if (arr[ve[i]] == subtraction.arr[subtraction.ve[j]]){
						b = 1;
					}
					else{
						break;
					}
				}
			}

			if (!b){
				final = 0;
				break;
			}
		}

		for (int j = 0; j < subtraction.ve.size(); ++j){
			bool b = 0;
			for (int i = 0; i < ve.size(); ++i){
				if (ve[i] == subtraction.ve[j]){
					if (arr[ve[i]] == subtraction.arr[subtraction.ve[j]]){
						b = 1;
					}
					else{
						break;
					}
				}
			}
			
			if (!b){
				final = 0;
				break;
			}
		}

		polynomial newone;

		if (final == 0){
			cout << "ERROR:They are not same" << endl;
			return;
		}

		for (int i = 0; i < subtraction.ve.size(); ++i){
			newone.addNewMonomial(subtraction.ve[i], arr[ve[i]] - subtraction.arr[subtraction.ve[i]]);
		}

		while (ve.size() > 0){
			ve.pop_back();
		}
		for (int i = 0; i < newone.ve.size(); ++i){
			ve.push_back(newone.ve[i]);
			arr[ve[i]] = newone.arr[ve[i]];
		}
	}

	void operator++(){
		arr[0]++;
		ve.push_back(0);
	}

	void operator--(){
		arr[0]--;
		ve.push_back(0);
	}

	polynomial operator*(const polynomial& multiplication){
		polynomial newone;

		for (int i = 0; i < ve.size(); ++i){
			for (int j = 0; j < multiplication.ve.size(); ++j){
				newone.addNewMonomial(ve[i] * multiplication.ve[j], arr[ve[i]] * multiplication.arr[multiplication.ve[j]]);
			}
		}

		return newone;
	}

	polynomial operator*(int multiplication){
		polynomial newone;

		for (int i = 0; i < ve.size(); ++i){
			arr[ve[i]] *= multiplication;
		}
		for (int i = 0; i < ve.size(); ++i){
			newone.addNewMonomial(ve[i], arr[ve[i]]);
		}

		return newone;
	}

	void operator*=(int multiplication){
		polynomial newone;

		for (int i = 0; i < ve.size(); ++i){
			arr[ve[i]] *= multiplication;
		}
		for (int i = 0; i < ve.size(); ++i){
			newone.addNewMonomial(ve[i], arr[ve[i]]);
		}

		while (ve.size() > 0){
			ve.pop_back();
		}
		for (int i = 0; i < newone.ve.size(); ++i){
			ve.push_back(newone.ve[i]);
			arr[ve[i]] = newone.arr[ve[i]];
		}
	}

	void operator*=(const polynomial& multiplication){
		polynomial newone;

		for (int i = 0; i < ve.size(); ++i){
			for (int j = 0; j < multiplication.ve.size(); ++j){
				newone.addNewMonomial(ve[i] * multiplication.ve[j], arr[ve[i]] * multiplication.arr[multiplication.ve[j]]);
			}
		}

		while (ve.size() > 0){
			ve.pop_back();
		}
		for (int i = 0; i < newone.ve.size(); ++i){
			ve.push_back(newone.ve[i]);
			arr[ve[i]] = newone.arr[ve[i]];
		}
	}

	polynomial operator/(int division){
		polynomial newone;
		if (division == 0){
			cout << "division by zero";
			return newone;
		}
		for (int i = 0; i < ve.size(); ++i){
			arr[ve[i]] /= division;
		}

		for (int i = 0; i < ve.size(); ++i){
			newone.addNewMonomial(ve[i], arr[ve[i]]);
		}

		return newone;
	}

	void operator/=(int division){
		polynomial newone;
            if (division == 0){
			cout << "division by zero";
			return;
		}
		for (int i = 0; i < ve.size(); ++i){
			arr[ve[i]] /= division;
		}
	}

	friend ostream& operator<<(ostream &os, const polynomial& multiplication);

	friend istream& operator>>(istream &os,polynomial pol);

	int operator[](int y){
		for (int i = 0; i < ve.size(); ++i){
			if (ve[i] == y){
				return arr[ve[i]];
			}
		}
		cout << "ERROR: NOT FOUND";
		return -1;
	}

	~polynomial(){}
};

ostream& operator<<(ostream &os, const polynomial& multiplication ){ 
	string s = "";

	string q;
	for (int i = 0; i < multiplication.ve.size();++i){
	    q = "";
	    if (multiplication.arr[multiplication.ve[i]] > 0){
	    	if (i != 0){
	    		q = " + ";
	    	}
	    	if (abs(multiplication.arr[multiplication.ve[i]]) != 1 ){
	    		q += to_string((multiplication.arr[multiplication.ve[i]]));
	    		q += '*';
	    	}
	    	q += "x^";
	    	q+= to_string(multiplication.ve[i]);
	    }
	    else{
	    	q = " - ";
	    	if (abs(multiplication.arr[multiplication.ve[i]]) != 1){
	    		q += to_string((multiplication.arr[multiplication.ve[i]]));
	    		q += '*';
	    	}
	    	q += "x^";
	   		q+= to_string(multiplication.ve[i]);
	   	}
	   	os << q;
    }

	return os;
}


istream& operator>>(istream &os, polynomial pol){
	int n; 
    double x;
    int y;
    cout << "type the number of monomial";
    os >> n;

    for(int i = 0; i < n; ++i){
    	cout << (i + 1) << " pair" << endl;
    	os >> x >> y;
    	pol.addNewMonomial(x, y);
    }

    return os;
}

int main() {

	polynomial a;
	polynomial b;
	
	b.addNewMonomial(1, 1);
	b.addNewMonomial(-1, 2);

	b *= 3;

	b.show();
	// a.show();
	// b.show();
	// a.show();

	
    return 0;
}