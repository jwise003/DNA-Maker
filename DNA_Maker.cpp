/*
DNA Sequence Generation and Comparison Project
Author:  John Wiseman

This program is designed to use multiple classes to generate Acid
chains of DNA Codons, and them compare them to one another to test
for similar sequences within the two chains, and to identify the
longest equivalent chains.
*/


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;
#include "DNA_Maker_Imp.cpp"


///here there be dragons.
int main()
{
    srand(time(NULL));


    ///User input control
    //create two lists
    int length1;    //Lengths of both lists
    int length2;
    acid* a1 = NULL;    //Create both lists with a NULL at the head.
    acid* a2 = NULL;
    char choice = 'z';
    cout << "Please select a number of 2 or greater." << endl;  //Create both lists of lengths obtained from user.
    cout << "How many links in chain 1? ";
    cin >> length1;
    cout << "How many links in chain 2? ";
    cin >> length2;

    if((length1 <= 1) || (length2 <= 1))  //If either langth are less than 2, get another value from the user.
        cout << "Try again." << endl;
    else
    {
        a1 = new acid(length1); //create the chains.
        a1->display_acid();
        cout << endl;
        a2 = new acid(length2);
        a2->display_acid();
        cout << endl;
        cout << "Would you like to compare them? Y/N: "; //ask user if they would like to compare the chains.
        cin >> choice;
        if(choice == 'y' || choice == 'Y')  //if Y, compare, if N, exit program.
            a1->acid_comparison(a1, a2);
        else
            return 0;
    }

    return 0;
}
