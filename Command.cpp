#include <iostream>
#include "Command.h"
#include "CommandChunk.h"
#include "Renderer.h"

Command::Command() : m_imageBuffer(nullptr), m_imageSize(0) {
    m_file = new FileChunk();
    m_texturePool = new ObjectPool<Texture>();  // Initialize texture pool
    m_sdlEvent = { };
}

Command::~Command() {
    delete m_file;
    delete m_texturePool;  // Free texture pool
    delete[] m_imageBuffer;  // Free allocated image buffer

    for (BaseCommand* cmd : m_commands) delete cmd;
    for (BaseCommand* cmd : m_undoneCommands) delete cmd;
}

void Command::HandleInput(const std::string& _b, std::vector<FileChunk*>& unitVector, Level* level) 
{  
    CommandChunk* moveCom = nullptr;

    if (_b == "S" || _b == "s"){
        std::ofstream writeStream("level.bin", std::ios::out | std::ios::binary);
        if (!writeStream) {
            std::cerr << "Error opening file for saving!\n";
            return;
        }

        level->Serialize(writeStream);
        writeStream.close();
        std::cout << "Level saved successfully.\n";
        
    }
    else if (_b == "L" || _b == "l")
    {
        std::ifstream readStream("level.bin", std::ios::in | std::ios::binary);
        if (!readStream) {
            std::cerr << "Error opening file for loading!\n";
            return;
        }
        unitVector.clear();

        level->Deserialize(readStream);
        readStream.close();

        std::cout << "Level loaded successfully.\n";
    }
    else if (_b == "Z" || _b == "z") Undo();
    else if (_b == "Y" || _b == "y") Redo();
    else if (_b == "C" || _b == "c") {
        if (unitVector.empty()) {
            std::cerr << "No file chunks available.\n";
            return;
        }

        // Calculate total size dynamically
        size_t totalSize = 0;
        for (const auto& chunk : unitVector) {
            totalSize += chunk->GetSize();  // Assume GetSize() returns byte size of chunk
        }

        // Allocate buffer and set to 0
        delete[] m_imageBuffer;  // Delete existing buffer if any
        m_imageBuffer = new byte[totalSize];
        memset(m_imageBuffer, 0, totalSize);
        m_imageSize = totalSize;

        // Save the buffer to NewImage.tga
        std::ofstream outFile("C:/Users/leana/source/repos/lab3/Assets/NewImage.tga", std::ios::binary);
        outFile.write(reinterpret_cast<char*>(m_imageBuffer), totalSize);
        if (!outFile) {
            std::cerr << "Error creating NewImage.tga\n";
            return;
        }
        outFile.write(reinterpret_cast<char*>(m_imageBuffer), totalSize);
        outFile.close();

        std::cout << "Image buffer created and saved as NewImage.tga.\n";
        AssetController::Instance().Initialize(10000000);
        Renderer* r = &Renderer::Instance();
        r->Initialize(800, 600);

        Texture::Pool = new ObjectPool<Texture>();
        Texture* texture = Texture::Pool->GetResource();
        texture->Load("C:/Users/leana/source/repos/lab3/Assets/FileChunk/BigFile.tga");

        while (m_sdlEvent.type != SDL_QUIT)
        {
            SDL_PollEvent(&m_sdlEvent);
            r->SetDrawColor(Color(255, 0, 0, 255));
            r->ClearScreen();
            r->RenderTexture(texture, Point(10, 10));
            SDL_RenderPresent(r->GetRenderer());
        }
    }

    else if (_b == "D" || _b == "d") 
    {
        if (!m_imageBuffer) {
            std::cerr << "No image buffer to delete.\n";
            return;
        }

        delete[] m_imageBuffer;
        m_imageBuffer = nullptr;
        m_imageSize = 0;

        std::cout << "Image buffer deleted.\n";
    }
    else if (_b == "A" || _b == "a") moveCom = new CommandChunk(m_file, unitVector);
    else if (_b == "R" || _b == "r") {}
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
