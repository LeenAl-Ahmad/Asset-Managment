#include "Level.h"

Level::Level() {
    AssetController::Instance().Initialize(10000000); // Allocate 10MB
    //
    m_file = nullptr;
}

Level::~Level() {
    //
    // Clean up FileChunk
    if (m_file) {
        delete m_file;
    }
    //
    AssetController::Instance().Clear(); // Free 10MB
}

void Level::AssignNonDefaultValues() {
    //
    // Create and assign a default FileChunk
    m_file = new FileChunk();
    m_file->AssignNonDefaultValues();
    
    Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {
    //
    // Serialize FileChunk
    if (m_file) {
        m_file->Serialize(_stream);
    }
    else {
        // Write a flag to indicate no FileChunk
        bool hasFileChunk = false;
        _stream.write(reinterpret_cast<char*>(&hasFileChunk), sizeof(hasFileChunk));
    }
    Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
    //
    bool hasFileChunk;
    _stream.read(reinterpret_cast<char*>(&hasFileChunk), sizeof(hasFileChunk));
    if (hasFileChunk) {
        if (!m_file) {
            m_file = new FileChunk();
        }
        m_file->Deserialize(_stream);
    }
    else {
        if (m_file) {
            delete m_file;
            m_file = nullptr;
        }
    }

    Resource::Deserialize(_stream);
}

void Level::ToString() {
    //
    // Print FileChunk
    if (m_file) {
        m_file->ToString();
    }
    else {
        cout << "FileChunk: nullptr" << endl;
    }
    Resource::ToString();
}
