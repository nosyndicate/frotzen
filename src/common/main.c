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

lua_State *L;
int islua_play = 1;

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

void bail(lua_State *L, char *msg){
        fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
                msg, lua_tostring(L, -1));
        exit(1);
}


/*
 * main
 *
 * Prepare and run the game.
 *
 */
int cdecl main (int argc, char *argv[])
{
    

    L = luaL_newstate();                        /* Create Lua state variable */
    luaL_openlibs(L);                           /* Load Lua libraries */

    if (luaL_loadfile(L, "helloscript.lua"))    /* Load but don't run the Lua script */
        bail(L, "luaL_loadfile() failed");      /* Error out if file can't be read */

    
    //  prime the lua script MUST DO THIS!!!
    if (lua_pcall(L, 0, 0, 0))                  /* Run the loaded Lua script */
        bail(L, "lua_pcall() failed");          /* Error out if Lua file has an error */

    lua_getglobal(L, "get_islua_play");
    // now actually call the function
    if (lua_pcall(L, 0, 1, 0))                  /* Run the function */
        bail(L, "lua_pcall() failed");          /* Error out if Lua file has an error */
    islua_play = lua_tonumber(L, -1);
    
    
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

    

    
    interpret ();   //process.c

    lua_close(L);                               /* Clean up, free the Lua state var */
    
    reset_memory ();

    os_reset_screen ();

    return 0;

}/* main */
