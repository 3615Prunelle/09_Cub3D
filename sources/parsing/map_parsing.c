#include "cub3d.h"

bool	is_map_valid(t_map_info *map_info)
{
	char	**map;
	int		line;
	int		column;

	line = 0;
	column = 0;
	map = map_info->map;

	while (line < map_info->total_lines)
	{
		column = 0;
		if (((line == 0) || (line == map_info->total_lines)) && (!is_wall_only(map[line])))
			return (false);
		while (((line != 0) && (line != map_info->total_lines)) && (column < map_info->total_columns))
		{
			if ((map[line][column] == '0') && (!are_surroundings_valid(map, line, column)))
				return (false);
			column++;
		}
		line++;
	}
	return (true);
}

/*
Checks if inside game : char before + after + above + below + 4 diagonals must be either 0 or 1
Returns -1 if error(no player or multiple or position outside game)
Pass in function is_line_from_map already done earlier, so no need to check for every single char - Focus on player only
*/
int		check_player(t_input *input_info, char **map)
{
	int		player_found;
	int		line;
	int		column;

	player_found = 0;
	line = 0;
	while (map[line])
	{
		column = 0;
		while (map[line][column] != '\0')
		{
			if (ft_strchr("NSEW", map[line][column]))
			{
				add_player_info_in_struct(input_info, line, column);
				player_found++;
				if (!are_surroundings_valid(map, line, column))
					return (-1);
			}
			column++;
		}
		line++;
	}
	if (player_found != 1)
		return (-1);
	return (1);
}

void	add_player_info_in_struct(t_input *input_info, int line, int column)
{
	char	**map;

	map = input_info->map_info->map;
	input_info->player.initial_direction = map[line][column];
	input_info->player.int_cords[0] = column;			// Switched line & column for Maxi to handle
	input_info->player.int_cords[1] = line;
	map[line][column] = '0';
}
