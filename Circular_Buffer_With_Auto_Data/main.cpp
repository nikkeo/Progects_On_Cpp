#include <iostream>
#include <string>
#include <algorithm> 


using namespace std;


class dot{
private:
    double a_;
    double b_;
public:
    dot() {}

    void AddNum(double a, double b){
        a_ = a;
        b_ = b;
    }

    double GetNumX(){
        return a_;
    }

    double GetNumY(){
        return b_;
    }

    void show(){
        cout << a_ << " " << b_ << endl;
    }

    ~dot(){}
};



template<class T>
class CircularBuffer {
private:

    T* data_;
    int  size_;
    int freeSpace_;
    int usedSpace_;
public:
    CircularBuffer(int val)
    {
        size_ = val;
        data_ = new T[size_];

        freeSpace_ = size_;
        usedSpace_ = 0;
    }
 
    const int GetFreeSpace(){
        return size_ - usedSpace_; 
    }
 
    int GetUsedSpace(){
        return usedSpace_; 
    }
    
    void AddBegin(T val){
        for (int i = usedSpace_; i >= 0; --i){
            data_[i + 1] = data_[i];
        }
        data_[0] = val;
        usedSpace_++;
    }

    void AddEnd(T val){
        data_[usedSpace_++ % size_] = val; 
    } 
    
    const T* begin(){
        return &data_[0];
    }

    const T* end(){
        return &data_[usedSpace_];
    }

    const T* index(int index){
        return &data_[index];
    }

    T GetBegin(){
        if (usedSpace_ == 0){
            cout << "Buffer is empty";
        }
        else{
            --usedSpace_;
            return data_[-1]; 
        }
        return 0;
    }

    T GetEnd(){
        if (usedSpace_ == 0){
            cout << "Buffer is empty";
        }
        else{
            T res = data_[0]; 

            for (int i = 1; i < usedSpace_; ++i)
                data_[i - 1] = data_[i];

            --usedSpace_;
            return res; 
        }
        return 0;
    }

    const T GetIndex(int index){
        return data_[index];
    }

    const int sizeIS(){
        return size_;
    }

    const int size(){
        return usedSpace_;
    }

    void resize(int NewSize){
        T *newOne = new T[NewSize];
        memcpy(newOne, data_, NewSize * sizeof(T));

        size_ = NewSize;
        delete[] data_;
        data_ = newOne;
    }

     
    ~CircularBuffer(){ 
        delete[] data_; 
    }
};
 


template <class G>
bool moreThanZero(G x){

    if (x > 0){
        return 1;
    }

    return 0;
}


template <class G>
const bool all_of(CircularBuffer <G> &newone){

    bool b = 1;

    for (int i = 0; i < newone.size(); ++i){
        if (!moreThanZero(newone.GetIndex(i))){
            b = 0;
            break;
        }
    }

    if (b){
        return 1;
    }
    else{
        return 0;
    }
}


template <class G>
const bool any_of(CircularBuffer <G> &newone){

    bool b = 0;

    for (int i = 0; i < newone.size(); ++i){
        if (moreThanZero(newone.GetIndex(i))){
            b = 1;
            break;
        }
    }

    if (b){
        return 1;
    }
    else{
        return 0;
    }
}


template <class G>
const bool none_of(CircularBuffer <G> &newone){

    bool b = 1;

    for (int i = 0; i < newone.size(); ++i){
        if (moreThanZero(newone.GetIndex(i))){
            b = 0;
            break;
        }
    }

    if (b){
        return 1;
    }
    else{
        return 0;
    }
}


template <class G>
const bool one_of(CircularBuffer <G> &newone){

    int b = 0;

    for (int i = 0; i < newone.size(); ++i){
        if (moreThanZero(newone.GetIndex(i))){
            b++;
            if (b > 1){
                break;
            }
        }
    }

    if (b == 1){
        return 1;
    }
    else{
        return 0;
    }
}


template <class G>
const bool isSorted(CircularBuffer <G> &newone, bool reversed){
    bool b = 1;

    if (reversed){
        for (int i = 1; i < newone.size(); ++i){
            if (newone.GetIndex(i - 1) < newone.GetIndex(i)){
                b = 0;
                break;
            }
        }
    }
    else{
        for (int i = 1; i < newone.size(); ++i){
            if (newone.GetIndex(i - 1) > newone.GetIndex(i)){
                b = 0;
                break;
            }
        }
    }

    if (b){
        return 1;
    }
    else{
        return 0;
    }
}


template <class G>
const bool is_partitioned(CircularBuffer <G> &newone){
    int b = 0;
    bool previous = moreThanZero(newone.GetIndex(0));

    for (int i = 1; i < newone.size(); ++i){
        if (moreThanZero(newone.GetIndex(i)) != previous){
            b++;
            if (b > 1){
                break;
            }
        }
        previous = moreThanZero(newone.GetIndex(i));
    }

    if (b == 1){
        return 1;
    }
    else{
        return 0;
    }
}

template <class G>
const G* find_not(CircularBuffer <G> &newone, G given){
    for (int i = 0; i < newone.size(); ++i){
        if (newone.GetIndex(i) != given){
            return newone.index(i);
        }
    }

    cout << "NOT FOUND, ALL IS LIKE GIVEN";
    return 0;
}

template <class G>
const G* find_backward(CircularBuffer <G> &newone, G given){
    for (int i = newone.size() - 1; i >= 0; --i){
        if (newone.GetIndex(i) == given){
            return newone.index(i);
        }
    }

    cout << "NOT EXISTS" << endl;
    return 0;
}



int main(int argc, char **argv)
{

    CircularBuffer <int> c(10);

    c.resize(13);

    for (int i = 0; i < 13; ++i){
        c.AddBegin(i);
    }   

    cout << *find_backward(c, 12);

    // sort(c.begin(), c.end());

    // for (int i = 0; i < c.size(); ++i){
    //     cout << c.GetIndex(i) << " ";
    // }
    return 0;
}
 

