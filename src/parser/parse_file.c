/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:36:15 by efsilva-          #+#    #+#             */
/*   Updated: 2026/06/22 11:08:33 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	check_extension(t_cub *cub, const char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		ft_error(cub, ERR_EXT);
	if (ft_strncmp(path + len - 4, "cub", 4) != 0)
		ft_error(cub, ERR_EXT);
}

static int	open_file(t_cub *cub, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error(cub, ERR_OPEN);
	return (fd);
}

void	parse_file(t_cub *cub, const char *path)
{
	int	fd;

	check_extension(cub, path);
	fd = open_file(cub, path);
	parse_config(cub, fd);
	close(fd);
	valid_map(cub);
}
