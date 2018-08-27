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
		printf("g->ray_dir_x = %f, g->ray_dir_y = %f\n", g->ray_dir_x, g->ray_dir_y);
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
		g->draw_end = g->line_height / 2 + g->size_y / 2;   // shukaty tut!
		//printf("perp_wall_dist = %f, g->size_y = %d, line_height = %d, g->draw_start = %d, end = %d\n", g->perp_wall_dist, g->size_y, g->line_height, g->draw_start, g->draw_end);
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
		g->start = g->draw_start;
		if (g->draw_end > 767)
			g->draw_end = 767;
		//printf("g->text_x = %d\n", g->text_x);
		//printf("calculating: start = %d, end = %d i = %d\n", g->start, g->draw_end, g->i);
		//printf("g->start = %d, g->draw_start = %d\n", g->start, g->draw_start);
		// if (g->text_num == 5 && g->dir_x)
		// {

		// }
		while (g->start < g->draw_end)
		{
			if (g->line_height < g->size_y)
				g->text_y = 63 - (int)((double)g->draw_end - (double)g->start) / (double)g->line_height * ((double)g->text_h - 1);
			else if (g->line_height > g->size_y)
			{
				g->draw = (63 - (double)g->size_y / (double)g->line_height * 63.0) / 2;
				g->text_y = (int)(((double)g->size_y / (double)g->line_height) * (double)g->text_h / (double)g->size_y * (double)g->start + g->draw);
			}
			//printf("g->draw_end = %d, g->start = %d, g->draw = %f, line_heght = %d, g->text_y = %d, g->text_num = %d\n", g->draw_end, g->start, g->draw, g->line_height, g->text_y, g->text_num);
			//if (g->text_y > 64)
			//	break ;
			// printf("g->text_y = %f\n", g->text_y);
			// printf("g->line_height = %d\n", g->line_height);
			//printf("g->draw = %d\n", (int)g->draw);
			//printf("textures[num] = %d, text_y = %d, start = %d, end = %d, g->text_h = %d\n", g->text_num, g->text_y, g->start, g->draw_end, g->text_h);
			g->color.channel[0] = g->textures[g->text_num][g->text_y * g->text_w * 4 + g->text_x * 4];
			g->color.channel[1] = g->textures[g->text_num][g->text_y * g->text_w * 4 + g->text_x * 4 + 1];
			g->color.channel[2] = g->textures[g->text_num][g->text_y * g->text_w * 4 + g->text_x * 4 + 2];
			//printf("color = %x\n", g->color.color);
			if (g->side == 1)
				g->color.color = (g->color.color >> 1) & 8355711;
			g->scr_buff[g->start][g->i] = g->color.color;
			//printf("scr_buff[%d] = %x\n", g->start, g->scr_buff[g->start][g->i]);
			g->start++;
		}
		//printf("g->start = %d, g->draw_start = %d\n", g->start, g->draw_start);
		g->i++;
	}
	//print_arr(g->scr_buff, g->size_x, g->size_y);
	buffer_draw(g);
	ft_clean_buffer(g);
}

void	buffer_draw(t_general *g)
{
	t_color	color;

	//print_arr(g->scr_buff, g->size_x, g->size_y);
	//printf("start = %d, end = %d\n", g->draw_start, g->draw_end);
	g->i = 0;
	while (g->i < g->size_x)
	{
		//printf("drawing: start = %d, end = %d, i = %d\n", g->draw_start, g->draw_end, g->i);
		g->j = 0;
		while (g->j < g->size_y)
		{
			color.color = g->scr_buff[g->j][g->i];
			//printf("color = %x, g->j = %d\n", color.color, g->j);
			put_pixel(g, g->i, g->j, color);
			//printf("start = %d, end = %d, pixel[%d][%d] = %x\n", g->start, g->draw_end, g->j, g->i, g->scr_buff[g->j][g->i]);
			g->j++;
		}
		g->i++;
	}
}

void	ft_clean_buffer(t_general *g)
{
	g->j = 0;
	while (g->j < g->size_y - 1)
	{
		g->i = 0;
		while (g->i < g->size_x - 1)
		{
			g->scr_buff[g->j][g->i] = 0;
			g->i++;
		}
		g->j++;
	}
}
