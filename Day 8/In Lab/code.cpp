#include <iostream>
#include <string>
using namespace std;

class Payment {
protected:
    string name, mobile_no, address, confirmation;
    double amount;

public:
    Payment(string n, string m, string add, double amt) {
        name = n;
        mobile_no = m;
        address = add;
        amount = amt;
        confirmation = "No";
    }

    void showInfo() {
        cout << "Name: " << name << endl;
        cout << "Mobile Number: " << mobile_no << endl;
        cout << "Address: " << address << endl;
        if (confirmation == "Yes")
            cout << "Total Amount: " << amount << endl;
        else
            cout << "Invalid Payment Method" << endl;
    }

    virtual void processPayment() = 0;
};

class CashonDelivery : public Payment {
public:
    CashonDelivery(string n, string m, string add, double amt)
        : Payment(n, m, add, amt) {}

    void processPayment() {
        double charge;
        if (address == "Dhaka")
            charge = 80;
        else
            charge = 150;
        
        confirmation = "Yes";
        cout << "Delivery charge: " << charge << endl;
        cout << "Pay method: Cash on Delivery" << endl;
        cout << "Final Total: " << amount + charge << endl;
    }
};

class MobileBanking : public Payment {
    string provider;
public:
    MobileBanking(string n, string m, string add, double amt, string pvdr)
        : Payment(n, m, add, amt) {
        provider = pvdr;
    }

    void processPayment() {
        double fee = 0;
        if (provider == "bkash")
            fee = 20;
        else if (provider == "rocket")
            fee = 15;
        else if (provider == "nagad")
            fee = 12;
        
        confirmation = "Yes";
        cout << "Pay method: " << provider << endl;
        cout << "Fee: " << fee << endl;
        cout << "Final Total: " << amount + fee << endl;
    }
};

class CardPayment : public Payment {
public:
    CardPayment(string n, string m, string add, double amt)
        : Payment(n, m, add, amt) {}

    void processPayment() {
        double discount = (amount / 100) * 10;
        confirmation = "Yes";
        cout << "Pay method: Card Pay" << endl;
        cout << "Discount: " << discount << endl;
        cout << "Final Total: " << amount - discount << endl;
    }
};

int main() {
    Payment *p;

    CashonDelivery a("Shamtha", "01711111111", "Natore", 1000);
    MobileBanking b("Saima", "01855555555", "Rangpur", 3000, "bkash");
    CardPayment c("Sajada", "01987654367", "Dhaka", 5000);

    p = &a;
    p->processPayment();
    p->showInfo();
    
    cout << endl;

    p = &b;
    p->processPayment();
    p->showInfo();

    cout << endl;

    p = &c;
    p->processPayment();
    p->showInfo();

    return 0;
}
