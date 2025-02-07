#pragma once
#include "Command.h"
#include "FileChunk.h"
#include <vector>

class CommandChunk : public BaseCommand
{
public:
    CommandChunk(FileChunk* _fileChunks, std::vector<FileChunk*>& _unitVector)
        : m_fileChunks(_fileChunks), m_unitVector(_unitVector), m_chunk(nullptr) {
    }

    virtual void Execute() override
    {
        m_chunk = FileChunk::Pool->GetResource(); // Create a new FileChunk
        if (m_chunk)
        {
            m_chunk->AssignNonDefaultValues(m_unitVector.size());
            m_unitVector.push_back(m_chunk);
            std::cout << "Executing: CommandAddChunk" << std::endl;
        }
        else
        {
            std::cerr << "Failed to allocate FileChunk" << std::endl;
        }
    }

    virtual void Undo() override
    {
        if (!m_unitVector.empty())
        {
            FileChunk* lastChunk = m_unitVector.back();
            m_unitVector.pop_back();
            FileChunk::Pool->ReleaseResource(lastChunk);
            std::cout << "Undo: Removed last FileChunk" << std::endl;
        }
        else
        {
            std::cerr << "No chunks to undo" << std::endl;
        }
    }

private:
    FileChunk* m_fileChunks;
    std::vector<FileChunk*>& m_unitVector;
    FileChunk* m_chunk;
};
