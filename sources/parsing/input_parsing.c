#include "cub3d.h"

void		parsing(char *path, t_input *input_info)
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

bool	is_filename_correct(char *path_to_map)
{
	size_t	file_length;
	char	*tmp;

	file_length = ft_strlen(path_to_map);
	if (!(tmp = ft_strrchr(path_to_map, '.')))
	{
		return(false);
	}
	if ((ft_strcmp(tmp, ".cub")))
	{
		return(false);
	}
	return(true);
}

// check 1st 2 letters of each line
// Except for the map content, each type of element can be separated by one or more empty lines.
// Except for the map content which always has to be the last, each type of element can be set in any order in the file.
// Except for the map, each type of information from an element can be separated by one or more spaces.
// Except for the map, each element must begin with its type identifier (composed by one or two characters), followed by its specific information in a strict order:

void	read_scene_description(t_input *input_info)
{
	int		fd;
	char	**file_content;
	int		line_counter;
	int		i = 0;
	int		elements_counter;
	char	*first_spaces_removed;
	char	**splitted_line;

	line_counter = count_lines_from_scene_description(input_info);
	elements_counter = 0;

	fd = open(input_info->path_to_map, O_RDONLY);
	file_content = ft_calloc(sizeof(char *), line_counter + 1);
	if (!file_content)
		print_error_free_exit(input_info, strerror(errno), false, NULL);
	file_content[i] = get_next_line(fd);				// Ⓜ️ (for each line)
	// Count_lines_from_scene_description function already made sure there's something to read

	while (file_content[i])
	{
		if(file_content[i][0] != '\n' && (strchr(file_content[i], '\n')))
			file_content[i][ft_strlen(file_content[i]) - 1] = ' ';		// Remplace le \n par un espace
		splitted_line = ft_split(file_content[i], ' ');
		if(!splitted_line)
			print_error_free_exit(input_info, ERR_MSG_04, true, file_content);
		// Caution - The \n at the end is kept (either as last separated section, either at the end of the last)
		if (splitted_line[0][0] == 'N' || splitted_line[0][0] == 'S' || splitted_line[0][0] == 'W' || splitted_line[0][0] == 'E')
		{
			if (!check_and_add_texture_path(splitted_line, input_info))
				print_error_free_exit(input_info, ERR_MSG_03, true, file_content);
			elements_counter++;
		}


		else if (splitted_line[0][0] == 'F' || splitted_line[0][0] == 'C')
		{
			if (!check_and_add_colors(splitted_line, input_info))
				print_error_free_exit(input_info, ERR_MSG_06, true, file_content);
			elements_counter++;
		}
		else if ((splitted_line[0][0] == ' ') || (splitted_line[0][0] == '1'))
		{
			if((is_line_from_map(file_content[i])) && (elements_counter == 6))
				break;
			else
				print_error_free_exit(input_info, ERR_MSG_04, true, file_content);
		}
		else if (splitted_line[0][0] != '\n')
		{
			print_error_free_exit(input_info, ERR_MSG_03, true, file_content);
		}
		free_strings_array(splitted_line);
		i++;
		file_content[i] = get_next_line(fd);
	}
	// when out of this loop, we're reaching the map part
	input_info->map_info->map = ft_calloc(sizeof(char *), line_counter);
	while (file_content[i])
	{
		add_line_in_map_struct(file_content[i], input_info);				// Ⓜ️
		i++;
		file_content[i] = get_next_line(fd);
		if(file_content[i] && !(is_line_from_map(file_content[i])))
			print_error_free_exit(input_info, ERR_MSG_04, true, file_content);
	}
	free_strings_array(file_content);
}

int		count_lines_from_scene_description(t_input *input_info)
{
	int		fd;
	char	*gnl_return;
	int		line_counter;

	fd = open(input_info->path_to_map, O_RDONLY);
	line_counter = 0;
	gnl_return = get_next_line(fd);
	if(!gnl_return)
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

/* The map must be composed of only 6 possible characters:
0 for an empty space, 1 for a wall,
and N,S,E or W for the player’s start position and spawning orientation
+ spaces
*/
bool	is_line_from_map(char *line)
{
	int	i;

	i = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == '\n')
		return (false);			// Avoids empty new lines in the middle of the map
	while (line[i] != '\0')
	{
		if ((line[i] == ' ') || (line[i] == '0') || (line[i] == '1') || (line[i] == '\n')
			|| (line[i] == 'N') || (line[i] == 'S') || (line[i] == 'E') || (line[i] == 'W'))
		{
			i++;
		}
		else
			return (false);
	}
	return (true);
}

// Fill empty spaces (at the end each line) with spaces to avoid segfault during parsing
void	spaces_fill_up(t_map_info *map_info)
{
	int		i;
	int		j;
	char	**map;
	char	*tmp;

	i = 0;
	j = 0;
	map = map_info->map;

	while (i <= map_info->max_lines)
	{
		j = map_info->max_columns - 1;									// To jump over the last '\0'
		if (ft_strlen(map[i]) < map_info->max_columns)
		{
			tmp = ft_calloc(sizeof(char), map_info->max_columns + 1);	// +1 for last '\0'
			ft_memcpy(tmp, map[i], ft_strlen(map[i]));
			tmp[j] = '\n';
			j--;
			while (tmp[j] != '\n')							// start by the end, put spaces till reaching the \n
			{
				tmp[j] = ' ';
				j--;
			}
			tmp[j] = ' ';
			free(map[i]);
			map[i] = tmp;
		}
		i++;
	}
	map_info->max_columns--;		// To exclude the \n at the end once we're done checking
	map_info->max_lines++;			// From index to regular digit
}
