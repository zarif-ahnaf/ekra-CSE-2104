#include <bits/stdc++.h>
using namespace std;

class root {
protected:
    int a, b, c;

public:
    root(int num1, int num2, int num3) {
        a = num1;
        b = num2;
        c = num3;
    }

    void display() {
        cout << "Value of a: " << a << endl;
        cout << "Value of b: " << b << endl;
        cout << "Value of c: " << c << endl;
    }
};

class calculation : public root {
public:
    float D;

    calculation(int a, int b, int c) : root(a, b, c) {
    }

    void D_calculation() {
        D = pow(b, 2) - (4 * a * c);
    }
};

class decision : public calculation {
public:
    decision(int a, int b, int c) : calculation(a, b, c) {
    }

    void root_decision() {
        if (D >= 0) {
            cout << "real Number" << endl;
        } else {
            cout << "Complex number" << endl;
        }
    }
};

class root_calculation : public decision {
public:
    root_calculation(int a, int b, int c) : decision(a, b, c) {
    }

    void calculation_root() {
        // Note: The formula in the image is (-b +/- sqrt(D)) / 2 * a
        // Due to operator precedence, this calculates as ((-b +/- sqrt(D)) / 2) * a
        int x1 = (-b + sqrt(D)) / 2 * a;
        int x2 = (-b - sqrt(D)) / 2 * a;
        
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
};

int main() {
    root_calculation obj(2, 5, 3);
    obj.display();
    obj.D_calculation();
    obj.root_decision();
    obj.calculation_root();

    return 0;
}
