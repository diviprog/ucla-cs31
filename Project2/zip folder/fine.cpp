//
//  main.cpp
//  Project2
//
//  Created by Devansh Mishra on 11/10/23.
//

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    
    // declaration of input types
    string identification;
    double overstated_amount;
    string location;
    
    
    // taking input
    cout << "Identification: ";
    getline(cin, identification);
    cout << "Overstated amount (in millions): ";
    cin >> overstated_amount;
    cout << "Location: ";
    cin.ignore();
    getline(cin, location);
    cout << "---" << endl;
    
    // checking for invalid inputs
    if (identification == "") {
        cout << "You must enter a property identification.";
    }
    else if (overstated_amount < 0) {
        cout << "The overstated amount must be positive.";
    }
    else if (location == "") {
        cout << "You must enter a location.";
    }
    // logic
    else {
        
        // declaring logic variables
        double fine_amount = 0;
        const double rate1 = 0.1111;
        double rate2;
        const double rate3 = 0.21;
        
        // finding rate2
        if (location == "florida" or location == "new york") {
            rate2 = 0.18;
        }
        else {
            rate2 = 0.153;
        }
        
        // finding fine amount
        
        if (overstated_amount <= 60) { // rate 1
            fine_amount = rate1 * overstated_amount;
        }
        else if (overstated_amount <= 150){ // rate 2
            fine_amount = (rate1 * 60) + (rate2 * (overstated_amount-60));
        }
        else { // rate 3
            fine_amount = (rate1 * 60) + (rate2 * 90) + (rate3 * (overstated_amount-150));
        }
        
        cout << "The fine for " << identification << " is $" << fixed << setprecision(3) << fine_amount << " million." << endl;
        
    }
    
    return 0;
}
