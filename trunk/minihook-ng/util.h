#ifndef __UTIL_H__
#define __UTIL_H__
#include <windows.h>
#include <fstream>
#include <cstdio>
using namespace std;

#define LOG_FILE "minihook-ng.log"

char *GetDirectoryFile(char *filename);

void init_log(HMODULE hDll);
void __cdecl add_log (const char *fmt, ...);
void deinit_log();

namespace toolkit
{
    typedef unsigned char uchar;
    typedef unsigned short ushort;
    typedef unsigned int uint;
    typedef unsigned long ulong;
    typedef unsigned long long ullong;

    typedef __int8 int8;
    typedef __int16 int16;
    typedef __int32 int32;
    typedef __int64 int64;

    typedef unsigned __int8 byte;
    typedef unsigned __int16 word;
    typedef unsigned __int32 dword;
    typedef unsigned __int64 qword;

    typedef int int_ptr;

    // Gets a member of a class by offset
    template< typename Ty >
    inline Ty& getmember( void* ptr, int_ptr offset )
    {
        return *reinterpret_cast<Ty*>( (int_ptr)ptr + offset );
    }
    template< typename Ty >
    inline const Ty& getmember( const void* ptr, int_ptr offset )
    {
        return *reinterpret_cast<const Ty*>( (int_ptr)ptr + offset );
    }

    // Make a pointer by offset
    template< typename Ty >
    inline Ty make_ptr( void* ptr, int_ptr offset )
    {
        return reinterpret_cast<Ty>( (int_ptr)ptr + offset );
    }
    template< typename Ty >
    inline const Ty make_ptr( const void* ptr, int_ptr offset )
    {
        return reinterpret_cast<const Ty>( (int_ptr)ptr + offset );
    }

    // Assign data to whatever pointer
    template< typename Ty >
    inline Ty& assign( void* ptr, const Ty& data )
    {
        *reinterpret_cast<Ty*>( ptr ) = data;
    }

    // Gets the address of a virtual function, offset is the offset of the vmt pointer
    template< typename Fn >
    inline Fn getvfunc( void* inst, int_ptr index, int_ptr offset = 0 )
    {
        return reinterpret_cast<Fn>( getmember<void**>( inst, offset )[ index ] );
    }

    // Gets the offset between 2 pointers
    inline int_ptr getoffset( const void* inst, const void* ptr )
    {
        return (int_ptr)ptr - (int_ptr)inst;
    }
    inline int_ptr getoffset( const void* inst, int_ptr ptr )
    {
        return ptr - (int_ptr)inst;
    }

};

#endif
