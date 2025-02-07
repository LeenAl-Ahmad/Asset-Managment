#include "Level.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    Level* level = new Level();
    level->AssignNonDefaultValues();

    ofstream writeStream("level.bin", ios::out | ios::binary);
    level->Serialize(writeStream);
    writeStream.close();

    level->ToString();
    delete level;
    cout << endl;

    cout << "[Q]uit [S]ave Level [L]oad Level [Z] Undo [Y] Redo\n"
        "[C]reate image buffer [D]elete image buffer [A]dd chunk [R]emove chunk\n"
        "Index ()   Undo count ()   Redo count ()" << endl;

    Command* c = new Command();
    string input;
    while (true) {
        cout << "Enter command: ";
        cin >> input;
        if (input == "Q" || input == "q") break;
        c->HandleInput(input);
    }
    delete c;

    return 0;
}