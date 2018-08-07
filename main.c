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

	g.dir_x = -1;
	g.dir_y = 0;
	g.plane_x = 0;
	g.plane_y = 0.66;
	g.size_x = 1024;
	g.size_y = 768;
	g.text_x = 64;
	g.text_y = 64;
	g.scr_buff = ft_int_arr(g.size_x, g.size_y);
	
	if (argc != 2 || validation(&g, argv[1]) != 1)
		ft_putstr("MAP ERROR\n");
	read_map(&g, argv[1]);
	if ((g.init = mlx_init()) == NULL ||
		(g.win = mlx_new_window(g.init,
		g.size_x, g.size_y, "Wolf3D")) == NULL || (g.img =
		mlx_new_image(g.init, g.size_x, g.size_y)) == NULL ||
		(g.image = mlx_get_data_addr(g.img, &g.bpp, &g.val,
		&g.ed)) == NULL)
		return (0);
	ft_clearscr(&g);
	raycaster(&g);
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
	else if (key == 13)
	{
		ft_move(g, 0.2);
		ft_screen_stuff(g);
	}
	else if (key == 1)
	{
		ft_move(g, -0.2);
		ft_screen_stuff(g);
	}
	else if (key == 2)
	{
		ft_turn(g, -0.078539816339745);
		ft_screen_stuff(g);
	}
	else if (key == 0)
	{
		ft_turn(g, 0.078539816339745);
		ft_screen_stuff(g);
	}
	return (0);
}

void	ft_clearscr(t_general *gen)
{
	int		i;

	i = 0;
	while (i < gen->size_x * gen->size_y * 4)
	{
		gen->image[i] = '\0';
		i++;
	}
}