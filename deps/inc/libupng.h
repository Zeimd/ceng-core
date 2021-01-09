// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBUPNG_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBUPNG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifndef LIBUPNG_H
#define LIBUPNG_H

#ifdef LIBUPNG_EXPORTS
#define LIBUPNG_API __declspec(dllexport)
#else
#define LIBUPNG_API __declspec(dllimport)
#endif

#endif
