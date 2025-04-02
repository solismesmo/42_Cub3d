/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:21:10 by livieira          #+#    #+#             */
/*   Updated: 2025/04/01 21:15:13 by bruno            ###   ########.fr       */
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

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
	char	**tokens;
}	t_rgb;

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

typedef struct s_render_info
{
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_render_info;

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
	int				row_move[8];
	int				col_move[8];
	int				check_coins;
	int				check_inputs;
	int				num_textures;
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
	t_rgb			color;
	unsigned int	floor_color;
	int				ceiling_color;
	t_render_info	info;
	t_dda_params	params;

}					t_game;

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
char			*ft_process_header(t_game *game);
char			*ft_process_map(t_game *game, char *map_full);
void			ft_parse_header_line(char *line, t_game *game);
char			*ft_process_map(t_game *game, char *map_full);
void			ft_init_map(t_game *game);
void			ft_parsing_file(t_game *game);
void			ft_parse_texture(char *line, t_game *game);
void			ft_parse_color(char *line, t_game *game);
void			ft_convert_rgb(t_game *game);
int				is_whitespace(char c);
int				ft_is_space(char **str);
int				ft_isspace(int c);
int				ft_check_rgb_format(t_game *game, char *line);
void			ft_msg_color_fmt(t_game *game);
void			ft_set_texture_aux(char *id, char *path, \
	t_game *game, char *line);
void			ft_ceiling_floor(t_game *game, mlx_image_t *img, int x, int y);
void			ft_draw_image(t_game *game, int pixels, mlx_image_t *image);
void			ft_initialize_texture_info(t_game *game);
void			ft_calculate_line_height(t_game *game);
double			ft_calculate_wall_x(t_game *game);
void			ft_calculate_tex_x(t_game *game, double wall_x);
void			ft_render_texture_line(t_game *game, int pixels, \
	mlx_image_t *image);
void			ft_initialize_side_dist_and_step_x(t_game *game);
void			ft_initialize_side_dist_and_step_y(t_game *game);
void			ft_update_dda_line_size(t_game *game);
void			ft_perform_dda_loop(t_game *game);
void			ft_calculate_delta_dist(t_game *game);
void			ft_calculate_perpendicular_dist(t_game *game);
void			ft_calculate_wall_line_height(t_game *game);
int				ft_isrgb(t_game *game, int *i, int *num_count, \
	char *ft_line);
void			ft_parser_error(char **rgb_values, \
	t_game *game, char *line, char *message);
int				ft_check_next_cell(t_game *game, int row, int col, int i);

#endif