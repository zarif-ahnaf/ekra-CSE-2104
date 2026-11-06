#include <iostream>
using namespace std;

class employee {
private:
    string CEO;
    string team_manager;
    string programmer;

    int CEO_salary;
    int team_manager_salary;
    int programmer_salary;

    static int CEO_total_salary;
    static int team_manager_total_salary;
    static int programmer_total_salary;

public:
    // Constructor
    employee(string c, string Tm, string p) {
        CEO = c;
        team_manager = Tm;
        programmer = p;

        CEO_salary = 10000;
        team_manager_salary = 6000;
        programmer_salary = 5000;

        // Calculating total salaries based on counts (1 CEO, 3 Managers, 7 Programmers)
        CEO_total_salary = 1 * CEO_salary;
        team_manager_total_salary = 3 * team_manager_salary;
        programmer_total_salary = 7 * programmer_salary;
    }

    // Destructor
    ~employee() {
        cout << "CEO Total salary: " << CEO_total_salary << endl;
        cout << "Team manager total salary: " << team_manager_total_salary << endl;
        cout << "Programmer total salary: " << programmer_total_salary << endl;

        if (CEO_total_salary > team_manager_total_salary && team_manager_total_salary > programmer_total_salary) {
            cout << "CEO salary are highest" << endl;
        }
        else if (team_manager_total_salary > CEO_total_salary && team_manager_total_salary > programmer_total_salary) {
            cout << "Team manger total salary are highest" << endl;
        }
        else {
            cout << "Programmer total salary are highest" << endl;
        }
    }
};

// Initializing static variables
int employee::CEO_total_salary = 0;
int employee::team_manager_total_salary = 0;
int employee::programmer_total_salary = 0;

int main() {
    // Creating object. When main ends, the destructor ~employee() is called automatically.
    employee e1("CEO", "Team manager", "Programmer");
    
    return 0;
}
