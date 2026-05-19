/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:29:37 by schappuy          #+#    #+#             */
/*   Updated: 2026/05/19 15:20:16 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_line_from_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n')
		return (false);
	while (line[i] != '\0')
	{
		if ((line[i] == ' ' || line[i] == '0') || (line[i] == '1')
			|| (line[i] == '\n') || (line[i] == 'N') || (line[i] == 'S')
			|| (line[i] == 'E') || (line[i] == 'W'))
		{
			i++;
		}
		else
			return (false);
	}
	return (true);
}

// Fill empty spaces (at the end each line) with spaces to avoid segfault
void	spaces_fill_up(t_map_info *map_info)
{
	int		i;
	int		j;
	char	**map;
	char	*tmp;

	i = 0;
	map = map_info->map;
	map_info->total_lines++;
	while (i < map_info->total_lines)
	{
		j = ft_strchr(map[i], '\n') - map[i];
		tmp = calloc(sizeof(char), map_info->total_columns + 1);
		ft_memcpy(tmp, map[i], j);
		while (j < map_info->total_columns)
		{
			tmp[j] = ' ';
			j++;
		}
		free(map[i]);
		map[i] = tmp;
		i++;
	}
}

// Ignore spaces, then must be consecutive '1' or spaces
bool	is_wall_only(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] == '1' || line[i] == ' ')
		i++;
	if ((i == 0) || (line[i] != '\0'))
		return (false);
	return (true);
}

// Checks only above/below/right/left (not diagonal)
bool	are_surroundings_valid(char **map, int element_line, int element_column)
{
	static int	directions[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
	int			i;

	i = 0;
	if (element_line == 0 || element_column == 0)
		return (false);
	while (i < 4)
	{
		if (!ft_strchr("01NSEW",
				map[element_line + directions[i][0]]
			[element_column + directions[i][1]]))
			return (false);
		i++;
	}
	return (true);
}
