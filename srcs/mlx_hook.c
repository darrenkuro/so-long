/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:40:52 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 12:22:36 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	//if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	//	mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_free_map(game->map);
		mlx_close_window(game->mlx);
	}
}

/* Free memory on close. */
void	ft_close_hook(void *param)
{
	t_game	*game;

	game = param;
	ft_free_map(game->map);
}
