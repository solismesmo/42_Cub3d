/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils_II.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:48:24 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/02/28 21:26:52 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_last_line(char **matrix, t_game	*game)
{
	int	i;

	i = 0;
	while (matrix[game->map.rows - 1][i])
	{
		if (matrix[game->map.rows - 1][i] != '1')
			ft_error("Missing walls\n", game);
		i++;
	}
}

void	ft_increment_player(t_game *game, int i, int j, char dir)
{
    if (game->player_info.found)
    {
        printf("Error: more than one player!\n");
        exit(1);
    }
    game->player_info.found = 1;
    game->player_info.x = j;
    game->player_info.y = i;
    game->player_info.direction = dir;
	
	printf("Player found at (%d, %d) with direction %c\n", i, j, dir);  // Adicione essa linha para depuração
}

void	ft_check_walls(t_game *game)
{
    int	i, j;

    j = 0;
    while (game->map.matrix[0][j])
    {
        if (game->map.matrix[0][j] != '1' && game->map.matrix[0][j] != ' ')
        {
            printf("Error: open map in superior line.\n");
            exit(1);
        }
        j++;
    }
    j = 0;
    while (game->map.matrix[game->map.lines - 1][j])
    {
        if (game->map.matrix[game->map.lines - 1][j] != '1' && game->map.matrix[game->map.lines - 1][j] != ' ')
        {
            printf("Error: open map inferior line.\n");
            exit(1);
        }
        j++;
    }
    i = 0;
    while (i < game->map.lines)
    {
        if (game->map.matrix[i][0] != '1' && game->map.matrix[i][0] != ' ')
        {
            printf("Error: open map col L.\n");
            exit(1);
        }
        if (game->map.matrix[i][game->map.columns - 1] != '1' && game->map.matrix[i][game->map.columns - 1] != ' ')
        {
            printf("Error: open map col R.\n");
            exit(1);
        }
        i++;
    }
}


void	ft_map_lego(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.lines)
	{
		j = 0;
		while (game->map.matrix[i][j])
		{
			if (game->map.matrix[i][j] == 'P' || game->map.matrix[i][j] == 'N' || \
            game->map.matrix[i][j] == 'S' || game->map.matrix[i][j] == 'W')
            {
                game->map.player++;
	            game->map.p_row = i;
	            game->map.p_col = j;
            }
			j++;
		}
		i++;
	}
    ft_check_walls(game);
    ft_map_condition(game);
}

void	ft_init_moves(t_game *game)
{
	game->map.row_move[0] = -1;
	game->map.row_move[1] = 1;
	game->map.row_move[2] = 0;
	game->map.row_move[3] = 0;
	game->map.col_move[0] = 0;
	game->map.col_move[1] = 0;
	game->map.col_move[2] = -1;
	game->map.col_move[3] = 1;
	game->moves = 0;
	game->map.check_coins = 0;
	game->map.matrix_fill = NULL;
}
