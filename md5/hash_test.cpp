//-------------------------------
// MD5
// 2020/4/19
//-------------------------------
#include "hash_md5.h"

#include <stdio.h>

#define	FILEPATH1	"hash_md5.h"
#define	FILEPATH2	"hash_md5.cpp"
#define	FILEPATH3	"hash_test.exe"

#define	MAX_BUF		0x100000
char	g_Buf[ MAX_BUF ];

int	print_md5( char *path )
{
	FILE	*fp;
	int		len, rlen;
	char	strbuf[ 33 ];
	
	fp = fopen( path, "rb");
	if( fp ==NULL ){
		fprintf( stderr, "ERROR: Not open hash.cpp.\n");
		return 1;
	}
	
	HashMD5		md5;
	
	if( ! md5.Create()){
		fprintf( stderr, "ERROR: in Create() = %d\n", GetLastError() );
		fclose( fp );
		return 1;
	}
	while( rlen = fread( g_Buf, 1, MAX_BUF, fp ) ){
		if( rlen > 0 ){
			if( ! md5.HashData( g_Buf, rlen )){
				fprintf( stderr, "ERROR: in HashData()\n");
				fclose( fp );
				return 1;
			}
		}
	}
	fclose( fp );
	
	if( ! md5.GetHashData( strbuf, sizeof(strbuf))){
		fprintf( stderr, "ERROR: in GetHashData()\n");
		return 1;
	}
	printf("%s : [%s]\n", strbuf, path );
	return 0;
}

int main()
{
	int		i=0;
	
	static char* tbl[] = {
		FILEPATH1,
		FILEPATH2,
		FILEPATH3,
		NULL
	};
	while( tbl[i] ){
		print_md5( tbl[i] );
		++i;
	}
	return 0;
}

