/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:55:06 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 12:13:20 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		ft_perror_exit(ERR_ARG, NULL);
	game_init(&game);
	ft_map_parser(av[1], &game);
	game.mlx = mlx_init(256, 256, "SO_LONG", true);
	if (!game.mlx)
		ft_perror_exit((char *) mlx_strerror(mlx_errno), &game);
	mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_close_hook(game.mlx, &ft_close_hook, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}

// only after validing the map will run mlx.
