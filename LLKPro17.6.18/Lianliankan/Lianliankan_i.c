

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Jun 20 01:15:54 2017
 */
/* Compiler settings for Lianliankan.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_Lianliankan,0x834E1909,0x6896,0x40ED,0xB3,0x53,0x8E,0xCF,0xBE,0x6B,0x3E,0xA8);


MIDL_DEFINE_GUID(IID, DIID_ILianliankan,0x2FFE508F,0x46E5,0x49AC,0xAF,0xCE,0x24,0x5C,0x24,0x81,0x2F,0x75);


MIDL_DEFINE_GUID(CLSID, CLSID_Lianliankan,0xBDC3A4DA,0xE97E,0x49F0,0x91,0x84,0xF8,0xA3,0x86,0xCF,0xBF,0x52);


MIDL_DEFINE_GUID(IID, DIID_IGameDlg,0xF497B997,0xB536,0x44C5,0x83,0x0B,0xFD,0x43,0x36,0x15,0xF5,0xF0);


MIDL_DEFINE_GUID(CLSID, CLSID_GameDlg,0x1F415D0B,0xFF70,0x4F55,0x9B,0xB4,0xAB,0x01,0xC9,0x37,0xC6,0x53);


MIDL_DEFINE_GUID(IID, DIID_IGameHelp,0x8D810658,0xD053,0x4FF9,0xAA,0x10,0xAE,0x6A,0xEE,0x92,0xAC,0x9F);


MIDL_DEFINE_GUID(CLSID, CLSID_GameHelp,0x6FF39C53,0xC6BB,0x4CB9,0x80,0x0B,0x1E,0x6D,0xE3,0x87,0xFF,0x20);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



