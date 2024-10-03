#include "cub3D.h"

void panic(char* msg) {
    printf("Error: %s\n", msg);
    char *c = 0;
    *c = 0;
}

char *read_file(int fd)
{
    int capacity = 1024;
    int length = 0;
    char *str = ft_calloc(capacity, sizeof(char) + 1);

    while(1) {
        int bytes_read = read(fd, &str[length], capacity - length);
        if (bytes_read < 0) {
            free(str);
            panic("read call failed");
            return NULL;
        }
        if (!bytes_read) {
            return str;
        }
        length += bytes_read;
        if (length == capacity) {
            char* s = ft_calloc(capacity * 2 + 1, sizeof(char));
            ft_memcpy(s, str, capacity);
            capacity *= 2;
            free(str);
            str = s;
        }
    }
    panic("unreachable file");
}

int find_prefix(char *prefix, char * string)
{   
    while (*prefix)
    {
        if (*prefix == *string)
        {
            prefix++;
            string++;
        }
        else
            return(0);
    }
    return(1);
}


char* trim_str(int len, char* str) {
    return &str[len];
}


int parse_path(char* direction, char **inp_string, t_image* img)
{
    char *path;
    char *end_path;
    void	*mlx;

    if (!find_prefix(direction, *inp_string))
        return 0;
    *inp_string = trim_str(ft_strlen(direction), *inp_string);
    end_path = ft_strchr(*inp_string, '\n');
    path = ft_substr(*inp_string,0,(end_path-*inp_string));
    *inp_string = trim_str(ft_strlen(path) + 1, *inp_string);
	mlx = mlx_init();
    img->img = mlx_xpm_file_to_image(mlx,path, &img->img_w, &img->img_h);
	if(!img->img) {
        return(0);
    }
    return(1);
}

int get_img( t_game* game, char **inp_string)
{
    int no = parse_path("NO ", inp_string, &game->mapdata.north_wall);
    if (!no)
        return 0;
    int so = parse_path("SO ", inp_string, &game->mapdata.south_wall);
    if (!so)
        return 0;
    int we = parse_path("WE ", inp_string, &game->mapdata.west_wall);
    if (!we)
        return 0;
    int ea = parse_path("EA ", inp_string, &game->mapdata.east_wall);
    if (!ea)
        return 0;
    return 1;
}

char* cut_string(char * string, int n )
{
    char* part = ft_calloc(n, sizeof(char));
    int i = 0;

    while (i < n) {
        part[i] = string[i];
        i++;
    }
    return part;
}

// validate that the first n characters are digits
// and parse them into an int. Return -1 on error or 
// if n is oustide the [0; 255] range
int parse_byte_n(char* s, int n) {
    int res = 0;
    int i = 0;
    while(i < n) {
        if (!ft_isdigit(s[i]))
            return -1;
        res = res * 10 + (s[i] - '0');
        i++;
    }
    if (res < 0 || res > 255)
        return -1;
    return res;
}

int index_of(char* s, char c) {
    int i = 0;
    if (!s)
        return -1;
    while(s[i]) {
        if (s[i] == c)
            return i;
        i++;
    }
    return -1;
}

int read_color(char** str, char sep) {
    int sep_pos = index_of(*str, sep);
    if (sep_pos == -1)
        return -1;
    int res = parse_byte_n(*str, sep_pos);
    if (res == -1)
        return -1;
    *str += sep_pos + 1;
    return res;
}

int read_colors(char **str)
{
    int red = read_color(str, ',');
    int green = read_color(str, ',');
    int blue = read_color(str, '\n');
    if (red == -1 || blue == -1 || green == -1)
        return -1;
    return red << 16 | green << 8 | blue;
}

int get_colors(t_game* game, char **inp_string)
{
    if((*inp_string)[0]== '\n')
        *inp_string = trim_str(1, *inp_string);
    if ((*inp_string)[0] == 'F')
    {
        *inp_string = trim_str(2, *inp_string);
        game->color_floor = read_colors(inp_string);
        if (game->color_floor == -1)
            return 0;
    }
    if ((*inp_string)[0] == 'C')
    {
        *inp_string = trim_str(2, *inp_string);
        game->color_ceiling = read_colors(inp_string);
        if (game->color_ceiling == -1)
            return 0;
    }
    return(1);
}



int parse(t_game* game, int fd) {
    char *inp_string = read_file(fd);
    if(!get_img(game, &inp_string))
    {
        panic( "could not parse image paths");
        return(0);
    }
    if(!(get_colors(game,&inp_string)==1))
        {
        panic( "could not parse floor and ceiling colors");
        return(0);
    }
    return 1;
}

void init_struct_game(t_game *game, char * file_name)
{
    (void)game;
    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        panic("could not open file");
    }

    int status = parse(game, fd);
    if (status == 0) {
        panic("pizdec");
    }

    printf("map parsed width=%d height=%d\n", game->mapdata.map_w, game->mapdata.map_h);
}