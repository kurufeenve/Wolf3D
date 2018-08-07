/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 13:40:46 by vordynsk          #+#    #+#             */
/*   Updated: 2018/08/07 13:40:49 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		**ft_int_arr(int x, int y)
{
	int		**arr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	arr = (int **)malloc(sizeof(int *) * y);
	while (j < y)
	{
		arr[j] = (int *)malloc(sizeof(int) * x);
		j++;
	}
	return (arr);
}
