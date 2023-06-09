/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 18:47:04 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 15:08:46 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Fill the reachable grid with 'X'. */
static void	ft_floodfill(char **grid, t_game *g, int x, int y)
{
	if (x < 0 || y < 0 || y >= g->map->height || x >= g->map->width
		|| (grid[y][x] != C_FLOOR && grid[y][x] != C_PLAYER
		&& grid[y][x] != C_COLLECT && grid[y][x] != C_EXIT))
		return ;
	grid[y][x] = 'X';
	ft_floodfill(grid, g, x + 1, y);
	ft_floodfill(grid, g, x - 1, y);
	ft_floodfill(grid, g, x, y + 1);
	ft_floodfill(grid, g, x, y - 1);
}

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
				m->col++;
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

/* Validate the map has a valid path. */
static void	ft_map_check_path(t_game *game, t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (map->lines[++y])
	{
		x = -1;
		while (map->lines[y][++x])
			if (map->lines[y][x] == C_PLAYER)
				game->player_pos = (t_pos){x, y};
	}
	ft_floodfill(map->lines_cpy, game, game->player_pos.x, game->player_pos.y);
	y = -1;
	while (map->lines_cpy[++y])
	{
		x = -1;
		while (map->lines_cpy[y][++x])
			if (map->lines_cpy[y][x] == C_EXIT
				|| map->lines_cpy[y][x] == C_COLLECT)
				ft_perror_exit(ERR_PATH, game);
	}
}

/* Validate the map has the right number of c, p, and e. */
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
	else if (map->col == 0)
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
	{
		ft_putendl_fd(ERR_MSG, STDERR);
		perror(ERR_OPEN);
		free(game->map);
		exit(EXIT_FAILURE);
	}
	game->map->lines = ft_split(content, '\n');
	game->map->lines_cpy = ft_split(content, '\n');
	free(content);
	game->map->width = ft_strlen(game->map->lines[0]);
	game->map->height = ft_strarrlen(game->map->lines);
	ft_map_parse_chars(game, game->map);
	ft_map_validator(game, game->map);
	ft_map_check_path(game, game->map);
}
