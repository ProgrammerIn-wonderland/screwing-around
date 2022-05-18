#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

int asciitonum(char num) { // ascii numbers are at a 48 offset 
    return (int)num - 48;
}

int main() {

    map<double, string> lrcparsed; 

    ifstream lrcfile("todo.txt");
    
    stringstream lrctext;
    lrctext << lrcfile.rdbuf();

    string line;
    int i=1;

    while (getline(lrctext, line)) {
        // cout << "Line: " << i << " " << line << endl;
        double sec;
        string linetimestring;
        stringstream linestream(line);

        if (getline(linestream, linetimestring, '[')) {
            if ((getline(stringstream(line), linetimestring, ']'))) {
                linetimestring += "]";
                // cout << linetimestring << endl;
                sec = asciitonum(linetimestring.c_str()[4]) * 10 + asciitonum(linetimestring.c_str()[5]); // parse seconds
                sec += 0.1 * asciitonum(linetimestring.c_str()[7]); // add the ms first digit
                sec += 0.01 * asciitonum(linetimestring.c_str()[8]); // add the ms 2nd digit
                sec += 60 * asciitonum(linetimestring.c_str()[1]) * 10 + asciitonum(linetimestring.c_str()[2]); // add the minutes
                // cout << sec << endl;
                
                
            }

        }
        
        string content;
        getline(linestream, content, ']'); // this is just here to increment the parsing
        if (getline(linestream, content, ']')) {
            if (lrcparsed.count(sec) == 0) {
                lrcparsed[sec] = content;
            }
        }
        
        i++;
        

    }

    for(auto item: lrcparsed) {
        cout << item.first << ": " << item.second << endl; 
    }

}