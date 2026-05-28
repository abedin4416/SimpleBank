#include<bits/stdc++.h>
#include "Simpleini.h"
using namespace std;
#define cc const char*
#define cs CSimpleIniA&
#define OPTIONS "\n1. Send  Any other key to exit"

CSimpleIniA data;
bool exists(cc ID);
string get(cc ID, cc value);
bool verified(cc ID);
void newAccount(cc ID);

int main(int argc, char *argv[]){
    if(argc < 2) return 1;
    data.SetUnicode();
    data.LoadFile("data.txt");
    cc ID = argv[1];
    if(exists(ID)){
        if(verified(ID)){
            cout << "\nBalance: " << get(ID, "money");
            cout << OPTIONS;
        }
    }
    else newAccount(ID);
    return 0;
}

bool exists(cc ID){
    return data.GetSection(ID) != nullptr;
}

string get(cc ID, cc value){
    return data.GetValue(ID, value, "0");
}

bool verified(cc ID){
    cout << "\nEnter password: ";
    string password;
    cin >> password;
    return get(ID, "key") == password;
}

void newAccount(cc ID){
    cout << "The Account doesn't exist";
    cout << "\n1. Create Account\n";
    int input;
    cin >> input;
    if(input != 1) return;
    char* password;
    cout << "\nEnter a new password: ";
    cin >> password;
    data.SetValue(ID, "key", password);
    data.SetValue(ID, "money", "0");
    cout << "\nAccount created successfully.";
}