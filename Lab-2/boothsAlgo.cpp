#include <bits/stdc++.h>
using namespace std;

void addBinaryNumbers(int acc[], int op, int bitCnt) {
    int carry = 0;
    for(int i = 0; i< bitCnt; i++){
        acc[i] = acc[i] + op[i] + carry;
        if(acc[i] > 1){
            acc[i] = acc[i] % 2;
            carry = 1;
        }
    }
    else{
        carry = 0;
    }
}

void computeTwosComplement(int bin[], int bitCnt){
    int arr[8] = {0};
    arr[0] = 1;

    for(int i = 0; i< bitCnt; i++) bin[i] = (bin[i] + 1) % 2;
    addBinaryNumbers(bin, arr, bitCnt);
    
}

void rightShift()

void performRightShift(int accumulator[], int multiplier[], int &lastBit, int bitCount)
{
    int temp = accumulator[0];
    lastBit = multiplier[0];

    cout << "\t\trightShift\t";

    for (int i = 0; i < bitCount - 1; i++)
    {
        accumulator[i] = accumulator[i + 1];
        multiplier[i] = multiplier[i + 1];
    }
    multiplier[bitCount - 1] = temp;
}

void findTwosComplement(int binary[], int bitCount)
{
    int temp[8] = {0};
    temp[0] = 1;

    for (int i = 0; i < bitCount; i++)
    {
        binary[i] = (binary[i] + 1) % 2;
    }
    addBinary(binary, temp, bitCount);
}

void addBinary(int accumulator[], int operand[], int bitCount)
{
    int carry = 0;
    for (int i = 0; i < bitCount; i++)
    {
        accumulator[i] = accumulator[i] + operand[i] + carry;
        if (accumulator[i] > 1)
        {
            accumulator[i] = accumulator[i] % 2;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
}





void displayState(int accumulator[], int multiplier[], int bitCount)
{
    for (int i = bitCount - 1; i >= 0; i--)
        cout << accumulator[i];
    cout << "\t";

    for (int i = bitCount - 1; i >= 0; i--)
        cout << multiplier[i];
}

void boothMultiplication(int multiplicand[], int multiplier[], int complement[], int bitCount, int stepCount)
{
    int lastBit = 0, accumulator[10] = {0};
    int tempState = 0;

    cout << "lastBit\tmultiplier[0]\t\tMultiplicand\t\tAccumulator\tMultiplier\t\tStep Count\n";
    cout << "\t\t\tinitial\t\t";

    displayState(accumulator, multiplier, bitCount);
    cout << "\t\t" << stepCount << "\n";

    while (stepCount != 0)
    {
        cout << multiplier[0] << "\t" << lastBit;

        if ((lastBit + multiplier[0]) == 1)
        {
            if (tempState == 0)
            {
                addBinary(accumulator, complement, bitCount);
                cout << "\t\tA = A - Multiplicand\t";

                for (int i = bitCount - 1; i >= 0; i--)
                    cout << accumulator[i];

                tempState = 1;
            }
            else if (tempState == 1)
            {
                addBinary(accumulator, multiplicand, bitCount);
                cout << "\t\tA = A + Multiplicand\t";

                for (int i = bitCount - 1; i >= 0; i--)
                    cout << accumulator[i];

                tempState = 0;
            }
            cout << "\n\t";
            performRightShift(accumulator, multiplier, lastBit, bitCount);
        }
        else if (lastBit - multiplier[0] == 0)
        {
            performRightShift(accumulator, multiplier, lastBit, bitCount);
        }

        displayState(accumulator, multiplier, bitCount);
        cout << "\t";

        stepCount--;
        cout << "\t" << stepCount << "\n";
    }
}

int main()
{
    int multiplicand[10], stepCount;
    int multiplicandBits = 2;

    int multiplicandBinary[] = {0, 1;
    for (int i = multiplicandBits - 1; i >= 0; i--)
        multiplicand[i] = multiplicandBinary[i];

    reverse(multiplicandBinary, multiplicandBinary + multiplicandBits);
    findTwosComplement(multiplicand, multiplicandBits);

    int multiplierBits = 4;
    stepCount = multiplierBits;

    int multiplierBinary[] = {1, 0, 1, 0};
    reverse(multiplierBinary, multiplierBinary + multiplierBits);

    boothMultiplication(multiplicandBinary, multiplierBinary, multiplicand, multiplierBits, stepCount);

    cout << endl
         << "Result = ";
    for (int i = multiplierBits - 1; i >= 0; i--)
        cout << multiplierBinary[i];
}
