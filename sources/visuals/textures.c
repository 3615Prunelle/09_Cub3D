/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlehmann <mlehmann@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:34:54 by mlehmann          #+#    #+#             */
/*   Updated: 2026/04/15 16:49:11 by mlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_south_north_color(t_cube *game, t_ray *ray, int *borders, int place)
{
	mlx_texture_t	*texture;
	int				y_size;
	int				spot[2];
	uint8_t			colors[4];
	u_int32_t		color;

	if (ray->wall[0] == 'N')
		texture = game->textures[0];
	else
		texture = game->textures[1];
	y_size = borders[1] - borders[0];
	spot[0] = (int)((ray->contact_x / MAP_SCALE - (int)(ray->contact_x / MAP_SCALE)) * texture->width);
	if (ray->wall[0] == 'S')
		spot[0] = texture->width - spot[0] - 1;
	spot[1] = (int)((place * texture->height) / y_size);
	colors[0] = (uint8_t)(texture->pixels[(spot[0] + spot[1] * texture->width) * 4]);
	colors[1] = (uint8_t)(texture->pixels[(spot[0] + spot[1] * texture->width) * 4 + 1]);
	colors[2] = (uint8_t)(texture->pixels[(spot[0] + spot[1] * texture->width) * 4 + 2]);
	colors[3] = (uint8_t)(texture->pixels[(spot[0] + spot[1] * texture->width) * 4 + 3]);
	color = (colors[0] << 24 | colors[1] << 16 | colors[2] << 8 | colors[3]);
	return (color);
}

uint32_t	get_west_east_color(t_cube *game, t_ray *ray, int *borders, int place)
{
	mlx_texture_t	*texture;
	int				y_size;
	int				spot[2];
	uint8_t			colors[4];
	uint32_t		color;

	if (ray->wall[0] == 'W')
		texture = game->textures[2];
	else
		texture = game->textures[3];
	y_size = borders[1] - borders[0];
	spot[0] = (int)((ray->contact_y / MAP_SCALE - (int)(ray->contact_y / MAP_SCALE)) * texture->width);
	if (ray->wall[0] == 'W')
		spot[0] = texture->width - spot[0] - 1;
	spot[1] = (int)((place * texture->height) / y_size);
	colors[0] = (uint8_t)(texture->pixels[(spot[0] + spot[1] * texture->width) * 4]);
	colors[1] = (uint8_t)(texture->pixels[(spot[0] + spot[1] * texture->width) * 4 + 1]);
	colors[2] = (uint8_t)(texture->pixels[(spot[0] + spot[1] * texture->width) * 4 + 2]);
	colors[3] = (uint8_t)(texture->pixels[(spot[0] + spot[1] * texture->width) * 4 + 3]);
	color = (colors[0] << 24 | colors[1] << 16 | colors[2] << 8 | colors[3]);
	return (color);
}

uint32_t	load_color(int *colors)
{
	uint32_t	color;

	color = (colors[0] << 24 | colors[1] << 16 | colors[2] << 8 | 0xFF);
	return (color);
}