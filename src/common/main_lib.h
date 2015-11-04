#ifndef MAIN_LIB_H
#define MAIN_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

    
    unsigned short moves;
    unsigned short scores;
    void init_frotz(int argc, char *argv[]);
    void start_game();
    void reset_frotz();
    int get_scores();
    int get_moves();

#ifdef __cplusplus
}
#endif

#endif