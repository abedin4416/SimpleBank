#include<bits/stdc++.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
#define FILE "data.json"
using str = const string&;

json db;
string ID, input;
void options(const vector<string>& v){
    for(int i = 0; i < v.size(); i++)
        cout << i + 1 << "." << v[i] << "  ";
    cout << "\n";
    cin >> input;
}
bool load(){
    ifstream in(FILE);
    if(in) return (in >> db), true;
    db = json::object();
    return false;
}
void save(){
    ofstream(FILE) << db.dump(4);
}
string get(str id, str name){
    return db.value(id, json{}).value(name, "");
}
bool verified(){
    cout << "Enter password: ";
    cin >> input;
    return get(ID, "key") == input;
}
void newPassword(){
    cout << "Enter a new password: ";
    cin >> input;
    db[ID]["key"] = input;
}
void newAccount(){
    cout << "The Account doesn't exist\n";
    options({"Create Account"});
    if(input != "1") return;
    newPassword();
    db[ID]["money"] = "0";
    save();
    cout << "Account created successfully.";
}

int main(int argc, char *argv[]){
    if(argc < 2) return 0;
    load();
    ID = argv[1];
    if(!db.contains(ID)){
        newAccount(); 
        return 0;
    }
    if(!verified()){
        cout << "Wrong password.";
        return 0;
    }
    cout << "Balance: " << get(ID, "money") << "\n";
    options({"Send", "Change Password", "Delete Account"});
    
    if(input == "1"){
        //send money
    }
    else if(input == "2"){
        newPassword();
        save();
        cout << "Password changed.";
    }
    else if(input == "3"){
        if(stoi(get(ID, "money")) == 0){
            cout << "Type DELETE to confirm: ";
            cin >> input;
            if(input != "DELETE") return 0;
            db.erase(ID);
            save();
            cout << "Account deleted.\n";
        }
        else cout << "Account is not empty!\n";
    }
    return 0;
}