#ifndef LEVEL_H
#define LEVEL_H

#include "FileChunk.h"

class Level : public Resource {
public:
    // Constructors / Destructors
    Level();
    virtual ~Level();

    // Methods
    void Serialize(std::ostream& _stream) override;
    void Deserialize(std::istream& _stream) override;
    void ToString() override;
    void AssignNonDefaultValues() override;

private:
    //
    
    FileChunk* m_file;
};

#endif // LEVEL_H
