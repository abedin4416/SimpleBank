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
bool exists(string id);
string get(string id, string name);
void setval(string id, string name, string value);
bool verified();
void newPassword();
void newAccount();

int main(int argc, char *argv[]){
    if(argc < 2) return 0;
    load();
    ID = argv[1];
    if(!exists(ID)){
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

bool exists(string id){
    return db.contains(id);
}

string get(string id, string name){
    if(!db.contains(id)) return "";
    if(!db[id].contains(name)) return "";
    return db[id][name].get<string>();
}

void setval(string id, string name, string value){
    db[id][name] = value;
}

bool verified(){
    cout << "Enter password: ";
    cin >> input;
    return get(ID, "key") == input;
}

void newPassword(){
    cout << "Enter a new password: ";
    cin >> input;
    setval(ID, "key", input);
}
void newAccount(){
    cout << "The Account doesn't exist\n";
    options({"Create Account"});
    if(input != "1") return;
    newPassword();
    setval(ID, "money", "0");
    save();
    cout << "Account created successfully.";
}