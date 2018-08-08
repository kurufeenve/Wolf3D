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
	if (g->points[(int)(g->pos_y + (g->dir_y * move) + 0.3)][(int)(g->pos_x +
	(g->dir_x * move) + 0.3)] == 0)
	{
		g->pos_x = g->pos_x + (g->dir_x * move);
		g->pos_y = g->pos_y + (g->dir_y * move);
	}
}

void	ft_turn(t_general *g, double turn)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->dir_x;
	g->dir_x = g->dir_x * cos(turn) - g->dir_y * sin(turn);
	g->dir_y = old_dir_x * sin(turn) + g->dir_y * cos(turn);
	old_plane_x = g->plane_x;
	g->plane_x = g->plane_x * cos(turn) - g->plane_y * sin(turn);
	g->plane_y = old_plane_x * sin (turn) + g->plane_y * cos(turn);
	//printf("dir_x = %f, dir_y = %f, plane_x = %f, plane_y = %f\n", g->dir_x, g->dir_y, g->plane_x, g->plane_y);
}

void	ft_textures(t_general *g)
{
	g->j = 0;
	while (g->j < g->text_y)
	{
		g->i = 0;
		while (g->i < g->text_x)
		{
			g->xor_color = (g->i * 256 / g->text_x) ^ (g->j * 256 / g->text_y);
			g->y_color = g->j * 256 / g->text_x;
			g->xy_color = g->j * 128 / g->text_y + g->i * 128 / g->text_x;
			g->textures[0][g->text_x * g->j + g->i] = 65536 * 254 * (g->i != g->j && g->i != (g->text_x - g->j));
			g->textures[1][g->text_x * g->j + g->i] = g->xy_color + 256 * g->xy_color + 65536 * g->xy_color;
			g->textures[2][g->text_x * g->j + g->i] = 256 * g->xy_color + 65526 * g->xy_color;
			g->textures[3][g->text_x * g->j + g->i] = g->xor_color + 256 * g->xor_color + 65536 * g->xor_color;
			g->textures[4][g->text_x * g->j + g->i] = 256 * g->xor_color;
			g->textures[5][g->text_x * g->j + g->i] = 65536 * 192 * (g->i % 16 && g->j % 16);
			g->textures[6][g->text_x * g->j + g->i] = 65536 * g->y_color;
			g->textures[7][g->text_x * g->j + g->i] = 128 + 256 * 128 + 65536 * 128;
		}
		g->j++;
	}
}
