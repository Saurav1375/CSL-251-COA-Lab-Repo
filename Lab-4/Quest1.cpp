#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> strToBinary(string& str) {
    vector<int> ans;
    for(char ch : str) ans.push_back(ch - '0');
    return ans;
}

string binaryToStr(vector<int>& bin) {
    string ans;
    for(int b : bin) ans += to_string(b);
    return ans;
}

vector<int> find2sComplement(vector<int>& num) {
    vector<int> ans = num;
    int n = ans.size();
    bool is_one = false;
    
    for(int i = n-1; i >= 0; i--) {
        if(!is_one) {
            if(ans[i] == 1) is_one = true;
            continue;
        }
        ans[i] = 1 - ans[i];
    }
    return ans;
}

string AddSub(string& A, string& B, bool isAdd) {
    vector<int> n1 = strToBinary(A);
    vector<int> n2 = strToBinary(B);
    int n = n1.size();
    vector<int> ans(n);
    
    if(!isAdd) n2 = find2sComplement(n2);
    
    int carry = 0;
    for(int i = n-1; i >= 0; i--) {
        int sum = n1[i] + n2[i] + carry;
        ans[i] = sum % 2;
        carry = sum / 2;
    }
    
    return binaryToStr(ans);
}

int main() {
    string A = "";
    cout << "Enter A: ";
    cin >> A;
    string B = "";
    cout << "Enter B: ";
    cin >> B;

    cout << "A + B = " << AddSub(A, B, true) << endl;
    cout << "A - B = " << AddSub(A, B, false) << endl;
    
    return 0;
}