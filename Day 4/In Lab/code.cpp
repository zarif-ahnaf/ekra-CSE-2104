#include <iostream>
#include <string>
using namespace std;

class Bag {
private:
    string name;
    int price;
    string sizes;

    static int totalBag;

public:
    // Constructor with default arguments
    Bag(string n = "", int p = 0, string s = "") {
        name = n;
        price = p;
        sizes = s;
        totalBag++;
    }

    // Friend functions declarations
    friend void findMostSold(Bag b[], int n);
    friend void findExpensive(Bag b[], int n);

    // Static function to show total bags
    static void showTotalBag() {
        cout << "Total Bags = " << totalBag << endl;
    }

    // Destructor
    ~Bag() {
    }
};

// Initialize static variable
int Bag::totalBag = 0;

// Function to find most sold size
// Note: The code uses hardcoded values for sales counts (m, l, xl, xxl)
// rather than calculating from the array, based on the image.
void findMostSold(Bag b[], int n) {
    int m = 35;
    int l = 20;
    int xl = 30;
    int xxl = 25;

    int max_sold = m;
    string most_sold_size = "M";

    if (l > max_sold) {
        max_sold = l;
        most_sold_size = "L";
    }

    if (xl > max_sold) {
        max_sold = xl;
        most_sold_size = "XL";
    }

    if (xxl > max_sold) {
        max_sold = xxl;
        most_sold_size = "XXL";
    }

    cout << "Most Sold Bag Size: " << most_sold_size << endl;
    cout << "Number Sold: " << max_sold << endl;
}

// Function to find the most expensive bag
void findExpensive(Bag b[], int n) {
    int max_price = b[0].price;
    int index = 0;

    for (int i = 1; i < n; i++) {
        if (b[i].price > max_price) {
            max_price = b[i].price;
            index = i;
        }
    }

    cout << "\nMost Expensive Bag:" << endl;
    cout << "Name  : " << b[index].name << endl;
    cout << "Size  : " << b[index].sizes << endl;
    cout << "Price : " << b[index].price << endl;
}

int main() {
    // Array of 10 bags. 
    // Note: This calls the constructor 10 times immediately.
    Bag b[10]; 

    for (int i = 0; i < 10; i++) {
        string name, sizes;
        int price;
        
        cout << "\nEnter details of Bag " << i + 1 << endl;

        cout << "Enter name: ";
        cin >> name;

        cout << "Enter size: ";
        cin >> sizes;

        cout << "Enter price: ";
        cin >> price;

        // Creates a temporary object and assigns it to b[i]
        b[i] = Bag(name, price, sizes);
    }

    Bag::showTotalBag();

    findMostSold(b, 10);

    findExpensive(b, 10);

    return 0;
}
