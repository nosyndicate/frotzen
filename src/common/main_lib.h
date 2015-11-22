#ifndef MAIN_LIB_H
#define MAIN_LIB_H




#ifdef __cplusplus
extern "C" {
#endif
    void init_frotz(int argc, char *argv[]);
    void start_game();
    void reset_frotz();
    void input(void);

#ifdef __cplusplus
}
#endif

#endif
