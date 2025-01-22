#include <iostream>
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

bool isNeg(string &bin) {
    return bin[0] == '1';
}

string twosComp(string bin, int len) {
    string res = bin;
    for (int i = 0; i < len; ++i) {
        res[i] = (bin[i] == '0') ? '1' : '0';
    }
    string one(len, '0');
    one[len - 1] = '1';
    return AddSub(res, one, len, false);
}

int main() {
    int n;
    cout << "Enter bits: ";
    cin >> n;

    string a(n, '0'), m, q;
    cout << "Divisor(M): ";
    cin >> m;
    cout << "Dividend(Q): ";
    cin >> q;

    bool mNeg = isNeg(m), qNeg = isNeg(q);
    if (mNeg) m = twosComp(m, n);
    if (qNeg) q = twosComp(q, n);

    int cnt = n;
    while (cnt > 0) {
        a = a.substr(1) + q[0];
        q = q.substr(1) + "0";
        a = AddSub(a, m, n, true);
        if (isNeg(a)) {
            q[n - 1] = '0';
            a = AddSub(a, m, n, false);
        } else {
            q[n - 1] = '1';
        }
        cnt--;
    }

    if (mNeg != qNeg) q = twosComp(q, n);
    if (qNeg) a = twosComp(a, n);

    cout << "Q: " << q << endl;
    cout << "A: " << a << endl;

    return 0;
}
