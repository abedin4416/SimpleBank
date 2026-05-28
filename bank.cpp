#include<iostream>
#include "Simpleini.h"
using namespace std;
using cc = const char*;
using cs = CSimpleIniA&;

int newAccount(cs x,cc y);
int get(cs x,cc y,cc a,cc b){return stoi(x.GetValue(y,a,b));}

int main(int argc, char* argv[]){
    if(argc > 2){
        CSimpleIniA data;
        data.SetUnicode();
        data.LoadFile("data.txt");
        string cmd = argv[2];
        bool no_acc = data.GetSection(argv[1]) == nullptr;
        if(cmd == "new") newAccount(data, argv[1]);
        else if(cmd == "send"){
            if(argc == 5){
                bool no_recipient = data.GetSection(argv[4]) == nullptr;
                if(no_acc||no_recipient){
                    cout << "Please enter valid account\n";
                }
                else {
                    int sf=get(data,argv[1],"money","0");
                    int rf=get(data,argv[4],"money","0");
                    int ra=stoi(argv[3]);
                    string se=to_string(sf-ra);
                    string re=to_string(rf+ra);
                    if(sf>=ra){
                        data.SetValue(argv[1],"money",se.c_str());
                        data.SetValue(argv[4],"money",re.c_str());
                        data.SaveFile("data.txt");
                        cout << "Transaction successful\n";
                    }
                    else cout << "Transaction failed\n";
                }
            }
        }
    }
}

int newAccount(cs x,cc y){cout << "Enter a new password:";string z; cin >> z;if(x.GetSection(y)==nullptr){
if(z!=""){x.SetValue(y,"pw",z.c_str());x.SetValue(y,"money","0");x.SaveFile("data.txt");return 0;}return 1;}return 2;}

void sendMoney(cs x, cc y){}