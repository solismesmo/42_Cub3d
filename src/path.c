/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:49:41 by livieira          #+#    #+#             */
/*   Updated: 2025/03/27 21:57:42 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_path(char *path)
{
	if (!path || !(*path))
		return ;
	while (*path != '\n')
	{
		path++;
	}
	*path = '\0';
}

int	ft_check_texture_path(const char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_error("Error: Trying to open texture path", game);
		return (0);
	}
	close(fd);
	return (1);
}
