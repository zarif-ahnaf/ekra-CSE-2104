#include <iostream>
#include <string>
using namespace std;

// Base Class
class shape {
protected:
    double side1, side2, side3;

public:
    shape(double x, double y, double z) {
        side1 = x;
        side2 = y;
        side3 = z;
    }

    void display() {
        cout << "side1 is: " << side1 << endl;
        cout << "side2 is: " << side2 << endl;
        cout << "side3 is: " << side3 << endl;
    }
};

// Derived Class for Volume
class volume : public shape {
protected:
    string shapeType;
    double Volume;

public:
    volume(string w, double x, double y, double z) : shape(x, y, z) {
        shapeType = w;
    }

    void CubeVolume() {
        Volume = side1 * side1 * side1;
    }

    void cylinderVolume() {
        Volume = 3.1416 * side1 * side1 * side2;
    }

    void boxVolume() {
        Volume = side1 * side2 * side3;
    }

    void displayVolume() {
        cout << "The Shape is: " << shapeType << endl;
        cout << "Volume = " << Volume << endl;
    }
};

// Derived Class for Area
class Area : public shape {
protected:
    double area;
    string shapeType;

public:
    Area(string w, double x, double y, double z) : shape(x, y, z) {
        shapeType = w;
    }

    void CubeArea() {
        area = 6 * side1 * side1;
    }

    void cylinderArea() {
        area = 2 * 3.1416 * side1 * (side1 + side2);
    }

    void boxArea() {
        area = 2 * ((side1 * side2) + (side2 * side3) + (side3 * side1));
    }

    void displayArea() {
        cout << "Area = " << area << endl;
    }
};

int main() {
    // 1. Cube Calculations
    volume volume1("Cube", 12, 0, 0);
    volume1.display();
    volume1.CubeVolume();
    volume1.displayVolume();
    
    Area area1("Cube", 12, 0, 0);
    area1.CubeArea();
    area1.displayArea();
    
    cout << endl; // Separator for clarity

    // 2. Cylinder Calculations
    volume volume2("Cylinder", 12, 25, 0);
    volume2.display();
    volume2.cylinderVolume();
    volume2.displayVolume();

    Area area2("Cylinder", 12, 25, 0);
    area2.cylinderArea();
    area2.displayArea();

    cout << endl;

    // 3. Box Calculations
    volume volume3("Box", 10, 20, 30);
    volume3.display();
    volume3.boxVolume();
    volume3.displayVolume();

    Area area3("Box", 10, 20, 30);
    area3.boxArea();
    area3.displayArea();

    return 0;
}
