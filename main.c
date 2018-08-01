/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 17:39:55 by vordynsk          #+#    #+#             */
/*   Updated: 2018/07/03 17:39:57 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int argc, char** argv)
{
	t_general	g;

	if (argc != 2 || validation(&g, argv[1]) != 1)
		ft_putstr("MAP ERROR\n");
	read_map(&g, argv[1]);
	g.size_x = 1024;
	g.size_y = 768;
	if ((g.init = mlx_init()) == NULL ||
		(g.win = mlx_new_window(g.init,
		g.size_x, g.size_y, "Wolf3D")) == NULL || (g.img =
		mlx_new_image(g.init, g.size_x, g.size_y)) == NULL ||
		(g.image = mlx_get_data_addr(g.img, &g.bpp, &g.val,
		&g.ed)) == NULL)
		return (0);
	pixel_color(&g);
	mlx_put_image_to_window(g.init, g.win, g.img, 0, 0);
	mlx_hook(g.win, 17, 1L << 17, exit_x, NULL);
	mlx_hook(g.win, 2, 5, key_hook, &g);
	mlx_loop(g.init);
	return (0);
}

void	put_pixel(t_general *g, int x, int y, t_color color)
{
	g->image[y * g->val + 4 * x] = color.channel[0];
	g->image[y * g->val + 4 * x + 1] = color.channel[1];
	g->image[y * g->val + 4 * x + 2] = color.channel[2];
}

int		exit_x(void)
{
	system("leaks wolf3d");
	exit(1);
}

int		key_hook(int key, void *ptr)
{
	t_general	*g;

	g = ptr;
	if (key == 53)
	{
		system("leaks wolf3d");
		exit(0);
	}
	return (0);
}

void	pixel_color(t_general *g)
{
	t_color	col;
	int	xi;
	int	yi;
	int	x1 = 0;
	int	x2 = 1023;
	int	y1 = 99;
	int	y2 = 667;
	int	perspective_x = 50;
	int	perspective_y = 40;

	col.color = 0xFFFFFF;
	while (x2 - x1 > 0 && y1 < 499 && y2 > 499)
	{
		yi = y1;
		while (yi < y2)
		{
			put_pixel(g, x1, yi, col);
			yi++;
		}
		xi = x1;
		while (xi < x2)
		{
			put_pixel(g, xi, y2, col);
			xi++;
		}
		yi = y1;
		while (yi < y2)
		{
			put_pixel(g, x2, yi, col);
			yi++;
		}
		x1 += perspective_x;
		x2 -= perspective_x;
		y1 += perspective_y;
		y2 -= perspective_y;
	}
}