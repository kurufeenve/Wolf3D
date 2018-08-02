/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:32:23 by vordynsk          #+#    #+#             */
/*   Updated: 2018/08/02 18:32:25 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_screen_stuff(t_general *g)
{
	ft_clearscr(g);
	mlx_clear_window(g->init, g->win);
	raycaster(g);
	mlx_put_image_to_window(g->init, g->win, g->img, 0, 0);
}

void	ft_move(t_general *g, double move)
{
	if (g->points[(int)(g->pos_y + (g->dir_y * move))][(int)(g->pos_x +
	(g->dir_x * move))] == 0)
	{
		g->pos_x = g->pos_x + (g->dir_x * move);
		g->pos_y = g->pos_y + (g->dir_y * move);
	}
}
