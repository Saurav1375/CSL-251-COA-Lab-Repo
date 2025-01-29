#include<bits/stdc++.h>
using namespace std;

double binToDec(string s) {
    double res = 1.0;
    double frac = 0.5;
    for (char c : s) {
        if (c == '1') res += frac;
        frac /= 2;
    }
    return res;
}

void floatOp(int n, int m, string s1, string s2, string e1, string e2, bool add) {
    int exp1 = stoi(e1, nullptr, 2);
    int exp2 = stoi(e2, nullptr, 2);

    double sig1 = binToDec(s1);
    double sig2 = binToDec(s2);
    
    if (!add) sig2 = -sig2;    
    while (exp1 < exp2) {
        sig1 /= 2;
        exp1++;
    }
    while (exp2 < exp1) {
        sig2 /= 2;
        exp2++;
    }
    double resSig = sig1 + sig2;
    int resExp = exp1;

    if (resSig == 0) {
        cout << "Result: 0" << endl;
        return;
    }
    while (resSig >= 2.0) {
        resSig /= 2;
        resExp++;
    }
    while (resSig < 1.0) {
        resSig *= 2;
        resExp--;
    }
    string resSigStr = "";
    double frac = resSig - 1.0;
    for (int i = 0; i < n; i++) {
        frac *= 2;
        if (frac >= 1.0) {
            resSigStr += '1';
            frac -= 1.0;
        } else {
            resSigStr += '0';
        }
    }
    string resExpStr = "";
    for (int i = m - 1; i >= 0; i--) resExpStr += ((resExp >> i) & 1) ? '1' : '0';
    
    cout << "Result: 1." << resSigStr << " x 2^" << resExpStr << endl;
}

int main() {
    int n, m;
    string s1, s2, e1, e2;
    bool add;
    
    cout << "Enter n: ";
    cin >> n;
    cout << "Enter m: ";
    cin >> m;

    cout << "Enter S1: ";
    cin >> s1;
    cout << "Enter S2: ";
    cin >> s2;

    cout << "Enter E1: ";
    cin >> e1;
    cout << "Enter E2: ";
    cin >> e2;
    
    cout << "Enter 1 for addition, 0 for subtraction: ";
    cin >> add;
    
    floatOp(n, m, s1, s2, e1, e2, add);
    
    return 0;
}
