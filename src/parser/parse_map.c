/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:31:31 by efsilva-          #+#    #+#             */
/*   Updated: 2026/06/22 10:46:18 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static char	**grow_map(t_cub *cub, char **map, int count)
{
	char	**new_map;
	int		i;

	new_map = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_map)
	{
		free_map(cub);
		ft_error(cub, ERR_MALLOC);
	}
	i = 0;
	while (i < count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

static char	add_line(t_cub *cub, char *line, int i)
{
	int	len;

	len = ft_strlen(line);
	if (len > cub->map_width)
		cub->map_width = len;
	cub->map[i] = ft_strdup(line);
	if (!cub->map[i])
		ft_error(cub, ERR_MALLOC);
}

void	parse_map(t_cub *cub, int fd)
{
	char	*line;
	int		i;

	cub->map = (char **)malloc(sizeof(char *) * 2);
	if (!cub->map)
		ft_error(cub, ERR_MALLOC);
	cub->map[0] = NULL;
	i = 0;
	line = read_line(fd);
	while (line)
	{
		if (ft_strlen(line) > 0)
		{
			cub->map = grow_map(cub, cub->map, i);
			add_line(cub, line, i);
			i++;
		}
		free(line);
		line = read_line(fd);
	}
	if (i == 0)
		ft_error(cub, ERR_MALLOC);
	cub->map[i] = NULL;
	cub->map_height = i;
}
