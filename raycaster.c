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
		g->text_num = g->points[g->map_y][g->map_x] - 1;
		if (g->side == 0)
			g->wall_x = g->pos_y + g->perp_wall_dist * g->ray_dir_y;
		else
			g->wall_x = g->pos_x + g->perp_wall_dist * g->ray_dir_x;
		g->wall_x -= floor(g->wall_x);
		g->text_xx = (int)(g->wall_x * (double)g->text_x);
		if (g->side == 0 && g->ray_dir_x > 0)
			g->text_xx = g->text_x - g->text_xx - 1;
		if (g->side == 1 && g->ray_dir_y < 0)
			g->text_xx = g->text_x - g->text_xx - 1;
		if (g->side == 1)
		{
			g->color.channel[0] /= 2;
			g->color.channel[1] /= 2;
			g->color.channel[2] /= 2;
		}
		g->start = g->draw_start;
		//printf("start = %d, end = %d\n", g->draw_start, g->draw_end);
		while (g->start < g->draw_end)
		{
			g->draw = g->start * 256 - g->size_y * 128 + g->line_height * 128;
			g->text_yy = ((g->draw * g->text_y) / g->line_height) / 256;
			//printf("textures[num] = %d, text_yy = %d\n", g->text_num, g->text_yy);
			g->color.color = g->textures[g->text_num][g->text_y * g->text_yy + g->text_xx];
			//printf("color = %x\n", g->color.color);
			if (g->side == 1)
				g->color.color = (g->color.color >> 1) & 8355711;
			g->scr_buff[g->start][g->i] = g->color.color;
			//printf("scr_buff = %x\n", g->scr_buff[g->start][g->i]);
			g->start++;
		}
		g->i++;
	}
	buffer_draw(g);
	ft_clean_buffer(g);
}

void	buffer_draw(t_general *g)
{
	t_color	color;

	//printf("start = %d, end = %d\n", g->draw_start, g->draw_end);
	g->i = 0;
	while (g->i < g->size_x)
	{
		g->start = g->draw_start;
		while (g->start < g->draw_end)
		{
			color.color = g->scr_buff[g->start][g->i];
			//printf("color = %x\n", color.color);
			put_pixel(g, g->i, g->start, color);
			//printf("start = %d, end = %d, pixel = %x, g->i = %d\n", g->start, g->draw_end, g->scr_buff[g->start][g->i], g->i);
			g->start++;
		}
		g->i++;
	}
}

void	ft_clean_buffer(t_general *g)
{
	g->j = 0;
	while (g->j < g->size_y)
	{
		g->i = 0;
		while (g->i < g->size_x)
		{
			g->scr_buff[g->j][g->i] = 0;
			g->i++;
		}
		g->j++;
	}
}
