#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> addBinary(vector<int>& a, vector<int>& b) {
    vector<int> result(a.size());
    int carry = 0;
    
    for (int i = a.size() - 1; i >= 0; i--) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }
    return result;
}

void arithmeticRightShift(vector<int>& num) {
    int msb = num[0];  
    for (int i = num.size() - 1; i > 0; i--) {
        num[i] = num[i - 1];
    }
    num[0] = msb;
}

vector<int> getTwosComplement(vector<int>& num) {
    vector<int> result = num;

    for (int i = 0; i < result.size(); i++) {
        result[i] = 1 - result[i];
    }

    vector<int> one(result.size(), 0);
    one[one.size() - 1] = 1;
    return addBinary(result, one);
}

vector<int> boothMultiply(int n, vector<int>& multiplicand, vector<int>& multiplier) {
    vector<int> M = multiplicand;  
    vector<int> Q = multiplier;   
    vector<int> A(n, 0);         
    int Q_1 = 0;                     
    
    for (int i = 0; i < n; i++) {
        int Q0 = Q[n-1];
        
        if (Q0 == 1 && Q_1 == 0) {
            vector<int> negM = getTwosComplement(M);
            A = addBinary(A, negM);
        }
        else if (Q0 == 0 && Q_1 == 1) {
            A = addBinary(A, M);
        }
        
        Q_1 = Q[n-1];
        arithmeticRightShift(Q);
        Q[0] = A[n-1];
        arithmeticRightShift(A);
    }
    
    vector<int> result(2*n);
    for (int i = 0; i < n; i++) {
        result[i] = A[i];
        result[i + n] = Q[i];
    }
    
    return result;
}

int main() {
    int n;
    string multiplicand_str, multiplier_str;
    
    cout << "Enter the size of binary numbers (n): ";
    cin >> n;
    
    cout << "Enter " << n << "-bit multiplicand in binary: ";
    cin >> multiplicand_str;
    cout << "Enter " << n << "-bit multiplier in binary: ";
    cin >> multiplier_str;
    
    vector<int> multiplicand(n), multiplier(n);
    for(int i = 0; i < n; i++) {
        multiplicand[i] = multiplicand_str[i] - '0';
        multiplier[i] = multiplier_str[i] - '0';
    }
    
    vector<int> result = boothMultiply(n, multiplicand, multiplier);
    
    cout << "Result: ";
    for(int bit : result) {
        cout << bit;
    }
    cout << endl;
    
    return 0;
}