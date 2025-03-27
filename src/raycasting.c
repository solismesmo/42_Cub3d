/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:41 by bruno             #+#    #+#             */
/*   Updated: 2025/03/27 02:16:50 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_game(t_game *game)
{
	ft_init_player(game);
	ft_init_textures(game);
	ft_init_image(game);
	ft_find_rays(game);
}
void ft_check_path(char *path)
{
	if (!path || !(*path))
		return;
	while(*path != '\n')
	{
		path++;
	}
	*path = '\0';
}

int ft_check_texture_path(const char *path, t_game *game)
{
    int fd;
	
	if (path == NULL)
		ft_error("Erro ao abrir o arquivo de textura", game);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        ft_error("Erro ao abrir o arquivo de textura", game);
    close(fd);
    return(1);      // Caminho válido
}

void	ft_init_textures(t_game *game)
{
	
	ft_check_path(game->img.path_north);
	ft_check_path(game->img.path_south);
	ft_check_path(game->img.path_west);
	ft_check_path(game->img.path_east);
	ft_check_texture_path(game->img.path_north, game);
	ft_check_texture_path(game->img.path_south, game);
	ft_check_texture_path(game->img.path_west, game);
	ft_check_texture_path(game->img.path_east, game);
	ft_place_png(game, &game->img.north, game->img.path_north);
	ft_place_png(game, &game->img.south, game->img.path_south);
	ft_place_png(game, &game->img.west, game->img.path_west);
	ft_place_png(game, &game->img.east, game->img.path_east);
}

void	ft_place_png(t_game *game, mlx_image_t **image, char *path)
{
	mlx_texture_t	*my_texture;

	my_texture = mlx_load_png(path);
	*image = mlx_texture_to_image(game->mlx, my_texture);
	if(!*image)
		ft_error("Error: Invalid texture path\n", game);
	mlx_delete_texture(my_texture);
}

void ft_init_image(t_game *game)
{
	mlx_image_t* img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	memset(img->pixels, 255, img->width * img->height * BPP);
	mlx_image_to_window(game->mlx, img, 0, 0);
	int x = 0;
	int y = 0;
	while (y < (WINDOW_HEIGHT) / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y,  game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < (WINDOW_HEIGHT))
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y,  game->floor_color);
			x++;
		}
		y++;
	}
	game->img.image = img;
}

void ft_draw_image(t_game *game, int pixels, mlx_image_t *image)
{
    // Convertemos os valores double que você calculou na DDA
    // para variáveis locais, facilitando a leitura.
    double wallLineStart = game->img.wall_line_start;
    double wallLineEnd   = game->img.wall_line_end;

    // Convertemos para int para usar no loop de desenho.
    int drawStart = (int)floor(wallLineStart);
    int drawEnd   = (int)floor(wallLineEnd);

    // Calcula a altura (quantos pixels serão desenhados na tela).
    int lineHeight = drawEnd - drawStart;

    // Se lineHeight for 0 ou negativo, não há o que desenhar.
    if (lineHeight <= 0)
        return;

    // ------------------------------------------------------------
    // 1) Cálculo de wallX para descobrir em qual coluna da textura
    //    iremos começar (valor de 0 a 1 dentro da célula).
    // ------------------------------------------------------------
    double wallX;
    if (game->img.hit_side == 0)
        wallX = game->player_info.vector_pos[1] + game->img.perpendicular_dist * game->camera.ray_dir[1];
    else
        wallX = game->player_info.vector_pos[0] + game->img.perpendicular_dist * game->camera.ray_dir[0];

    // wallX fica no intervalo [0,1); remove a parte inteira
    wallX -= floor(wallX);

    // Converte wallX em coordenada X da textura (0 a TEX_WIDTH - 1)
    int texX = (int)(wallX * (double)TEX_WIDTH);

    // Inverte a coordenada X caso o raio esteja vindo “de trás”
    if (game->img.hit_side == 0 && game->camera.ray_dir[0] > 0)
        texX = TEX_WIDTH - texX - 1;
    if (game->img.hit_side == 1 && game->camera.ray_dir[1] < 0)
        texX = TEX_WIDTH - texX - 1;

    // ------------------------------------------------------------
    // 2) Cálculo do step e posição inicial na textura (texPos).
    // ------------------------------------------------------------
    // step = quantos pixels da textura "andamos" a cada 1 pixel da tela
    double step = 1.0 * TEX_HEIGHT / lineHeight;

    // Normalmente, a fórmula para texPos é:
    //   (drawStart - (WINDOW_HEIGHT / 2 - lineHeight / 2)) * step
    // Ou seja, o quanto o topo da linha está acima do meio da tela.
    double texPos = (drawStart - (WINDOW_HEIGHT / 2.0 - lineHeight / 2.0)) * step;

    // ------------------------------------------------------------
    // 3) Clamp de drawStart e drawEnd, ajustando também texPos.
    // ------------------------------------------------------------
    // Se drawStart for negativo, significa que parte da parede
    // deveria estar acima da tela. Precisamos "pular" essa parte
    // na textura, avançando texPos.
    if (drawStart < 0)
    {
        texPos += (0 - drawStart) * step;
        drawStart = 0;
    }
    if (drawEnd >= WINDOW_HEIGHT)
        drawEnd = WINDOW_HEIGHT - 1;

    // ------------------------------------------------------------
    // 4) Loop de desenho (varremos de drawStart até drawEnd).
    // ------------------------------------------------------------
    for (int y = drawStart; y < drawEnd; y++)
    {
        // Pegamos a coordenada Y da textura (entre 0 e TEX_HEIGHT-1).
        int texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;

        // Busca a cor no pixel (texX, texY) da textura apropriada.
        int color = get_texture_pixel(game, texX, texY);

        // Desenha na imagem final.
        mlx_put_pixel(image, pixels, y, color);
    }
}


unsigned int fix_color(unsigned int color)
{
    unsigned char t = ((unsigned char *)&color)[0];
    unsigned char r = ((unsigned char *)&color)[1];
    unsigned char g = ((unsigned char *)&color)[2];
    unsigned char b = ((unsigned char *)&color)[3];
    
    return ((t << 24) | (r << 16) | (g << 8) | b);
}


int get_texture_pixel(t_game *game, int texX, int texY)
{
    mlx_image_t *tex;

    // Seleciona a "imagem-textura" correta com base na direção da colisão:
    if (game->img.hit_side == 0)
    {
        if (game->camera.ray_dir[0] > 0)
            tex = game->img.east;
        else
            tex = game->img.west;
    }
    else
    {
        if (game->camera.ray_dir[1] > 0)
            tex = game->img.south;
        else
            tex = game->img.north;
    }

    if (!tex || !tex->pixels)
        return 0; // ou uma cor padrão

    int index = texY * TEX_WIDTH + texX;
    int *pixels = (int *)tex->pixels;
    int color = pixels[index];
    return fix_color(color);
}

void    ft_init_player(t_game *game)
{
	game->player_info.vector_pos[0] = game->map.p_col + 0.5;
	game->player_info.vector_pos[1] = game->map.p_row + 0.5;
	game->player_info.vector_dir[0] = -1;
	game->player_info.vector_dir[1] = 0;	
	game->player_info.x = game->map.p_col;
	game->player_info.y = game->map.p_row;
	game->camera.plane[0] = 0;
	game->camera.plane[1] = -0.66;
}

// Configurações comentadas para as direções 'N', 'S', 'E' e 'W'
// (os comentários permanecem para referência)

void ft_find_rays(t_game *game)
{
	int     pixels;
	double  multiplier; 
	double  camera_pixel[2];

	pixels = 0;
	multiplier = 0;
	game->camera.ray_dir[0] = 0;
	game->camera.ray_dir[1] = 0;
	while (pixels <= WINDOW_WIDTH)
	{
		multiplier = 2.0 * ((double)pixels / (double)WINDOW_WIDTH) - 1.0;
		camera_pixel[0] = game->camera.plane[0] * multiplier;
		camera_pixel[1] = game->camera.plane[1] * multiplier;
		game->camera.ray_dir[0] = game->player_info.vector_dir[0] + camera_pixel[0];
		game->camera.ray_dir[1] = game->player_info.vector_dir[1] + camera_pixel[1];
		ft_dda(game);
		ft_draw_image(game, pixels, game->img.image);
		pixels++;
	}
}

void ft_dda(t_game *game)
{
	double delta_distx;
	double delta_disty;
	double dist_side_x;
	double dist_side_y;
	double step_x;
	double step_y;
	double dda_line_size_x;
	double dda_line_size_y;
	int wall_map_pos[2];
	double wall_line_height;

	wall_line_height = 0;
	delta_distx = 0;
	delta_disty = 0;
	step_x = 0;
	step_y = 0;
	game->img.hit = 0;
	dda_line_size_x = 0;
	dda_line_size_y = 0;
	game->img.hit_side = -1;
	game->img.perpendicular_dist = 0;
	
	if (game->camera.ray_dir[0] != 0)
		delta_distx = fabs(1 / game->camera.ray_dir[0]);
	else
		delta_distx = INFINITY;
	if (game->camera.ray_dir[1] != 0)
		delta_disty = fabs(1 / game->camera.ray_dir[1]);
	else
		delta_disty = INFINITY;
	game->player_info.square_pos[0] = (int)game->player_info.vector_pos[0];
	game->player_info.square_pos[1] = (int)game->player_info.vector_pos[1];
	if (game->camera.ray_dir[0] < 0)
	{
		dist_side_x = (game->player_info.vector_pos[0] - game->player_info.square_pos[0]) * delta_distx;
		step_x = -1;
	}
	else
	{
		dist_side_x = (game->player_info.square_pos[0] + 1.0 - game->player_info.vector_pos[0]) * delta_distx;
		step_x = 1;
	}
	if (game->camera.ray_dir[1] < 0)
	{
		dist_side_y = (game->player_info.vector_pos[1] - game->player_info.square_pos[1]) * delta_disty;
		step_y = -1;
	}
	else
	{
		dist_side_y = (game->player_info.square_pos[1] + 1.0 - game->player_info.vector_pos[1]) * delta_disty;
		step_y = 1;
	}
	dda_line_size_x = dist_side_x;
	dda_line_size_y = dist_side_y;
	wall_map_pos[0] = game->player_info.square_pos[0];
	wall_map_pos[1] = game->player_info.square_pos[1];
	while (game->img.hit == 0)
	{
		if (dda_line_size_x < dda_line_size_y)
		{
			dda_line_size_x += delta_distx;
			wall_map_pos[0] += step_x;
			game->img.hit_side = 0;
		}
		else
		{
			dda_line_size_y += delta_disty;
			wall_map_pos[1] += step_y;
			game->img.hit_side = 1;
		}
		if (game->map.matrix[wall_map_pos[1]][wall_map_pos[0]] == '1')
			game->img.hit = 1;
	}
	if (game->img.hit_side == 0)
		game->img.perpendicular_dist = fabs((wall_map_pos[0] - game->player_info.vector_pos[0] + ((1 - step_x) / 2)) / game->camera.ray_dir[0]);
	else
		game->img.perpendicular_dist = fabs((wall_map_pos[1] - game->player_info.vector_pos[1] + ((1 - step_y) / 2)) / game->camera.ray_dir[1]);
	wall_line_height = (WINDOW_HEIGHT / game->img.perpendicular_dist);
	game->img.wall_line_start = WINDOW_HEIGHT / 2 - wall_line_height / 2;
	game->img.wall_line_end = WINDOW_HEIGHT / 2 + wall_line_height / 2;
}
