#include "cub3d.h"

void		parsing(char *path, t_input *map_data)
{
	map_data->path_to_map = path;
	if (!is_filename_correct(path))
	{
		perror(ERR_MSG_02);
		free(map_data);
		exit(1);
	}
	read_scene_description(map_data);
	if(!is_map_valid(map_data))
	{
		// free all the other stuff that has been allocated in read_scene_description function
		print_error_free_exit(map_data, ERR_MSG_07, false, NULL);	// array has been freed in read_scene_description function
	}
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

void	read_scene_description(t_input *map_data)
{
	int		fd;
	char	**file_content;
	int		line_counter;
	int		i = 0;
	int		elements_counter;

	line_counter = count_lines(map_data);
	elements_counter = 0;

	fd = open(map_data->path_to_map, O_RDONLY);
	file_content = ft_calloc(sizeof(char *), line_counter + 1);
	if (!file_content)
		print_error_free_exit(map_data, strerror(errno), false, NULL);
	file_content[i] = get_next_line(fd);				// Ⓜ️ (for each line)
	// No need to check for error because count_lines function already made sure there's something to read
	while (file_content[i])
	{
		if (file_content[i][0] == 'N' || file_content[i][0] == 'S' || file_content[i][0] == 'W' || file_content[i][0] == 'E')
		{
			if (!check_and_add_texture_path(file_content[i], map_data))
				print_error_free_exit(map_data, ERR_MSG_03, true, file_content);
			elements_counter++;
		}
		else if (file_content[i][0] == 'F' || file_content[i][0] == 'C')
		{
			if (!check_and_add_colors(file_content[i], map_data))
				print_error_free_exit(map_data, ERR_MSG_06, true, file_content);
			elements_counter++;
		}
		else if (file_content[i][0] == ' ')		// check tabs also ?
		{
			if((is_line_from_map(file_content[i])) && (elements_counter == 6))
				break;
			else
				print_error_free_exit(map_data, ERR_MSG_04, true, file_content);
		}
		else if (file_content[i][0] != '\n')
		{
			print_error_free_exit(map_data, ERR_MSG_03, true, file_content);
		}
		i++;
		file_content[i] = get_next_line(fd);
	}
	// when out of this loop, we're reaching the map part.
	// free file_content
	// go to build_map function
	map_data->map_info.map = ft_calloc(sizeof(char *), line_counter);
	while (file_content[i])
	{
		add_line_in_map_struct(file_content[i], map_data);				// Ⓜ️
		i++;
		file_content[i] = get_next_line(fd);
		if(file_content[i] && !(is_line_from_map(file_content[i])))
			print_error_free_exit(map_data, ERR_MSG_04, true, file_content);
	}
	free_strings_array(file_content);
}

int		count_lines(t_input *map_data)
{
	int		fd;
	char	*gnl_return;
	int		line_counter;

	fd = open(map_data->path_to_map, O_RDONLY);
	line_counter = 0;
	gnl_return = get_next_line(fd);
	if(!gnl_return)
		print_error_free_exit(map_data, ERR_MSG_05, false, NULL);
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
Added spaces & tabs
*/
bool	is_line_from_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == ' ') || (line[i] == '0') || (line[i] == '1') || (line[i] == '\n') || (line[i] == '\t')
			|| (line[i] == 'N') || (line[i] == 'S') || (line[i] == 'E') || (line[i] == 'W'))
		{
			i++;
		}
		else
			return (false);
	}
	return (true);
}

/*
The map must be closed/surrounded by walls, if not the program must return an error.
*/

bool	is_map_valid(t_input *map_data)
{
	// Also fill up struct (amount of lines + colums)
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = map_data->map_info.map;

	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			// find a way to calculate the longuest line, to fill the total_columns variable in struct
			j++;
		}

		i++;
	}
	map_data->map_info.total_lines = i;

}
