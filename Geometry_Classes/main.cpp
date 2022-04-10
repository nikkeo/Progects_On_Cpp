#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class dot{
private:
    double a_;
    double b_;

public:

    dot(double a, double b) : a_(a), b_(b) {}

    void assignment(double a, double b){
        this->a_ = a;
        this->b_ = b;
    }

    void assignmentA(double a){
        this->a_ = a;
    }

    void assignmentB (double b){
        this->b_ = b;
    }

    void copyA(){
        this->a_ = b_;
    }

    void copyB(){
        this->b_ = a_;
    }

    double getA(){
        return this->a_;
    }

    double getB(){
        return this->b_;
    }

    void display(){
        cout << a_ << " " << b_;
    }

    void operator= (dot d){
        this->a_ = d.a_;
        this->b_ = d.b_;
    }

    dot operator+ (const dot b){
        dot c(this->a_ + b.a_, this->b_ + b.b_);
        return c;
    }

    void operator+= (dot b){
        this->a_ += b.a_;
        this->b_ += b.b_;
    }

    dot operator- (const dot b){
        dot c(this->a_ - b.a_, this->b_ - b.b_);
        return c;
    }

    void operator-= (dot b){
        this->a_ -= b.a_;
        this->b_ -= b.b_;
    }

    bool operator== (const dot b){
        return this->a_ == b.a_ && this->b_ == b.b_;
    }

    bool operator!= (const dot b){
        return !(this->a_ == b.a_ && this->b_ == b.b_);
    }

    dot operator* (const double c){
        dot d(this->a_ * c, this->b_ * c);

        return d;
    }

    void operator*= (double c){
        this->a_ *= c;
        this->b_ *= c;
    }

    dot operator/ (const double c){
        if (c != 0){
            dot d(this->a_ / c, this->b_ / c);
            return d;
        }
        else{
            return *this;
        }
    }

    void operator/= (double c){
        if (c != 0){
            this->a_ /= c;
            this->b_ /= c;
        }
    }

    ~dot(){}
};

ostream& operator<<(ostream &os, dot d) {
    return os  << d.getA() << " " << d.getB();
}

istream& operator>> (istream &os, dot& d){
    double a, b;
    os >> a;
    os >> b;
    d.assignment(a, b);

    return os;
}



class polyline{
protected:
    vector <dot> ve_;
public:

    polyline(const vector <dot>& ve){
        ve_ = ve;
    }
    
    void ADDnewDot(double a, double b){
        dot d(a, b);
        this->ve_.push_back(d);
    }

    void copy(int whatElemToChange){
        this->ve_.push_back(this->ve_[whatElemToChange]);
    }

    void reassignment(double a, double b, int whatElemToChange){
        dot d(a, b);
        this->ve_[whatElemToChange] = d;
    }

    void display(){
        for (int i = 0; i < this->ve_.size();++i){
            this->ve_[i].display();
            cout << endl;
        }
    }

    dot show(int c){
        return this->ve_[c];
    }

    void Length(){
        double sumOfLength;
        double x, y;
        for (int i = 0; i < (this->ve_.size() - 1);++i){
            x = (this->ve_[i].getA() - this->ve_[i + 1].getA()) * (this->ve_[i].getA() - this->ve_[i + 1].getA());
            y = (this->ve_[i].getB() - this->ve_[i + 1].getB()) * (this->ve_[i].getB() - this->ve_[i + 1].getB());
            sumOfLength += sqrt(x + y);
        }

        cout << sumOfLength << endl;
    }
    ~polyline(){}
};



class closed_polyline : public polyline
{
public:
    closed_polyline (const vector <dot> ve) : polyline(ve){}

    bool isItClosed(){
        return this->ve_[0] == this->ve_[this->ve_.size()-1];
    }

    void display(){
        if (!isItClosed()){
            cout << "ERROR: This polyline is not closed" << endl;
            return;
        }
        for (int i = 0; i < this->ve_.size();++i){
                this->ve_[i].display();
                cout << endl;
        }
    }

