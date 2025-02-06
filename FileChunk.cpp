#include "FileChunk.h"
#include "FileController.h"

ObjectPool<FileChunk>* FileChunk::Pool = nullptr;

FileChunk::FileChunk()
{
    cout << "Creating new pool object: class FileChunk" << endl;
}

FileChunk::~FileChunk() {}

void FileChunk::AssignNonDefaultValues() {
    for (int i = 0; i < 7; i++) {
        std::string chunkPath = "C:/Users/leana/source/repos/Lab3/Assets/FileChunk/chunk" + std::to_string(i) + ".bin";
        std::cout << "Loading chunk: " << chunkPath << std::endl;

        // Allocate new Asset from pool
        Asset* chunkAsset = Asset::Pool->GetResource();
        std::cout << "Creating new pool object: class Asset" << endl;

        if (chunkAsset) {
            chunkAsset->SetGUID(chunkPath);
            chunkAsset->SetDataSize(FileController::Instance().GetFileSize(chunkPath));
            chunkAsset->SetData(AssetController::Stack->GetMemory(chunkAsset->GetDataSize()));

            FileController::Instance().ReadFile(chunkPath, chunkAsset->GetData(), chunkAsset->GetDataSize());

            std::cout << "Allocating asset " << chunkPath << std::endl;

            m_chunks.push_back(chunkAsset); // Store in vector
        }
        else {
            std::cerr << "Failed to allocate asset for chunk: " << chunkPath << std::endl;
        }
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

Asset* FileChunk::GetChunk(size_t index) {
    return (index < m_chunks.size()) ? m_chunks[index] : nullptr;
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
