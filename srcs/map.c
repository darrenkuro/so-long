/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:47:04 by dlu               #+#    #+#             */
/*   Updated: 2023/06/08 13:48:10 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Parse chars of the map, exit if there's invalid char or wrong width. */
static void	ft_map_parse_chars(t_game *game)
{
	t_map	*map;
	int		i;
	int		j;

	map = game->map;
	i = -1;
	while (map->lines[++i])
	{
		j = -1;
		while (map->lines[i][++j])
		{
			if (map->lines[i][j] == C_COLLECT)
				map->collectible++;
			else if (map->lines[i][j] == C_PLAYER)
				map->player++;
			else if (map->lines[i][j] == C_EXIT)
				map->exit++;
			else if (map->lines[i][j] != C_WALL && map->lines[i][j] != C_FLOOR)
				ft_perror_exit(ERR_CHAR, game);
		}
		if (!map->width)
			map->width = j;
		else if (map->width != j)
			ft_perror_exit(ERR_WIDTH, game);
	}
}

/* Handles file error with system perror and exit. */
static void	ft_file_perror_exit(void)
{
	ft_putendl_fd(ERR_MSG, STDERR);
	perror(ERR_OPEN);
	exit(EXIT_FAILURE);
}

static void	ft_map_validator(t_game *game)
{
	if (game->map->player == 0)
		ft_perror_exit(ERR_NO_P, game);
	else if (game->map->player > 1)
		ft_perror_exit(ERR_DUP_P, game);
	else if (game->map->exit == 0)
		ft_perror_exit(ERR_NO_E, game);
	else if (game->map->exit > 1)
		ft_perror_exit(ERR_DUP_E, game);
	else if (game->map->collectible == 0)
		ft_perrror_exit(ERR_NO_C, game);
}

/* Try to parse map from file, return FALSE if an error occurs. */
void	ft_map_parser(const char *filename, t_game *game)
{
	const char	*ext = ft_strrchr(filename, '.');
	char		*content;

	if (!ext || ft_strncmp(ext, MAP_EXT, ft_strlen(MAP_EXT)))
		ft_perror_exit(ERR_EXT, game);
	content = ft_read_file(filename);
	if (!content)
		ft_file_perror_exit();
	game->map->lines = ft_split(content, '\n');
	free(content);
	ft_map_parse_chars(game);
	ft_map_validator(game);
	ft_printf("%d", game->map->width);
}
