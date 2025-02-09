#include "FileChunk.h"
#include "FileController.h"

ObjectPool<FileChunk>* FileChunk::Pool;

FileChunk::FileChunk()
{
    
}

FileChunk::~FileChunk() {}

void FileChunk::AssignNonDefaultValues(int i) {
    std::string chunkPath = "C:/Users/leana/source/repos/Lab3/Assets/FileChunk/chunk" + std::to_string(i) + ".bin";

    if (m_chunks.size() <= i) {
        m_chunks.resize(i + 1, nullptr);
    }

    Asset* chunkAsset = GetChunk(i);
    if (!chunkAsset) {
        chunkAsset = Asset::Pool->GetResource();
        if (chunkAsset) {
            chunkAsset->SetGUID(chunkPath);

            size_t dataSize = FileController::Instance().GetFileSize(chunkPath);
            chunkAsset->SetDataSize(dataSize);

            byte* buffer = new byte[dataSize];
            if (!buffer) {
                std::cerr << "Error: Memory allocation failed for chunk " << i << ".bin" << std::endl;
                return;
            }
            chunkAsset->SetData(buffer);

            FileController::Instance().ReadFile(chunkPath, chunkAsset->GetData(), dataSize);

            std::cout << "Allocating asset chunk " << i << ".bin" << std::endl;
            SetChunk(i, chunkAsset);  // Assign the chunk directly without push_back
        }
        else {
            std::cerr << "Failed to allocate asset for chunk: " << chunkPath << std::endl;
        }
    }

    else {
        std::cout << "Asset already exists for chunk " << i << ".bin, skipping allocation" << std::endl;
    }

    Resource::AssignNonDefaultValues();
}

void FileChunk::Serialize(std::ostream& _stream) {
    for (auto& chunk : m_chunks) {
        if (chunk == nullptr) {
            std::cerr << "Error: Null chunk encountered during serialization." << std::endl;
            return;
        }
        SerializeAsset(_stream, chunk);
    }

    Resource::Serialize(_stream);
}

void FileChunk::ClearChunks() { 
    for (Asset* asset : m_chunks) {
        if (asset) {
            Asset::Pool->ReleaseResource(asset);
        }
    }
    m_chunks.clear();  // Clear after releasing
}

void FileChunk::Deserialize(std::istream& _stream) {
    for (auto& chunk : m_chunks) {
        DeserializeAsset(_stream, chunk);
    }
    Resource::Deserialize(_stream);
}

void FileChunk::ToString() {
    std::cout << "FileChunk" << std::endl;
    for (auto& chunk : m_chunks) {
        if (chunk) chunk->ToString();
    }
    Resource::ToString();
}

void FileChunk::SetChunk(size_t index, Asset* _p) {
    if (index < m_chunks.size()) {
        m_chunks[index] = _p;
    }
    else {
        m_chunks.push_back(_p);
    }
}

std::vector<Asset*>& FileChunk::GetChunks() {
    return m_chunks;
}

void FileChunk::LoadMetadata() {
    if (m_chunks.empty()) {
        std::cerr << "Error: No chunk data available to read metadata.\n";
        return;
    }

    std::ifstream file(m_chunks[0]->GetGUID(), std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open chunk file to read metadata.\n";
        return;
    }

    file.seekg(12, std::ios::beg);  // TGA width starts at byte 12

    uint16_t width = 0, height = 0;
    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));

    m_width = static_cast<size_t>(width);
    m_height = static_cast<size_t>(height);

    if (m_width == 0 || m_height == 0) {
        std::cerr << "Error: Invalid width or height read from chunk metadata.\n";
    }
    else {
        std::cout << "Chunk Metadata Loaded: Width = " << m_width << ", Height = " << m_height << "\n";
    }

    file.close();
}

