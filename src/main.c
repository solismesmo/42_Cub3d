/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:14:31 by livieira          #+#    #+#             */
/*   Updated: 2025/01/20 21:05:13 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*ft_init_values(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (game == NULL)
		return (NULL);
	game->map.map_full = NULL;
	game->map.matrix = NULL;
	game->map.matrix_fill = NULL;
	game->map.line = NULL;
	game->map.player = 0;
	game->map.columns = 0;
	game->map.rows = 0;
	game->map.coin = 0;
	game->map.exits = 0;
	game->map.floor = 0;
	game->map.walls = 0;
	game->map.enemy = 0;
	game->count = 0;
	game->map.lines = 0;
	game->moves = 1;
	game->map.p_col = 0;
	game->map.p_row = 0;
	game->img.wall = NULL;
	ft_init_moves(game);
	return (game);
}

void	ft_init_map(t_game *game)
{
	char	*temp;

	while (game->map.line != NULL || game->map.lines == 0)
	{
		game->map.line = get_next_line(game->fd);
		if (game->map.line == NULL)
			break ;
		if (*game->map.line == '\n')
			ft_error("Error, empty line!\n", game);
		if (game->map.map_full != NULL)
		{
			temp = game->map.map_full;
			game->map.map_full = ft_strjoin(temp, game->map.line);
			free(temp);
		}
		else
			game->map.map_full = ft_strdup(game->map.line);
		ft_map_walls(game);
		ft_check_rectangle(game);
		free(game->map.line);
	}
	if (game->map.map_full == NULL)
		ft_error("Error, empty map!\n", game);
	game->map.matrix = ft_split(game->map.map_full, '\n');
	ft_init_map_matrix(game);
}

void	ft_init_map_matrix(t_game *game)
{
	ft_map_lego(game);
}

void	ft_init_mlx(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init( WINDOW_WIDTH, \
	WINDOW_HEIGHT, "Cube 3D", true);
	if (!game->mlx)
	{
		ft_error("Erro na mlx. \n", game);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	ft_check_args(argc, argv);
	game = ft_init_values();
	game->map_name = argv[1];
	ft_map_open(game);
	ft_init_map(game);
	ft_init_mlx(game);
    mlx_image_t* img = mlx_new_image(game->mlx, 320, 100);
    memset(img->pixels, 255, img->width * img->height * BPP);
    mlx_image_to_window(game->mlx, img, 0, 0);
	int x = 0;
	int y = 0;
	while (y < (WINDOW_HEIGHT)/2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y, 0xCFD1F9FF);
			x++;
		}
		y++;
	}
	mlx_loop(game->mlx);

	//ft_image_init(game);
	//mlx_key_hook(game->mlx, &ft_keyhooks, game);
	mlx_loop(game->mlx);
	//ft_finish("Thanks for playing", game);
	return (0);
}
