/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:47:04 by dlu               #+#    #+#             */
/*   Updated: 2023/06/08 15:26:17 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Parse chars of the map, exit if there's invalid char or wrong width. */
static void	ft_map_parse_chars(t_game *game, t_map *m)
{
	int		i;
	int		j;

	i = -1;
	while (m->lines[++i])
	{
		j = -1;
		while (m->lines[i][++j])
		{
			if ((i == 0 || i == m->height - 1 || j == 0 || j == m->width - 1)
				&& m->lines[i][j] != C_WALL)
				ft_perror_exit(ERR_WALL, game);
			else if (m->lines[i][j] == C_COLLECT)
				m->collectible++;
			else if (m->lines[i][j] == C_PLAYER)
				m->player++;
			else if (m->lines[i][j] == C_EXIT)
				m->exit++;
			else if (m->lines[i][j] != C_WALL && m->lines[i][j] != C_FLOOR)
				ft_perror_exit(ERR_CHAR, game);
		}
		if (m->width != j)
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

static void	ft_map_validator(t_game *game, t_map *map)
{
	if (map->player == 0)
		ft_perror_exit(ERR_NO_P, game);
	else if (map->player > 1)
		ft_perror_exit(ERR_DUP_P, game);
	else if (map->exit == 0)
		ft_perror_exit(ERR_NO_E, game);
	else if (map->exit > 1)
		ft_perror_exit(ERR_DUP_E, game);
	else if (map->collectible == 0)
		ft_perror_exit(ERR_NO_C, game);
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
	game->map->width = ft_strlen(game->map->lines[0]);
	game->map->height = ft_strarrlen(game->map->lines);
	ft_map_parse_chars(game, game->map);
	ft_map_validator(game, game->map);
}
