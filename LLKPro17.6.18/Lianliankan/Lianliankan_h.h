

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __Lianliankan_h_h__
#define __Lianliankan_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILianliankan_FWD_DEFINED__
#define __ILianliankan_FWD_DEFINED__
typedef interface ILianliankan ILianliankan;

#endif 	/* __ILianliankan_FWD_DEFINED__ */


#ifndef __Lianliankan_FWD_DEFINED__
#define __Lianliankan_FWD_DEFINED__

#ifdef __cplusplus
typedef class Lianliankan Lianliankan;
#else
typedef struct Lianliankan Lianliankan;
#endif /* __cplusplus */

#endif 	/* __Lianliankan_FWD_DEFINED__ */


#ifndef __IGameDlg_FWD_DEFINED__
#define __IGameDlg_FWD_DEFINED__
typedef interface IGameDlg IGameDlg;

#endif 	/* __IGameDlg_FWD_DEFINED__ */


#ifndef __GameDlg_FWD_DEFINED__
#define __GameDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class GameDlg GameDlg;
#else
typedef struct GameDlg GameDlg;
#endif /* __cplusplus */

#endif 	/* __GameDlg_FWD_DEFINED__ */


#ifndef __IGameHelp_FWD_DEFINED__
#define __IGameHelp_FWD_DEFINED__
typedef interface IGameHelp IGameHelp;

#endif 	/* __IGameHelp_FWD_DEFINED__ */


#ifndef __GameHelp_FWD_DEFINED__
#define __GameHelp_FWD_DEFINED__

#ifdef __cplusplus
typedef class GameHelp GameHelp;
#else
typedef struct GameHelp GameHelp;
#endif /* __cplusplus */

#endif 	/* __GameHelp_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Lianliankan_LIBRARY_DEFINED__
#define __Lianliankan_LIBRARY_DEFINED__

/* library Lianliankan */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Lianliankan;

#ifndef __ILianliankan_DISPINTERFACE_DEFINED__
#define __ILianliankan_DISPINTERFACE_DEFINED__

/* dispinterface ILianliankan */
/* [uuid] */ 


EXTERN_C const IID DIID_ILianliankan;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2FFE508F-46E5-49AC-AFCE-245C24812F75")
    ILianliankan : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ILianliankanVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILianliankan * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILianliankan * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILianliankan * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILianliankan * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILianliankan * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILianliankan * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILianliankan * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ILianliankanVtbl;

    interface ILianliankan
    {
        CONST_VTBL struct ILianliankanVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILianliankan_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILianliankan_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILianliankan_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILianliankan_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILianliankan_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILianliankan_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILianliankan_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ILianliankan_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Lianliankan;

#ifdef __cplusplus

class DECLSPEC_UUID("BDC3A4DA-E97E-49F0-9184-F8A386CFBF52")
Lianliankan;
#endif

#ifndef __IGameDlg_DISPINTERFACE_DEFINED__
#define __IGameDlg_DISPINTERFACE_DEFINED__

/* dispinterface IGameDlg */
/* [uuid] */ 


EXTERN_C const IID DIID_IGameDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F497B997-B536-44C5-830B-FD433615F5F0")
    IGameDlg : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IGameDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGameDlg * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGameDlg * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGameDlg * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGameDlg * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGameDlg * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGameDlg * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGameDlg * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IGameDlgVtbl;

    interface IGameDlg
    {
        CONST_VTBL struct IGameDlgVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGameDlg_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGameDlg_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGameDlg_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGameDlg_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGameDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGameDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGameDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IGameDlg_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GameDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("1F415D0B-FF70-4F55-9BB4-AB01C937C653")
GameDlg;
#endif

#ifndef __IGameHelp_DISPINTERFACE_DEFINED__
#define __IGameHelp_DISPINTERFACE_DEFINED__

/* dispinterface IGameHelp */
/* [uuid] */ 


EXTERN_C const IID DIID_IGameHelp;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8D810658-D053-4FF9-AA10-AE6AEE92AC9F")
    IGameHelp : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IGameHelpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGameHelp * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGameHelp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGameHelp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGameHelp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGameHelp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGameHelp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGameHelp * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IGameHelpVtbl;

    interface IGameHelp
    {
        CONST_VTBL struct IGameHelpVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGameHelp_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGameHelp_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGameHelp_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGameHelp_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGameHelp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGameHelp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGameHelp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IGameHelp_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GameHelp;

#ifdef __cplusplus

class DECLSPEC_UUID("6FF39C53-C6BB-4CB9-800B-1E6DE387FF20")
GameHelp;
#endif
#endif /* __Lianliankan_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


