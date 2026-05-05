#include "cub3d.h"

bool	is_map_valid(t_map_info *map_info)
{
	char	**map;
	int		line;
	int		column;

	line = 0;
	column = 0;
	map = map_info->map;

	while (line < map_info->max_lines)
	{
		column = 0;
		if (((line == 0) || (line == map_info->max_lines)) && (!is_wall_only(map[line])))
			return (false);
		while (((line != 0) && (line != map_info->max_lines)) && (column < map_info->max_columns))
		{
			if ((map[line][column] == '0') && (!are_surroundings_valid(map, line, column)))
				return (false);
			column++;
		}
		line++;
	}
	return (true);
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

/*
Checks if inside game : char before + after + above + below + 4 diagonals must be either 0 or 1
Returns -1 if error(no player or multiple or position outside game)
*/
int		update_player_info(t_input *input_info)
{
	char	**map;
	bool	player_found;
	int		line;
	int		column;

	map = input_info->map_info->map;
	player_found = false;
	line = 0;
	column = 0;
	while (map[line])
	{
		column = 0;
		while (map[line][column] != '\0')
		{
			// Pass in function is_line_from_map already done earlier, so no need to check for every single char - Focus on player only
			if ((map[line][column] == 'N') || (map[line][column] == 'S') || (map[line][column] == 'E') || (map[line][column] == 'W'))
			{
				if (player_found)
					return (-1);
				input_info->player.initial_direction = map[line][column];
				input_info->player.int_cords[0] = column;			// Switched line & column for Maxi to handle
				input_info->player.int_cords[1] = line;
				player_found = true;
				if (!are_surroundings_valid(map, line, column))
					return (-1);
			}
			column++;
		}
		line++;
	}
	return (1);
}
