/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils_II.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:48:24 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/02/26 19:39:30 by livieira         ###   ########.fr       */
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

    game->map.walls = 0;
    game->player_info.found = 0;

    i = 0;
    printf("Mapa carregado:\n");
    for (int i = 0; game->map.matrix[i]; i++)
    printf("%s\n", game->map.matrix[i]);

    printf("\nProcurando jogador...\n");

    if (!game->map.matrix)
    {
        printf("Error: game->map.matrix é NULL!\n");
        exit(1);
    }


    while (i < game->map.lines)
    {
        j = 0;
        while (game->map.matrix[i][j])
        {
            if (game->map.matrix[i][j] == '1')
                game->map.walls++;
            if (game->map.matrix[i][j] == '0')
            {
				
			}
            printf("Pos [%d][%d]: %c\n", i, j, game->map.matrix[i][j]);
            if (game->map.matrix[i][j] == 'N' || game->map.matrix[i][j] == 'S'
                  || game->map.matrix[i][j] == 'E' || game->map.matrix[i][j] == 'W')
                ft_increment_player(game, i, j, game->map.matrix[i][j]);
            else
            {
                printf("Error: invalid char: %c\n", game->map.matrix[i][j]);
                exit(1);
            }
            j++;
        }
        i++;
    }
    if (!game->player_info.found)
    {
        printf("Error: no player!\n");
        exit(1);
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
