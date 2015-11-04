#include "stdio.h"
#include "common/main_lib.h"

int main(int argc, char *argv[])
{
    init_frotz(argc, argv);
    start_game();
    printf("%d\n",get_scores());
    printf("%d\n", get_moves());
    reset_frotz();
}