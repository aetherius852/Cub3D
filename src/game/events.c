/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/02 02:06:57 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	handle_keypress(int key, t_cub *cub)
{
	if (key == 65307)
		exit_clean(cub, 0);
	return (0);
}

int	handle_close(t_cub *cub)
{
	exit_clean(cub, 0);
	return (0);
}
