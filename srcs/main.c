/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:55:06 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 14:13:20 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void load_image(t_game *game)
{
	mlx_texture_t	*texture;
	
	texture = mlx_load_png(IMG_WALL);
	game->img_wall = mlx_texture_to_image(game->mlx, texture);
	texture = mlx_load_png(IMG_FLOOR);
	game->img_floor = mlx_texture_to_image(game->mlx, texture);
	texture = mlx_load_png(IMG_COL);
	game->img_collectible = mlx_texture_to_image(game->mlx, texture);
	texture = mlx_load_png(IMG_PLAYER);
	game->img_player = mlx_texture_to_image(game->mlx, texture);
	texture = mlx_load_png(IMG_EXIT);
	game->img_exit = mlx_texture_to_image(game->mlx, texture);
}

static void	game_init(t_game *game)
{
	game->map = (t_map *) malloc(sizeof(t_map));
	if (!game->map)
		exit(EXIT_FAILURE);
	game->map->player = 0;
	game->map->collectible = 0;
	game->map->exit = 0;
	game->map->width = 0;
	game->map->height = 0;
	game->map->lines = NULL;
	game->map->lines_cpy = NULL;
	game->mlx = NULL;
}

void	render(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (g->map->lines[++y])
	{
		x = -1;
		while (g->map->lines[y][++x])
		{
			if (g->map->lines[y][x] == C_WALL)
				mlx_image_to_window(g->mlx, g->img_wall, x * 32, y * 32);
			else
				mlx_image_to_window(g->mlx, g->img_floor, x * 32, y * 32);
			if (g->map->lines[y][x] == C_PLAYER)
				mlx_image_to_window(g->mlx, g->img_player, x * 32, y * 32);
			if (g->map->lines[y][x] == C_COLLECT)
				mlx_image_to_window(g->mlx, g->img_collectible, x * 32, y * 32);
			if (g->map->lines[y][x] == C_EXIT)
				mlx_image_to_window(g->mlx, g->img_exit, x * 32, y * 32);
		}
	}
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		ft_perror_exit(ERR_ARG, NULL);
	game_init(&game);
	ft_map_parser(av[1], &game);
	game.mlx = mlx_init(game.map->width * 32, game.map->height * 32, \
			"SO_LONG", false);
	if (!game.mlx)
		ft_perror_exit((char *) mlx_strerror(mlx_errno), &game);
	load_image(&game);
	render(&game);
	mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_close_hook(game.mlx, &ft_close_hook, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
