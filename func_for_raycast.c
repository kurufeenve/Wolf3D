/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_for_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 15:09:21 by vordynsk          #+#    #+#             */
/*   Updated: 2018/08/30 15:09:23 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	four_textures(t_general *g)
{
	if (g->text_num == 5 && g->side == 1 && g->pos_y < g->map_y)
	{
		g->text_num = g->text_num - 1;
	}
	else if (g->text_num == 5 && g->side == 0 && g->pos_x < g->map_x)
	{
		g->text_num = g->text_num - 2;
	}
	else if (g->text_num == 5 && g->side == 0 && g->pos_x > g->map_x)
	{
		g->text_num = g->text_num - 3;
	}
}

void	ft_hit(t_general *g)
{
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
		if (g->points[g->map_y][g->map_x] > 0)
			g->hit = 1;
	}
}

void	ft_ray(t_general *g)
{
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
}

void	a_bunch_of_stuff(t_general *g)
{
	if (g->side == 0)
		g->perp_wall_dist = (g->map_x - g->pos_x + (1 - g->step_x) / 2) \
		/ g->ray_dir_x;
	else
		g->perp_wall_dist = (g->map_y - g->pos_y + (1 - g->step_y) / 2) \
		/ g->ray_dir_y;
	g->line_height = (int)(g->size_y / g->perp_wall_dist);
	g->draw_start = -g->line_height / 2 + g->size_y / 2;
	g->draw_end = g->line_height / 2 + g->size_y / 2;
	if (g->draw_start < 0)
		g->draw_start = 0;
	if (g->draw_end > g->size_y)
		g->draw_end = g->size_y - 1;
	g->text_num = g->points[g->map_y][g->map_x] - 1;
	if (g->side == 0)
		g->wall_x = g->pos_y + g->perp_wall_dist * g->ray_dir_y;
	else
		g->wall_x = g->pos_x + g->perp_wall_dist * g->ray_dir_x;
	g->wall_x -= floor(g->wall_x);
	g->text_x = (int)(g->wall_x * (double)g->text_w);
	if (g->side == 0 && g->ray_dir_x > 0)
		g->text_x = g->text_w - g->text_x - 1;
	if (g->side == 1 && g->ray_dir_y < 0)
		g->text_x = g->text_w - g->text_x - 1;
}

void	text_map_and_color(t_general *g)
{
	while (g->start < g->draw_end)
	{
		if (g->line_height < g->size_y)
			g->text_y = 63 - (int)((double)g->draw_end - (double)g->start)\
			/ (double)g->line_height * ((double)g->text_h - 1);
		else if (g->line_height > g->size_y)
		{
			g->draw = (63 - (double)g->size_y / \
			(double)g->line_height * 63.0) / 2;
			g->text_y = (int)(((double)g->size_y / (double)g->line_height)\
			* (double)g->text_h / (double)g->size_y * (double)g->start \
			+ g->draw);
		}
		g->color.channel[0] = g->textures[g->text_num][g->text_y * \
		g->text_w * 4 + g->text_x * 4];
		g->color.channel[1] = g->textures[g->text_num][g->text_y * \
		g->text_w * 4 + g->text_x * 4 + 1];
		g->color.channel[2] = g->textures[g->text_num][g->text_y * \
		g->text_w * 4 + g->text_x * 4 + 2];
		if (g->side == 1)
			g->color.color = (g->color.color >> 1) & 8355711;
		g->scr_buff[g->start][g->i] = g->color.color;
		g->start++;
	}
}
