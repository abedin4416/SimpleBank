#include<bits/stdc++.h>
#include "SimpleIni.h"
using namespace std;
#define cc const char*
#define DATA "data.txt"

CSimpleIniA data;
cc ID;
string input;
bool exists();
string get(cc name);
void setval(cc name, string value);
bool verified();
void newPassword();
void newAccount();

int main(int argc, char *argv[]){
    if(argc < 2) return 0;
    data.LoadFile(DATA);
    ID = argv[1];
    if(exists()){
        if(verified()){
            cout << "Balance: " << get("money");
            cout << "\n1. Send  2. Change Password\n";
            cin >> input;
            //input 1 send
            if(input == "2"){
                newPassword();
                data.SaveFile(DATA);
                cout << "Password changed.";
            }
        }
        else cout << "Wrong password.";
    }
    else newAccount();
    return 0;
}

bool exists(){
    return data.GetSection(ID) != nullptr;
}

string get(cc name){
    return data.GetValue(ID, name, "");
}

void setval(cc name, string value){
    data.SetValue(ID, name, value.c_str());
}

bool verified(){
    cout << "Enter password: ";
    cin >> input;
    return get("key") == input;
}

void newPassword(){
    cout << "Enter a new password: ";
    cin >> input;
    setval("key", input);
}
void newAccount(){
    cout << "The Account doesn't exist";
    cout << "\n1. Create Account" << "\n";
    cin >> input;
    if(input != "1") return;
    newPassword();
    setval("money", "0");
    data.SaveFile(DATA);
    cout << "Account created successfully.";
}