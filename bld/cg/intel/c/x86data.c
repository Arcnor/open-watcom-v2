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


#include "_cgstd.h"
#include "coderep.h"
#include "system.h"
#include "jumps.h"
#include "zoiks.h"
#include "cgauxcc.h"
#include "cgauxinf.h"
#include "x86objd.h"
#include "data.h"
#include "utils.h"
#include "objout.h"
#include "namelist.h"
#include "objio.h"
#include "optmain.h"
#include "opttell.h"
#include "x86enc2.h"
#include "encode.h"
#include "x86obj.h"
#include "x86data.h"
#include "feprotos.h"


static void DoLblPtr( label_handle lbl, segment_id segid, fix_class class, offset plus );


void    DataAlign( uint_32 align )
/********************************/
{
    offset      curr_loc;
    uint        modulus;

    curr_loc = AskLocation();
    modulus = curr_loc % align;
    if( modulus != 0 ) {
        if( !AskSegIsBlank( AskOP() ) ) {
            IterBytes( (offset)( align - modulus ), 0 );
        } else {
            IncLocation( align - modulus );
        }
    }
}

void    DataBytes( unsigned len, const void *src )
/************************************************/
{
    if( len != 0 ) {
        TellOptimizerByPassed();
        SetUpObj( true );
        OutDBytes( len, src );
        TellByPassOver();
    }
}


void    DataShort( uint_16 val )
/******************************/
{
    TellOptimizerByPassed();
    SetUpObj( true );
    OutDataShort( val );
    TellByPassOver();
}

void    DataLong( uint_32 val )
/*****************************/
{
    TellOptimizerByPassed();
    SetUpObj( true );
    OutDataLong( val );
    TellByPassOver();
}


void    IterBytes( offset len, byte pat )
/***************************************/
{
    TellOptimizerByPassed();
    SetUpObj( true );
    OutIBytes( pat, len );
    TellByPassOver();
}


void    DoBigBckPtr( back_handle bck, offset off )
/*************************************************
 * Careful! Make sure a DGLabel has been done first!
 */
{
    TellOptimizerByPassed();
    DoLblPtr( bck->lbl, bck->segid, F_PTR, off );
    TellByPassOver();
}

static void     DoLblPtr( label_handle lbl, segment_id segid, fix_class class, offset plus )
/******************************************************************************************/
{
    SetUpObj( true );
    TellKeepLabel( lbl );
    OutReloc( segid, class, false );
    OutLblPatch( lbl, class, plus );
}


void    DoBigLblPtr( cg_sym_handle sym )
/**************************************/
{
    TellOptimizerByPassed();
    DoLblPtr( FEBack( sym )->lbl, FESegID( sym ), F_PTR, 0 );
    TellByPassOver();
}



static  void    DoImpPtr( cg_sym_handle sym, fix_class class, offset plus )
/*************************************************************************/
{
    SetUpObj( true );
    OutImport( sym, class, false );
    if( F_CLASS( class ) == F_BASE ) {
        _OutFarSeg( 0 );
    } else {
        _OutFarOff( plus );
        if( F_CLASS( class ) == F_PTR ) {
            _OutFarSeg( 0 );
        }
    }
}

void    BackImpPtr( const char *nm, back_handle bck, offset plus )
/****************************************************************/
{
    fix_class const class = F_OFFSET;

    SetUpObj( true );
    OutBckImport( nm, bck, class );
    if( class == F_BASE ) {
        _OutFarSeg( 0 );
    } else {
        _OutFarOff( plus );
        if( class == F_PTR ) {
            _OutFarSeg( 0 );
        }
    }
}

void    OutLblPatch( label_handle lbl, fix_class class, offset plus )
/*******************************************************************/
{
    offset      val;

    val = AskAddress( lbl );
    if( val == ADDR_UNKNOWN ) {
        OutPatch( lbl, ADD_PATCH | _OFFSET_PATCH );
        val = 0;
    }
    if( F_CLASS( class ) == F_BASE ) {
        _OutFarSeg( 0 );
    } else {
        if( F_CLASS( class ) == F_BIG_OFFSET ) {
            OutDataLong( val + plus );
        } else {
            _OutFarOff( val + plus );
        }
        if( F_CLASS( class ) == F_PTR ) {
            _OutFarSeg( 0 );
        }
    }
}


