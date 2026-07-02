/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 13:24:25 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/02 01:55:55 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static int	game_loop(t_cub *cub)
{
	move_player(cub);
	render(cub);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		ft_error(NULL, ERR_ARGS);
	init_cub(&cub);
	parse_file(&cub, av[1]);
	init_player_dir(&cub);
	init_mlx(&cub);
	load_textures(&cub);
	render(&cub);
	listen_for_input(&cub);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
