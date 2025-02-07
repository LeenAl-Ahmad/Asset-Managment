#include <iostream>
#include "Command.h"
#include "CommandChunk.h"

Command::Command() {
    m_file = new FileChunk();
}

Command::~Command() {
    delete m_file;
    for (BaseCommand* cmd : m_commands) delete cmd;
    for (BaseCommand* cmd : m_undoneCommands) delete cmd;
}

void Command::HandleInput(const std::string& _b, std::vector<FileChunk*>& unitVector) 
{  
    CommandChunk* moveCom = nullptr;

    if (_b == "A" || "a"){}
    else if (_b == "S" || "s"){}
    else if (_b == "L" || "l"){}
    else if (_b == "Z" || "z") Undo();
    else if (_b == "Y" || "y") Redo();
    else if (_b == "C" || "c"){}
    else if (_b == "D" || "d") {}
    else if (_b == "A" || "a") moveCom = new CommandChunk(m_file, unitVector);
    else if (_b == "R" || "r") {}
    else {
        std::cerr << "Invalid command or not implemented.\n";
        return;
    }

    if (moveCom) {
        moveCom->Execute();
        m_commands.push_back(moveCom);
    }
}

void Command::Undo() {
    if (m_commands.empty()) {
        std::cerr << "Nothing to undo.\n";
        return;
    }

    BaseCommand* lastCommand = m_commands.back();
    lastCommand->Undo();
    m_commands.pop_back();
    m_undoneCommands.push_back(lastCommand);
}

void Command::Redo() {
    if (m_undoneCommands.empty()) {
        std::cerr << "Nothing to redo.\n";
        return;
    }

    BaseCommand* lastUndone = m_undoneCommands.back();
    lastUndone->Execute();
    m_undoneCommands.pop_back();
    m_commands.push_back(lastUndone);
}
