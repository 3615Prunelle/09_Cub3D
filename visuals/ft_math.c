/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:28:39 by mlehmann          #+#    #+#             */
/*   Updated: 2026/03/13 09:36:30 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	add_degree(float a, float b)
{
	if ((a + b) < 0)
		return (a + b + 360);
	if ((a + b) > 360)
		return (a + b - 360);
	else
		return (a + b);
}
