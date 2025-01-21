#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

//code for Question-1
vector<int> strToBinary(string &str){
    vector<int> ans;
    for (char ch : str)
        ans.push_back(ch - '0');
    return ans;
}

string binaryToStr(vector<int> &bin){
    string ans;
    for (int b : bin)
        ans += to_string(b);
    return ans;
}

vector<int> find2sComplement(vector<int> &num){
    vector<int> ans = num;
    int n = ans.size();
    bool is_one = false;

    for (int i = n - 1; i >= 0; i--){
        if (!is_one){
            if (ans[i] == 1)
                is_one = true;
            continue;
        }
        ans[i] = 1 - ans[i];
    }
    return ans;
}

string AddSub(string &A, string &B, bool isAdd){
    vector<int> n1 = strToBinary(A);
    vector<int> n2 = strToBinary(B);
    int n = n1.size();
    vector<int> ans(n);

    if (!isAdd)
        n2 = find2sComplement(n2);

    int carry = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int sum = n1[i] + n2[i] + carry;
        ans[i] = sum % 2;
        carry = sum / 2;
    }

    return binaryToStr(ans);
}

//code for Question-2 (using flow chart)
int main() {
    int n;
    cout << "Number of Bits: ";
    cin >> n;

    string M, Q;
    cout << "Enter M: ";
    cin >> M;
    cout << "Enter Q: ";
    cin >> Q;

    string A(n, '0');  
    char Q_1 = '0';   
    int count = n;     

    while (count > 0) {
        char Q_0 = Q[n - 1];

        if (Q_0 == '1' && Q_1 == '0')  A = AddSub(A, M, false); 
        else if (Q_0 == '0' && Q_1 == '1') A = AddSub(A, M, true);
    
        Q_1 = Q[n - 1];
        Q = A[n - 1] + Q.substr(0, n - 1);
        A = A[0] + A.substr(0, n - 1);
        count--;
    }

    string prod = A + Q;
    cout << "Product: " << prod << endl;
}
