#pragma once
#include<string>
#include <vector>
#include "Texture.h"
#include "objPool.h"  // If ObjectPool is also a separate class

#include "BaseCommand.h"
#include "Level.h"

class FileChunk;

class Command : public Singleton<Command>
{
public:
	Command();
	~Command();
	void HandleInput(const std::string& _b, std::vector<FileChunk*>& unitVector, Level* level);
	void Undo();
	void Redo();
private:
	std::vector<BaseCommand*> m_commands;
	std::vector<BaseCommand*> m_undoneCommands;
	FileChunk* m_file;
	SDL_Event m_sdlEvent;

	ObjectPool<Texture>* m_texturePool;  // Store texture pool
	byte* m_imageBuffer;  // Store the created image buffer
	size_t m_imageSize;   // Track allocated memory size
};

