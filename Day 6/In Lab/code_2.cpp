#include <iostream>
using namespace std;

// Reconstructed Base Class A
class A {
protected:
    int x;
public:
    A() : x(0) {}
    A(int a) {
        x = a;
    }
};

// Reconstructed Class B (Virtual Inheritance usually applies to both paths)
class B : virtual public A {
public:
    B(int a) : A(a) {}
};

// From Image 3
class C : virtual public A {
protected:
    int y;
public:
    C(int b) {
        y = b;
    }
};

// From Image 3
class D : public B, public C {
public:
    D(int a, int b) : B(a), C(b), A(a) { // A(a) is needed because A is virtual
    }

    void display() {
        // This function name appears in main() but definition is missing in image. 
        // Assuming it displays x and y.
        cout << "x: " << x << ", y: " << y << endl;
    }

    void add() {
        cout << "Summation of two numbers: " << x + y << endl;
    }
};

int main() {
    D obj(2, 4);
    obj.display();
    obj.add();
    return 0;
}
