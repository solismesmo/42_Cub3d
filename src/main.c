/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:14:31 by livieira          #+#    #+#             */
/*   Updated: 2025/01/15 21:26:18 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	ft_check_args(argc, argv);
	game = ft_init_values();
	game->map_name = argv[1];
	ft_map_open(game);
	ft_init_map(game);
	ft_init_mlx(game);
	ft_image_init(game);
	mlx_key_hook(game->mlx, &ft_keyhooks, game);
	mlx_loop(game->mlx);
	ft_finish("Thanks for playing", game);
	return (0);
}
