#pragma	comment(lib, "Advapi32.lib")

#include "hash_md5.h"

HashMD5::HashMD5()
{
	m_hProv = 0;
	m_hHash = 0;
	
	AcquireContext();
}
HashMD5::~HashMD5()
{
	Free();
}

void	HashMD5::FreeHash()
{
	if( m_hHash ){
		CryptDestroyHash( m_hHash );
		m_hHash = 0;
	}
}
void	HashMD5::FreeProv()
{
	if( m_hProv ){
		CryptReleaseContext( m_hProv, 0);
		m_hProv = 0;
	}
}

void	HashMD5::Free()
{
	FreeHash();
	FreeProv();
}

bool	HashMD5::AcquireContext()
{
	Free();
	
	if( ! CryptAcquireContext( &m_hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)){
		return false;
	}
	return true;
}

bool	HashMD5::Create()
{
	FreeHash();
	
	if( !CryptCreateHash( m_hProv, CALG_MD5, 0, 0, &m_hHash)){
		return false;
	}
	return true;
}
void	HashMD5::Destroy()
{
	FreeHash();
}

bool	HashMD5::HashData( void* pBuf, int len )
{
	if( !CryptHashData(m_hHash, (BYTE*)pBuf, len, 0)){
		return false;
	}
	return true;
}

bool	HashMD5::GetHashData( char *poHash, int buflen )
{
	DWORD	cbHash = 0, i;
	BYTE	rgbHash[MD5LEN];
	CHAR	rgbDigits[] = "0123456789abcdef";

	cbHash = MD5LEN;
	if( ! CryptGetHashParam(m_hHash, HP_HASHVAL, rgbHash, &cbHash, 0)){
		return false;
	}
	if( (cbHash * 2 + 1) < buflen ){
		return false;
	}
	for(i=0;i<cbHash;i++){
		*poHash++ = rgbDigits[rgbHash[i] >> 4];
		*poHash++ = rgbDigits[rgbHash[i] & 0xf];
	}
	*poHash = 0;
	return true;
}
