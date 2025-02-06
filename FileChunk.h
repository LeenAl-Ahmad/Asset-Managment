#ifndef FILECHUNK_H
#define FILECHUNK_H

#include "Resource.h"

class FileChunk : public Resource
{
public:
	FileChunk();
	virtual ~FileChunk();

	// Getters & Setters
	Asset* GetChunk(size_t index);
	void SetChunk(size_t index, Asset* _p);
	std::vector<Asset*>& GetChunks();

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues(int i = 0);

	static ObjectPool<FileChunk>* Pool;

private:
	std::vector<Asset*> m_chunks;
};

#endif // FILECHUNK_H
