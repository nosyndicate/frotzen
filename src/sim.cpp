#include "stdio.h"
#include "common/main_lib.h"

int main(int argc, char *argv[])
{
    init_frotz(argc, argv);
    start_game();
    reset_frotz();
}
