#ifndef UNIT_H
#define UNIT_H

#include "Resource.h"
#include "FileChunk.h"

class Unit : public Resource
{
public:
    // Constructors/Destructors
    Unit();
    virtual ~Unit();

    // Methods
    void Serialize(std::ostream& _stream) override;
    void Deserialize(std::istream& _stream) override;
    void ToString() override;
    void AssignNonDefaultValues() override;

    // Members
    static ObjectPool<Unit>* Pool;

private:
    // Members
    FileChunk* m_file;
};

#endif // UNIT_H
