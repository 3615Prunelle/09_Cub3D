/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:29:47 by schappuy          #+#    #+#             */
/*   Updated: 2026/05/08 16:32:23 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_filename_correct(char *path_to_map)
{
	size_t	file_length;
	char	*tmp;

	file_length = ft_strlen(path_to_map);
	tmp = ft_strrchr(path_to_map, '.');
	if (!tmp)
	{
		return (false);
	}
	if ((ft_strcmp(tmp, ".cub")))
	{
		return (false);
	}
	return (true);
}

// Replaces 'to_remove' by spaces (used for '\n' ',')
// Change chars in memory
void	remove_char_from_line(char **line, char to_remove)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == to_remove)
		{
			(*line)[i] = ' ';
		}
		i++;
	}
}

int	count_lines_from_scene_description(t_input *input_info)
{
	int		fd;
	int		line_counter;
	char	*gnl_return ;

	fd = open(input_info->path_to_map, O_RDONLY);
	line_counter = 0;
	gnl_return = get_next_line(fd);
	if (!gnl_return)
		print_error_free_exit(input_info, ERR_MSG_05, false, NULL);
	while (gnl_return)
	{
		line_counter++;
		free(gnl_return);
		gnl_return = get_next_line(fd);
	}
	close(fd);
	return (line_counter);
}

// Return 0 if error
int	coma_check(char *line)
{
	int	i;
	int	coma_count;

	i = 0;
	coma_count = 0;
	while (line[i] != '\0')
	{
		while (line[i] == ' ' || line[i] == 'F' || line[i] == 'C')
			i++;
		while (ft_isdigit(line[i]))
			i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			break ;
		if (line[i] != ',')
			return (0);
		coma_count++;
		i++;
	}
	if (coma_count == 2)
		return (1);
	return (0);
}
