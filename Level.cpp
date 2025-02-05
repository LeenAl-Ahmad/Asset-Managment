#include "Level.h"

Level::Level() {
    AssetController::Instance().Initialize(10000000); // Allocate 10MB
    Unit::Pool = new ObjectPool<Unit>();
    SoundEffect::Pool = new ObjectPool<SoundEffect>();

    m_mapSizeX = 0;
    m_mapSizeY = 0;
    m_gameTime = 0.0f;
    m_unit.clear();
    m_file = nullptr;
}

Level::~Level() {
    m_unit.clear();
    delete SoundEffect::Pool;
    delete Unit::Pool;
    AssetController::Instance().Clear(); // Free 10MB
}

void Level::AssignNonDefaultValues() {
    m_mapSizeX = 128;
    m_mapSizeY = 256;
    m_gameTime = 10.5f;
    for (int count = 0; count < 5; count++)
    {
        Unit* unit = Unit::Pool->GetResource();
        unit->AssignNonDefaultValues();
        m_unit.push_back(unit);
    }
    
    Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {
    _stream.write(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
    _stream.write(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));
    _stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
    int numberOfUnits = m_unit.size();
    _stream.write(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
    for (int count = 0; count < numberOfUnits; count++)
    {
        SerializePointer(_stream, m_unit[count]);
    }
    Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
    _stream.read(reinterpret_cast<char*>(&m_mapSizeX), sizeof(m_mapSizeX));
    _stream.read(reinterpret_cast<char*>(&m_mapSizeY), sizeof(m_mapSizeY));
    _stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
    
    int numberOfUnits;
    _stream.read(reinterpret_cast<char*>(&numberOfUnits), sizeof(numberOfUnits));
    for (int count = 0; count < numberOfUnits; count++)
    {
        Unit* unit;
        DeserializePointer(_stream, unit);
        m_unit.push_back(unit);
    }
    Resource::Deserialize(_stream);
}

void Level::ToString() {
    cout << "LEVEL" << endl;
    cout << "MapSizeX: " << m_mapSizeX << endl;
    cout << "MapSizeY: " << m_mapSizeY << endl;
    cout << "GameTime: " << m_gameTime << endl;
    for (int count = 0; count < m_unit.size(); count++)
    {
        m_unit[count]->ToString();
    }
    Resource::ToString();
}
