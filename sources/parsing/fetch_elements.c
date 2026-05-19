/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:29:54 by schappuy          #+#    #+#             */
/*   Updated: 2026/05/16 13:54:26 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check direction
// Ignore spaces
// Fetch clean path and fill struct
// Malloc for each strdup
int	check_and_add_texture_path(char **split_line, t_input *input_info)
{
	if (!split_line[1] || !is_image_reachable(split_line[1]))
		return (FAIL);
	if (ft_strncmp(split_line[0], "NO", 3) == 0)
	{
		input_info->north = ft_strdup(split_line[1]);
	}
	else if (ft_strncmp(split_line[0], "SO", 3) == 0)
	{
		input_info->south = ft_strdup(split_line[1]);
	}
	else if (ft_strncmp(split_line[0], "WE", 3) == 0)
	{
		input_info->west = ft_strdup(split_line[1]);
	}
	else if (ft_strncmp(split_line[0], "EA", 3) == 0)
	{
		input_info->east = ft_strdup(split_line[1]);
	}
	return (SUCCESS);
}

bool	is_image_reachable(char *path)
{
	char	*tmp;
	int		file_fd;

	tmp = ft_strrchr(path, '.');
	if (!tmp)
		return (false);
	if (ft_strcmp(tmp, ".xpm") && ft_strcmp(tmp, ".png"))
		return (false);
	file_fd = open(path, O_RDONLY);
	if (file_fd == -1)
		return (false);
	close(file_fd);
	return (true);
}

int	check_and_add_colors(char *line, t_input *input_info)
{
	int		i;
	int		number_to_check;
	char	**rgb_split;

	i = 0;
	if (!coma_check(line))
		return (FAIL);
	remove_char_from_line(&line, ',');
	rgb_split = ft_split(line, ' ');
	while (rgb_split[i + 1])
	{
		number_to_check = ft_atoi(rgb_split[i + 1]);
		if (!add_rgb_in_struct(input_info, rgb_split[0], number_to_check, i))
		{
			free_strings_array(rgb_split);
			return (FAIL);
		}
		i++;
	}
	free_strings_array(rgb_split);
	if (i != 3)
		return (FAIL);
	return (SUCCESS);
}

int	add_rgb_in_struct(t_input *input_info, char *identifier, int color, int i)
{
	if (color >= 0 && color <= 255)
	{
		if (identifier[0] == 'F')
			input_info->floor[i] = color;
		if (identifier[0] == 'C')
			input_info->ceiling[i] = color;
		return (SUCCESS);
	}
	else
		return (FAIL);
}

// total_columns is the length of the longuest line including \n
// Corrected in spaces_fill_up function
// malloc in strdup
void	add_line_in_map_struct(char *line, t_input *input_info)
{
	static int		i;
	static size_t	j;

	if (ft_strlen(line) > j)
	{
		j = ft_strlen(line);
		input_info->map_info->total_columns = j;
	}
	input_info->map_info->map[i] = ft_strdup(line);
	input_info->map_info->total_lines = i;
	i++;
}
