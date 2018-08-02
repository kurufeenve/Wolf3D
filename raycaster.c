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
		g->delta_dist_x = fabs(1 / g->ray_dir_x);
		g->delta_dist_y = fabs(1 / g->ray_dir_y);
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
		if (g->side == 0)
			g->perp_wall_dist = (g->map_x - g->pos_x + (1 - g->step_x) / 2) / g->ray_dir_x;
		else
			g->perp_wall_dist = (g->map_y - g->pos_y + (1 - g->step_y) / 2) / g->ray_dir_y;
		g->line_height = (int)(g->size_y / g->perp_wall_dist);
		g->draw_start = -g->line_height / 2 + g->size_y / 2;
		g->draw_end = g->line_height / 2 + g->size_y / 2;
		if (g->draw_start < 0)
			g->draw_start = 0;
		if (g->draw_end > g->size_y)
			g->draw_end = g->size_y - 1;
		if (g->points[g->map_y][g->map_x] == 1) // may be you should read the map reverce. [x][y]
			g->color.color = 0xFF0000;
		else if (g->points[g->map_y][g->map_x] == 2)
			g->color.color = 0x00FF00;
		else if (g->points[g->map_y][g->map_x] == 3)
			g->color.color = 0x0000FF;
		else if (g->points[g->map_y][g->map_x] == 4)
			g->color.color = 0xFFFFFF;
		else
			g->color.color = 0xFFFF00;
		if (g->side == 1)
			g->color.color /= 2;
		vert_line_draw(g);
		g->i++;
	}
}

void	vert_line_draw(t_general *g)
{
	while (g->draw_start <= g->draw_end)
	{
		put_pixel(g, g->i, g->draw_start, g->color);
		g->draw_start++;
	}
}
