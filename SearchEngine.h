#ifndef SEARCHEGNINE_H
#define SEARCHEGNINE_H

#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

//include Helper class
#include "Helper.h"

using namespace std;

namespace fs = filesystem;

//For color chaning in selected text while navigation in console
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Helper helper;

class SearchEngine {
public:
    // to open a file in  the explorer
    void openInExplorer(const string& path) {
        ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
    }

    //search function
    void search() {
        string fileToSearch;
        string root;

        root = "C:/Users/god/Downloads";
        cout << "Enter file to search: ";
        getline(cin, fileToSearch);

        vector<string> results;

        try {
            int indexCounter = 1;
            cout << "Searching............." << endl;
            for(const auto& entry: fs::recursive_directory_iterator(root, fs::directory_options::skip_permission_denied)) {
                if(entry.is_regular_file()) {
                    string currentFileName = entry.path().filename().string();

                    if(helper.toLower(currentFileName).find(helper.toLower(fileToSearch)) != string::npos) {
                        // cout << indexCounter << " Found in: " << entry.path().string() << endl;

                        results.push_back(entry.path().string());
                        indexCounter++;
                    }
                }
            }
        } catch(const fs::filesystem_error& e) {
            cerr << "Error: " << e.what() << endl;
            return;
        }

        if(results.empty()) {
            cout << "No results found.\n";
            return;
        }

        int selected = 0;

        while(true) {
            system("cls");

            cout << "Results:\n";
            for(int i = 0; i < results.size(); i++) {
                if(i == selected){
                    //set color to blue
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    cout << ">";
                    cout << fs::path(results[i]).filename().string() << endl;
                    //reset color to light gray
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                } else{
                    cout << fs::path(results[i]).filename().string() << endl;
                }
            }

            int ch = _getch();
            if(ch == 224) {
                int arrow = _getch();
                if(arrow == 72 && selected > 0) selected--; //up
                else if(arrow == 80 && selected < results.size() - 1)  selected++; // down
            } else if(ch == 13) {
                //enter
                openInExplorer(results[selected]);
                cout << "Opening";
                return;
            }
        }
    }    
};

#endif