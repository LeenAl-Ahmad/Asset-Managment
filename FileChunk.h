#ifndef FILECHUNK_H
#define FILECHUNK_H

#include "Resource.h"

class FileChunk : public Resource
{
public:
	FileChunk();
	virtual ~FileChunk();

	// Getters & Setters
	Asset* GetChunk(size_t index) {
		if (index < m_chunks.size()) {
			return m_chunks[index];
		}
		return nullptr; 
	}
	;
	void SetChunk(size_t index, Asset* _p);
	std::vector<Asset*>& GetChunks();
	size_t GetSize() const { return m_size; }

	// Methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues(int i = 0);
	void ClearChunks();

	static ObjectPool<FileChunk>* Pool;
	
private:
	std::vector<Asset*> m_chunks;
	size_t m_size;
	byte* m_data;

	
public:
		size_t GetWidth() const { return m_width; }
		size_t GetHeight() const { return m_height; }

		void LoadMetadata();  // Reads width & height from chunk data
private:
		size_t m_width = 0;
		size_t m_height = 0;
	

};

#endif // FILECHUNK_H
