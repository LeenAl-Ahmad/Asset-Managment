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

	//Methods 
	virtual void Serialize(std::ostream& _s);
	virtual void Deserialize(std::istream& _s);
	virtual void ToString();
	virtual void AssignNonDefaultValues();

	static ObjectPool<FileChunk>* Pool;

	private:
		Asset* m_chunk;
};

#endif //FILECHUNK_H