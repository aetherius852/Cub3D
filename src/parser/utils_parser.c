/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/06/24 13:33:32 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

char	*read_line(int fd)
{
	char	*line;
	char	c;
	int		bytes;
	int		i;

	line = malloc(10000);
	if (!line)
		return (NULL);
	i = 0;
	bytes = read(fd, &c, 1);
	while (bytes > 0)
	{
		if (c == '\n')
			break ;
		line[i++] = c;
		bytes = read(fd, &c, 1);
	}
	line[i] = '\0';
	if (bytes <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	ft_error(t_cub *cub, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	if (cub)
		free_cub(cub);
	exit(1);
}

void	free_map(t_cub *cub)
{
	int	i;

	i = 0;
	if (!cub->map)
		return ;
	while (cub->map[i])
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
	cub->map = NULL;
}

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->no_texture)
		free(cub->no_texture);
	if (cub->so_texture)
		free(cub->so_texture);
	if (cub->we_texture)
		free(cub->we_texture);
	if (cub->ea_texture)
		free(cub->ea_texture);
	free_map(cub);
}
