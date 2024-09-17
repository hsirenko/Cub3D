/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:05:28 by helensirenk       #+#    #+#             */
/*   Updated: 2024/09/16 18:44:34 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

/*COLORS*/
# define BLACK   0x000000
# define WHITE   0xFFFFFF
# define RED     0xFF0000
# define GREEN   0x00FF00
# define BLUE    0x0000FF
# define YELLOW  0xFFFF00
# define ORANGE  0xFFA500
# define PURPLE  0x800080
# define CYAN    0x00FFFF
# define MAGENTA 0xFF00FF

# define PSYCHEDELIC_PINK    0xFF1493
# define PSYCHEDELIC_LIME    0x32CD32
# define PSYCHEDELIC_CYAN    0x00FFFF
# define PSYCHEDELIC_YELLOW  0xFFFF00
# define PSYCHEDELIC_PURPLE  0x9400D3


typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;

} t_img;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    int     color_floor;
    int     color_ceiling;
    t_img   img;
} t_game;

#endif