/****************************************************************************
*
*                            Open Watcom Project
*
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


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dos.h>
#include <malloc.h>
#include <io.h>
#include "drwatcom.h"
#include "sopen.h"
#include "dip.h"
#include "dipimp.h"
#include "dipcli.h"


//#define DEBUGOUT( x ) LBPrintf( ListBox, x );
#define DEBUGOUT( x )

#if 0
FILE *PathOpen( char *name, unsigned len, char *ext )
{
    char        path[ _MAX_PATH ];
    char        *realname;
    char        *filename;

    len = len;
    if( ext == NULL || *ext == '\0' ) {
        realname = name;
    } else {
        realname = MemAlloc( _MAX_PATH );
        filename = MemAlloc( _MAX_FNAME );
        _splitpath( name, NULL, NULL, filename, NULL );
        _makepath( realname, NULL, NULL, filename, ext );
        MemFree( realname );
        MemFree( filename );
    }
    _searchenv( realname, "PATH", path );
    if( *path == '\0' )
        return( NULL );
    return( DIGCli( Open )( path, DIG_READ ) );
}
#endif

/*##########################################################################
  #
  # CLIENT routines for the DIG
  #
  ##########################################################################*/

/*
 * DIGCliAlloc
 */
void *DIGCLIENTRY( Alloc )( size_t size )
{
    void        *ret;

    DEBUGOUT( "alloc BEGIN" );
    ret = MemAlloc( size );
    DEBUGOUT( "alloc END" );
    return( ret );
}

/*
 * DIGCliRealloc
 */
void *DIGCLIENTRY( Realloc )( void *ptr, size_t size )
{
    void        *ret;

    DEBUGOUT( "realloc BEGIN" );
    ret = MemReAlloc( ptr, size );
    DEBUGOUT( "realloc END" );
    return( ret );
}

/*
 * DIGCliFree
 */
void DIGCLIENTRY( Free )( void *ptr )
{
    DEBUGOUT( "free BEGIN" );
    MemFree( ptr );
    DEBUGOUT( "free END" );
}

/*
 * DIGCliOpen
 */
FILE * DIGCLIENTRY( Open )( const char *path, dig_open mode )
{
    int         fd;
    int         flags;

    flags = O_BINARY;
    if( mode & DIG_READ )
        flags |= O_RDONLY;
    if( mode & DIG_WRITE )
        flags |= O_WRONLY;
    if( mode & DIG_TRUNC )
        flags |= O_TRUNC;
    if( mode & DIG_CREATE ) {
        flags |= O_CREAT;
        fd = sopen4( path, flags, SH_DENYWR, S_IRWXU | S_IRWXG | S_IRWXO );
    } else {
        fd = sopen3( path, flags, SH_DENYWR );
    }
    if( fd == -1 )
        return( NULL );
    return( DIG_PH2FID( fd ) );
}

/*
 * DIGCliSeek
 */
int DIGCLIENTRY( Seek )( FILE *fp, unsigned long offset, dig_seek dipmode )
{
    int                 mode;
    unsigned long       ret;

    DEBUGOUT( "seek BEGIN" );
    switch( dipmode ) {
    case DIG_ORG:
        mode = SEEK_SET;
        break;
    case DIG_CUR:
        mode = SEEK_CUR;
        break;
    case DIG_END:
        mode = SEEK_END;
        break;
    }
    ret = lseek( DIG_FID2PH( fp ), offset, mode );
    DEBUGOUT( "seek END" );
    return( ret == -1L );
}

/*
 * DIGCliTell
 */
unsigned long DIGCLIENTRY( Tell )( FILE *fp )
{
    unsigned long       ret;

    DEBUGOUT( "tell BEGIN" );
    ret = lseek( DIG_FID2PH( fp ), 0, SEEK_CUR );
    DEBUGOUT( "tell END" );
    return( ret );
}

/*
 * DIGCliRead
 */
size_t DIGCLIENTRY( Read )( FILE *fp, void *buf, size_t size )
{
    DEBUGOUT( "reading" );
    return( read( DIG_FID2PH( fp ), buf, size ) );
}

/*
 * DIGCliWrite
 */
size_t DIGCLIENTRY( Write )( FILE *fp, const void *buf, size_t size )
{
    return( write( DIG_FID2PH( fp ), buf, size ) );
}

/*
 * DIGCliClose
 */
void DIGCLIENTRY( Close )( FILE *fp )
{
    close( DIG_FID2PH( fp ) );
}

/*
 * DIGCliRemove
 */
void DIGCLIENTRY( Remove )( const char *path, dig_open mode )
{
    mode = mode;
    remove( path );
}


/*
 * DIGCliMachineData
 */
unsigned DIGCLIENTRY( MachineData )( address addr, dig_info_type info_type,
                        dig_elen in_size,  const void *in,
                        dig_elen out_size, void *out )
{
    addr = addr;
    info_type = info_type;
    in_size = in_size;
    in = in;
    out_size = out_size;
    out = out;
    return( 0 );
}
