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

int		main(int argc, char **argv)
{
	t_general	g;

	ft_init(&g);
	ft_int_arr(&g.scr_buff, g.size_x, g.size_y);
	if (argc != 2 || super_validation(&g, argv[1]) != 1)
	{
		ft_putstr("ERROR\n");
		exit(0);
	}
	ft_clearscr(&g);
	ft_textures(&g);
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
		ft_move(g, 0.2);
	else if (key == 1)
		ft_move(g, -0.2);
	else if (key == 2)
		ft_turn(g, -0.078539816339745);
	else if (key == 0)
		ft_turn(g, 0.078539816339745);
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
