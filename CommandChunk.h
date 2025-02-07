#pragma once
#include "Command.h"
#include "FileChunk.h"

class CommandChunk : public BaseCommand
{
public:
	CommandChunk(FileChunk* _u)
	{
		/*m_file = _u;
		m_xBefore = 0;
		m_yBefore = 0;
		m_x = _x;
		m_y = _y;*/
	}

	virtual void Execute()
	{
		/*m_xBefore = m_file->GetX();
		m_yBefore = m_file->GetY();
		m_file->MoveTo(m_x, m_y);*/
	}

	virtual void Undo()
	{
		/*m_file->MoveTo(m_xBefore, m_yBefore);*/
	}
private:
	FileChunk* m_file;
	int m_xBefore;
	int m_yBefore;
	int m_x;
	int m_y;
};