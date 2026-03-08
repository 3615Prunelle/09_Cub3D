#include "cub3d.h"

int		check_and_add_texture_path(char *line, t_input *input_info)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		input_info->NO = clean_path(line);		// Malloc done for every line
		if (!input_info->NO)
			return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		input_info->SO = clean_path(line);
		if (!input_info->SO)
		{
			free(input_info->SO);
			return (0);
		}
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		input_info->WE = clean_path(line);
		if (!input_info->WE)
		{
			free(input_info->NO);
			free(input_info->SO);
			return (0);
		}
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		input_info->EA = clean_path(line);
		if (!input_info->EA)
		{
			free(input_info->NO);
			free(input_info->SO);
			free(input_info->WE);
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
int		check_and_add_colors(char *line, t_input *input_info)
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
					input_info->floor[i] = number_to_check;
				if (line[0] == 'C')
					input_info->ceiling[i] = number_to_check;
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

void	add_line_in_map_struct(char *line, t_input *input_info)
{
	static int	i;
	static int	j;

	if (ft_strlen(line) > j)
	{
		j = ft_strlen(line);		// To get the length of the longuest line
		input_info->map_info->max_columns = j;
	}

	input_info->map_info->map[i] = ft_strdup(line);					// Ⓜ️
	input_info->map_info->max_lines = i;
	i++;
}
