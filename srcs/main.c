/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:55:06 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 10:13:06 by dlu              ###   ########.fr       */
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
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		ft_perror_exit(ERR_ARG, NULL);
	game_init(&game);
	ft_map_parser(av[1], &game);
	return (EXIT_SUCCESS);
}

// only after validing the map will run mlx.
