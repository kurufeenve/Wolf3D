/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:47:30 by vordynsk          #+#    #+#             */
/*   Updated: 2018/07/31 16:47:33 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	raycaster(t_general *g)
{
	g->pos_x = 22;
	g->pos_y = 12;
	g->dir_x = -1;
	g->dir_y = 0;
	g->plane_x = 0;
	g->plane_y = 0.66;
	g->newtime = 0;
	g->oldtime = 0;
	g->i = 0;
	while (g->i < g->size_x)
	{
		g->camera_x = 2 * g->i / (double)g->size_x - 1;
		g->ray_dir_x = g->dir_x + g->plane_x * g->camera_x;
		g->ray_dir_y = g->dir_y + g->plane_y * g->camera_x;
		g->map_x = (int)g->pos_x;
		g->map_y = (int)g->pos_y;
		g->delta_dist_x = abs(1 / g->ray_dir_x);
		g->delta_dist_y = abs(1 / g->ray_dir_y);
		g->hit = 0;
		if (g->ray_dir_x < 0)
		{
			g->step_x = -1;
			g->side_dist_x = (g->pos_x - g->map_x) * g->delta_dist_x;
		}
		else
		{
			g->step_x = 1;
			g->side_dist_x = (g->map_x + 1.0 - g->pos_x) * g->delta_dist_x;
		}
		if (g->ray_dir_y < 0)
		{
			g->step_y = -1;
			g->side_dist_y = (g->pos_y - g->map_y) * g->delta_dist_y;
		}
		else
		{
			g->step_y = 1;
			g->side_dist_y = (g->map_y + 1.0 - g->pos_y) * g->delta_dist_y;
		}
		while (g->hit == 0)
		{
			if (g->side_dist_x < g->side_dist_y)
			{
				g->side_dist_x += g->delta_dist_x;
				g->map_x += g->step_x;
				g->side = 0;
			}
			else
			{
				g->side_dist_y += g->delta_dist_y;
				g->map_y += g->step_y;
				g->side = 1;
			}
			if (g->points[g->map_y][g->map_x] > 0) // may be you should read the map reverce. [x][y]
				g->hit = 1;
		}
		g->i++;
	}
}
