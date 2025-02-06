#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit()
{
    m_file = nullptr;
}

Unit::~Unit()
{
}

void Unit::AssignNonDefaultValues()
{
    m_file = FileChunk::Pool->GetResource();
    m_file->AssignNonDefaultValues();
    Resource::AssignNonDefaultValues();
}

void Unit::Serialize(std::ostream& _stream)
{
    SerializePointer(_stream, m_file);
    Resource::Serialize(_stream);
}

void Unit::Deserialize(std::istream& _stream)
{
    DeserializePointer(_stream, m_file);
    Resource::Deserialize(_stream);
}

void Unit::ToString()
{
    cout << "UNIT" << endl;
    m_file->ToString();
    Resource::ToString();
}
