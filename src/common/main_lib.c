/* main.c - Frotz V2.40 main function
 *	Copyright (c) 1995-1997 Stefan Jokisch
 *
 * This file is part of Frotz.
 *
 * Frotz is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Frotz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*
 * This is an interpreter for Infocom V1 to V6 games. It also supports
 * the recently defined V7 and V8 games.
 *
 */

#include "frotz.h"
#include "main_lib.h"



#ifndef MSDOS_16BIT
#define cdecl
#endif

extern void interpret (void);
extern void init_memory (void);
extern void init_undo (void);
extern void reset_memory (void);


/* Story file name, id number and size */

char *story_name = 0;

enum story story_id = UNKNOWN;
long story_size = 0;

/* Story file header data */

zbyte h_version = 0;
zbyte h_config = 0;
zword h_release = 0;
zword h_resident_size = 0;
zword h_start_pc = 0;
zword h_dictionary = 0;
zword h_objects = 0;
zword h_globals = 0;
zword h_dynamic_size = 0;
zword h_flags = 0;
zbyte h_serial[6] = { 0, 0, 0, 0, 0, 0 };
zword h_abbreviations = 0;
zword h_file_size = 0;
zword h_checksum = 0;
zbyte h_interpreter_number = 0;
zbyte h_interpreter_version = 0;
zbyte h_screen_rows = 0;
zbyte h_screen_cols = 0;
zword h_screen_width = 0;
zword h_screen_height = 0;
zbyte h_font_height = 1;
zbyte h_font_width = 1;
zword h_functions_offset = 0;
zword h_strings_offset = 0;
zbyte h_default_background = 0;
zbyte h_default_foreground = 0;
zword h_terminating_keys = 0;
zword h_line_width = 0;
zbyte h_standard_high = 1;
zbyte h_standard_low = 0;
zword h_alphabet = 0;
zword h_extension_table = 0;
zbyte h_user_name[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

zword hx_table_size = 0;
zword hx_mouse_x = 0;
zword hx_mouse_y = 0;
zword hx_unicode_table = 0;

/* Stack data */

zword stack[STACK_SIZE];
zword *sp = 0;
zword *fp = 0;
zword frame_count = 0;

/* IO streams */

bool ostream_screen = TRUE;
bool ostream_script = FALSE;
bool ostream_memory = FALSE;
bool ostream_record = FALSE;
bool istream_replay = FALSE;
bool message = FALSE;

/* Current window and mouse data */

int cwin = 0;
int mwin = 0;

int mouse_y = 0;
int mouse_x = 0;

/* Window attributes */

bool enable_wrapping = FALSE;
bool enable_scripting = FALSE;
bool enable_scrolling = FALSE;
bool enable_buffering = FALSE;

int option_sound = 1;
char *option_zcode_path;


/* Size of memory to reserve (in bytes) */

long reserve_mem = 0;


/*
 * z_piracy, branch if the story file is a legal copy.
 *
 *	no zargs used
 *
 */
void z_piracy (void)
{
    branch (!f_setup.piracy);

}/* z_piracy */

void init_frotz(int argc, char *argv[])
{
    os_init_setup ();
    os_process_arguments (argc, argv);
    init_buffer ();     // in buffer.c   set variable "buffer" to all 0
    init_err ();    //err.c
    init_memory ();     //fastmem.c    load the story file
    init_process ();    //process.c   set variable "finished" to 0
    init_sound ();
    os_init_screen ();
    init_undo ();
    z_restart ();   //fastmem.c
}


void start_game()
{
    interpret ();   //process.c
}

void reset_frotz()
{
    reset_memory ();
    os_reset_screen ();
}


void input (void)
{
//    zchar buffer[INPUT_BUFFER_SIZE];
//    zword addr;
//    zchar key;
//    zbyte max, size;
//    zbyte c;
//    int i;
//
//
//    //printf("in z_read, the version number is %d", h_version);   // by Ermo
//
//    /* Supply default arguments */
//    if (zargc < 3)
//	   zargs[2] = 0;
//
//    /* Get maximum input size */
//    addr = zargs[0];
//    LOW_BYTE (addr, max);
//
//    if (h_version <= V4) {
//        max--;
//    }
//
//
//    if (max >= INPUT_BUFFER_SIZE) {
//        max = INPUT_BUFFER_SIZE - 1;
//    }
//
//
//    /* Get initial input size */
//    if (h_version >= V5) {
//        addr++;
//        LOW_BYTE (addr, size);
//    } else
//        size = 0;
//
//    /* Copy initial input to local buffer */
//
//    for (i = 0; i < size; i++) {
//        addr++;
//        LOW_BYTE (addr, c);
//        buffer[i] = translate_from_zscii (c);
//    }
//
//    buffer[i] = 0;
//
//    //printf("before stream_read_input\n");   by Ermo
//
//    /* Draw status line for V1 to V3 games */
//
//    if (h_version <= V3)
//        z_show_status ();
//
//    /* Read input from current input stream */
//    key = stream_read_input (
//        max, buffer,		/* buffer and size */
//        zargs[2],		/* timeout value   */
//        zargs[3],		/* timeout routine */
//        TRUE,	        	/* enable hot keys */
//        h_version == V6);	/* no script in V6 */
//
//    printf("buffer : %s\n",buffer);
//
//    if (key == ZC_BAD)
//        return;
//
//    /* Perform save_undo for V1 to V4 games */
//
//    if (h_version <= V4)
//        save_undo ();
//
//    /* Copy local buffer back to dynamic memory */
//
//    for (i = 0; buffer[i] != 0; i++) {
//        if (key == ZC_RETURN) {
//        	// all convert to lower case
//            if (buffer[i] >= 'A' && buffer[i] <= 'Z')
//                buffer[i] += 'a' - 'A';
//            if (buffer[i] >= 0xc0 && buffer[i] <= 0xde && buffer[i] != 0xd7)
//                buffer[i] += 0x20;
//        }
//        if (truncate_question_mark() && buffer[i] == '?') buffer[i] = ' ';
//        // put the input to dynamic library
//        storeb ((zword) (zargs[0] + ((h_version <= V4) ? 1 : 2) + i), translate_to_zscii (buffer[i]));
//    }
//
//    /* Add null character (V1-V4) or write input length into 2nd byte */
//
//    if (h_version <= V4)
//        storeb ((zword) (zargs[0] + 1 + i), 0);
//    else
//        storeb ((zword) (zargs[0] + 1), i);
//
//    /* Tokenise line if a token buffer is present */
//
//    if (key == ZC_RETURN && zargs[1] != 0)
//        tokenise_line (zargs[0], zargs[1], 0, FALSE);
//
//    /* Store key */
//
//    if (h_version >= V5)
//        store (translate_to_zscii (key));

}/* z_read */