void    FEPtr( cg_sym_handle sym, type_def *tipe, offset plus )
/*************************************************************/
{
    fe_attr     attr;
    fix_class   class;

    TellOptimizerByPassed();
    attr = FEAttr( sym );
    if( (attr & FE_PROC)
      && _IsTargetModel( CGSW_X86_WINDOWS )
      && ((call_class_target)(pointer_uint)FindAuxInfoSym( sym, FEINF_CALL_CLASS_TARGET ) & FECALL_X86_FAR_CALL) ) {
        class = F_LDR_OFFSET;
    } else {
        class = F_OFFSET;
    }
    if( tipe->length != WORD_SIZE ) {
        class = F_PTR;
    }
    if( (attr & (FE_PROC | FE_DLLIMPORT)) == (FE_PROC | FE_DLLIMPORT)
      && (tipe->attr & TYPE_CODE) ) {
        class |= F_ALT_DLLIMP;
    }
    if( UseImportForm( attr ) ) {
        DoImpPtr( sym, class, plus );
    } else {
        DoLblPtr( FEBack( sym )->lbl, FESegID( sym ), class, plus );
    }
    TellByPassOver();
}

void    FEPtrBaseOffset( cg_sym_handle sym,  offset plus )
/********************************************************/
{
    fe_attr     attr;

    TellOptimizerByPassed();
    attr = FEAttr( sym );
    if( UseImportForm( attr ) ) {
        DoImpPtr( sym, F_PTR, plus );
    } else {
        DoLblPtr( FEBack( sym )->lbl, FESegID( sym ), F_PTR, plus );
    }
    TellByPassOver();
}

void    FEPtrBase( cg_sym_handle sym )
/************************************/
{
    fe_attr     attr;

    TellOptimizerByPassed();
    attr = FEAttr( sym );
    if( UseImportForm( attr ) ) {
        DoImpPtr( sym, F_BASE, 0 );
    } else {
        DoLblPtr( FEBack( sym )->lbl, FESegID( sym ), F_BASE, 0 );
    }
    TellByPassOver();
}


void    BackPtr( back_handle bck, segment_id segid, offset plus, type_def *tipe )
/*******************************************************************************/
{
    TellOptimizerByPassed();
    if( tipe->length != WORD_SIZE ) {
        DoLblPtr( bck->lbl, segid, F_PTR, plus );
    } else {
        DoLblPtr( bck->lbl, segid, F_OFFSET, plus );
    }
    TellByPassOver();
}

void    BackPtrBigOffset( back_handle bck, segment_id segid, offset plus )
/************************************************************************/
{
    TellOptimizerByPassed();
    DoLblPtr( bck->lbl, segid, F_BIG_OFFSET, plus );
    TellByPassOver();
}

void    BackPtrBase( back_handle bck, segment_id segid )
/******************************************************/
{
    TellOptimizerByPassed();
    DoLblPtr( bck->lbl, segid, F_BASE, 0 );
    TellByPassOver();
}

static  cg_class ConstDataClass( void )
/*************************************/
{
    if( _IsTargetModel( CGSW_X86_CONST_IN_CODE ) ) {
        return( CG_CLB );
    } else if( _IsTargetModel( CGSW_X86_FLOATING_DS ) && _IsTargetModel( CGSW_X86_FLOATING_SS ) ) {
        return( CG_CLB );
    } else {
        return( CG_LBL );
    }
}

name    *GenConstData( const void *buffer, type_class_def type_class )
/********************************************************************/
{
    segment_id          segid;
    cg_class            cgclass;
    name                *result;
    label_handle        label;
    type_length         size;

    TellOptimizerByPassed();
    cgclass = ConstDataClass();
    size = TypeClassSize[type_class];
    label = AskForLabel( NULL );
    if( cgclass == CG_CLB ) {
        segid = AskCodeSeg();
    } else {
        segid = AskBackSeg();
    }
    PUSH_OP( segid );
        SetUpObj( true );
        if( cgclass == CG_CLB ) {
            GenSelEntry( true );
            CodeLabel( label, size );
            CodeBytes( buffer, size );
            GenSelEntry( false );
        } else {
            DataAlign( size );
            OutLabel( label );
            DataBytes( size, buffer );
        }
    POP_OP();
    TellByPassOver();
    result = AllocMemory( label, 0, cgclass, type_class );
    result->v.usage |= USE_IN_ANOTHER_BLOCK;
    return( result );
}

name    *GenFloat( name *cons, type_class_def type_class )
/********************************************************/
{
    constant_defn       *defn;
    name                *result;

    defn = GetFloat( cons, type_class );
    if( defn->label == NULL ) {
        result = GenConstData( defn->value, type_class );
        defn->label = result->v.symbol;
    } else {
        result = AllocMemory( defn->label, 0, ConstDataClass(), type_class );
    }
    return( result );
}


void    DataLabel( label_handle lbl )
/***********************************/
{
    TellObjNewLabel( AskForLblSym( lbl ) );
    TellOptimizerByPassed();
    SetUpObj( true );
    OutLabel( lbl );
    TellByPassOver();
}
