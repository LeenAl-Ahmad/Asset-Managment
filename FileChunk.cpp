#include "FileChunk.h"

ObjectPool<FileChunk>* FileChunk::Pool = nullptr;

FileChunk::FileChunk()
{
    cout << "FileChunk constructed: " << this << endl;
	m_chunk = nullptr;
}

FileChunk::~FileChunk()
{

}

void FileChunk::AssignNonDefaultValues() {
    static int chunkCounter = 0;
    std::string chunkPath = "C:/Users/leana/source/repos/Lab3/Assets/FileChunk/chunk" + std::to_string(chunkCounter) + ".bin";
    chunkCounter++;

    std::cout << "Loading chunk: " << chunkPath << std::endl;
    m_chunk = AssetController::Instance().GetAsset(chunkPath);
    Resource::AssignNonDefaultValues();
}

void FileChunk::Serialize(std::ostream& _stream)
{
    SerializeAsset(_stream, m_chunk);
    Resource::Serialize(_stream);
}

void FileChunk::Deserialize(std::istream& _stream)
{
    DeserializeAsset(_stream, m_chunk);
    Resource::Deserialize(_stream);
}

void FileChunk::ToString()
{
    cout << "FileChunk" << endl;
    m_chunk->ToString();
    Resource::ToString();
}