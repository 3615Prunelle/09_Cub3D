/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_assignment_and_color.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:47:27 by mlehmann          #+#    #+#             */
/*   Updated: 2026/05/19 10:08:21 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	paint_wall(t_cube *game, t_ray *ray, int *borders, int j)
{
	if (ray->wall[0] == 'N' && game->input->north)
		return (get_south_north_color(game, ray, borders, j));
	if (ray->wall[0] == 'S' && game->input->south)
		return (get_south_north_color(game, ray, borders, j));
	if (ray->wall[0] == 'W' && game->input->west)
		return (get_west_east_color(game, ray, borders, j));
	if (ray->wall[0] == 'E' && game->input->east)
		return (get_west_east_color(game, ray, borders, j));
	if (ray->wall[0] == 'K' && game->input->south)
		return (0x00FF00FF);
	return (0x000000FF);
}
