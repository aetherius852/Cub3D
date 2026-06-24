/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 13:24:25 by efsilva-          #+#    #+#             */
/*   Updated: 2026/06/24 13:34:01 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	main(int ac, int **av)
{
	t_cub	cub;

	if (ac != 2)
		ft_error(NULL, ERR_ARGS);
	init_cub(&cub);
	parse_files(&cub, av[1]);
	free_cub(&cub);
	return (0);
}
