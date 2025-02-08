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

    std::vector<FileChunk*>& GetUnitVector() { return m_unit; }
private:
    // Members
    int m_mapSizeX;
    int m_mapSizeY;
    float m_gameTime;
    vector<FileChunk*> m_unit;
};

#endif // LEVEL_H
