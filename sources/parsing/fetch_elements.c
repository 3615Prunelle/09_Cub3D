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

	if ((ft_strncmp(line, "F ", 2) == 0) || (ft_strncmp(line, "C ", 2) == 0))
	{
		rgb_array = get_rgb_array(line);								// Ⓜ️
		if (!rgb_array)
			return (0);
		while (i < 3)
		{
			number_to_check = atoi(rgb_array[i]);
			if (number_to_check >= 0 && number_to_check <= 255)
			{
				if (line[0] == 'F')
					map_data->floor[i] = number_to_check;
				if (line[0] == 'C')
					map_data->ceiling[i] = number_to_check;
			}
			else
			{
				free_strings_array(rgb_array);
				return (0);
			}
			i++;
		}
		free_strings_array(rgb_array);
	}
	else
			return (0);
	return (1);
}

char	**get_rgb_array(char *full_line)
{
	char	*tmp;
	char	**RGB_split;
	tmp = ft_strrchr(full_line, ' ');			// Jumps to the last space
	if (!tmp)
		return (NULL);
	RGB_split = ft_split(tmp, ',');				// Ⓜ️
	if (!RGB_split)
		return (NULL);
	return (RGB_split);
}

// return 0 if error
int		add_line_in_map_struct(char *line, t_input *map_data)
{
	static int	i;

	map_data->map_info.map[i] = ft_strdup(line);					// Ⓜ️
	i++;
}
