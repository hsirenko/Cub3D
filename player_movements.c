/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helensirenko <helensirenko@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:39:53 by helensirenk       #+#    #+#             */
/*   Updated: 2024/10/10 15:25:57 by helensirenk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	key_release(t_keydata keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_D && keydata.action == RELEASE)
		game->player.left_right = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == RELEASE)
		game->player.left_right = 0;
	else if (keydata.key == MLX_KEY_W && keydata.action == RELEASE)
		game->player.up_down = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == RELEASE)
		game->player.up_down = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == RELEASE)
		game->player.rotate = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == RELEASE)
		game->player.rotate = 0;
}

void	key_press(t_keydata keydata, void *game_void)
{
	t_game	*game;

	game = game_void;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == PRESS \
		|| keydata.action == REPEAT))
		ft_exit(game);
	else if ((keydata.key == MLX_KEY_A) && (keydata.action == PRESS))
		game->player.left_right = -1;
	else if ((keydata.key == MLX_KEY_D) && (keydata.action == PRESS))
		game->player.left_right = 1;
	else if ((keydata.key == MLX_KEY_S) && (keydata.action == PRESS))
		game->player.up_down = -1;
	else if ((keydata.key == MLX_KEY_W) && (keydata.action == PRESS))
		game->player.up_down = 1;
	else if ((keydata.key == MLX_KEY_LEFT) && (keydata.action == PRESS))
		game->player.rotate = -1;
	else if ((keydata.key == MLX_KEY_RIGHT) && (keydata.action == PRESS))
		game->player.rotate = 1;
	key_release(keydata, game);
	// draw_map(game);
}

void	rotate(t_game *game, int i)
{
	if (i == 1)
	{
		game->player.angle += ROTATION_SPEED;
		if (game->player.angle >= 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	else
	{
		game->player.angle -= ROTATION_SPEED;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
}

void	move(t_game *game, double move_x, double move_y)
{
	int	new_pos_x;
	int	new_pos_y;
	int	map_x;
	int	map_y;

	new_pos_x = round(game->player.player_x + move_x);
	new_pos_y = round(game->player.player_y + move_y);
	map_x = new_pos_x / TILE_SIZE;
	map_y = new_pos_y / TILE_SIZE;
	if ((game->mapdata.map2d[map_y][map_x] != '1')
		&& (game->mapdata.map_check[map_y][game->player.player_x
		/ TILE_SIZE] != '1')
		&& (game->mapdata.map_check[game->player.player_y
		/ TILE_SIZE][map_x] != '1'))
	{
		game->player.player_x = new_pos_x;
		game->player.player_y = new_pos_y;
	}
}
// check  verifying that the player is not 
//crossing walls horizontally or vertically based on the player's current tile coordinates.
// Here's what each sq_map check does:

//(game->mapdata.map_check[map_y][game->player.player_x / TILE_SIZE] != '1')
//This check ensures that even if the player is within the correct y tile (map_grid_y),
//there isn't a wall directly in the tile corresponding to the player's x coordinate. 
//It checks the column derived from the player’s x position and the row from map_grid_y.

//(game->mapdata.map_check[game->player.player_y / TILE_SIZE][map_x] != '1')
//Similarly, this ensures that even if the player is within the correct x tile (map_grid_x),
// there isn’t a wall in the tile corresponding to the player’s y coordinate. 
//It checks the row derived from the player’s y position and the column from map_grid_x.

void	hook_move_rotate(t_game *game, double move_x, double move_y)
{
	if (game->player.rotate == 1)
		rotate(game, 1);
	else if (game->player.rotate == -1)
		rotate(game, 0);
	if (game->player.left_right == 1)
	{
		move_x = -sin(game->player.angle) * PLAYER_SPEED;
		move_y = cos(game->player.angle) * PLAYER_SPEED;
	}
	if (game->player.left_right == -1)
	{
		move_x = sin(game->player.angle) * PLAYER_SPEED;
		move_y = -cos(game->player.angle) * PLAYER_SPEED;
	}
	if (game->player.up_down == 1)
	{
		move_x = cos(game->player.angle) * PLAYER_SPEED;
		move_y = sin(game->player.angle) * PLAYER_SPEED;
	}
	if (game->player. up_down == -1)
	{
		move_x = -cos(game->player.angle) * PLAYER_SPEED;
		move_y = -sin(game->player.angle) * PLAYER_SPEED;
	}
	move(game, move_x, move_y);
}

