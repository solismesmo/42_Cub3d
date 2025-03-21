/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:44:25 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/03/21 03:15:17 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_char_allowed(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '1' || c == '0' || c == ' ' || c == '\n')
		return (1);
	else
		return (0);
}

void	ft_char_check(t_game *game)
{
	int	i;
	int	j;
	i = 0;
	while (i < game->map.lines)
	{
		j = 0;
		while (game->map.matrix[i][j])
		{
			if (!ft_char_allowed(game->map.matrix[i][j]))
			{
				printf("Char: %c\n", game->map.matrix[i][j]);
				ft_error("Forbidden char on the map\n", game);
			}
			j++;
		}
		i++;
	}
	game->map.rows = i;
}

void	ft_map_condition(t_game *game)
{
	// if (game->map.exits != 1)
	// 	ft_error("The map doesn't have exit or have more then one exit\n", game);
	// if (game->map.coin == 0)
	// 	ft_error("The map doesn't have at least one collectable\n", game);
	if (game->map.player != 1)
		ft_error("have zero or more then one player\n", game);
	return ;
} 

void ft_mark_visited(t_game *game, int row, int col)
{
    // Marca a célula como visitada
    game->map.matrix_fill[row][col] = 'x';
}

int ft_dfs_closed(t_game *game, int row, int col)
{
    int next_row;
    int next_col;
    int i;
    int row_length;

    // Obtém o comprimento da linha atual
    row_length = strlen(game->map.matrix[row]);

    // Verifica se a célula atual está na borda do mapa.
    // Considera: primeira ou última linha ou primeira ou última coluna da linha.
    if (row == 0 || row == game->map.rows - 1 ||
        col == 0 || col == row_length - 1)
    {
        printf("Erro: mapa aberto na posição [%d][%d]\n", row, col);
        return (0);
    }

    ft_mark_visited(game, row, col);

    i = 0;
    while (i < 4)
    {
        next_row = row + game->map.row_move[i];
        next_col = col + game->map.col_move[i];

        // Verifica se next_row está dentro do número de linhas
        if (next_row >= 0 && next_row < game->map.rows)
        {
            // Obtém o comprimento da linha de destino
            int next_row_length = strlen(game->map.matrix[next_row]);
            if (next_col >= 0 && next_col < next_row_length &&
                game->map.matrix[next_row][next_col] != '1' &&
                game->map.matrix_fill[next_row][next_col] != 'x')
            {
                // Se alguma chamada recursiva detectar que a borda foi alcançada,
                // retorna 0 imediatamente.
                if (!ft_dfs_closed(game, next_row, next_col))
                    return (0);
            }
        }
        i++;
    }
    // Se em nenhuma parte da área acessível foi encontrada uma célula de borda,
    // então a área está completamente cercada por paredes.
    return (1);
}

void ft_check_closed(t_game *game)
{
    if (ft_dfs_closed(game, game->map.p_row, game->map.p_col))
        return;
    else
    {
        print_fill_matrix(game);
        ft_error("O mapa não está fechado por paredes", game);
    }
}

void	print_fill_matrix(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map.matrix_fill[i] != NULL)
    {
        j = 0;
        while (game->map.matrix_fill[i][j] != '\0')
        {
            printf("%c", game->map.matrix_fill[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void	print_matrix(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map.matrix[i] != NULL)
    {
        j = 0;
        while (game->map.matrix[i][j] != '\0')
        {
            printf("%c", game->map.matrix[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}