/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:41 by bruno             #+#    #+#             */
/*   Updated: 2025/02/28 23:48:38 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void   ft_init_game(t_game *game)
{
	ft_init_player(game);
	ft_init_textures(game);
	ft_init_image(game);
	ft_find_rays(game);
}

void	ft_init_textures(t_game *game)
{
	ft_place_png(game, &game->img.north, NO);
	ft_place_png(game, &game->img.south, SO);
	ft_place_png(game, &game->img.west, WE);
	ft_place_png(game, &game->img.east, EA);
}

void	ft_place_png(t_game *game, mlx_image_t **image, char *path)
{
	mlx_texture_t	*my_texture;

	my_texture = mlx_load_png(path);
	*image = mlx_texture_to_image(game->mlx, my_texture);
	mlx_delete_texture(my_texture);
}

void ft_init_image(t_game *game)
{
	mlx_image_t* img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
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
	game->img.image = img;
}

void    ft_draw_image(t_game *game, int pixels, mlx_image_t *image)
{
	if (game->img.wall_line_start < 0)
	{
		game->img.wall_line_start = 0;
	}
	if (game->img.wall_line_end >= WINDOW_HEIGHT)
	{
		game->img.wall_line_end = WINDOW_HEIGHT - 1;
	}
	int drawStart = game->img.wall_line_start;
    int drawEnd = game->img.wall_line_end;
    int lineHeight = drawEnd - drawStart;

    // Calcula wallX, que indica a posição exata de impacto na parede (valor entre 0 e 1)
    double wallX;
    if (game->img.hit_side == 0)
        wallX = game->player_info.vector_pos[1] + game->img.perpendicular_dist * game->camera.ray_dir[1];
    else
        wallX = game->player_info.vector_pos[0] + game->img.perpendicular_dist * game->camera.ray_dir[0];
    wallX -= floor(wallX);

    // Converte wallX para a coordenada X da textura
    int texX = (int)(wallX * (double)TEX_WIDTH);
    // Inverte a coordenada se necessário (dependendo da direção do raio)
    if (game->img.hit_side == 0 && game->camera.ray_dir[0] > 0)
        texX = TEX_WIDTH - texX - 1;
    if (game->img.hit_side == 1 && game->camera.ray_dir[1] < 0)
        texX = TEX_WIDTH - texX - 1;

    // Calcula o quanto a textura deve avançar a cada pixel da parede desenhada
    double step = (double)TEX_HEIGHT / lineHeight;
    // Ajusta a posição inicial na textura
    // Aqui, usamos (WINDOW_HEIGHT / 2 - lineHeight / 2) como referência para o topo da parede desenhada
    double texPos = (drawStart - (WINDOW_HEIGHT / 2 - lineHeight / 2)) * step;

    // Para cada pixel na coluna, mapeia a posição correspondente da textura e desenha o pixel
    for (int y = drawStart; y < drawEnd; y++)
    {
        int texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;
        int color = get_texture_pixel(game, texX, texY);
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

    // Corrige a ordem dos canais, se necessário
    return fix_color(color);
}

void    ft_init_player(t_game *game)
{
	game->player_info.vector_pos[0] = game->map.p_row;
	game->player_info.vector_pos[1] = game->map.p_col;
	game->player_info.vector_dir[0] = -1;
	game->player_info.vector_dir[1] = 0;
	game->player_info.x = game->map.p_row;
	game->player_info.y = game->map.p_col;
	game->camera.plane[0] = 0;
	game->camera.plane[1] = -0.66;
}

// Para 'N' (Norte):
// Já está definido como:

// vector_dir = (0, -1)
// camera.plane = (0.66, 0)
// (Isso está correto)
// Para 'S' (Sul):
// Uma configuração comum é:

// vector_dir = (0, 1)
// camera.plane = (-0.66, 0)
// Se os comandos de seta estão invertidos, pode ser necessário ajustar o sinal do vetor do plano ou tratar a rotação de forma consistente com essa configuração.
// Para 'E' (Leste):
// Uma configuração adequada seria:

// vector_dir = (1, 0)
// camera.plane = (0, 0.66)
// (Observe que o vetor do plano é perpendicular a (1, 0).)
// Para 'W' (Oeste):
// Configure como:

// vector_dir = (-1, 0)
// camera.plane = (0, -0.66)
// (Aqui também, o vetor do plano precisa ser perpendicular a (-1, 0).)

void ft_find_rays(t_game *game)
{
	int     pixels;
	float   multiplier; 
	float   camera_pixel[2];

	pixels = 0;
	multiplier = 0;
	game->camera.ray_dir[0] = 0;
	game->camera.ray_dir[1] = 0;
	while (pixels <= WINDOW_WIDTH)
	{
		multiplier = 2.0f * ((float)pixels / (float)WINDOW_WIDTH) -1.0f;
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
	float delta_distx;
	float delta_disty;
	float dist_side_x;
	float dist_side_y;
	float step_x;
	float step_y;
	float dda_line_size_x;
	float dda_line_size_y;
	int wall_map_pos[2];
	float wall_line_height;

	wall_line_height= 0;
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
		if(game->map.matrix[wall_map_pos[1]][wall_map_pos[0]] == '1')
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


