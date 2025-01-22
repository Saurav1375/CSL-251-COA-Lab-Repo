#include <iostream>
#include <vector>
#include <string>
using namespace std;

string AddSub(string x, string y, int len, bool sub) {
    string res = "";
    char c = sub ? '1' : '0';

    for (int i = 0; i < len; ++i) {
        y[i] = ((y[i] - '0') ^ sub) + '0';
    }

    for (int i = len - 1; i >= 0; --i) {
        int tmp = (x[i] - '0') + (y[i] - '0') + (c - '0');
        res = (char)((tmp % 2) + '0') + res;
        c = (char)((tmp / 2) + '0');
    }

    return res;
}
int main() {
    string A = "";
    cout << "Enter A: ";
    cin >> A;
    string B = "";
    cout << "Enter B: ";
    cin >> B;

    int n = A.length();
    cout << "A + B = " << AddSub(A, B, n, false) << endl;
    cout << "A - B = " << AddSub(A, B,n,  true) << endl;
    
    return 0;
}