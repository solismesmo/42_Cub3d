/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:21:10 by livieira          #+#    #+#             */
/*   Updated: 2025/02/25 23:42:30 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TEX_WIDTH 256
# define TEX_HEIGHT 256

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

#define BPP sizeof(int32_t)

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
# define EA "./src/textures/west_texture.png"

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
}	t_map;

typedef struct s_player
{
	int				square_pos[2];
	float			vector_pos[2];
	float			vector_dir[2];
	int				x;
	int				y;
	int				found;
	char			direction;
	
}	t_player;

typedef struct s_camera
{
	float	plane[2];
	float	negative_plane[2];
	float   ray_dir[2];

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
	int				hit_side;
	float			wall_line_start;
	float			wall_line_end;
	float 			perpendicular_dist;
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

}					t_game;

void	ft_check_args(int argc, char **argv);
void	ft_check_walls(t_game *game);
void	ft_increment_player(t_game *game, int i, int j, char dir);
t_game	*ft_init_values(void);
void	ft_map_open(t_game *game);
int		ft_char_allowed(char c);
void	ft_char_check(t_game *game);
void	ft_map_condition(t_game *game);
//void	ft_mark_visited(t_game	*game, int row, int col);
//int		ft_dfs(t_game *game, int row, int col);
//void	ft_check_path(t_game *game);
void	ft_map_lego(t_game *game);
//void	ft_map_walls(t_game *game);
//void	ft_check_rectangle(t_game *game);
void	ft_init_map_matrix(t_game *game);
void	ft_error_message(char *message);
void	ft_error(char *message, t_game *game);
int		ft_map_close(int fd);
void	ft_finish(char *message, t_game *game);
void	ft_free_map(char **matriz);
void	ft_error_temp(char *message, t_game *game, char **temp);
void	ft_place_png(t_game *game, mlx_image_t **image, char *path);
void	ft_init_mlx(t_game *game);
void	ft_keyhooks(mlx_key_data_t keydata, void *param);
void	ft_floor(t_game *game);
void	ft_place_png(t_game *game, mlx_image_t **image, char *path);
void	ft_image_init(t_game *game);
void	ft_render_map(t_game *game);
void	ft_last_line(char **matrix, t_game	*game);
void	ft_movement(t_game *game, int x, int y);
t_bool	ft_verify_walls(t_game *game, int x, int y);
void	ft_render_coin(t_game *game, int x, int y, int *count);
void	ft_collect_item(t_game *game, int x, int y);
void	ft_exit_game(t_game *game, int x, int y);
void	ft_delete_image(t_game *game);
void	ft_init_moves(t_game *game);
void	ft_increment(t_game *game, int i, int j);
void	ft_init_map(t_game *game);
void	ft_init_player(t_game *game);
void	ft_find_rays(t_game *game);
void	ft_dda(t_game *game);
void	ft_init_game(t_game *game);
void	ft_draw_image(t_game *game, int pixels, mlx_image_t *image);
void	ft_init_image(t_game *game);
void	ft_rotate_player(t_game *game, double angle);
void    ft_refresh_img(t_game *game);
void	ft_move_player(t_game *game, double move_speed);
void	ft_init_textures(t_game *game);
int		get_texture_pixel(t_game *game, int texX, int texY);
unsigned int fix_color(unsigned int color);
int create_trgb(int t, int r, int g, int b);


#endif
