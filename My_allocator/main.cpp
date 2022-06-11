#include <iostream>
#include <map>
#include <iostream>
#include <fstream>
#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>
#include  <stdexcept>
#include <limits>

#define SIZE 100000

using namespace std;

template <class T>
class dataForStorage{
private:
	char *begin_;
	vector <bool> used_;
	int usedsize_;
	int bites_;

public:
	dataForStorage(char *begin, int usedsize, int bites): begin_(begin), usedsize_(usedsize), bites_(bites){
		for (int i = 0; i < usedsize; ++i){
			used_.push_back(0);
		}
	}
	bool isFree(){
		bool found = 0;
		for (int i = 0;i < usedsize_; ++i){
			if (used_[i] == 0){
				used_[i] = 1;
				found = 1;
				break;
			}
		}
		return found;
	}

	char* firstFree(){
		int i = 0;
		for (i = 0;i < usedsize_; ++i){
			if (used_[i] == 0){
				used_[i] = 1;
				break;
			}
		}
		return (begin_+i*bites_);
	}

	bool isDeleted(char* cur){
		if (cur < begin_+usedsize_*bites_ && cur > begin_){
			used_[*cur/bites_] = 0;
			return 1;
		}
		return 0;
	}

	int maxSize() const{
		int count, i;
		for (i = 0;i < usedsize_; ++i){
			if (used_[i] == 0){
				count++;
			}
		} 

		return count * bites_;
	}

	~dataForStorage(){

	}
};

template <class T>
class MyAllocator{
private:
	map <int, dataForStorage<T> > mp_;
	char *arr;

public:
	//typedef T value_type;

	MyAllocator(){}

	MyAllocator(MyAllocator<T>& other){
		for (auto& i : other.mp_){
			mp_.insert(make_pair(other.mp_.first, other.mp_.second));
		}
	}

	MyAllocator(map <int, int> mp){	
		map<int, int>::iterator it;
		int size = 0;

	    for(it=mp.begin(); it!=mp.end(); ++it){
	    	size += (it->first * it->second);
	    }

	    arr = new char(size);
	    shared_ptr<char> arrPTR(arr);

	    int curSize = 0;

	    for(it=mp.begin(); it!=mp.end(); ++it){    	
	    	mp_.insert(make_pair(it->first, dataForStorage<int>(arr + curSize, it->second, it->first)));
	    	curSize += it->first * it->second;
	    }
	}

	MyAllocator(const MyAllocator<T> &other){

	}
	char* allocate(int neededSize){
		for (auto& i : mp_){
			if (neededSize * sizeof(T) < i.first){
				if (i.second.isFree()){
					return i.second.firstFree();
				}
			}
		}
		overflow_error("Not such size in array");
	}

	bool operator==(const MyAllocator<T> &other) const{
		return (arr == other.arr);
	}

	bool operator!=(const MyAllocator<T> &other) const{
		return (arr != other.arr);
	}

	void deallocate(char* toDel){
		for (auto& i : mp_){
			if (i.second.isDeleted(toDel)){
				return;
			}
		}
		runtime_error("Cant be deleted, since not object in array");
	}

	template <class U>
	void destroy(U* p){
		p->~U();;
	}

	template <class U, class... Args>
	void construct(U* p, Args&& ... args){ ::new ((void*)p) U (forward<Args>(args)...);}

	int max_size() const{
		return mp_.rbegin()->second.maxSize() / sizeof(T);
	}

	template <class U>
	struct rebind
	{
		typedef MyAllocator<U> other;
	};

	~MyAllocator(){}
};


int main(){

	ifstream fin("input.txt");

	map <int, int > mp;
	int n, m, quantity;

	fin >> n;
	for (int i = 0; i < n; ++i){
		fin >> m >> quantity;

		mp.insert(make_pair(m, quantity));
	}

	MyAllocator<int> all(mp);
	MyAllocator<int> another(mp);

	//cout << (all == another);
	cout << all.max_size();
	int ex = 3;

	char* a = all.allocate(3);

	all.deallocate(a);

	return 0;
}
