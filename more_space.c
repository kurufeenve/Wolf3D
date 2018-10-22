/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:59:57 by vordynsk          #+#    #+#             */
/*   Updated: 2018/09/05 15:59:59 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_texture_validation(t_general *g)
{
	int		trigger;

	trigger = 0;
	g->i = 0;
	while (g->i < 9)
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
	if (g->sprites == NULL)
	{
		ft_putstr("\n\n\n===    !!!Failed to upload sprite!!!    ===\n\n\n");
		trigger = 1;
	}
	if (trigger == 1)
		exit(0);
}
