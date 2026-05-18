/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:29:42 by schappuy          #+#    #+#             */
/*   Updated: 2026/05/18 15:11:04 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(char *path, t_input *input_info)
{
	input_info->path_to_map = path;
	if (!is_filename_correct(path))
	{
		printf("%s", ERR_MSG_2);
		free(input_info);
		exit(1);
	}
	input_info->map_info = ft_calloc(sizeof(t_map_info), 1);
	input_info->scene = open_fd_export_content(input_info);
	read_scene(input_info, input_info->scene);
	spaces_fill_up(input_info->map_info);
	if (check_player(input_info, input_info->map_info->map) == FAIL)
		print_error_free_exit(input_info, ERR_MSG_5, false, NULL);
	if (!is_map_valid(input_info->map_info))
		print_error_free_exit(input_info, ERR_MSG_6, false, NULL);
}

void	read_scene(t_input *input_info, char **scene)
{
	char	**split_line;
	int		i;
	int		elements_counter;
	int		line_management_return ;

	i = 0;
	elements_counter = 0;
	while (scene[i])
	{
		if (scene[i][0] != '\n' &&
			(strchr(scene[i], '\n')) && (elements_counter != 6))
			remove_char_from_line(&scene[i], '\n');
		split_line = ft_split(scene[i], ' ');
		if (!split_line)
			print_error_free_exit(input_info, ERR_MSG_4, true, scene);
		line_management_return = line_management(input_info, split_line, i,
				&elements_counter);
		free_strings_array(split_line);
		if (line_management_return == FAIL)
			print_error_free_exit(input_info, ERR_MSG_4, true, scene);
		else if (line_management_return == MAP_BEGINS)
			break ;
		i++;
	}
	input_info->map_info->map = export_map(input_info, scene, i);
}

int	line_management(t_input *input_info, char **split_line, int i,
		int *elements_counter)
{
	char	**scene;

	scene = input_info->scene;
	if (ft_strchr("NSWE", split_line[0][0]))
	{
		if (!check_and_add_texture_path(split_line, input_info))
			return (FAIL);
		(*elements_counter)++;
	}
	else if (!ft_strcmp(split_line[0], "F") || !ft_strcmp(split_line[0], "C"))
	{
		if (!check_and_add_colors(scene[i], input_info))
			return (FAIL);
		(*elements_counter)++;
	}
	else if (split_line[0][0] == '1')
	{
		if ((is_line_from_map(scene[i])) && (*elements_counter == 6))
			return (MAP_BEGINS);
		return (FAIL);
	}
	else if (split_line[0][0] != '\n')
		return (FAIL);
	return (SUCCESS);
}

char	**export_map(t_input *input_info, char **scene, int i)
{
	int	line_counter;
	int	lines_in_map;

	line_counter = count_lines_from_scene(input_info);
	lines_in_map = line_counter - i;
	input_info->map_info->map = ft_calloc(sizeof(char *), lines_in_map + 1);
	while (scene[i])
	{
		add_line_in_map_struct(scene[i], input_info);
		i++;
		if (scene[i] && !(is_line_from_map(scene[i])))
			print_error_free_exit(input_info, ERR_MSG_6, true,
				scene);
	}
	free_strings_array(scene);
	return (input_info->map_info->map);
}

// Malloc for scene description char*array + every line (through GNL)
char	**open_fd_export_content(t_input *input_info)
{
	int		i;
	int		fd;
	int		line_counter;
	char	**scene;

	i = 0;
	fd = open(input_info->path_to_map, O_RDONLY);
	line_counter = count_lines_from_scene(input_info);
	scene = ft_calloc(sizeof(char *), line_counter + 1);
	if (!scene)
		print_error_free_exit(input_info, strerror(errno), false, NULL);
	while (i < line_counter)
	{
		scene[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	return (scene);
}
