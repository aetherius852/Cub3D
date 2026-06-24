/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 13:31:49 by efsilva-          #+#    #+#             */
/*   Updated: 2026/06/22 10:51:32 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	check_chars(t_cub *cub)
{
	int	i;
	int	j;
	int	players;

	i = 0;
	players = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (!is_valid_char(cub->map[i][j]))
				ft_error(cub, ERR_CHAR);
			if (is_player(cub->map[i][j]))
				check_player(cub, i, j, &players);
			j++;
		}
		i++;
	}
	if (players != 1)
		ft_error(cub, ERR_PLAYER);
}

static void	check_space_neighbors(t_cub *cub, int i, int j)
{
	int	row_len;

	if (i == 0 || i == cub->map_height - 1)
		ft_error(cub, ERR_CLOSE);
	row_len = ft_strlen(cub->map[i - 1]);
	if (j >= row_len || cub->map[i - 1][j] == ' ')
		ft_error(cub, ERR_CLOSE);
	row_len = ft_strlen(cub->map[i + 1]);
	if (j >= row_len || cub->map[i - 1][j] == ' ')
		ft_error(cub, ERR_CLOSE);
	if (j == 0 || cub->map[i][j - 1] == ' ')
		ft_error(cub, ERR_CLOSE);
	if (!cub->map[i][j + 1] || cub->map[i][j + 1] == ' ')
		ft_error(cub, ERR_CLOSE);
}

static void	check_open_ceils(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '0' || is_player(cub->map[i][j]))
				check_space_neighbors(cub, i, j);
			j++;
		}
		i++;
	}
}

void	valid_map(t_cub *cub)
{
	if (!cub->map || cub->map_height == 0)
		ft_error(cub, ERR_MAP);
	check_chars(cub);
	check_open_ceils(cub);
}
