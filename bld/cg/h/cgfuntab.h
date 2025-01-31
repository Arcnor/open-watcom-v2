/****************************************************************************
*
*                            Open Watcom Project
*
* Copyright (c) 2002-2024 The Open Watcom Contributors. All Rights Reserved.
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


CGAPIDEF( BEMemInit,    void,           (void) )
CGAPIDEF( BEInitCg,     cg_init_info,   (cg_switches,cg_target_switches,uint,proc_revision) )
CGAPIDEF( BEInit,       cg_init_info,   (cg_switches,cg_target_switches,uint,proc_revision) )
CGAPIDEF( BEStart,      void,           (void) )
CGAPIDEF( BEStop,       void,           (void) )
CGAPIDEF( BEAbort,      void,           (void) )
CGAPIDEF( BEFini,       void,           (void) )
CGAPIDEF( BEFiniCg,     void,           (void) )
CGAPIDEF( BEMemAlloc,   pointer,        (uint) )
CGAPIDEF( BEMemFree,    void,           (pointer) )
CGAPIDEF( BEMemFini,    void,           (void) )
CGAPIDEF( BEMoreMem,    bool,           (void) )
CGAPIDEF( BEGetSeg,     segment_id,     (void) )
CGAPIDEF( BESetSeg,     segment_id,     (segment_id) )
CGAPIDEF( BEFlushSeg,   void,           (segment_id) )
CGAPIDEF( BEDefSeg,     void,           (segment_id,seg_attr,cchar_ptr,uint) )
CGAPIDEF( BENewBack,    back_handle,    (cg_sym_handle) )
CGAPIDEF( BEFiniBack,   void,           (back_handle) )
CGAPIDEF( BEFreeBack,   void,           (back_handle) )
CGAPIDEF( BEDefType,    void,           (cg_type,uint,unsigned_32) )
CGAPIDEF( BEAliasType,  void,           (cg_type,cg_type) )
CGAPIDEF( BETypeLength, unsigned_32,    (cg_type) )
CGAPIDEF( BETypeAlign,  uint,           (cg_type) )
CGAPIDEF( BEUnrollCount,unsigned_32,    (unsigned_32) )
CGAPIDEF( BENewLabel,   label_handle,   (void) )
CGAPIDEF( BEFiniLabel,  void,           (label_handle) )
CGAPIDEF( BEPatch,      patch_handle,   (void) )
CGAPIDEF( BEPatchInteger,void,          (patch_handle,signed_32) )
CGAPIDEF( BEFiniPatch,  void,           (patch_handle) )

CGAPIDEF( CGBitMask,    cg_name,        (cg_name,byte,byte,cg_type) )
CGAPIDEF( CGChoose,     cg_name,        (cg_name,cg_name,cg_name,cg_type) )
CGAPIDEF( CGIndex,      cg_name,        (cg_name,cg_name,cg_type,cg_type) )
CGAPIDEF( CGWarp,       cg_name,        (cg_name,label_handle,cg_name) )
CGAPIDEF( CG3WayControl,void,           (cg_name,label_handle,label_handle,label_handle) )
CGAPIDEF( CGFlow,       cg_name,        (cg_op,cg_name,cg_name) )
CGAPIDEF( CGPostGets,   cg_name,        (cg_op,cg_name,cg_name,cg_type) )
CGAPIDEF( CGPreGets,    cg_name,        (cg_op,cg_name,cg_name,cg_type) )
CGAPIDEF( CGLVPreGets,  cg_name,        (cg_op,cg_name,cg_name,cg_type) )
CGAPIDEF( CGSelectRestricted,void,      (sel_handle,cg_name,cg_switch_type) )
CGAPIDEF( CGUnary,      cg_name,        (cg_op,cg_name,cg_type) )
CGAPIDEF( CGBinary,     cg_name,        (cg_op,cg_name,cg_name,cg_type) )
CGAPIDEF( CGAssign,     cg_name,        (cg_name,cg_name,cg_type) )
CGAPIDEF( CGLVAssign,   cg_name,        (cg_name,cg_name,cg_type) )
CGAPIDEF( CGProcDecl,   void,           (cg_sym_handle,cg_type) )
CGAPIDEF( CGParmDecl,   void,           (cg_sym_handle,cg_type) )
CGAPIDEF( CGLastParm,   label_handle,   (void) )
CGAPIDEF( CGInitCall,   call_handle,    (cg_name,cg_type,cg_sym_handle) )
CGAPIDEF( CGAddParm,    void,           (call_handle,cg_name,cg_type) )
CGAPIDEF( CGCall,       cg_name,        (call_handle) )
CGAPIDEF( CGReturn,     void,           (cg_name,cg_type) )
CGAPIDEF( CGCompare,    cg_name,        (cg_op,cg_name,cg_name,cg_type) )
CGAPIDEF( CGControl,    void,           (cg_op,cg_name,label_handle) )
CGAPIDEF( CGDone,       void,           (cg_name) )
CGAPIDEF( CGTrash,      void,           (cg_name) )
CGAPIDEF( CGAttr,       cg_name,        (cg_name,cg_sym_attr) )
CGAPIDEF( CGVolatile,   cg_name,        (cg_name) )
CGAPIDEF( CGBigLabel,   void,           (back_handle) )
CGAPIDEF( CGBigGoto,    void,           (label_handle,int) )
CGAPIDEF( CGDuplicate,  cg_name *,      (cg_name) )
CGAPIDEF( CGType,       cg_type,        (cg_name) )
CGAPIDEF( CGEval,       cg_name,        (cg_name) )
CGAPIDEF( CGVarargsBasePtr,cg_name,     (cg_type) )

CGAPIDEF( CGCallback,   cg_name,        (cg_callback,callback_handle) )
CGAPIDEF( CGPatchNode,  cg_name,        (patch_handle,cg_type) )

CGAPIDEF( CGFloat,      cg_name,        (cchar_ptr,cg_type) )
CGAPIDEF( CGInteger,    cg_name,        (signed_32,cg_type) )
CGAPIDEF( CGInt64,      cg_name,        (signed_64,cg_type) )

CGAPIDEF( CGBackName,   cg_name,        (back_handle,cg_type) )
CGAPIDEF( CGFEName,     cg_name,        (cg_sym_handle,cg_type) )
CGAPIDEF( CGTempName,   cg_name,        (temp_handle,cg_type) )
CGAPIDEF( CGTemp,       temp_handle,    (cg_type) )
CGAPIDEF( CGAutoDecl,   void,           (cg_sym_handle,cg_type) )

CGAPIDEF( CGSelInit,    sel_handle,     (void) )
CGAPIDEF( CGSelCase,    void,           (sel_handle,label_handle,signed_32) )
CGAPIDEF( CGSelRange,   void,           (sel_handle,signed_32,signed_32,label_handle) )
CGAPIDEF( CGSelOther,   void,           (sel_handle,label_handle) )
CGAPIDEF( CGSelect,     void,           (sel_handle,cg_name) )

CGAPIDEF( DGLabel,      void,           (back_handle) )
CGAPIDEF( DGTell,       unsigned_32,    (void) )
CGAPIDEF( DGBackTell,   unsigned_32,    (back_handle) )
CGAPIDEF( DGBackPtr,    void,           (back_handle,segment_id,signed_32,cg_type) )
CGAPIDEF( DGFEPtr,      void,           (cg_sym_handle,cg_type,signed_32) )
CGAPIDEF( DGInteger,    void,           (unsigned_32,cg_type) )
CGAPIDEF( DGInteger64,  void,           (unsigned_64,cg_type) )
CGAPIDEF( DGFloat,      void,           (cchar_ptr,cg_type) )
CGAPIDEF( DGChar,       void,           (char) )
CGAPIDEF( DGString,     void,           (cchar_ptr,uint) )
CGAPIDEF( DGBytes,      void,           (unsigned_32,const void *) )
CGAPIDEF( DGIBytes,     void,           (unsigned_32,byte) )
CGAPIDEF( DGUBytes,     void,           (unsigned_32) )
CGAPIDEF( DGAlign,      void,           (uint) )
CGAPIDEF( DGSeek,       unsigned_32,    (unsigned_32) )
CGAPIDEF( DGCFloat,     void,           (pointer,cg_type) )

CGAPIDEF( DBLineNum,    void,           (uint) )
CGAPIDEF( DBModSym,     void,           (cg_sym_handle,cg_type) )
CGAPIDEF( DBLocalSym,   void,           (cg_sym_handle,cg_type) )
CGAPIDEF( DBTypeDef,    void,           (cchar_ptr,dbg_type) )
CGAPIDEF( DBLocalType,  void,           (cg_sym_handle,bool) )
CGAPIDEF( DBScalar,     dbg_type,       (cchar_ptr,cg_type) )
CGAPIDEF( DBFtnType,    dbg_type,       (cchar_ptr,dbg_ftn_type) )
CGAPIDEF( DBDereference,dbg_type,       (cg_type,dbg_type) )
CGAPIDEF( DBIndCharBlock,dbg_type,      (back_handle,cg_type,int) )
CGAPIDEF( DBLocCharBlock,dbg_type,      (dbg_loc,cg_type) )
CGAPIDEF( DBCharBlock,  dbg_type,       (unsigned_32) )
CGAPIDEF( DBCharBlockNamed, dbg_type,   (cchar_ptr,unsigned_32) )
CGAPIDEF( DBScope,      dbg_type,       (cchar_ptr) )
CGAPIDEF( DBNested,     bool,           (bool) )
CGAPIDEF( DBBegName,    dbg_name,       (cchar_ptr,dbg_type) )
CGAPIDEF( DBForward,    dbg_type,       (dbg_name) )
CGAPIDEF( DBEndName,    dbg_type,       (dbg_name,dbg_type) )
CGAPIDEF( DBArray,      dbg_type,       (dbg_type,dbg_type) )
CGAPIDEF( DBBegArray,   dbg_array,      (dbg_type,cg_type, bool) )
CGAPIDEF( DBDimCon,     void,           (dbg_array,dbg_type,signed_32,signed_32) )
CGAPIDEF( DBDimVar,     void,           (dbg_array,back_handle,int,cg_type,cg_type) )
CGAPIDEF( DBEndArray,   dbg_type,       (dbg_array) )
CGAPIDEF( DBFtnArray,   dbg_type,       (back_handle,cg_type,cg_type,int,dbg_type) )
CGAPIDEF( DBIntArray,   dbg_type,       (unsigned_32,dbg_type) )
CGAPIDEF( DBIntArrayCG, dbg_type,       (cg_type,unsigned_32,dbg_type) )
CGAPIDEF( DBSubRange,   dbg_type,       (signed_32,signed_32,dbg_type) )
CGAPIDEF( DBPtr,        dbg_type,       (cg_type,dbg_type) )
CGAPIDEF( DBBegStruct,  dbg_struct,     (cg_type,bool) )
CGAPIDEF( DBBegNameStruct,dbg_struct,   (cchar_ptr,cg_type,bool) )
CGAPIDEF( DBStructForward,dbg_type,     (dbg_struct) )
CGAPIDEF( DBAddField,   void,           (dbg_struct,unsigned_32,cchar_ptr,dbg_type) )
CGAPIDEF( DBAddBitField,void,           (dbg_struct,unsigned_32,byte,byte,cchar_ptr,dbg_type) )
CGAPIDEF( DBAddStField, void,           (dbg_struct,dbg_loc,cchar_ptr,unsigned_32,dbg_type) )
CGAPIDEF( DBAddMethod,  void,           (dbg_struct,dbg_loc,uint,uint,cchar_ptr,dbg_type) )
CGAPIDEF( DBAddNestedType,void,         (dbg_struct,cchar_ptr,dbg_type) )
CGAPIDEF( DBEndStruct,  dbg_type,       (dbg_struct) )
CGAPIDEF( DBBegEnum,    dbg_enum,       (cg_type) )
CGAPIDEF( DBAddConst,   void,           (dbg_enum,cchar_ptr,signed_32) )
CGAPIDEF( DBAddConst64, void,           (dbg_enum,cchar_ptr,signed_64) )
CGAPIDEF( DBEndEnum,    dbg_type,       (dbg_enum) )
CGAPIDEF( DBBegProc,    dbg_proc,       (cg_type,dbg_type) )
CGAPIDEF( DBAddMethParms,void,          (dbg_proc,dbg_type,dbg_type) )
CGAPIDEF( DBAddParm,    void,           (dbg_proc,dbg_type) )
CGAPIDEF( DBEndProc,    dbg_type,       (dbg_proc) )
CGAPIDEF( DBGenSym,     void,           (cg_sym_handle,dbg_loc,int) )
CGAPIDEF( DBGenStMem,   void,           (cg_sym_handle,dbg_loc) )
CGAPIDEF( DBBasedPtr,   dbg_type,       (cg_type,dbg_type,dbg_loc) )
CGAPIDEF( DBAddLocField,void,           (dbg_struct,dbg_loc,uint,byte,byte,cchar_ptr,dbg_type) )
CGAPIDEF( DBAddInheritance,void,        (dbg_struct,dbg_type,uint,uint,dbg_loc) )
CGAPIDEF( DBAddBaseInfo,void,           (dbg_struct,unsigned_32,int,dbg_type,cg_type) )
CGAPIDEF( DBAddVFuncInfo,void,          (dbg_struct,unsigned_32,int,cg_type) )
CGAPIDEF( DBLocInit,    dbg_loc,        (void) )
CGAPIDEF( DBLocSym,     dbg_loc,        (dbg_loc,cg_sym_handle) )
CGAPIDEF( DBLocTemp,    dbg_loc,        (dbg_loc,temp_handle) )
CGAPIDEF( DBLocConst,   dbg_loc,        (dbg_loc,unsigned_32) )
CGAPIDEF( DBLocOp,      dbg_loc,        (dbg_loc,dbg_loc_op,unsigned) )
CGAPIDEF( DBLocFini,    void,           (dbg_loc) )
CGAPIDEF( DBObject,     void,           (dbg_type,dbg_loc,cg_type) )
CGAPIDEF( DBSrcFile,    uint,           (cchar_ptr) )
CGAPIDEF( DBSrcCue,     void,           (uint,uint,uint) )
CGAPIDEF( DBBegBlock,   void,           (void) )
CGAPIDEF( DBEndBlock,   void,           (void) )
CGAPIDEF( DFClient,     pointer,        (void) )
CGAPIDEF( DFDwarfLocal, void,           (pointer,pointer,pointer) )
