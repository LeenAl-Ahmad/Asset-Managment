#include <iostream>
#include "Command.h"
#include "BaseCommand.h"
#include "FileChunk.h"
#include "CommandChunk.h"

class Quit : public BaseCommand 
{
public:
	Quit() {}

};

class Save : public BaseCommand 
{
public:
	Save() {}
	virtual void Execute() { std::cout << "Level Saved: LEVEL\n"; }
};

class Load : public BaseCommand 
{
public:
	Load() {}
	virtual void Execute() { std::cout << "Loaded Level: LEVEL\n"; }
};

class Undo : public BaseCommand 
{
public:
	Undo() {}
};

class Redo : public BaseCommand 
{
public:
	Redo() {}
};

class Create : public BaseCommand 
{
public:
	Create() {}
	virtual void Execute() { std::cout << "Executing: CommandCreateImageBuffer\n"; }
};

class Delete : public BaseCommand 
{
public:
	Delete() {}
	virtual void Execute() { std::cout << "Executing: CommandDeleteImageBuffer\n"; }
};

class Add : public BaseCommand 
{
public:
	Add() {}
	virtual void Execute() { std::cout << "Executing: CommandAddChunk\n"; }
};

class Remove : public BaseCommand 
{
public:
	Remove() {}
};

Command::Command()
{
	m_file = new FileChunk();
}

Command ::~Command()
{
	delete m_file;
}

void Command::HandleInput(std::string _b)
{
	CommandChunk* moveCom = nullptr;
	if (_b == "Q") moveCom = new CommandChunk(m_file);
	else if (_b == "S")  moveCom = new CommandChunk(m_file);
	else if (_b == "L")  moveCom = new CommandChunk(m_file);
	else if (_b == "Z")  moveCom = new CommandChunk(m_file);
	else if (_b == "Y")  moveCom = new CommandChunk(m_file);
	else if (_b == "C")  moveCom = new CommandChunk(m_file);
	else if (_b == "D")  moveCom = new CommandChunk(m_file);
	else if (_b == "A")  moveCom = new CommandChunk(m_file);
	else if (_b == "R")  moveCom = new CommandChunk(m_file);

	if (moveCom != nullptr)
	{
		moveCom->Execute();
		m_commands.push_back(moveCom);
	}
}

void Command::Undo()
{
	BaseCommand* lastCommand = m_commands.back();
	lastCommand->Undo();
	delete lastCommand;
	m_commands.pop_back();
	m_undoneCommands.push_back(lastCommand);
}

void Command::Redo()
{
	if (!m_undoneCommands.empty()) {
		BaseCommand* lastUndone = m_undoneCommands.back();
		lastUndone->Execute();
		m_undoneCommands.pop_back();
		m_commands.push_back(lastUndone);
	}
}
