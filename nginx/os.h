
#pragma once 

#ifdef DLL_IMPLEMENTATION 
#define DLL_API __declspec(dllexport)
#else 
#define DLL_API __declspec(dllimport)
#endif 

DLL_API int add(int, int); 
