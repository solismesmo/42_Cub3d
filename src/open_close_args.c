/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:43:03 by bgomes-l          #+#    #+#             */
/*   Updated: 2025/04/03 16:38:05 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_open(t_game *game)
{
	game->fd = open(game->map_name, O_RDONLY);
	if (game->fd == -1)
		ft_error("The map does not exist\n", game);
}

int	ft_map_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("Error closing file");
		return (1);
	}
	return (0);
}

void	ft_check_args(int argc, char **argv)
{
	char			*map_ext;
	unsigned int	comp;
	int				ext_len;

	if (argc > 2)
		ft_error_message("Too many arguments\n");
	if (argc < 2)
		ft_error_message("Too few arguments\n");
	map_ext = (ft_strrchr(argv[1], 46));
	if (!map_ext)
		ft_error_message("Invalid file name: Missing extension.\n");
	ext_len = ft_strlen(map_ext);
	if (ext_len < 4)
		ext_len = 4;
	comp = ft_strncmp(map_ext, MAP_EXT_DEF, ext_len);
	if (comp != 0)
		ft_error_message("The file must to be a (.cub) file.\n");
}