    dot show(int c){
        if (!isItClosed()){
            cout << "ERROR: This polyline is not closed" << endl;
            dot d(0, 0);
            return d;
        }
        return this->ve_[c];
    }

    void Length(){
        if (!isItClosed()){
            cout << "ERROR: This polyline is not closed" << endl;
            return;
        }
        double sumOfLength;
        double x, y;
        for (int i = 0; i < (this->ve_.size() - 1);++i){
            x = (this->ve_[i].getA() - this->ve_[i + 1].getA()) * (this->ve_[i].getA() - this->ve_[i + 1].getA());
            y = (this->ve_[i].getB() - this->ve_[i + 1].getB()) * (this->ve_[i].getB() - this->ve_[i + 1].getB());
            sumOfLength += sqrt(x + y);
        }

        cout << sumOfLength << endl;
    }

    ~closed_polyline(){}
};



class polyhedron : public closed_polyline{
public:
    polyhedron(const vector <dot>& ve) : closed_polyline(ve){}
    
    bool ifItConvexed(){
        double x, y, x1, y1;
        bool b = 1;

        for (int i = 1; i < (this->ve_.size() - 1); ++i){
            x = (this->ve_[i - 1].getA() - this->ve_[i].getA()) * (this->ve_[i - 1].getA() - this->ve_[i].getA());
            y = (this->ve_[i - 1].getB() - this->ve_[i].getB()) * (this->ve_[i - 1].getB() - this->ve_[i].getB());
            x1 = (this->ve_[i].getA() - this->ve_[i + 1].getA()) * (this->ve_[i].getA() - this->ve_[i + 1].getA());
            y1 = (this->ve_[i].getB() - this->ve_[i + 1].getB()) * (this->ve_[i].getB() - this->ve_[i + 1].getB());
            if ((x * y1 - x1 * y) <= 0){
                b = 0;
                break;
            }
        }

        return b;
    }

    void perimeter(){

        if (!ifItConvexed()){
            cout << "ERROR: polyhedron if not Convexed";
            return;
        }
        double sumOfPerimeter = 0;
        double x, y;
        for (int i = 0; i < (this->ve_.size() - 1);++i){
            x = (this->ve_[i].getA() - this->ve_[i + 1].getA()) * (this->ve_[i].getA() - this->ve_[i + 1].getA());
            y = (this->ve_[i].getB() - this->ve_[i + 1].getB()) * (this->ve_[i].getB() - this->ve_[i + 1].getB());
            sumOfPerimeter += sqrt(x + y);
        }

        cout << sumOfPerimeter << endl;
    }

    void aria(){

        if (!ifItConvexed()){
            cout << "ERROR: polyhedron if not Convexed";
            return;
        }
        double sumOfAria = 0;
        double x, y;
        for (int i = 0; i < (this->ve_.size()); ++i){
            if (i != (this->ve_.size() - 1)){
                sumOfAria += abs(this->ve_[i].getA() * this->ve_[i + 1].getB() - this->ve_[i].getB() * this->ve_[i + 1].getA());
            }
            else{
                sumOfAria += abs(this->ve_[i].getA() * this->ve_[0].getB() - this->ve_[i].getB() * this->ve_[0].getA());
            }
        }

        cout << sumOfAria * 0.5 << endl;
    }


    ~polyhedron(){}
};



class triangle : public polyhedron
{
public:
    triangle (const vector <dot> ve) : polyhedron(ve){}

    bool isItTriangle(){
        if (this->ve_.size() != 3){
            return 0;
        }
        int a, b, c;
        a = sqrt(sqrt(this->ve_[0].getA() - this->ve_[1].getA()) + sqrt(this->ve_[0].getB() - this->ve_[1].getB()));
        b = sqrt(sqrt(this->ve_[1].getA() - this->ve_[2].getA()) + sqrt(this->ve_[1].getB() - this->ve_[2].getB()));
        c = sqrt(sqrt(this->ve_[2].getA() - this->ve_[2].getA()) + sqrt(this->ve_[2].getB() - this->ve_[3].getB()));

        if ((a <= abs(b - c)) || (a >= (b + c))){
            return 0;
        }

        return 1;
    }

