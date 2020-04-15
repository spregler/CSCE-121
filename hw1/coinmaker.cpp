#include <iostream> 
using namespace std;
 
 
int main()
{
     
    int dollars, cents, totQuarters, quarters, dimes, nickels, pennies, totalCoins;
     
    cin >> dollars;
    cin >> cents;
     
    
    quarters = dollars / (.25);
    totQuarters = cents / 25 + quarters;
    dimes = (cents % 25) /10;
    nickels = (cents % 25) % 10 / 5;
    pennies = (cents % 25) % 10 % 5 /1;
    totalCoins = totQuarters + dimes + nickels + pennies;

    cout <<"Enter dollars: Enter cents: ";
    cout << "Pennies: "<< pennies << endl;
    cout << "Nickels: "<< nickels <<endl;
    cout << "Dimes: "<< dimes <<endl;
    cout << "Quarters: "<< totQuarters <<endl;
    cout << endl;
    cout << "Total coins used: " << totalCoins;

    
     
    return 0;
     
}