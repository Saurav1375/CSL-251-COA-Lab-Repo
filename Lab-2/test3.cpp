#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Helper function to perform binary addition
vector<int> binaryAdd(const vector<int> &a, const vector<int> &b) {
    int n = a.size();
    vector<int> result(n, 0);
    int carry = 0;
    for (int i = n - 1; i >= 0; --i) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
    return result;
}

// Helper function to perform binary negation (2's complement)
vector<int> binaryNegate(const vector<int> &bin) {
    int n = bin.size();
    vector<int> onesComplement(n, 0);
    for (int i = 0; i < n; ++i) {
        onesComplement[i] = 1 - bin[i];
    }
    vector<int> one(n, 0);
    one[n - 1] = 1;
    return binaryAdd(onesComplement, one);
}

// Helper function to perform arithmetic right shift
void arithmeticRightShift(vector<int> &A, vector<int> &Q, int &Q_1) {
    int msb_A = A[0];
    Q_1 = Q.back();
    Q.insert(Q.begin(), A.back());
    Q.pop_back();
    A.insert(A.begin(), msb_A);
    A.pop_back();
}

// Convert binary string to vector<int>
vector<int> binaryStringToVector(const string &binStr) {
    vector<int> binVec;
    for (char bit : binStr) {
        binVec.push_back(bit - '0');
    }
    return binVec;
}

// Convert vector<int> to binary string
string vectorToBinaryString(const vector<int> &binVec) {
    string binStr;
    for (int bit : binVec) {
        binStr += to_string(bit);
    }
    return binStr;
}

int main() {
    int n;
    string binary1, binary2;

    cout << "Enter the size of binary integers (n): ";
    cin >> n;
    cout << "Enter the first binary number (in 2's complement format): ";
    cin >> binary1;
    cout << "Enter the second binary number (in 2's complement format): ";
    cin >> binary2;

    vector<int> M = binaryStringToVector(binary1);
    vector<int> Q = binaryStringToVector(binary2);
    vector<int> A(n, 0);
    int Q_1 = 0;

    vector<int> negM = binaryNegate(M);

    // Booth's algorithm
    for (int i = 0; i < n; ++i) {
        if (Q.back() == 1 && Q_1 == 0) {
            A = binaryAdd(A, negM);
        } else if (Q.back() == 0 && Q_1 == 1) {
            A = binaryAdd(A, M);
        }
        arithmeticRightShift(A, Q, Q_1);
    }

    // Combine A and Q to form the final result
    vector<int> result;
    result.insert(result.end(), A.begin(), A.end());
    result.insert(result.end(), Q.begin(), Q.end());

    cout << "Product in binary: " << vectorToBinaryString(result) << endl;

    return 0;
}