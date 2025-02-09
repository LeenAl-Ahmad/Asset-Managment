
#include "Command.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    Level* level = new Level();
    level->AssignNonDefaultValues();

    ofstream writeStream("level.bin", ios::out | ios::binary);
    writeStream.close();

    level->ToString();
    cout << endl;

    Command* c = new Command();
    string input;

    while (true) {
        cout << "[Q]uit [S]ave Level [L]oad Level [Z] Undo [Y] Redo\n"
            "[C]reate image buffer [D]elete image buffer [A]dd chunk [R]emove chunk\n"
            "Index (" << level->index << ")   Undo count ()   Redo count ()" << endl;
        cin >> input;
        if (input == "Q" || input == "q") break;
        
        // Pass Level's m_unit vector to Command
        c->HandleInput(input, level->GetUnitVector(), level);
    }

    delete c;
    delete level;
    return 0;
}
