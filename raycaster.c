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
	distance_to_sprite(g);
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
	draw_the_sprites(g);
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
				if (g->points[g->j][g->i] == 0)
					return (0);
				g->i++;
			}
		else if (g->points[g->j][0] == 0 || g->points[g->j][g->len - 1] == 0)
			return (0);
		g->j++;
	}
	return (1);
}

void	distance_to_sprite(t_general *g)
{
	g->sprite.distance = sqrt((g->sprite.pos_x - g->pos_x) * (g->sprite.pos_x - g->pos_x) +
	(g->sprite.pos_y - g->pos_y) * (g->sprite.pos_y - g->pos_y));
	printf("g->sprite.pos_x = %f, g->sprite.pos_y = %f, g->pos_x = %f, g->pos_y = %f\
g->sprite.distance = %f\n",
	g->sprite.pos_x, g->sprite.pos_y, g->pos_x, g->pos_y, g->sprite.distance);
}

void	draw_the_sprites(t_general *g)
{
	g->sprite.spritex = g->sprite.pos_x - g->pos_x;
	g->sprite.spritey = g->sprite.pos_y - g->pos_y;
	g->sprite.invDet = 1.0 / (g->plane_x * g->dir_y - g->plane_y * g->dir_x);
	g->sprite.transformx = g->sprite.invDet * (g->dir_y * g->sprite.spritex - g->dir_x *
	g->sprite.spritey);
	g->sprite.transformy = g->sprite.invDet * (-g->plane_y * g->sprite.spritex + g->plane_x *
	g->sprite.spritey);
	g->sprite.sprite_screen_x = (int)((g->size_x / 2) * (1 + g->sprite.transformx /
	g->sprite.transformy));

	g->sprite.sprite_height = abs((int)(g->size_y / g->sprite.transformy));
	g->sprite.draw_start_Y = -g->sprite.sprite_height / 2 + g->size_y / 2;
	if (g->sprite.draw_start_Y < 0)
		g->sprite.draw_start_Y = 0;
	g->sprite.draw_end_Y = g->sprite.sprite_height / 2 + g->size_y / 2;
	if (g->sprite.draw_end_Y > g->size_y)
		g->sprite.draw_end_Y = g->size_y - 1;

	g->sprite.sprite_width = abs((int)(g->size_y / g->sprite.transformy));
	g->sprite.draw_start_X = -g->sprite.sprite_width / 2 + g->sprite.sprite_screen_x;
	if (g->sprite.draw_start_X < 0)
		g->sprite.draw_start_X = 0;
	g->sprite.draw_end_X = g->sprite.sprite_width / 2 + g->sprite.sprite_screen_x;
	if (g->sprite.draw_end_X < 0)
		g->sprite.draw_end_X = g->size_x - 1;
	g->sprite.stripe = g->sprite.draw_start_X;
	while (g->sprite.stripe < g->sprite.draw_end_X)
	{
		g->sprite.tex_x = (int)(256 * (g->sprite.stripe - (-g->sprite.sprite_width / 2 +
		g->sprite.sprite_screen_x) * g->text_w / g->sprite.sprite_width) / 256);
		if (g->sprite.transformy > 0 && g->sprite.stripe > 0 && g->sprite.stripe < 
		g->size_x && g->sprite.transformy < g->Zbuffer[g->sprite.stripe])
		{
			g->sprite.pixel = g->sprite.draw_start_Y;
			while (g->sprite.pixel < g->sprite.draw_end_Y)
			{
				g->sprite.tex_y = (((g->sprite.pixel * 256 - g->size_y * 128 +
				g->sprite.sprite_height * 128) * g->text_h) / g->sprite.sprite_height) / 256;
				g->sprite.color.color = g->sprites[g->sprite.sprite_width * g->sprite.tex_y +
				g->sprite.tex_x];
				g->scr_buff[g->sprite.pixel][g->sprite.stripe] = g->sprite.color.color;
				g->sprite.pixel++;
			}
		}
		g->sprite.stripe++;
	}
}
