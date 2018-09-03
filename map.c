/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 18:13:58 by vordynsk          #+#    #+#             */
/*   Updated: 2018/07/28 18:14:00 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		validation(t_general *g, char *filename)
{
	if ((g->fd = open(filename, O_RDONLY)) <= 0)
		return (0);
	while (get_next_line(g->fd, &g->line) > 0)
	{
		g->i = 0;
		g->len_buff = 0;
		g->buff = ft_strsplit(g->line, ' ');
		while (g->buff[g->i] != NULL)
		{
			if (ft_isnumber(g->buff[g->i]) == 1 || g->buff[g->i][0] == 'P')
				g->len_buff++;
			if (ft_isalpha(g->buff[g->i][0]) == 1 && g->buff[g->i][0] != 'P')
				return (0);
			g->i++;
		}
		if (g->len == 0 || g->len == g->len_buff)
			g->len = g->len_buff;
		else if (g->len_buff != 0 && g->len != g->len_buff)
			return (0);
		g->line != NULL ? g->rows++ : 1;
		ft_strdel(&g->line);
		ft_chararrdel(g->buff, &g->buff);
	}
	return (1);
}

int		read_map(t_general *g, char *filename)
{
	g->j = 0;
	if ((g->fd = open(filename, O_RDONLY)) < 0)
		return (0);
	g->points = (int **)malloc(sizeof(int *) * g->rows);
	while (g->j < g->rows && get_next_line(g->fd, &g->line) > 0)
	{
		g->i = 0;
		g->buff = ft_strsplit(g->line, ' ');
		g->points[g->j] = (int *)malloc(sizeof(int) * g->len);
		while (g->i < g->len && g->buff[g->i] != '\0')
		{
			if (g->buff[g->i][0] == 'P')
			{
				g->pos_x = g->i;
				g->pos_y = g->j;
				g->buff[g->i][0] = '0';
			}
			g->points[g->j][g->i] = ft_atoi(g->buff[g->i]);
			g->i++;
		}
		ft_strdel(&g->line);
		ft_chararrdel(g->buff, &g->buff);
		g->j++;
	}
	return (1);
}

void	print_arr(int **arr, int i, int j)
{
	int		x;
	int		y;

	y = 0;
	while (y < j)
	{
		x = 0;
		while (x < i)
		{
			printf("%d ", arr[y][x]);
			x++;
		}
		printf("\n\n");
		y++;
	}
}

int		ft_space_check(t_general *g, char *filename)
{
	int		i;

	if ((g->fd = open(filename, O_RDONLY)) <= 0)
		return (0);
	while (get_next_line(g->fd, &g->line) > 0)
	{
		i = 0;
		while (g->line[i] != '\0')
		{
			if (g->line[i] != ' ' && (g->line[i + 1] != ' ' && g->line[i + 1] != '\0'))
				return (0);
			else if (g->line[i] == ' ' && g->line[i + 1] == ' ')
				return (0);
			i++;
		}
		ft_strdel(&g->line);
	}
	return (1);
}

void	ft_init(t_general *g)
{
	g->dir_x = -1;
	g->dir_y = 0;
	g->plane_x = 0;
	g->plane_y = 0.66;
	g->size_x = 1024;
	g->size_y = 768;
	g->text_w = 64;
	g->text_h = 64;
	g->len_buff = 0;
}

int		super_validation(t_general *g, char *file_name)
{
	if (ft_space_check(g, file_name) != 1)
		return (0);
	else if (validation(g, file_name) != 1)
		return (0);
	else if (additional_map_validation(file_name, g) != 1)
		return (0);
	else if (read_map(g, file_name) == 0)
		return (0);
	else if (wall_validation(g) != 1)
		return (0);
	else if ((g->init = mlx_init()) == NULL)
		return (0);
	else if ((g->win = mlx_new_window(g->init, g->size_x, g->size_y, \
	"Wolf3D")) == NULL)
		return (0);
	else if ((g->img = mlx_new_image(g->init, g->size_x, g->size_y)) == NULL)
		return (0);
	else if ((g->image = mlx_get_data_addr(g->img, &g->bpp, &g->val, \
	&g->ed)) == NULL)
		return (0);
	else
		return (1);
}
