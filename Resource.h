#ifndef RESOURCE_H
#define RESOURCE_H

#include "Serializable.h"
#include "AssetController.h"

class Resource : public Serializable
{
public:
    // Constructor/Destructor
    Resource();
    virtual ~Resource();

    // Methods
    virtual void Serialize(std::ostream& _stream);
    virtual void Deserialize(std::istream& _stream);
    void AssignNonDefaultValues();
    void ToString();

    //members
    static ObjectPool<Resource>* Pool;

protected:
    void SerializePointer(std::ostream& _stream, Resource* _p);
    void DeserializePointer(std::istream& _stream, Resource*& _p);
    void SerializeAsset(std::ostream& _s, Asset* _a);
    void DeserializeAsset(std::istream& _s, Asset*& _a);

private:
    int m_val1;
    double m_val2;
    char m_val3;
    Resource* m_subResource;
    Asset* m_asset;
};

#endif // RESOURCE_H
