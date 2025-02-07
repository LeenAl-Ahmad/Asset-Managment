#include "Level.h"

int main()
{
    Level* level = new Level();
    level->AssignNonDefaultValues();

    ofstream writeStream("level.bin", ios::out | ios::binary);
    level->Serialize(writeStream);
    writeStream.close();
    //cout << "Level To Save: ";
    level->ToString();
    delete level;
    cout << endl;

    cout << "[Q]uit [S]ave Level [L]oad Level [Z] Undo [Y] Redo\n[C]reate image buffer [D]elete image buffer [A]dd chunk [R]emove chunk\nIndex (" << ")   Undo count (" << ")   Redo count(" << ")" << endl;
    /*Level* loadedLevel = new Level();
    ifstream readStream("level.bin", ios::in | ios::binary);
    loadedLevel->Deserialize(readStream);
    readStream.close();
    //cout << "Loaded Level: ";
    loadedLevel->ToString();
    delete loadedLevel;*/

    
}
