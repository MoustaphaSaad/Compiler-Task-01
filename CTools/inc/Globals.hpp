#pragma once

#include <stdint.h>
#include <cstddef>
#include <fstream>
#include <string>

#if defined(WIN32)||defined(_WIN32)||defined(__WIN32__)||defined(_WIN64)||defined(WIN64)||defined(__MINGW32__)||defined(__MINGW64__)
    #define OS_WINDOWS
#elif defined(__linux__) || defined(__unix__)
    #define OS_LINUX
#endif


#ifdef OS_WINDOWS
#ifdef COMPILE_DLL
    #define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif
#endif

#ifdef OS_LINUX
    #define API
#endif

namespace CTools{
	typedef unsigned char byte;

    typedef int8_t s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef float real32;
    typedef double real64;
    
    static const u32 MEMORY_SIZE = 25 * 1024 * 1024;

	namespace IO
	{
		static std::string read(std::string path)
		{
			std::string res;
			std::ifstream file;
			file.open(path);
			std::string line;
			while(getline(file,line))
			{
				res+=line+"\n";
			}
			file.close();
			return res;
		}
	}

	class API Position
	{
	public:
		s64 absolute_location,row,col;
		Position()
		{
			absolute_location=0;
			row=0;
			col=0;
		}
		static Position UNDEFINED()
		{
			static Position p;
			p.absolute_location=-1;
			p.row = -1;
			p.col = -1;
			return p;
		}
	};

	typedef void (*errorCallback)(std::string,Position);
}