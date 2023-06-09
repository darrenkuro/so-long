/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:23:10 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 16:20:44 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Check if the current position has collectible, and pick up if so. */
void	ft_pick_up(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->img_col->count)
	{
		if (g->img_col->instances[i].x == g->img_player->instances[0].x
			&& g->img_col->instances[i].y == g->img_player->instances[0].y
			&& g->img_col->instances[i].enabled)
		{
			g->img_col->instances[i].enabled = false;
			g->collected++;
		}
	}
}

/* Move the player to target x and y, check if collectible and exit. */
void	ft_move(t_game *g, int x, int y)
{
	if (g->map->lines[y / 32][x / 32] == C_WALL)
		return ;
	g->img_player->instances[0].y = y;
	g->img_player->instances[0].x = x;
	g->movement++;
	ft_printf("Current movement count: %d\n", g->movement);
	ft_pick_up(g);
	if (g->map->lines[y / 32][x / 32] == C_EXIT && g->collected == g->map->col)
		mlx_terminate(g->mlx);
}
