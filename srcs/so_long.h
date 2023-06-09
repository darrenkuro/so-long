/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:59:23 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 15:37:26 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42/MLX42.h"
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

# define IMG_WALL	"./assets/wall_32.png"
# define IMG_FLOOR	"./assets/floor_32.png"
# define IMG_PLAYER	"./assets/player_single_32.png"
# define IMG_COL	"./assets/collectible_32.png"
# define IMG_EXIT	"./assets/exit_single_32.png"

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	char	**lines;
	char	**lines_cpy;
	int		height;
	int		width;
	int		col;
	int		player;
	int		exit;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img_player;
	int32_t		player_id;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_col;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_floor;
	t_pos		player_pos;
	int32_t		collected;
	int32_t		movement;
}	t_game;

void	ft_map_parser(const char *filename, t_game *game);
void	ft_free_map(t_map *map);
void	ft_perror_exit(char *msg, t_game *game);
void	ft_key_hook(mlx_key_data_t keydata, void *param);
void	ft_close_hook(void *param);
void	ft_move(t_game *g, int x, int y);

#endif
