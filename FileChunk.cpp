#include "FileChunk.h"

ObjectPool<FileChunk>* FileChunk::Pool;

FileChunk::FileChunk()
{
	m_chunk = nullptr;
}

FileChunk::~FileChunk()
{

}

void FileChunk::AssignNonDefaultValues()
{
	m_chunk = AssetController::Instance().GetAsset("../Assets/FileChunk/Chunk0.bin");
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
    m_chunk->ToString();
    Resource::ToString();
}