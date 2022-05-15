#include <iostream>
#include <string>
#include <vector>
#include <iterator>

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

template <typename Q>
class MyIterator;


template<class T>
class CircularBuffer {
private:
    T* data_;
    int  size_;
    int freeSpace_;
    int usedSpace_;
    int startIndex_;
    int midpoint_;
    int endIndex_;
public:

    CircularBuffer(int val)
    {
        size_ = val;
        data_ = new T[size_];

        freeSpace_ = size_;
        usedSpace_ = 0;
        midpoint_ = (size_ / 2);
        startIndex_ = midpoint_ - 1;
        endIndex_ = midpoint_;
    }
 
    const T GetFreeSpace(){
        return size_ - usedSpace_; 
    }
 
    const T GetUsedSpace(){
        return usedSpace_; 
    }
    
    void AddBegin(T val){
        if (usedSpace_ == size_){
            cout << "ERROR: NOT ENOUGHT SPACE" << endl;
            return;
        }
        usedSpace_++;

        if (startIndex_ > 0){
            data_[startIndex_] = val;
            --startIndex_;
        }
        else{
            data_[startIndex_] = val;
            startIndex_ = size_ - 1;
        }

        if (startIndex_ == endIndex_){
            endIndex_--;
        }
    }

    void AddEnd(T val){
        if (usedSpace_ == size_){
            cout << "ERROR: NOT ENOUGHT SPACE" << endl;
            return;
        }
        usedSpace_++;

        if (endIndex_ < (size_ - 1)){
            data_[endIndex_] = val;
            ++endIndex_;
        }
        else{
            data_[endIndex_] = val;
            endIndex_ = 0;
        }
    } 


    void DelBegin(){
        if (usedSpace_ == 0){
            cout << "Buffer is empty";
        }
        else{
            --usedSpace_;
            
            //когда старт еще не добавлен => мы убираем из начала конца
            if (startIndex_ == size_ - 1){
                startIndex_ = 0;
            }
            else{
                startIndex_++;
            }
        }
    }

    void DelEnd(){
        if (usedSpace_ == 0){
            cout << "Buffer is empty";
        }
        else{

            --usedSpace_;
            
            //когда конца еще нет, выбираем из конца старта
            if (endIndex_ == 0){
                endIndex_ = size_ - 1;
            }
            else{
                endIndex_--;
            }
        }
    }

    T* GetIndex(int index){
        return &data_[index];
    }

    const int size(){
        return size_;
    }

    const MyIterator <T> begin(){
        MyIterator <T> I(&data_[startIndex_], this);
        return I;
    }

    const MyIterator <T> end(){
        MyIterator <T> I(&data_[endIndex_], this);
        return I;
    }

    const MyIterator <T> index(int index){
        MyIterator <T> I(&data_[index], this);
        return I;
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


template <typename Q>
class MyIterator: public iterator<
                        input_iterator_tag,   // iterator_category
                        long,                      // value_type
                        long,                      // difference_type
                        const long*,               // pointer
                        long                       // reference
                                      >
{
private:
    Q* current;
    CircularBuffer <Q>* buffer; 
public:

    MyIterator() : current(0){}

    MyIterator(Q* curr, CircularBuffer<Q>* buff) : current(curr), buffer(buff){}

    MyIterator(const MyIterator& other) : current(other.current){}

    ~MyIterator(){}

    MyIterator& operator=(const MyIterator& other){
        if (this != &other){
            current = other.current;
            buffer = other.buffer;
        }
        return *this;
    }

    MyIterator& operator++(){
        ++current;
        
        if (current == buffer->GetIndex(buffer->size())){
            current = buffer->GetIndex(0);
        }

        return *this;
    } 

    MyIterator& operator--(){
        --current;

        if (*current < 0){
            current = &buffer->GetIndex(buffer->size() - 1);
        }

        return *this;
    }

    MyIterator  operator++(int){
        MyIterator newone(*this);
        operator++();

        if (*current == buffer->GetIndex(-1)){
            current = &buffer->GetIndex(0);
            *current = 0;
        }

        return newone;
    }

    MyIterator  operator--(int){
        MyIterator newone(*this);
        operator--();

        if (*current < 0){
            current = &buffer->GetIndex(buffer->size() - 1);
        }

        return newone;
    }

    Q& operator*(){
        return *current;
    }

    Q* operator->(){
        return current;
    }

    bool operator==(const MyIterator& other){
        return current == other.current;
    }

    bool operator!=(const MyIterator& other){
        return !(*this == other);
    }

    bool operator<(const MyIterator& other){
        return (current < other.current);
    }

    bool operator<=(const MyIterator& other){
        return (current < other.current);
    }

    bool operator>(const MyIterator& other){
        return (current < other.current);
    }

    bool operator>=(const MyIterator& other){
        return (current < other.current);
    }
};

 
template <class G>
bool moreThanZero(G x){

    if (x > 0){
        return 1;
    }

    return 0;
}


template<class Iter, class Predicate>
bool All_of(Iter first, Iter last, Predicate pred)
{
    for (; first != last; ++first) {
        if (!pred(*first)) {
            return 0;
        }
    }
    return 1;
}

template<class Iter, class Predicate>
bool None_of(Iter first, Iter last, Predicate pred)
{
    return !All_of(first, last, pred);
}


template<class Iter, class Predicate>
bool One_of(Iter first, Iter last, Predicate pred)
{
    int b = 0;
    for (; first != last; ++first) {
        if (pred(*first)) {
            b += 1;
        }
        if (b > 1){
            return 0;
        }
    }
    if (b){
        return 1;
    }
    return 0;
}


template<class Iter>
bool IsSorted(Iter first, Iter last, bool reversed){

    if (reversed){
        for (; first != last; ++first) {
            Iter next = first;
            ++next;
            if (next > first) {
                return 0;
            }
        }
        return 1;
    }

    for (; first != last; ++first) {
        Iter next = first;
        ++next;
        if (next < first) {
            return 0;
        }
    }
    return 1;
    
}


template<class Iter, class Predicate>
bool Is_partitioned(Iter first, Iter last, Predicate pred)
{
    for (; first != last; ++first){
        if (!pred(*first)){
            break;
        }
    }

    for (; first != last; ++first){
        if (pred(*first)){
            return 0;
        }
    }

    return 1;
}

template<class Iter, class G>
G Find_not(Iter first, Iter last, G elem){

    for (; first != last; ++first) {
        if (*first != elem) {
            return *first;
        }
    }

    return 0;
}

template<class Iter, class G>
G Find_backward(Iter first, Iter last, G elem){

    for (; last != first; --first) {
        if (*first != elem) {
            return *first;
        }
    }

    return 0;
}

template<class Iter, class Predicate>
bool Is_palindrome(Iter first, Iter last, Predicate pred){
    Iter backward = last;

    for (; first != last; ++first){
        if (!pred(first, --backward)){
            return 0;
        }
    }

    return 1;
}


int main()
{

    CircularBuffer <int> c(10);
    vector <int> ve;
    ve.push_back(-1);
    ve.push_back(-1);

    for (int i = 9; i >= 0; --i){
        c.AddBegin(i);
    } 

    int a = 1;
    MyIterator<int> I(&a, &c); 


    // for (I = c.begin(); I != c.end(); ++I){
    //     cout << *I << " ";
    // }

    cout << IsSorted(c.begin(), c.end(), 0);

    // sort(c.begin(), c.end());


    // for (int i = 0; i < c.size(); ++i){
    //     cout << c.GetIndex(i) << " ";
    // }


}