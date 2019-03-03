#ifndef __HASH_MD5_H__
#define __HASH_MD5_H__

#include <windows.h>
#include <wincrypt.h>

#define MD5LEN  16

class HashMD5
{
public:
	HashMD5();
	~HashMD5();
	
	void	FreeProv();
	void	FreeHash();
	void	Free();
	
	bool	AcquireContext();
	
	bool	Create();
	void	Destroy();
	
	bool	HashData( void* pBuf, int len );
	bool	GetHashData( char *poHash, int buflen );
	
protected:
	HCRYPTPROV	m_hProv;
	HCRYPTHASH	m_hHash;
	
};

#endif

