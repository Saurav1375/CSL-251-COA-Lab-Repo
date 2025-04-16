#include <iostream>
#include <string>
using namespace std;

enum State { INVALID, SHARED, EXCLUSIVE, MODIFIED };
string states[] = {"INVALID", "SHARED", "EXCLUSIVE", "MODIFIED"};

int main() {
    State caches[4] = {INVALID, INVALID, INVALID, INVALID};
    int a;
    char b;
    int c;
    
    while (true) {
        cout << "Enter (a b c) : ";
        cin >> a >> b >> c;
        
        int proc = a - 1;
        
        if (b == 'R') {
            if (caches[proc] == INVALID) {
                bool containsData = false;
                
                for (int i = 0; i < 4; i++) {
                    if (i != proc && (caches[i] == SHARED || caches[i] == EXCLUSIVE || caches[i] == MODIFIED)) {
                        containsData = true;
                        break;
                    }
                }
                
                if (containsData) {
                    caches[proc] = SHARED;
                    
                    for (int i = 0; i < 4; i++) {
                        if (caches[i] == MODIFIED || caches[i] == EXCLUSIVE) {
                            caches[i] = SHARED;
                        }
                    }
                } else {
                    caches[proc] = EXCLUSIVE;
                }
            }
        } else {
            caches[proc] = MODIFIED;
            for (int i = 0; i < 4; i++) {
                if (i != proc) {
                    caches[i] = INVALID;
                }
            }
        }
        
        for (int i = 0; i < 4; i++) {
            cout << "C" << (i + 1) << ": " << states[caches[i]];
            if (i < 3) cout << ", ";
        }
        cout << endl;
        
        if (c == 0) break;
    }
    
    return 0;
}