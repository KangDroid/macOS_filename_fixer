#include <iostream>
#include <filesystem>
#include <string>

using namespace std;

string urlDecode(string &SRC) {
    string ret;
    char ch;
    int i, ii;
    for (i=0; i<SRC.length(); i++) {
        if (int(SRC[i])==37) {
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else {
            ret+=SRC[i];
        }
    }
    return (ret);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        return -1;
    }
    string file_name = argv[1];
    string converted = urlDecode(file_name);
    try {
        std::filesystem::rename(file_name, converted);
    } catch (std::filesystem::filesystem_error& e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}
