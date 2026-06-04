#include<bits/stdc++.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
#define FILE "data.json"

json db;
string ID;
string input;
void options(const vector<string>& options);
bool load();
void save();
bool exists();
string get(string name);
void setval(string name, string value);
bool verified();
void newPassword();
void newAccount();

int main(int argc, char *argv[]){
    if(argc < 2) return 0;
    load();
    ID = argv[1];
    if(!exists()){
        newAccount(); 
        return 0;
    }
    if(!verified()){
        cout << "Wrong password.";
        return 0;
    }
    cout << "Balance: " << get("money") << "\n";
    options({"Send", "Change Password"});
    //input 1 send
    if(input == "2"){
        newPassword();
        save();
        cout << "Password changed.";
    }
    return 0;
}
void options(const vector<string>& options){
    for(int i = 0; i < options.size(); i++){
        cout << i + 1 << "." << options[i] << "  ";
    }
    cout << "\n";
    cin >> input;
}
bool load(){
    ifstream in(FILE);
    if (in.is_open()){
        in >> db;
        return true;
    }
    db = json::object();
    return false;
}

void save(){
    ofstream out(FILE);
    out << db.dump(4);
}

bool exists(){
    return db.contains(ID);
}

string get(string name){
    if(!db.contains(ID)) return "";
    if(!db[ID].contains(name)) return "";
    return db[ID][name].get<string>();
}

void setval(string name, string value){
    db[ID][name] = value;
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
    cout << "The Account doesn't exist\n";
    cout << "1. Create Account" << "\n";
    cin >> input;
    if(input != "1") return;
    newPassword();
    setval("money", "0");
    save();
    cout << "Account created successfully.";
}