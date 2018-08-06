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
		g->len_buff = 0;
		g->i = 0;
		g->buff = ft_strsplit(g->line, ' ');
		while (g->buff[g->i] != NULL)
		{
			if (ft_isnumber(g->buff[g->i]) == 1 || g->buff[g->i][0] == 'P')
				g->len_buff++;
			g->i++;
		}
		if (g->len == 0 || g->len == g->len_buff)
			g->len = g->len_buff;
		else if (g->len_buff != 0 && g->len != g->len_buff)
			return (0);
		if (g->line != NULL)
			g->rows++;
		ft_strdel(&g->line);
		ft_chararrdel(g->buff, &g->buff);
	}
	close(g->fd);
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
			printf("%d ", arr[j][i]);
			x++;
		}
		printf("\n");
		y++;
	}
}
