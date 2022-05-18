
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <openssl/sha.h>


using namespace std;
using namespace nlohmann;

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
bool isNumber(const string& str) {
    for (char const &c : str) {
        if (std::isdigit(c) == 0 && c != '.') return false;
    }
    return true;
}

void accessloop(json jsonData, string username) {
    while (true) {
        cout << "\033[2J\033[1;1H" // flush screen
            << "what would you like to do today?\n"
            << "1. deposit\n"
            << "2. withdraw\n"
            << "3. commit changes\n";
        if (jsonData.contains("money")) 
            cout << "You have " << jsonData["money"] << " dollars\n";

        ofstream filewrite; 
        string choice;
        cin >> choice;
        string value;
        
        while (!isNumber(choice)) {
            cout << "Invalid number, try again:\n";
            cin >> choice;
        }
        
        switch (stoi(choice)) {
            case 1: // deposit
                cout << "how much would you like to deposit?\n";
                cin >> value;
                if (isNumber(value)) {
                    if (jsonData.contains("money")) {
                        jsonData["money"] = (double)jsonData["money"] + stod(value);
                        cout << "you now have " << jsonData["money"] << " dollars\n";
                    } else {
                        jsonData["money"] = stod(value);
                    }
                } else {
                    cout << "invalid number\n";
                }
                break;
            case 2: // withdrawing
                cout << "how much would you like to withdraw?\n";
                cin >> value;
                if (isNumber(value)) {
                    if (jsonData.contains("money")) {
                        jsonData["money"] = (double)jsonData["money"] - stod(value);
                        cout << "you now have " << jsonData["money"] << " dollars\n"; 
                    } else {
                        jsonData["money"] = value;
                    }
                } else {
                    cout << "invalid number\n";
                }
                break;
            case 3: // writing file 
                filewrite.open(string(string("db/") + username + "/data.json"), ios::trunc);
                filewrite << jsonData;
                filewrite.close();
                cout << "commiting changes";
                break;
            case 0:
                cout << "no choice\n";
                break;
        }

    }
}

int main() {
    mkdir("db", 0777);
    string username;
    cout << "What is your username?\n";
    cin >> username;
    mkdir(string(string("db/") + username).c_str(), 0777);
    fstream file(string(string("db/") + username + "/data.json"));
    stringstream stringdata;
    string line;
    if(file.is_open()) {  // write all the file data to a string
        while (getline(file,line)) {
            stringdata << line << "\n";
        
        }
        file.close();
    } else { // if no file just make an empty json string
        stringdata << "{}";
    }

    // password checking/sign up process
    json jsondata = json::parse(stringdata.str());
    cout << "what is your password?" << "\n";
    string password;
    cin >> password;
    if (jsondata.contains("password")) { 
        if (jsondata["password"] == sha256(password)) {
            cout << "access granted\n";
            accessloop(jsondata, username);
        }
    } else {
        cout << "This is your first login, please create a password\n";
        cin >> password;
        jsondata["password"] = sha256(password);
        ofstream filewrite(string(string("db/") + username + "/data.json"), ios::trunc);
        filewrite << jsondata;
        filewrite.close();
        accessloop(jsondata, username);
    }


    return 0;
}