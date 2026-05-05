#include "cub3d.h"

// Check direction
// Ignore spaces
// Fetch clean path and fill struct
int		check_and_add_texture_path(char **splitted_line, t_input *input_info)
{
	if (!splitted_line[1] || !is_image_reachable(splitted_line[1]))
		return (0);

	if (ft_strncmp(splitted_line[0], "NO", 3) == 0)
	{
		input_info->NO = ft_strdup(splitted_line[1]);		// Malloc for each strdup
	}
	else if (ft_strncmp(splitted_line[0], "SO", 3) == 0)
	{
		input_info->SO = ft_strdup(splitted_line[1]);
	}
	else if (ft_strncmp(splitted_line[0], "WE", 3) == 0)
	{
		input_info->WE = ft_strdup(splitted_line[1]);
	}
	else if (ft_strncmp(splitted_line[0], "EA", 3) == 0)
	{
		input_info->EA = ft_strdup(splitted_line[1]);
	}
	return (1);
}

bool	is_image_reachable(char *path)
{
	char	*tmp;
	int		file_fd;

	if (!(tmp = ft_strrchr(path, '.')))
		return(false);
	if (ft_strcmp(tmp, ".xpm") && ft_strcmp(tmp, ".png"))
		return(false);
	if((file_fd = open(path, O_RDONLY)) == -1)
		return (false);
	return (true);
}

int		check_and_add_colors(char *line, char **splitted_line, t_input *input_info)
{
	int	i;
	int	number_to_check;

	i = 0;
	if (!coma_check(line))
		return (0);
	while (splitted_line[i + 1])
	{
		remove_char_from_line(&splitted_line[i + 1], ',');
		number_to_check = ft_atoi(splitted_line[i + 1]);
		if (number_to_check >= 0 && number_to_check <= 255)
		{
			if (splitted_line[0][0] == 'F')
				input_info->floor[i] = number_to_check;
			if (splitted_line[0][0] == 'C')
				input_info->ceiling[i] = number_to_check;
		}
		else
			return (0);
		i++;
	}
	if (i != 3)				// Not the right amount of numbers
		return (0);
	return (1);
}

// Return 0 if error
int		coma_check(char *line)
{
	int	i;
	int	coma_count;

	i = 0;
	coma_count = 0;
	while (line[i] != '\0')
	{
		while(line[i] == ' ' || line[i] == 'F' || line[i] == 'C')
			i++;
		while (ft_isdigit(line[i]))
			i++;
		while(line[i] == ' ')
			i++;
		if (line[i] == '\0')
			break;
		if (line[i] != ',')
			return(0);
		coma_count++;
		i++;
	}
	if (coma_count == 2)
		return (1);
	return (0);
}

void	add_line_in_map_struct(char *line, t_input *input_info)
{
	static int	i;
	static int	j;

	if (ft_strlen(line) > j)
	{
		j = ft_strlen(line);		// To get the length of the longuest line - Will include \n - Corrected in spaces_fill_up function
		input_info->map_info->max_columns = j;
	}

	input_info->map_info->map[i] = ft_strdup(line);					// Ⓜ️
	input_info->map_info->max_lines = i;
	i++;
}
