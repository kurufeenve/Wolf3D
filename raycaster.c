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
		ft_ray(g);
		ft_hit(g);
		a_bunch_of_stuff(g);
		if (g->draw_end > 767)
			g->draw_end = 767;
		four_textures(g);
		g->start = g->draw_start;
		text_map_and_color(g);
		g->i++;
	}
	buffer_draw(g);
	ft_clean_buffer(g);
}

void	buffer_draw(t_general *g)
{
	t_color	color;

	g->i = 0;
	while (g->i < g->size_x)
	{
		g->j = 0;
		while (g->j < g->size_y)
		{
			color.color = g->scr_buff[g->j][g->i];
			put_pixel(g, g->i, g->j, color);
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

int		additional_map_validation(char *file_name, t_general *g)
{
	int		trigger;

	trigger = 0;
	if ((g->fd = open(file_name, O_RDONLY)) <= 0)
		return (0);
	while (get_next_line(g->fd, &g->line) > 0)
	{
		g->i = 0;
		while (g->line[g->i] != '\0')
		{
			if (g->line[g->i] == 'P' && trigger == 1)
				return (0);
			else if (g->line[g->i] == 'P' && trigger == 0)
				trigger = 1;
			g->i++;
		}
		ft_strdel(&g->line);
	}
	if (trigger == 0)
		return (0);
	return (1);
}

int		wall_validation(t_general *g)
{
	g->j = 0;
	while (g->j < g->rows)
	{
		g->i = 0;
		if (g->j == 0 || g->j == (g->rows - 1))
			while (g->i < g->len)
			{
				if (g->points[g->i * (g->j + 1)] == 0)
					return (0);
				g->i++;
			}
		else if (g->points[(g->j + 1) * 3] == 0 || g->points[(g->j + 1) * 3 + 2] == 0)
			return (0);
		g->j++;
	}
	return (1);
}
