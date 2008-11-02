/*****************************************************************************
 * es_out.h: Input es_out functions
 *****************************************************************************
 * Copyright (C) 1998-2008 the VideoLAN team
 * Copyright (C) 2008 Laurent Aimar
 * $Id$
 *
 * Authors: Laurent Aimar <fenrir@via.ecp.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#if defined(__PLUGIN__) || defined(__BUILTIN__) || !defined(__LIBVLC__)
# error This header file can only be included from LibVLC.
#endif

#ifndef _INPUT_ES_OUT_H
#define _INPUT_ES_OUT_H 1

#include <vlc_common.h>

enum es_out_query_private_e
{
    /* Get date to wait before demuxing more data */
    ES_OUT_GET_WAKE_UP = ES_OUT_PRIVATE_START,   /* arg1=mtime_t*            res=cannot fail */

    /* Wrapper for some ES command to work with id */
    ES_OUT_SET_ES_BY_ID,
    ES_OUT_RESTART_ES_BY_ID,
    ES_OUT_SET_ES_DEFAULT_BY_ID,
};

static inline mtime_t es_out_GetWakeup( es_out_t *p_out )
{
    mtime_t i_wu;
    int i_ret = es_out_Control( p_out, ES_OUT_GET_WAKE_UP, &i_wu );

    assert( !i_ret );
    return i_wu;
}

es_out_t  *input_EsOutNew( input_thread_t *, int i_rate );

void       input_EsOutSetDelay( es_out_t *, int i_cat, int64_t );
int        input_EsOutSetRecord( es_out_t *, bool b_record );
void       input_EsOutChangeRate( es_out_t *, int );
void       input_EsOutChangePause( es_out_t *, bool b_paused, mtime_t i_date );
void       input_EsOutChangePosition( es_out_t * );
bool       input_EsOutDecodersIsEmpty( es_out_t * );
bool       input_EsOutIsBuffering( es_out_t * );
void       input_EsOutFrameNext( es_out_t * );

void       input_EsOutLock( es_out_t * );
void       input_EsOutUnlock( es_out_t * );

#endif
