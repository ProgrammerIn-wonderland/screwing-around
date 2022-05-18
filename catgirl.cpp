#include "deps/alicenet.hpp"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <fstream>

using namespace std;
using namespace nlohmann;

int main() {
    alicenet request;
    // request.url = "https://nekos.life/api/v2/img/neko";
    request.url = "https://api.catboys.com/img";
    request.makeRequest();

    ofstream outputfile("image.png", ios::binary);

    request.url = json::parse(request.responseData)["url"];

    request.makeRequest();

    outputfile << request.responseData;
}