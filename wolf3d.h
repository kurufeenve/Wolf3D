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
# include <time.h>
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
	int				fd;
	char			*line;
	int				len_buff;
	int				i;
	int				j;
	char			**buff;
	int				len;
	int				rows;
	int				**points;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			newtime;
	double			oldtime;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			frame_time;
	int				**scr_buff;
	int				text_w;
	int				text_h;
	char			**textures;
	int				xor_color;
	int				y_color;
	int				xy_color;
	int				text_num;
	double			wall_x;
	int				text_x;
	int				text_y;
	double			draw;
	int				start;
	int				t_bpp;
	int				t_val;
	int				t_ed;
	t_color			color;
}					t_general;

int					exit_x(void);
int					key_hook(int key, void *ptr);
void				put_pixel(t_general *g, int x, int y, t_color color);
int					validation(t_general *g, char *filename);
int					read_map(t_general *g, char *filename);
void				raycaster(t_general *g);
void				buffer_draw(t_general *g);
void				ft_clearscr(t_general *gen);
void				ft_screen_stuff(t_general *g);
void				ft_move(t_general *g, double move);
void				ft_turn(t_general *g, double turn);
void				print_arr(int **arr, int i, int j); // delete me)
void				ft_textures(t_general *g);
void				ft_clean_buffer(t_general *g);
void				ft_texture_validation(t_general *g);
void				four_textures(t_general *g);
void				ft_hit(t_general *g);
void				ft_ray(t_general *g);
void				a_bunch_of_stuff(t_general *g);
void				text_map_and_color(t_general *g);
void				ft_init(t_general *g);
int					super_validation(t_general *g, char *file_name);

#endif
