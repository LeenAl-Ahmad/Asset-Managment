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

            byte* buffer = new byte[dataSize];  // Allocate correct type
            if (!buffer) {
                std::cerr << "Error: Memory allocation failed for chunk " << i << ".bin" << std::endl;
                return;
            }
            chunkAsset->SetData(buffer);  // Assign buffer to Asset

            FileController::Instance().ReadFile(chunkPath, chunkAsset->GetData(), dataSize);

            std::cout << "Allocating asset chunk " << i << ".bin" << std::endl;
            SetChunk(i, chunkAsset);
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
        SerializeAsset(_stream, chunk);
    }
    Resource::Serialize(_stream);
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
    if (index < m_chunks.size())
        m_chunks[index] = _p;
    else
        m_chunks.push_back(_p);
}

std::vector<Asset*>& FileChunk::GetChunks() {
    return m_chunks;
}
