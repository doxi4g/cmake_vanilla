#ifndef __INC_LZO_MANAGER_H
#define __INC_LZO_MANAGER_H

#include "lzo/lzoconf.h"
#include "lzo/lzodefs.h"
#include "lzo/lzoutil.h"
#include "lzo/lzo1x.h"

class LZOManager : public singleton<LZOManager>
{
	public:
		LZOManager();
		virtual ~LZOManager();

		bool	Compress(const BYTE* src, size_t srcsize, BYTE* dest, lzo_uint * puiDestSize);
		bool	Decompress(const BYTE* src, size_t srcsize, BYTE* dest, lzo_uint * puiDestSize);
		size_t	GetMaxCompressedSize(size_t original);

		BYTE *	GetWorkMemory() { return m_workmem; }

	private:
		BYTE *	m_workmem;
};

#endif
