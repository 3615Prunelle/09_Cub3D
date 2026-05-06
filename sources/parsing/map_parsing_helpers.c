#include "cub3d.h"

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
	char	**map;			// Pass as arg to gain 2 lines
	char	*tmp;

	i = 0;
	map = map_info->map;	// Pass as arg to gain 2 lines
	while (i <= map_info->max_lines)
	{
		j = map_info->max_columns - 1;									// To jump over the last '\0'
		if (ft_strlen(map[i]) < map_info->max_columns)
		{
			tmp = ft_calloc(sizeof(char), map_info->max_columns + 1);	// +1 for last '\0'
			ft_memcpy(tmp, map[i], ft_strlen(map[i]));
			tmp[j] = '\n';
			j--;
			while (tmp[j] != '\n')										// start by the end, put spaces till reaching the initial \n
			{
				tmp[j] = ' ';
				j--;
			}
			tmp[j] = ' ';												// To replace initial \n by a space - Can probably be optimized
			free(map[i]);
			map[i] = tmp;
		}
		i++;
	}
	// Put the 2 following lines in the calling function to make room ?
	// Or find another way to shorten the function
	map_info->max_columns--;		// To exclude the \n at the end once we're done checking
	map_info->max_lines++;			// From index to regular digit
}

// Ignore spaces, then must be consecutive '1' or spaces
bool	is_wall_only(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
	{
		i++;
	}
	while (line[i] == '1' || line[i] == ' ')
	{
		i++;
	}
	if ((i == 0) || (line[i] != '\n'))			// other characters than spaces/walls have been found
		return (false);
	return (true);
}

// Ne pas checker les diagonales partant de l'element
bool	are_surroundings_valid(char **map, int element_line, int element_column)
{
	// OLD CODE BEFORE OPTIMIZATION - KEEP IF ISSUE
	// char	to_check;

	// if ((element_line == 0) || (element_column == 0))
	// 	return (false);									// No element (player or '0') should be at line 0 or column 0

	// to_check = map[element_line][element_column + 1];	// What's on the left ?
	// if (!ft_strchr("01NSEW", to_check))
	// 	return(false);

	// to_check = map[element_line][element_column - 1];	// What's on the right ?
	// if (!ft_strchr("01NSEW", to_check))
	// 	return(false);

	// to_check = map[element_line - 1][element_column];	// What's above ?
	// if (!ft_strchr("01NSEW", to_check))
	// return(false);

	// to_check = map[element_line + 1][element_column];	// What's below ?
	// if (!ft_strchr("01NSEW", to_check))
	// 	return(false);

	// return (true);

	static int	directions[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};	// static so it's norminette approved for decl + init on same line
	int			i;

	i = 0;
	if (element_line == 0 || element_column == 0)
		return (false);
	while (i < 4)
	{
		if (!ft_strchr("01NSEW", map[element_line + directions[i][0]][element_column + directions[i][1]]))
			return (false);
		i++;
	}
	return (true);
}
