/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:29:41 by bruno             #+#    #+#             */
/*   Updated: 2025/03/29 19:44:39 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mark_visited(t_game *game, int row, int col)
{
	game->map.matrix_fill[row][col] = 'x';
}

int ft_dfs_closed(t_game *game, int row, int col)
{
    //int next_row;
    //int next_col;
    int i;
    int row_length;
    int row_move[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int col_move[8] = {0, 0, -1, 1, -1, 1, -1, 1};

    // Obtém o comprimento da linha atual
    row_length = strlen(game->map.matrix[row]);

    // Verifica se a célula atual está na borda do mapa.
    // Considera: primeira ou última linha ou primeira ou última coluna da linha.
    if ((row == 0 || row == game->map.rows - 1 ||
        col == 0 || col == row_length - 1) &&
       game->map.matrix[row][col] != '1')
       ft_error("Missing Walls", game);
    ft_mark_visited(game, row, col);

    i = 0;
    while (i < 8)
    {
        int next_row = row + row_move[i];
        int next_col = col + col_move[i];
    
        // Verifica se next_row está dentro dos limites do mapa
        if (next_row < 0 || next_row >= game->map.rows)
            ft_error("Missing Walls", game);
        
        // Obtém o comprimento da linha de destino
        int next_row_length = strlen(game->map.matrix[next_row]);
        
        // Se a coluna estiver fora do intervalo válido, considera abertura
        if (next_col < 0 || next_col >= next_row_length)
            ft_error("Missing Walls", game);
        
        // Se a célula de destino não for parede e ainda não foi visitada...
        if (game->map.matrix[next_row][next_col] != '1' &&
            game->map.matrix_fill[next_row][next_col] != 'x')
        {
            if (!ft_dfs_closed(game, next_row, next_col))
                return (0);
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
        //print_fill_matrix(game);
        ft_error("Missing Walls", game);
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

void	ft_check_closed(t_game *game)
{
	if (ft_dfs_closed(game, game->map.p_row, game->map.p_col))
		return ;
	else
		ft_error("The map is not closed by walls", game);
}
