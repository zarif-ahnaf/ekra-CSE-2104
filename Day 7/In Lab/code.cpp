#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int score = 0, life = 3;

class Point {
    int x, y;
public:
    Point() {
        x = 0;
        y = 0;
    }

    Point(int a, int b) {
        x = a;
        y = b;
    }

    // Overloading + operator
    Point operator+(Point p) {
        Point t;
        t.x = x + p.x;
        t.y = y + p.y;
        return t;
    }

    // Overloading == operator to return a direction/relationship code
    int operator==(Point p) {
        if (x == p.x && y == p.y)
            return 1;
        else if (p.x > x && p.y > y)
            return 2;
        else if (p.x > x && p.y < y)
            return 3;
        else if (p.x < x && p.y < y)
            return 4;
        else if (p.x < x && p.y > y)
            return 5;
        
        return 0;
    }

    void show() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

class Snake {
    Point P, Q, R;
public:
    void move(Point p) {
        P = p;
    }

    void move(Point p, Point q) {
        P = p;
        Q = q;
    }

    void play() {
        P = Point(rand() % 2, rand() % 2);
        
        while (life > 0) {
            Q = Point(rand() % 2, rand() % 2);
            
            cout << "\nP = ";
            P.show();
            cout << "Q = ";
            Q.show();

            int a = (P == Q); // Calls overloaded == operator

            if (a == 1) {
                life--;
                cout << "Life = " << life << endl;
            }
            else if (a == 2) {
                score++;
                cout << "Up-Up" << endl;
                R = P + Q;
                cout << "R = ";
                R.show();
                move(Q);
            }
            else if (a == 3) {
                score++;
                cout << "Up-Down" << endl;
                move(P, Q);
            }
            else if (a == 4) {
                score++;
                cout << "Down-Down" << endl;
                move(Q);
            }
            else if (a == 5) {
                score++;
                cout << "Down-Up" << endl;
                move(P, Q);
            }
            
            cout << "Score = " << score << endl;
        }
    }
};

int main() {
    srand(time(0));
    Snake s;
    s.play();
    
    cout << "\nGame Over!" << endl;
    cout << "Total Score = " << score << endl;
    
    return 0;
}
