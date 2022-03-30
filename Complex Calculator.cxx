
#include <iostream>
#include <regex> 
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

// Defining the functions.
bool isValidComplex(string& str);
void parseComplex(string& str, float& real, float& img);

int main()
{
    // Defining required variables
	string strComplex, strComplex2;
	float r1, img1, r2, img2, R, Img;
	string operation;
    char operation_;

	cout << "              Complex Calculator\n\nWelcome Dear user!\n\n";
    
    while(true)
    {
        bool isValidOp = false;
        int nChances = 2;

        /* Repeat until the number of chances equal 0, You have only two chances to input a valid complex number on form (a+bi), 
        if you entered a wrong number the nChances decreases by one */
        while (nChances > 0)
        {
            cout << "\nPlease Enter a valid complex number like: (a+bi) OR Quit\nBe careful you only have " << nChances << " chances remaining to enter a valid one:\n>>";

            // Getting a complex number from the user
            cin >> strComplex;
            // Transforming the whole string to lowercase to accept any form of the word quit.
            transform(strComplex.begin(), strComplex.end(), strComplex.begin(), ::tolower);

            // if the strcomplex was on the complex number form (a+bi)
            if (isValidComplex(strComplex))
            {
                // Getting the real part and imagine part from strComplex and storing them in r1, img1 
                parseComplex(strComplex, r1, img1);
                cout << "You entered: " << r1 << " + " << img1 << 'i' << '\n';
                break;
            }
            // if user entered quit, Close the program
            else if (strComplex == "quit")
            {
                return 1;
            }
            // if the input was not on form (a+bi). a,b is real numbers
            else
            {

                cout << "It is not a valid complex number.\n";
                // Decrement the number of chances by one
                --nChances;
                // If we reach to zero chances left exit the program.
                if (nChances == 0)
                {
                    return 1;
                } 
            }
            
        }
        
        // Reassign the number of chances to the primary value to get the second number 
        nChances = 2;

        // Redoing the previous process but for the second input
        while (nChances > 0)
        {
            cout << "\nPlease Enter the second valid complex number like:(a+bi) OR Quit\nBe careful you only have " << nChances << " chances remaining to enter a valid one:\n>>";
            cin >> strComplex2;

            // Transforming the whole string to lowercase to accept any form of the word quit.
            transform(strComplex2.begin(), strComplex2.end(), strComplex2.begin(), ::tolower);

            if (isValidComplex(strComplex2))
            {
                parseComplex(strComplex2, r2, img2);
                cout << "You entered: " << r2 << " + " << img2 << 'i' << '\n';
                break;
            }
            else if (strComplex2 == "quit")
            {
                return 1;
            }
            else
            {
                cout << "It is not a valid complex number.\n";
                --nChances;

                if (nChances == 0)
                {
                    return 1;
                } 
            }   
        }

        
        while (!isValidOp)
        {
            cout << "\nPlease, enter the operation like: + or - or / or * OR Quit:\n>>";
            cin >> operation;

            // Transforming the whole string to lowercase to accept any form of the word quit.
            transform(operation.begin(), operation.end(), operation.begin(), ::tolower);

            // Checking if the operation was just one character
            if(operation.length() == 1)
            {
                // Store this character in char variable called operation_
                operation_ = operation[0];
            }
            // if the string operation equal quit, Close the program
            else if (operation == "quit")
            {
                return 1;
            }
            // Else if the operation was not one character, store in char operation_ D which is dummy character
            else
            {
                operation_ = 'D';   // D stand for a dummy character.
            }
            
            // Make is valid operator equals true until proven otherwise
            isValidOp = true;

            // Takes opreation_ char and checks if equals a valid operator
            switch (operation_)
            {
                case ('+'):
                    // Getting the sum of real parts and imagine parts from the two complex numbers
                    R = r1 + r2;
                    Img = img1 + img2;
                    // Displaying the result
                    cout << "The Result = " << "(" << R << " + " << Img << "i" << ")" << '\n';
                    break;

                case ('-'):
                    // Getting the substract of real parts and imagine parts from the two complex numbers
                    R = r1 - r2;
                    Img = img1 - img2;
                    cout << "The Result = " << "(" << R << " + " << Img << "i" << ")" << '\n';
                    break;

                case ('*'):
                    // Multiplying the two complex numbers and getting the result real part and imagine part using the formula 
                    R = (r1 * r2) - (img1 * img2);
                    Img = (r1 * img2) + (img1 * r2);
                    // Displaying the result
                    cout << "The Result = " << "(" << R << " + " << Img << "i" << ")" << '\n';
                    break;

                case ('/'):
                    // Dividing the two complex numbers and getting the result real part and imagine part using the formula 
                    R = ((r1 * r2) + (img1 * img2)) / ((r2 * r2) + (img2 * img2));
                    Img = ((img1 * r2) - (r1 * img2)) / ((r2 * r2) + (img2 * img2));
                    cout << "The Result = " << "(" << R << " + " << Img << "i" << ")" << '\n';
                    break;

                // else if the operation_ was not equal to any operation from above.
                default:
                    cout << "Invalid input!";
                    // Make is valid operator false again to repeat the loop
                    isValidOp = false;
                    break;
            }

        }
    }


}

bool isValidComplex (string& str)
{
    // Making a form for input complex number using regular expressions 
	regex isValidComplex("[(][+-]?[0-9]+(.[0-9]*)*[+-][0-9]+(.[0-9]*)*[i][)]");
    //Returning True if the input string was like the complex number form we just make, False otherwise
	return regex_match (str, isValidComplex);

}

void parseComplex(string& str, float& real, float& img)
{
    // Getting plus sign index in the strcomplex if exist starting searching from the third character, returning -1 if not found
	int plusPos = str.find('+',2);
    // Getting minus sign index in the strcomplex if exist starting searching from the third character, returning -1 if not found
	int minusPos = str.find('-',2);
    // Getting the existing sign by getting the higher returning value of find()
	int singPOS = max(minusPos, plusPos); //if you find + or - retrun postion of the sing.
    // Getting the 'i' index in the strcomplex
	int iPos = str.find('i');
    //Getting the real part of the number by substracting the number from index 1 to(ends before) the + or - index 
	real = stof(str.substr(1, singPOS));
    //Getting the real part of the number by substracting the number from + or - to(ends before) 'i' index 
	img = stof(str.substr(singPOS, iPos));

}
