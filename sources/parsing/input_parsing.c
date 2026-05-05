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
	read_scene_description(input_info);
	// map is saved, but needs to be adjusted (spaces to fill blanks)
	spaces_fill_up(input_info->map_info);
	if (update_player_info(input_info) == -1)			// Checks if only one player + surroundings ok + update struct
		print_error_free_exit(input_info, ERR_MSG_08, false, NULL);

	if(!is_map_valid(input_info->map_info))
		print_error_free_exit(input_info, ERR_MSG_07, false, NULL);	// array has been freed in read_scene_description function
}

void	read_scene_description(t_input *input_info)
{
	char	**file_content;
	char	**splitted_line;
	int		i;
	int		elements_counter;

	i = 0;
	elements_counter = 0;
	file_content = open_fd_export_content(input_info);

	while (file_content[i])
	{
		if(file_content[i][0] != '\n' && (strchr(file_content[i], '\n')) && (elements_counter != 6))
			remove_char_from_line(&file_content[i], '\n');
		splitted_line = ft_split(file_content[i], ' ');
		if(!splitted_line)
			print_error_free_exit(input_info, ERR_MSG_04, true, file_content);

		// create function 'categorize_line'

		if (ft_strchr("NSWE", splitted_line[0][0]))
		{
			if (!check_and_add_texture_path(splitted_line, input_info))
				print_error_free_exit(input_info, ERR_MSG_03, true, file_content);
			elements_counter++;
		}
		else if (ft_strcmp(splitted_line[0], "F") || ft_strcmp(splitted_line[0], "C"))
		{
			if (!check_and_add_colors(file_content[i], splitted_line, input_info))
				print_error_free_exit(input_info, ERR_MSG_06, true, file_content);
			elements_counter++;
		}
		else if (splitted_line[0][0] == '1')
		{
			if((is_line_from_map(file_content[i])) && (elements_counter == 6))
			{
				free_strings_array(splitted_line);
				break;
			}
			else
				print_error_free_exit(input_info, ERR_MSG_04, true, file_content);
		}
		else if (splitted_line[0][0] != '\n')
		{
			print_error_free_exit(input_info, ERR_MSG_04, true, file_content);
		}
		free_strings_array(splitted_line);
		i++;
	}
	// when out of this loop, we're reaching the map part
	input_info->map_info->map = export_map(input_info, file_content, i);
}

int		line_management(char **splitted_line, t_input *input_info, )
{

}

char	**export_map(t_input *input_info, char **file_content, int i)
{
	int		line_counter;

	line_counter = count_lines_from_scene_description(input_info);			// Not ideal because count all the lines
	input_info->map_info->map = ft_calloc(sizeof(char *), line_counter);	// Too much, just allocate for map size
	while (file_content[i])
	{
		add_line_in_map_struct(file_content[i], input_info);				// Ⓜ️
		i++;
		// file_content[i] = get_next_line(fd);		// No need, been exported already earlier
		if(file_content[i] && !(is_line_from_map(file_content[i])))
			print_error_free_exit(input_info, ERR_MSG_04, true, file_content);
	}
	free_strings_array(file_content);
	return (input_info->map_info->map);
}

char	**open_fd_export_content(t_input *input_info)
{
	int		i;
	int		fd;
	int		line_counter;
	char	**file_content;

	i = 0;
	fd = open(input_info->path_to_map, O_RDONLY);
	line_counter = count_lines_from_scene_description(input_info);
	// Count_lines_from_scene_description function makes sure there's something to read, otherwise exit
	file_content = ft_calloc(sizeof(char *), line_counter + 1);
	if (!file_content)
		print_error_free_exit(input_info, strerror(errno), false, NULL);
	while (i < line_counter)
	{
		file_content[i] = get_next_line(fd);				// Ⓜ️ (for each line)
		i++;
	}
	close(fd);
	return (file_content);
}
