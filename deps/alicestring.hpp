#include <iostream>
#include <sstream>
#include <string>
#include <vector>


namespace alice {
    std::vector<std::string> split(std::string inputstring, char delim) {
        using namespace std;
        std::stringstream stream(inputstring);
        std::string tempstring;
        std::vector<string> returnvector;
        while (getline(stream, tempstring, delim)) {
            returnvector.push_back(tempstring);
        }
        return returnvector;
    }
    std::vector<std::string> split(std::string inputstring) {
        return split(inputstring, '\n');
    }
}