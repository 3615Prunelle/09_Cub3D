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

bool	are_surroundings_valid(char **map, int element_line, int element_column)
{
	int		i;
	int		j;

	if ((element_line != 0) && (element_column != 0))
	{
		i = element_line - 1;
		j = element_column - 1;
	}
	else
		return (false);

	while (i <= element_line + 1)
	{
		j = element_column - 1;
		while (j <= element_column + 1)
		{
			if ((i == element_line) && (j == element_column))
				j++;
			else if ((map[i][j] == '0') || (map[i][j] == '1')
				|| (map[i][j] == 'N') || (map[i][j] == 'S') || (map[i][j] == 'E') || (map[i][j] == 'W'))
				j++;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

/*
return -1 if error(no player or multiple or position outside game)
check if inside game : char before + after + above + below + 4 diagonals must be either 0 or 1
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
				input_info->player.initial_coordinates[0] = line;
				input_info->player.initial_coordinates[1] = column;
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
