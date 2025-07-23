#include <bits/stdc++.h>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Incorrect number of arguments\n";
        return 1;
    }

    string encodedFile = argv[1];
    ifstream inFile(encodedFile, ios::binary);
    if (!inFile) {
        cerr << "Failed to open encoded file.\n";
        return 1;
    }

    int mapSize;
    inFile >> mapSize;
    inFile.get(); 

    unordered_map<string, char> decodeMap;
    for (int i = 0; i < mapSize; ++i) {
        char ch;
        string code;
        inFile.get(ch);  
        inFile.get();     
        getline(inFile, code);
        decodeMap[code] = ch;
    }

  
    string outFileName = "decocded-"+encodedFile.substr(0, encodedFile.find_last_of('.')) ;

    ofstream outFile(outFileName);
    if (!outFile) {
        cerr << "Failed to create output file\n";
        return 1;
    }

   
    string currentCode = "";
    char byte;
    while (inFile.read(&byte, 1)) {
        uint8_t b = static_cast<uint8_t>(byte);
        for (int i = 7; i >= 0; --i) {
            char bit = ((b >> i) & 1) + '0';
            currentCode += bit;
            if (decodeMap.count(currentCode)) {
                outFile << decodeMap[currentCode];
                currentCode.clear();
            }
        }
    }

    cout << "Decompressed file written to: " << outFileName << endl;
    return 0;
}

