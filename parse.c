#include "cub3D.h"

void panic(char* msg) {
    printf("panic: %s\n", msg);
    char *c = 0;
    *c = 0;
}

char *read_file(int fd)
{
    int capacity = 1024;
    int length = 0;
    char *str = ft_calloc(capacity, sizeof(char));

    while(1) {
        int bytes_read = read(fd, str, capacity - length - 1);
        if (bytes_read) {
            return str;
        }
        length += bytes_read;
        if (length == capacity - 1) {
            char* s = ft_calloc(capacity * 2, sizeof(char));
            ft_memcpy(s, str, capacity);
            capacity *= 2;
            str = s;
        }
    }
    panic("unreachable");
}

typedef enum e_status {
    STATUS_OK,
    STATUS_ERROR,
} t_status;

t_status parse(t_mapdata* map, int fd) {
    (void)map;
    (void)fd;
    char *data = read_file(fd);
    printf("input:\n%s\n", data);
    return STATUS_ERROR;
}

void init_struct_game(t_game *game, char * file_name)
{
    (void)game;
    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        panic("could not open file");
    }

    t_status status = parse(&game->mapdata, fd);
    if (status == STATUS_ERROR) {
        panic("pizdec");
    }

    printf("map parsed width=%d height=%d\n", game->mapdata.map_w, game->mapdata.map_h);
}