#ifndef COMMAND_H
#define COMMAND_H

#include <stack>

// Base Command Interface
class Command {
public:
    virtual ~Command() {}
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual bool IsUndoable() const { return true; }  // Default: commands are undoable
};

// Command Manager to handle undo/redo
class CommandManager {
private:
    std::stack<Command*> undoStack;
    std::stack<Command*> redoStack;

public:
    void ExecuteCommand(Command* command) {
        command->Execute();
        if (command->IsUndoable()) {
            undoStack.push(command);
            while (!redoStack.empty()) redoStack.pop(); // Clear redo stack on new command
        }
        else {
            delete command; // One-time commands should be deleted immediately
        }
    }

    void Undo() {
        if (!undoStack.empty()) {
            Command* command = undoStack.top();
            undoStack.pop();
            command->Undo();
            redoStack.push(command);
        }
    }

    void Redo() {
        if (!redoStack.empty()) {
            Command* command = redoStack.top();
            redoStack.pop();
            command->Execute();
            undoStack.push(command);
        }
    }

    int GetUndoCount() const { return undoStack.size(); }
    int GetRedoCount() const { return redoStack.size(); }
};

#endif // COMMAND_H
