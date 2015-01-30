// Generic helper definitions for shared library support
#ifndef _ETX2SQL_DLLDEFINES_H_
#define _ETX2SQL_DLLDEFINES_H_

#if defined _WIN32 || defined _WINDOWS
	/* #define ETX2SQL_DLL_IMPORT __declspec(dllimport)
	#define ETX2SQL_DLL_EXPORT __declspec(dllexport)
	#define ETX2SQL_DLL_LOCAL*/
#ifdef QueryTranslate_SHARED
	#define EXTERNAL extern "C"
	#define EXTERNAL_CPP extern
	#ifdef QueryTranslate_EXPORTS
		#define ETX2SQL_EXPORT __declspec(dllexport)
	#else	
		#define ETX2SQL_EXPORT __declspec(dllimport)
	#endif
#else
	#define EXTERNAL
	#define EXTERNAL_CPP
	#define ETX2SQL_EXPORT 
#endif
	
#else
	/*#if __GNUC__ >= 4
	#define ETX2SQL_DLL_IMPORT __attribute__ ((visibility ("default")))
	#define ETX2SQL_DLL_EXPORT __attribute__ ((visibility ("default")))
	#define ETX2SQL_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
	#else
	#define ETX2SQL_DLL_IMPORT
	#define ETX2SQL_DLL_EXPORT
	#define ETX2SQL_DLL_LOCAL
	#endif*/
	#define ETX2SQL_EXPORT
#endif

#ifdef __cplusplus

	#define ETXLONG  long

#else

	#define ETXLONG long

#endif

EXTERNAL
ETX2SQL_EXPORT ETXLONG QueryETXKernel   (const char& descfile, const char& dirs,   
                          char& outfile,const char& tmpfile,
													const char& deffile,const char& queryName,
                          const char& dynQuery,const char& queryPars,
                          long& nrecp); 

#endif /* _ETX2SQL_DLLDEFINES_H_ */