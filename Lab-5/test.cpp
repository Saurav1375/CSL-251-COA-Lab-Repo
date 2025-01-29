#include <iostream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

// Function to convert binary string to integer
int binaryToInt(const string &binary)
{
    return stoi(binary, nullptr, 2);
}

// Function to perform floating-point addition/subtraction
string floatingPointOperation(int n, int m, const string &S1, const string &S2, const string &E1, const string &E2, bool isAddition)
{
    // Convert inputs
    int exponent1 = binaryToInt(E1);
    int exponent2 = binaryToInt(E2);
    bitset<32> significand1("1" + S1);
    bitset<32> significand2("1" + S2);

    if (!isAddition)
    {
        significand2.flip();                        // Change the sign for subtraction
        significand2 = significand2.to_ulong() + 1; // Add one for two's complement
    }

    // Align exponents
    while (exponent1 < exponent2)
    {
        significand1 >>= 1;
        exponent1++;
    }
    while (exponent2 < exponent1)
    {
        significand2 >>= 1;
        exponent2++;
    }

    // Perform addition of significands
    bitset<32> resultSignificand = significand1.to_ulong() + significand2.to_ulong();

    // Normalize result
    while (resultSignificand[31] == 0 && resultSignificand.any())
    {
        resultSignificand <<= 1;
        exponent1--;
    }

    // Handle underflow and overflow
    if (exponent1 < 0)
    {
        return "Underflow occurred!";
    }
    if (exponent1 > (1 << m) - 1)
    {
        return "Overflow occurred!";
    }

    // Convert result back to binary strings
    string resultSignificandStr = resultSignificand.to_string().substr(1, n);       // Skip leading 1
    string resultExponentStr = bitset<16>(exponent1).to_string().substr(16 - m, m); // Keep m bits

    // Return formatted result
    return "Significand: " + resultSignificandStr + ", Exponent: " + resultExponentStr;
}

int main()
{
    // Input parameters
    int n, m;
    string S1, S2, E1, E2;
    bool isAddition;

    cout << "Enter the number of bits for significand (n): ";
    cin >> n;
    cout << "Enter the number of bits for exponent (m): ";
    cin >> m;

    cout << "Enter significand S1: ";
    cin >> S1;
    cout << "Enter significand S2: ";
    cin >> S2;

    cout << "Enter exponent E1: ";
    cin >> E1;
    cout << "Enter exponent E2: ";
    cin >> E2;

    cout << "Enter 1 for addition or 0 for subtraction: ";
    cin >> isAddition;

    // Validate inputs
    if (S1.size() != n || S2.size() != n || E1.size() != m || E2.size() != m)
    {
        cout << "Invalid input sizes!" << endl;
        return 1;
    }

    // Perform operation and display result
    string result = floatingPointOperation(n, m, S1, S2, E1, E2, isAddition);
    cout << "Result: " << result << endl;

    return 0;
}
