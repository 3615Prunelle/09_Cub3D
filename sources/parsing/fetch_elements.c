#include "cub3d.h"

int		check_and_add_texture_path(char *line, t_input *map_data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		map_data->NO = clean_path(line);		// Malloc done for every line
		if (!map_data->NO)
			return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		map_data->SO = clean_path(line);
		if (!map_data->SO)
		{
			free(map_data->NO);
			return (0);
		}
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		map_data->WE = clean_path(line);
		if (!map_data->WE)
		{
			free(map_data->NO);
			free(map_data->SO);
			return (0);
		}
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		map_data->EA = clean_path(line);
		if (!map_data->NO)
		{
			free(map_data->NO);
			free(map_data->SO);
			free(map_data->WE);
			return (0);
		}
	}
	else
		return (0);
	return (1);
}

char	*clean_path(char *full_line)
{
	char	*path;	// removes unnecessary chars/spaces before & after path
	char	*tmp;
	size_t	path_length;

	tmp = ft_strchr(full_line, '.');				// Removes the first chars/spaces
	if (!tmp)
		return (NULL);
	path_length = ft_strlen(tmp);
	path = ft_calloc(sizeof(char), path_length);
	if (!path)
		return (NULL);
	ft_strlcpy(path, tmp, path_length);				// Removes the \n
	return (path);
}

// return 0 if error
int		check_and_add_colors(char *line, t_input *map_data)
{
	int		i = 0;
	char	**rgb_array;
	int		number_to_check;

	if (ft_strncmp(line, "F ", 2) == 0)
	{

	}
	else if (ft_strncmp(line, "C ", 2) != 0)
	{

	}
	else
			return (0);

	// below a revoir
	// twice the same action => put that in a function that takes an int* and returns 0 or 1
	rgb_array = get_rgb_array(line);
	if (!rgb_array)
		return (0);
	while (i < 3)
	{
		number_to_check = atoi(rgb_array[i]);
		if (number_to_check >= 0 && number_to_check <= 255)
			map_data->floor[i] = atoi(rgb_array[i]);
		else
		{
			free(rgb_array[i]);
			return (0);
		}
		free(rgb_array[i]);
		i++;
	}
	rgb_array = get_rgb_array(line);
	if (!rgb_array)
		return (0);
	i = 0;
	while (i < 3)
	{
		number_to_check = atoi(rgb_array[i]);
		if (number_to_check >= 0 && number_to_check <= 255)
			map_data->ceiling[i] = number_to_check;
		else
		{
			free(rgb_array[i]);
			return (0);
		}
		free(rgb_array[i]);
		i++;
	}
	return (1);
}

char	**get_rgb_array(char *full_line)
{
	char	*tmp;
	char	**RGB_split;
	tmp = ft_strchr(full_line, ' ');
	if (!tmp)
		return (NULL);
	tmp++;										// Maybe not necessary ?
	RGB_split = ft_split(tmp, ',');				// Ⓜ️
	if (!RGB_split)
		return (NULL);
	return (RGB_split);
}

// return 0 if error
int		create_map(char **file_content, t_input *map_data)
{
	/*
	- The map must be composed of only 6 possible characters: 0 for an empty space,
		1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.
	- The map must be closed/surrounded by walls, if not the program must return an error.
	- Except for the map content, each type of element can be separated by one or more empty lines.
‼️	- Except for the map content which always has to be the last, each type of
		element can be set in any order in the file.
	- Except for the map, each type of information from an element can be separated by one or more spaces.
	- The map must be parsed as it looks in the file. Spaces are a valid part of the
		map and are up to you to handle. You must be able to parse any kind of map,
		as long as it respects the rules of the map.
	- Except for the map, each element must begin with its type identifier (composed by one or two
		characters), followed by its specific information in a strict order : identifier - path/rgb
	*/
}
