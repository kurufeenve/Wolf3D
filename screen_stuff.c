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
	printf("g->dir_x = %f, g->dir_y = %f, g->plane_x = %f, g->plane_y = %f\n", g->dir_x, g->dir_y, g->plane_x, g->plane_y);
}

void	ft_textures(t_general *g)
{
	int		trigger;

	trigger = 0;
	g->i = 0;
	g->textures = (char **)malloc(sizeof(char *) * 8);
	g->textures[0] = mlx_get_data_addr(mlx_xpm_file_to_image(g->init, "tex/bluestone.xpm", &g->text_w, &g->text_h), &g->t_bpp, &g->t_val, &g->t_ed);
	g->textures[1] = mlx_get_data_addr(mlx_xpm_file_to_image(g->init, "tex/colorstone.xpm", &g->text_w, &g->text_h), &g->t_bpp, &g->t_val, &g->t_ed);
	g->textures[2] = mlx_get_data_addr(mlx_xpm_file_to_image(g->init, "tex/eagle.xpm", &g->text_w, &g->text_h), &g->t_bpp, &g->t_val, &g->t_ed);
	g->textures[3] = mlx_get_data_addr(mlx_xpm_file_to_image(g->init, "tex/greystone.xpm", &g->text_w, &g->text_h), &g->t_bpp, &g->t_val, &g->t_ed);
	g->textures[4] = mlx_get_data_addr(mlx_xpm_file_to_image(g->init, "tex/mossy.xpm", &g->text_w, &g->text_h), &g->t_bpp, &g->t_val, &g->t_ed);
	g->textures[5] = mlx_get_data_addr(mlx_xpm_file_to_image(g->init, "tex/purplestone.xpm", &g->text_w, &g->text_h), &g->t_bpp, &g->t_val, &g->t_ed);
	g->textures[6] = mlx_get_data_addr(mlx_xpm_file_to_image(g->init, "tex/redbrick.xpm", &g->text_w, &g->text_h), &g->t_bpp, &g->t_val, &g->t_ed);
	g->textures[7] = mlx_get_data_addr(mlx_xpm_file_to_image(g->init, "tex/wood.xpm", &g->text_w, &g->text_h), &g->t_bpp, &g->t_val, &g->t_ed);
	while (g->i < 8)
	{
		if (g->textures[g->i] == NULL)
		{
			ft_putstr("\n\n\n===    !!!Failed to upload texture #");
			ft_putnbr(g->i);
			ft_putstr("!!!    ===\n\n\n");
			trigger = 1;
		}
		g->i++;
	}
	if (trigger == 1)
		exit(0);
}
