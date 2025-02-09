#pragma once

#ifndef ASSET_H
#define ASSET_H

#include "StandardInclude.h"
#include "objPool.h"

class Asset
{
public:
	Asset();
	virtual ~Asset() {}

	string GetGUID() { return m_GUID; }
	void SetGUID(string _g) { m_GUID = _g; }
	int GetDataSize() { return m_dataSize; }
	void SetDataSize(int _s) { m_dataSize = _s; }
	byte* GetData() { return m_data; }
	void SetData(byte* _d) { m_data = _d; }

	void ToString();
	static ObjectPool<Asset>* Pool;

	virtual void Serialize(std::ostream& _stream) {
		// Serialize the Asset data (e.g., GUID, data size, etc.)
		_stream.write(reinterpret_cast<char*>(&m_GUID), sizeof(m_GUID));
		_stream.write(reinterpret_cast<char*>(&m_dataSize), sizeof(m_dataSize));
		_stream.write(reinterpret_cast<char*>(m_data), m_dataSize);  // Assuming m_data is a pointer to the asset's binary data
	}

private:
	string m_GUID;
	int m_dataSize;
	byte* m_data;
};

#endif // !ASSET_h

