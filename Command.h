#pragma once
#include<string>
#include <vector>

#include "BaseCommand.h"

class FileChunk;

class Command
{
public:
	Command();
	~Command();
	void HandleInput(std::string _b);
	void Undo();
	void Redo();
private:
	std::vector<BaseCommand*> m_commands;
	std::vector<BaseCommand*> m_undoneCommands;
	FileChunk* m_file;
};

