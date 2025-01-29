#include <bits/stdc++.h>
using namespace std;

const int BIAS = 127; // Bias for IEEE 754 single-precision representation

double binaryToDecimal(const string &s)
{
    double result = 0.0;
    double frac = 0.5;
    for (char c : s)
    {
        if (c == '1')
            result += frac;
        frac /= 2;
    }
    return result;
}

void floatingPointOperation(int n, int m, string S1, string S2, string E1, string E2, bool isAddition)
{
    int exp1 = stoi(E1, nullptr, 2) - BIAS; // Convert exponent from biased form
    int exp2 = stoi(E2, nullptr, 2) - BIAS;

    double significand1 = 1.0 + binaryToDecimal(S1); // Assume normalized representation
    double significand2 = 1.0 + binaryToDecimal(S2);

    if (!isAddition)
        significand2 = -significand2;

    // Align exponents
    while (exp1 < exp2)
    {
        significand1 /= 2;
        exp1++;
    }
    while (exp2 < exp1)
    {
        significand2 /= 2;
        exp2++;
    }

    double resultSignificand = significand1 + significand2;
    int resultExponent = exp1;

    // Handle zero result case
    if (resultSignificand == 0)
    {
        cout << "Result: 0" << endl;
        return;
    }

    // Normalize result
    while (resultSignificand >= 2.0)
    {
        resultSignificand /= 2;
        resultExponent++;
    }
    while (resultSignificand < 1.0)
    {
        resultSignificand *= 2;
        resultExponent--;
    }

    // Check for overflow and underflow
    if (resultExponent > 127)
    {
        cout << "Overflow!!" << endl;
        return;
    }
    if (resultExponent < -126)
    {
        cout << "Underflow!!" << endl;
        return;
    }

    // Convert back to binary
    string resultS = "";
    double frac = resultSignificand - 1.0;
    for (int i = 0; i < n; i++)
    {
        frac *= 2;
        if (frac >= 1.0)
        {
            resultS += '1';
            frac -= 1.0;
        }
        else
        {
            resultS += '0';
        }
    }

    // Convert exponent back to biased binary form
    string resultE = bitset<8>(resultExponent + BIAS).to_string().substr(8 - m);

    cout << "Result: 1." << resultS << " x 2^" << resultE << endl;
}

int main()
{
    int n, m;
    string S1, S2, E1, E2;
    bool isAddition;

    cout << "Enter n: ";
    cin >> n;
    cout << "Enter m: ";
    cin >> m;

    cout << "Enter S1: ";
    cin >> S1;
    cout << "Enter S2: ";
    cin >> S2;

    cout << "Enter E1: ";
    cin >> E1;
    cout << "Enter E2: ";
    cin >> E2;

    cout << "Enter 1 for addition, 0 for subtraction: ";
    cin >> isAddition;

    floatingPointOperation(n, m, S1, S2, E1, E2, isAddition);

    return 0;
}
