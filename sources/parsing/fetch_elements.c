#include "cub3d.h"

int		check_and_add_texture_path(char **splitted_line, t_input *input_info)
{
	// check direction
	// ignore spaces
	// fetch clean path and fill struct
	if (!splitted_line[1] || !is_image_reachable(splitted_line[1]))
		return (0);

	if (ft_strncmp(splitted_line[0], "NO", 3) == 0)
	{
		input_info->NO = splitted_line[1];
	}
	else if (ft_strncmp(splitted_line[0], "SO", 3) == 0)
	{
		input_info->SO = splitted_line[1];
	}
	else if (ft_strncmp(splitted_line[0], "WE", 3) == 0)
	{
		input_info->WE = splitted_line[1];
	}
	else if (ft_strncmp(splitted_line[0], "EA", 3) == 0)
	{
		input_info->EA = splitted_line[1];
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

// return 0 if error
int		check_and_add_colors(char **splitted_line, t_input *input_info)
{
	int		i = 0;
	int		number_to_check;

	if ((ft_strncmp(splitted_line[0], "F", 2) == 0) || (ft_strncmp(splitted_line[0], "C", 2) == 0))
	{
		while (i < 3)
		{
			number_to_check = atoi(splitted_line[i+1]);
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
	}
	else
			return (0);
	return (1);
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
