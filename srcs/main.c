/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:55:06 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 13:41:23 by dlu              ###   ########.fr       */
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
	game.mlx = mlx_init(416, 160, "SO_LONG", false);
	if (!game.mlx)
		ft_perror_exit((char *) mlx_strerror(mlx_errno), &game);
	
	mlx_texture_t	*texture = mlx_load_png("./assets/wall.png");
	mlx_image_t		*img = mlx_texture_to_image(game.mlx, texture);
	mlx_resize_image(img, 32, 32);
	mlx_image_to_window(game.mlx, img, 50, 0);
	
	mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_close_hook(game.mlx, &ft_close_hook, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
