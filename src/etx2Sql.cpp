#include "etx2Sql.h"

/**
* descfile : descriptor file
* dirs : directories where find database and dlls
* outfile : name of file containing the result / the result into a char* variable
* tmpfile : temporary file for logs
* deffile : Definition / Queries file. 
* queryName : name of query launched
* dynQuery : A string containing a dynamic query to be launched
* queryPars : Parameters to pass to query/dynQuery
* nrep : number of results
*/
EXTERNAL
ETX2SQL_EXPORT ETXLONG QueryETXKernel  (const char& descfile, const char& dirs,   
                          char& outfile,const char& tmpfile,
													const char& deffile,const char& queryName,
                          const char& dynQuery,const char& queryPars,
                          long& nrecp)
{
	return 0;
	//TODO : Argument parser
	//TODO : file reader/writer
	//TODO : output formatter
	//TODO : properties reader
	//TODO : log system
	//TODO : exception system ??'
}