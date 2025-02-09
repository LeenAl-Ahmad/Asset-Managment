#include <iostream>
#include <fstream>
#include <cstring>
#include "Command.h"
#include "CommandChunk.h"
#include "Renderer.h"

Command::Command() : m_imageBuffer(nullptr), m_imageSize(0) {
    m_file = new FileChunk();
    m_texturePool = new ObjectPool<Texture>();  // Initialize texture pool
    m_sdlEvent = {};
}

Command::~Command() {
    delete m_file;
    delete m_texturePool;  // Free texture pool
    delete[] m_imageBuffer;  // Free allocated image buffer

    for (BaseCommand* cmd : m_commands) delete cmd;
    for (BaseCommand* cmd : m_undoneCommands) delete cmd;
}

void Command::HandleInput(const std::string& _b, std::vector<FileChunk*>& unitVector, Level* level) {
    CommandChunk* moveCom = nullptr;

    if (_b == "S" || _b == "s") {
        std::ofstream writeStream("level.bin", std::ios::binary);
        if (!writeStream) {
            std::cerr << "Error: Could not open level.bin for saving.\n";
            return;
        }
        level->Serialize(writeStream);
        std::cout << "Level saved successfully.\n";
    }
    else if (_b == "L" || _b == "l") {
        std::ifstream readStream("level.bin", std::ios::binary);
        if (!readStream) {
            std::cerr << "Error: Could not open level.bin for loading.\n";
            return;
        }
        level->Deserialize(readStream);
        level->AssignNonDefaultValues();
        std::cout << "Level loaded successfully.\n";
    }
    else if (_b == "Z" || _b == "z") {
        Undo();
    }
    else if (_b == "Y" || _b == "y") {
        Redo();
    }
    else if (_b == "C" || _b == "c") {
        if (unitVector.empty()) {
            std::cerr << "No file chunks available.\n";
            return;
        }

        // Calculate total size dynamically
        size_t totalSize = 0;
        for (const auto& chunk : unitVector) {
            totalSize += chunk->GetSize();
        }

        // Allocate and initialize buffer
        delete[] m_imageBuffer;  // Free previous buffer if exists
        m_imageBuffer = new uint8_t[totalSize]();
        m_imageSize = totalSize;

        // Save buffer to NewImage.tga
        std::ofstream outFile("C:/Users/leana/source/repos/lab3/Assets/NewImage.tga", std::ios::binary);
        if (!outFile) {
            std::cerr << "Error: Could not create NewImage.tga.\n";
            return;
        }
        outFile.write(reinterpret_cast<char*>(m_imageBuffer), totalSize);
        outFile.close();

        std::cout << "Image buffer created and saved as NewImage.tga.\n";

        // Initialize Rendering
        AssetController::Instance().Initialize(10000000);
        Renderer* renderer = &Renderer::Instance();
        renderer->Initialize(800, 600);

        Texture::Pool = new ObjectPool<Texture>();
        Texture* texture = Texture::Pool->GetResource();
        if (texture) {
            texture->Load("C:/Users/leana/source/repos/lab3/Assets/FileChunk/BigFile.tga");
        }
        else {
            std::cerr << "Error: Failed to load texture.\n";
            return;
        }

        while (m_sdlEvent.type != SDL_QUIT) {
            SDL_PollEvent(&m_sdlEvent);
            renderer->SetDrawColor(Color(255, 0, 0, 255));
            renderer->ClearScreen();
            renderer->RenderTexture(texture, Point(10, 10));
            SDL_RenderPresent(renderer->GetRenderer());
        }
    }
    else if (_b == "D" || _b == "d") {
        if (!m_imageBuffer) {
            std::cerr << "No image buffer to delete.\n";
            return;
        }

        delete[] m_imageBuffer;
        m_imageBuffer = nullptr;
        m_imageSize = 0;

        std::cout << "Image buffer deleted.\n";
    }
    else if (_b == "A" || _b == "a") {
        moveCom = new CommandChunk(m_file, unitVector);
    }
    else if (_b == "R" || _b == "r") {
        if (!m_imageBuffer || m_imageSize == 0) {
            std::cerr << "No image buffer to remove chunks from.\n";
            return;
        }

        if (unitVector.empty()) {
            std::cerr << "No chunks to remove.\n";
            return;
        }

        // Find last chunk and remove it
        FileChunk* lastChunk = unitVector.back();
        size_t lastSize = lastChunk->GetSize();
        size_t offset = m_imageSize - lastSize;

        memset(m_imageBuffer + offset, 0, lastSize);
        unitVector.pop_back();
        m_imageSize -= lastSize;

        std::cout << "Removed last added chunk from buffer.\n";
    }
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

    std::cout << "Undo successful.\n";
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

    std::cout << "Redo successful.\n";
}