    void display(){
        if (!isItTriangle()){
            cout << "ERROR: This is not triangle" << endl;
            return;
        }
        for (int i = 0; i < this->ve_.size();++i){
                this->ve_[i].display();
                cout << endl;
        }
    }

    dot show(int c){
        if (!isItTriangle()){
            cout << "ERROR: This is not triangle" << endl;
            dot d(0, 0);
            return d;
        }
        return this->ve_[c];
    }

    void perimeter(){

        if (!isItTriangle()){
            cout << "ERROR: This is not triangle" << endl;
            return;
        }

        double x, y, z;
        x = sqrt((this->ve_[1].getA() - this->ve_[0].getA()) * (this->ve_[1].getA() - this->ve_[0].getA()) + (this->ve_[1].getB() - this->ve_[0].getB()) * (this->ve_[1].getB() - this->ve_[0].getB()));
        y = sqrt((this->ve_[2].getA() - this->ve_[1].getA()) * (this->ve_[2].getA() - this->ve_[1].getA()) + (this->ve_[2].getB() - this->ve_[1].getB()) * (this->ve_[2].getB() - this->ve_[1].getB()));
        z = sqrt((this->ve_[2].getA() - this->ve_[0].getA()) * (this->ve_[2].getA() - this->ve_[0].getA()) + (this->ve_[2].getB() - this->ve_[0].getB()) * (this->ve_[2].getB() - this->ve_[0].getB()));
        cout << x + y + z << endl;
    }

    void aria(){

        if (!isItTriangle()){
            cout << "ERROR: This is not triangle" << endl;
        }
        double sumOfAria = (this->ve_[1].getA() - this->ve_[0].getA()) * (this->ve_[2].getB() - this->ve_[0].getB()) - (this->ve_[2].getA() - this->ve_[0].getA()) * (this->ve_[1].getB() - this->ve_[0].getB());
        

        cout << abs(sumOfAria * 0.5) << endl;
    }

    ~triangle(){}
};



class trapezoid : public polyhedron
{
public:
    trapezoid(const vector <dot>& ve) : polyhedron(ve){}
    
    bool isItTrapezoid(){
        if (this->ve_.size() != 4){
            return 0;
        }
        int a, b, c, d;
        a = this->ve_[0].getB() - this->ve_[1].getB();
        b = this->ve_[2].getB() - this->ve_[3].getB();
        c = this->ve_[0].getA() - this->ve_[1].getA();
        d = this->ve_[2].getA() - this->ve_[3].getA();

        if ((a == 0 && b == 0) || (c == 0 && d == 0)){
            return 1;
        }

        return 0;
    }


    void display(){
        if (!isItTrapezoid()){
            cout << "ERROR: This is not Trapezoid" << endl;
            return;
        }
        for (int i = 0; i < this->ve_.size();++i){
                this->ve_[i].display();
                cout << endl;
        }
    }

    dot show(int c){
        if (!isItTrapezoid()){
            cout << "ERROR: This is not Trapezoid" << endl;
            dot d(0, 0);
            return d;
        }
        return this->ve_[c];
    }

