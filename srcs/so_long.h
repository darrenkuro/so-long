/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:59:23 by dlu               #+#    #+#             */
/*   Updated: 2023/06/08 15:26:07 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>

# define C_PLAYER	'P'
# define C_EXIT		'E'
# define C_COLLECT	'C'
# define C_WALL		'1'
# define C_FLOOR	'0'
# define MAP_EXT	".ber"
# define ERR_MSG	"Error"
# define ERR_ARG	"Wrong number of arguments: requires 1 (map file path)."
# define ERR_EXT	"Wrong file format, maps must have extension 'ber'."
# define ERR_OPEN	"Failed to open map"
# define ERR_CHAR	"Invalid map: invalid character."
# define ERR_WIDTH	"Invalid map: not a rectangle."
# define ERR_NO_P	"Invalid map: missing starting player position."
# define ERR_DUP_P	"Invalid map: more than one starting player position."
# define ERR_NO_E	"Invalid map: missing exit."
# define ERR_DUP_E	"Invalid map: more than one exit."
# define ERR_NO_C	"Invalid map: there are no collectibles."
# define ERR_WALL	"Invalid map: wall does not enclose the map."
# define ERR_PATH	"Invalid map: there is no valid path."

typedef struct s_map
{
	char	**lines;
	int		height;
	int		width;
	int		collectible;
	int		player;
	int		exit;
}	t_map;

typedef struct s_game
{
	t_map	*map;
}	t_game;

void	ft_map_parser(const char *filename, t_game *game);
void	ft_free_map(t_map *map);
void	ft_perror_exit(char *msg, t_game *game);

#endif
