#include "cub3d.h"

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

// Replaces 'to_remove' by spaces (used for '\n' ',')
// Change chars in memory
void	remove_char_from_line(char **line, char to_remove)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == to_remove)
		{
			(*line)[i] = ' ';
		}
		i++;
	}
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
+ spaces. Before & after space - Only :
- space
- wall
- \0
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
		if ((line[i] == ' ' || line[i] == '0') || (line[i] == '1') || (line[i] == '\n')
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
			while (tmp[j] != '\n')										// start by the end, put spaces till reaching the \n
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
