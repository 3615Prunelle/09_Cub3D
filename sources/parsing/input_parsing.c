#include "cub3d.h"

void	parsing(char *path, t_input *input_info)
{
	input_info->path_to_map = path;
	if (!is_filename_correct(path))
	{
		printf("%s", ERR_MSG_02);
		free(input_info);
		exit (1);
	}
	input_info->map_info = ft_calloc(sizeof(t_map_info), 1);
	input_info->scene_description = open_fd_export_content(input_info);
	read_scene_description(input_info, input_info->scene_description);
	spaces_fill_up(input_info->map_info);
	if (check_player(input_info, input_info->map_info->map) == -1)	// Checks if only one player + surroundings ok + update struct
		print_error_free_exit(input_info, ERR_MSG_08, false, NULL);

	if(!is_map_valid(input_info->map_info))
		print_error_free_exit(input_info, ERR_MSG_07, false, NULL);	// array has been freed in read_scene_description function
}

void	read_scene_description(t_input *input_info, char **scene_description)
{
	char	**splitted_line;
	int		i;
	int		elements_counter;
	int		line_management_return;

	i = 0;
	elements_counter = 0;
	while (scene_description[i])
	{
		if(scene_description[i][0] != '\n' && (strchr(scene_description[i], '\n')) && (elements_counter != 6))
			remove_char_from_line(&scene_description[i], '\n');
		splitted_line = ft_split(scene_description[i], ' ');
		if(!splitted_line)
			print_error_free_exit(input_info, ERR_MSG_03, true, scene_description);
		line_management_return = line_management(input_info, splitted_line, i, &elements_counter);
		free_strings_array(splitted_line);
		if (line_management_return == -1)
			print_error_free_exit(input_info, ERR_MSG_03, true, scene_description);
		else if (line_management_return == 1)
			break;			// when out of this loop, we're reaching the map part
		i++;
	}
	input_info->map_info->map = export_map(input_info, scene_description, i);
}

int		line_management(t_input *input_info, char **splitted_line, int i, int *elements_counter)
{
	char	**scene_description = input_info->scene_description;
	if (ft_strchr("NSWE", splitted_line[0][0]))
	{
		if (!check_and_add_texture_path(splitted_line, input_info))
			return (-1);
		(*elements_counter)++;
	}
	else if (!ft_strcmp(splitted_line[0], "F") || !ft_strcmp(splitted_line[0], "C"))
	{
		if (!check_and_add_colors(scene_description[i], input_info))
			return (-1);
		(*elements_counter)++;
	}
	else if (splitted_line[0][0] == '1')
	{
		if((is_line_from_map(scene_description[i])) && (*elements_counter == 6))
			return (1);
		else
			return (-1);
	}
	else if (splitted_line[0][0] != '\n')
		return (-1);
	return (0);			// Success
}

char	**export_map(t_input *input_info, char **scene_description, int i)
{
	int		line_counter;
	int		lines_in_map;

	line_counter = count_lines_from_scene_description(input_info);
	lines_in_map = line_counter - i;
	input_info->map_info->map = ft_calloc(sizeof(char *), lines_in_map + 1);
	while (scene_description[i])
	{
		add_line_in_map_struct(scene_description[i], input_info);				// Ⓜ️
		i++;
		if(scene_description[i] && !(is_line_from_map(scene_description[i])))
			print_error_free_exit(input_info, ERR_MSG_03, true, scene_description);
	}
	free_strings_array(scene_description);
	return (input_info->map_info->map);
}

char	**open_fd_export_content(t_input *input_info)
{
	int		i;
	int		fd;
	int		line_counter;
	char	**scene_description;

	i = 0;
	fd = open(input_info->path_to_map, O_RDONLY);
	line_counter = count_lines_from_scene_description(input_info);
	// Count_lines_from_scene_description function makes sure there's something to read, otherwise exit
	scene_description = ft_calloc(sizeof(char *), line_counter + 1);
	if (!scene_description)
		print_error_free_exit(input_info, strerror(errno), false, NULL);
	while (i < line_counter)
	{
		scene_description[i] = get_next_line(fd);				// Ⓜ️ (for each line)
		i++;
	}
	close(fd);
	return (scene_description);
}
