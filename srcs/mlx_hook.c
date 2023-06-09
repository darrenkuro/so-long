/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:40:52 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 16:11:33 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game			*game;
	mlx_instance_t	player;

	game = param;
	player = game->img_player->instances[0];
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_terminate(game->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		ft_move(game, player.x, player.y - 32);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		ft_move(game, player.x, player.y + 32);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		ft_move(game, player.x - 32, player.y);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ft_move(game, player.x + 32, player.y);
}

/* Free memory on close. */
void	ft_close_hook(void *param)
{
	t_game	*game;

	game = param;
	ft_free_map(game->map);
}
