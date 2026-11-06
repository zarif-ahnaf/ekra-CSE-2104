#include <iostream>
#include <string>
using namespace std;

class Daraz {
public:
    string phoneNo;
    string uname;
    string pass;
    string mail;
    double coins;
    double product_Price;
    double disc_Amount;
    double final_price;
    double voucher_Discount;
    double delFee;
    double servFee;

    void userInfo() {
        cout << "Enter Mobile Number: ";
        cin >> phoneNo;
        cout << "Enter User Name: ";
        cin >> uname;
        cout << "Enter Password: ";
        cin >> pass;
        cout << "Enter Email: ";
        cin >> mail;
        cout << "Enter Product Price: ";
        cin >> product_Price;
        cout << "Enter Voucher Price: ";
        cin >> voucher_Discount;
        cout << "Enter Delivery Charge: ";
        cin >> delFee;
        cout << "Enter Service Charge: ";
        cin >> servFee;
        coins = 20000;
    }

    void calcDiscount() {
        disc_Amount = (product_Price * 4.0) / 100.0;
    }

    double calculate_Coin_Discount() {
        double coinVal = coins / 100.0;
        double maxAllowed = (product_Price * 4.0) / 100.0;
        if (coinVal < maxAllowed) {
            return coinVal;
        } else {
            return maxAllowed;
        }
    }

    void payCOD() {
        double coinValue = calculate_Coin_Discount();
        final_price = product_Price - coinValue - voucher_Discount + delFee + servFee;
        cout << "\nCash on Delivery Details " << endl;
        cout << "Product Price : " << product_Price << " Tk" << endl;
        cout << "Coin Price : " << coinValue << " Tk" << endl;
        cout << "Voucher : " << voucher_Discount << " Tk" << endl;
        cout << "Delivery Charge : " << delFee << " Tk" << endl;
        cout << "Service Charge : " << servFee << " Tk" << endl;
        cout << "Total Payable Amount : " << final_price << " Tk" << endl;
    }

    void payOnline() {
        int payChoice;
        double pay_Discount_Rate = 0.0;
        double pay_Discount = 0.0;
        double coinValue = calculate_Coin_Discount();

        cout << "\nSelect Payment Option " << endl;
        cout << "1. bKash (10% Discount)" << endl;
        cout << "2. Nagad (15% Discount)" << endl;
        cout << "3. Rocket (0% Discount)" << endl;
        cout << "4. Card (0% Discount)" << endl;
        cout << "Enter choice: ";
        cin >> payChoice;

        if (payChoice == 1) {
            pay_Discount_Rate = 0.10;
        } else if (payChoice == 2) {
            pay_Discount_Rate = 0.15;
        } else if (payChoice == 3 || payChoice == 4) {
            pay_Discount_Rate = 0.00;
        } else {
            cout << "Invalid Payment Method Selected!" << endl;
            return;
        }

        pay_Discount = product_Price * pay_Discount_Rate;
        final_price = product_Price - coinValue - voucher_Discount - pay_Discount + delFee + servFee;

        cout << "\nOnline Payment Summary" << endl;
        cout << "Product Price : " << product_Price << " Tk" << endl;
        cout << "Product Discount : " << disc_Amount << " Tk" << endl;
        cout << "Coin Price : " << coinValue << " Tk" << endl;
        cout << "Voucher : " << voucher_Discount << " Tk" << endl;
        cout << "Delivery Charge : " << delFee << " Tk" << endl;
        cout << "Service Charge : " << servFee << " Tk" << endl;
        cout << "Total Payable Amount : " << final_price << " Tk" << endl;
    }
};

int main() {
    cout << "DARAZ SHOPPING SYSTEM" << endl;

    Daraz order;
    order.userInfo();
    order.calcDiscount();

    int type;
    cout << "\nChoose Payment Type:" << endl;
    cout << "1. Cash on Delivery" << endl;
    cout << "2. Online Payment" << endl;
    cout << "Your Option: ";
    cin >> type;

    if (type == 1) {
        order.payCOD();
    } else if (type == 2) {
        order.payOnline();
    } else {
        cout << "Invalid option Chosen!" << endl;
    }

    return 0;
}