    void perimeter(){
        
        if (!isItTrapezoid()){
            cout << "ERROR: This is not Trapezoid" << endl;
            return;
        }

        double x, y, z, m;
        x = sqrt((this->ve_[2].getA() - this->ve_[1].getA()) * (this->ve_[2].getA() - this->ve_[1].getA()) + (this->ve_[2].getB() - this->ve_[1].getB()) * (this->ve_[2].getB() - this->ve_[1].getB()));
        y = sqrt((this->ve_[3].getA() - this->ve_[2].getA()) * (this->ve_[3].getA() - this->ve_[2].getA()) + (this->ve_[3].getB() - this->ve_[2].getB()) * (this->ve_[3].getB() - this->ve_[2].getB()));
        z = sqrt((this->ve_[3].getA() - this->ve_[4].getA()) * (this->ve_[3].getA() - this->ve_[4].getA()) + (this->ve_[3].getB() - this->ve_[4].getB()) * (this->ve_[3].getB() - this->ve_[4].getB()));
        m = sqrt((this->ve_[4].getA() - this->ve_[1].getA()) * (this->ve_[4].getA() - this->ve_[1].getA()) + (this->ve_[4].getB() - this->ve_[1].getB()) * (this->ve_[4].getB() - this->ve_[1].getB()));

        cout << x + y + z + m << endl;
    }

    ~trapezoid(){}
};



class equilateral_polyhedron : public polyhedron{
public:
    equilateral_polyhedron(const vector <dot>& ve) : polyhedron(ve){}

    bool isItEquil(){
        double x, y, x1, y1;
        bool b = 1;
        double qx = 0, qy = 0;

        for (int i = 1; i < (this->ve_.size() - 1); ++i){

            x = (this->ve_[i - 1].getA() - this->ve_[i].getA()) * (this->ve_[i - 1].getA() - this->ve_[i].getA());
            y = (this->ve_[i - 1].getB() - this->ve_[i].getB()) * (this->ve_[i - 1].getB() - this->ve_[i].getB());
            x1 = (this->ve_[i].getA() - this->ve_[i + 1].getA()) * (this->ve_[i].getA() - this->ve_[i + 1].getA());
            y1 = (this->ve_[i].getB() - this->ve_[i + 1].getB()) * (this->ve_[i].getB() - this->ve_[i + 1].getB());
            if ((x * y1 - x1 * y) <= 0){
                b = 0;
                break;
            }
            if (qx == 0 && qy == 0){
                qx = x;
                qy = y; 
            }
            if (qx != x || qx != x1){
                b = 0;
                break;
            }
            if (qy != y || qy != y1){
                b = 0;
                break;
            }
        }

        return b;
    }

    void perimeter(){

        if (!isItEquil()){
            cout << "ERROR: polyhedron if not equilateral";
            return;
        }
        double sumOfPerimeter = 0;
        double x, y;
        for (int i = 0; i < (this->ve_.size() - 1);++i){
            x = (this->ve_[i].getA() - this->ve_[i + 1].getA()) * (this->ve_[i].getA() - this->ve_[i + 1].getA());
            y = (this->ve_[i].getB() - this->ve_[i + 1].getB()) * (this->ve_[i].getB() - this->ve_[i + 1].getB());
            sumOfPerimeter += sqrt(x + y);
        }

        cout << sumOfPerimeter << endl;
    }

    void aria(){

        if (!isItEquil()){
            cout << "ERROR: polyhedron if not equilateral";
            return;
        }
        double sumOfAria = 0;
        double x, y;
        for (int i = 0; i < (this->ve_.size()); ++i){
            if (i != (this->ve_.size() - 1)){
                sumOfAria += abs(this->ve_[i].getA() * this->ve_[i + 1].getB() - this->ve_[i].getB() * this->ve_[i + 1].getA());
            }
            else{
                sumOfAria += abs(this->ve_[i].getA() * this->ve_[0].getB() - this->ve_[i].getB() * this->ve_[0].getA());
            }
        }

        cout << sumOfAria * 0.5 << endl;
    }
    ~equilateral_polyhedron(){}
};



int main() {

    dot d(1, 2);

    dot dop(3, 10);
    

    vector <dot> ve;
    ve.push_back(d);
    ve.push_back(dop);

    closed_polyline pol(ve);

    pol.display();
    //d.display();
    // vector <dot> ve;
    // dot d(1, 1);
    // ve.push_back(d);

    // triangle po(ve);

    // po.ADDnewDot(2, 3);
    // po.ADDnewDot(7, 1);

    // po.display();

    // po.perimeter();
    // po.aria();

    return 0;
}