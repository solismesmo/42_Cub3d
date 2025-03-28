/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:21:10 by livieira          #+#    #+#             */
/*   Updated: 2025/03/27 21:21:10 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TEX_WIDTH 256
# define TEX_HEIGHT 256
# define WINDOW_WIDTH 1020
# define WINDOW_HEIGHT 800
# define BPP 4

# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../includes/libft/libft.h"
# include "../includes/lib/MLX42/include/MLX42/MLX42.h"

# define SO "./src/textures/south_texture.png"
# define NO "./src/textures/north_texture.png"
# define WE "./src/textures/west_texture.png"
# define EA "./src/textures/east_texture.png"
# define MAP_EXT_DEF ".cub"

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_map
{
	char			*map_full;
	char			**matrix;
	char			**matrix_fill;
	char			*line;
	int				player;
	int				columns;
	int				lines;
	int				rows;
	int				coin;
	int				exits;
	int				floor;
	int				walls;
	int				enemy;
	int				p_row;
	int				p_col;
	int				row_move[4];
	int				col_move[4];
	int				check_coins;
	int				check_inputs;
}	t_map;

typedef struct s_player
{
	int				square_pos[2];
	double			vector_pos[2];
	double			vector_dir[2];
	int				x;
	int				y;
	int				found;
	char			direction;

}	t_player;

typedef struct s_camera
{
	double	plane[2];
	double	negative_plane[2];
	double	ray_dir[2];

}	t_camera;

typedef struct s_mult
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	int				x;
	int				y;
}					t_mult;

typedef struct s_image
{
	mlx_image_t		*north;
	mlx_image_t		*image;
	mlx_image_t		*south;
	mlx_image_t		*west;
	mlx_image_t		*east;
	int				hit;
	char			*path_north;
	char			*path_south;
	char			*path_west;
	char			*path_east;
	int				hit_side;
	double			wall_line_start;
	double			wall_line_end;
	double			perpendicular_dist;
}	t_image;

typedef struct s_game
{
	mlx_t			*mlx;
	t_player		player_info;
	int				fd;
	char			*map_name;
	t_map			map;
	t_image			img;
	int				count;
	t_mult			coin[100000];
	t_mult			player[1];
	int				moves;
	t_camera		camera;
	unsigned int	floor_color;
	int				ceiling_color;

}	t_game;

typedef struct s_render_info
{
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_render_info;

typedef struct s_dda_params
{
	double	delta_distx;
	double	delta_disty;
	double	dist_side_x;
	double	dist_side_y;
	double	step_x;
	double	step_y;
	double	dda_line_size_x;
	double	dda_line_size_y;
	int		wall_map_pos[2];
}	t_dda_params;

void			ft_check_args(int argc, char **argv);
void			ft_check_walls(t_game *game);
t_game			*ft_init_values(void);
void			ft_map_open(t_game *game);
int				ft_char_allowed(char c);
void			ft_char_check(t_game *game);
void			ft_map_condition(t_game *game);
void			ft_map_lego(t_game *game);
void			ft_map_walls(t_game *game);
void			ft_init_map_matrix(t_game *game);
void			ft_error_message(char *message);
void			ft_error(char *message, t_game *game);
int				ft_map_close(int fd);
void			ft_finish(char *message, t_game *game);
void			ft_free_map(char **matriz);
void			ft_error_temp(char *message, t_game *game, char **temp);
void			ft_place_png(t_game *game, mlx_image_t **image, char *path);
void			ft_init_mlx(t_game *game);
void			ft_keyhooks(mlx_key_data_t keydata, void *param);
void			ft_place_png(t_game *game, mlx_image_t **image, char *path);
void			ft_last_line(char **matrix, t_game	*game);
void			ft_init_moves(t_game *game);
void			ft_init_map(t_game *game);
void			ft_init_player(t_game *game);
void			ft_find_rays(t_game *game);
void			ft_dda(t_game *game);
void			ft_init_game(t_game *game);
void			ft_draw_image(t_game *game, int pixels, mlx_image_t *image);
void			ft_init_image(t_game *game);
void			ft_rotate_player(t_game *game, double angle);
void			ft_refresh_img(t_game *game);
void			ft_move_player(t_game *game, double move_speed);
void			ft_init_textures(t_game *game);
int				get_texture_pixel(t_game *game, int texX, int texY);
unsigned int	fix_color(unsigned int color);
int				ft_is_header_line(char *line);
void			ft_check_map_information(t_game *game);
int				ft_dfs_closed(t_game *game, int row, int col);
void			ft_check_closed(t_game *game);
void			ft_mark_visited(t_game *game, int row, int col);
void			print_fill_matrix(t_game *game);
void			print_matrix(t_game *game);
int				ft_dfs_done(int next_row, int col, int col_move, t_game *game);

#endif