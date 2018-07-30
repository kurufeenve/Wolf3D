/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 17:16:59 by vordynsk          #+#    #+#             */
/*   Updated: 2018/07/28 17:17:01 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/includes/libft.h"
# include <OpenCL/opencl.h>
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>

typedef	union		u_color
{
	int				color;
	unsigned char	channel[4];
}					t_color;

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
	t_color			color;
}					t_point;

typedef struct		s_general
{
	void			*init;
	void			*win;
	int				size_x;
	int				size_y;
	void			*img;
	char			*image;
	int				bpp;
	int				val;
	int				ed;
    int             fd;
    char            *line;
    int             len_buff;
    int             i;
	int				j;
    char            **buff;
    int             len;
    int             rows;
	int				**points;
}					t_general;

int					exit_x(void);
int					key_hook(int key, void *ptr);
void				put_pixel(t_general *g, int x, int y, t_color color);
void				pixel_color(t_general *g);
int		            validation(t_general *g, char *filename);
int					read_map(t_general *g, char *filename);

#endif
