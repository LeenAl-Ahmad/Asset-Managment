#ifndef FILECHUNK_H
#define FILECHUNK_H

#include "Resource.h"

class FileChunk : public Resource
{
public:
	FileChunk();
	virtual ~FileChunk();

	Asset* GetChunk() { return m_chunk; }
	void SetChunk(Asset* _p) { m_chunk = _p; }

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

	static ObjectPool<FileChunk>* Pool;

	private:
		Asset* m_chunk;
};

#endif //FILECHUNK_H