#include "cub3D.h"

void panic(char* msg) {
    printf("panic: %s\n", msg);
    char *c = 0;
    *c = 0;
}

void init_struct_game(t_game *game, char * file_name)
{
    (void)game;
    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        panic("could not open file");
    }


}