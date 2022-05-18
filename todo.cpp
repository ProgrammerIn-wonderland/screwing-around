#include <iostream>
#include <fstream>
#include <list>
#include <ostream>
#include <sstream>
#include <string>


using namespace std;

list<string> todo;
list<string> done;

void writefile() {
    ofstream file("todo.txt", ios::trunc);
    for (string item: todo) {
        file << item << endl;
    }
    file << "---" << endl;
    for (string item: done) {
        file << item << endl;
    }
    file.close();

}

void readfile() {
    ifstream file("todo.txt");
    
    bool todoflag = true;
    for (string line; getline(file, line); ) {
        if (todoflag) 
            if (line == "---") 
                todoflag = false;
            else 
                todo.push_back(line);
        
        if (!todoflag) 
            done.push_back(line);
        
    }

}

void repl () {
    bool doneflag;
    while (!doneflag) {
        string output = "Items todo:\n";
        for (string item: todo) {
            output += item;
            output += "\n";
        }
        output += "Items done:\n";
        for (string item: done) {
            output += item;
            output += "\n";
        }
        cout 
            << output << "\n"
            << "What would you like to do?" << "\n"
            << "1. add item" << "\n"
            << "2. mark item finished" << "\n"
            << "3. remove item" << "\n";
    }
    
}

int main() {
    readfile();


}