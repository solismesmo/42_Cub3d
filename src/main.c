/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:14:31 by livieira          #+#    #+#             */
/*   Updated: 2025/03/27 20:31:26 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_msg_color_fmt(char **tokens, t_game *game)
{
	ft_error("Error: Invalid color format\n", game);
	ft_free_map(tokens);
	return ;
}

int	main(int argc, char **argv)
{
	t_game	*game;

	ft_check_args(argc, argv);
	game = ft_init_values();
	game->map_name = argv[1];
	ft_map_open(game);
	ft_init_map(game);
	if (game->map.check_inputs != 6)
		ft_error("Error: Missing texture or color\n", game);
	ft_init_mlx(game);
	ft_init_game(game);
	mlx_key_hook(game->mlx, &ft_keyhooks, game);
	mlx_loop(game->mlx);
	ft_finish("Thanks for playing", game);
	return (0);
}
