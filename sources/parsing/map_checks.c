#include "cub3d.h"

/*
The map must be closed/surrounded by walls, if not the program must return an error.
*/

bool	is_map_valid(t_input *input_info)
{
	// Also fill up struct (amount of lines + colums)
	// Keep count of lines & columns here to be able to put player position in struct
	int		i;
	int		idx_backup[2];				// {first '1', last '1'}
	bool	player_found;
	char	**map;

	i = 0;
	player_found = false;
	map = input_info->map_info.map;

	/*
	every next line :
		- ignore spaces
		- 1st char must be '1'
		- 1st '1' must be at most the same index as last '1' from previous line
		- If 1st '1' is before index as first '1' from previous line, must be '1' till reaching that index
		- ignore every 0 1 coming next
		- if N S E W, save position, update struct variables + make sure there's only one (bool player_found)
		- last char must be '1' + must be at least the same index as first '1' from previous line
		- from there, must be '1' only
	*/

	while (map[i])
	{
		if (i == 0)			// Check walls on line [0], save index start + end
		{
			if (!is_full_wall(map[0], idx_backup))
				return (false);
		}
		else if (map[i+1])
		{
			if (is_line_valid(map[i], idx_backup, &player_found))		// TO DO NEXT
				return (false);
		}
		else				// Last line - THEORICALLY
		{
			if (!is_full_wall(map[0], idx_backup))
				return (false);
			// Check index matching
		}
		i++;
	}
	input_info->map_info.total_lines = i;

}

// return -1 if error(no player or multiple or position outside game)
// check if inside game : char before + after + above + below + 4 diagonals must be either 0 or 1
/*
11111
10P01
11111
*/
int		update_player_info(t_input *input_info)
{
	char	**map;
	bool	player_found;
	int		line;
	int		column;

	map = input_info->map_info.map;
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
				if (!is_player_position_valid(input_info))
					return (-1);
			}
			column++;
		}
		line++;
	}

}

/*
	line above must be either 0 or 1 on column player_column-1, player_column, player_column+1
	same for line below
	line must be either 0 or 1 on column player_column-1 & player_column+1
111
1P1
111
*/

bool	is_player_position_valid(t_input *input_info)
{
	int		player_line;
	int		player_column;
	int		i;
	int		j;
	char	**map;

	player_line = input_info->player.initial_coordinates[0];
	player_column = input_info->player.initial_coordinates[1];
	i = player_line - 1;
	j = player_column - 1;
	map = input_info->map_info.map;

	while (i <= player_line + 1)
	{
		j = player_column - 1;
		while (j <= player_column + 1)
		{
			if ((i == player_line) && (j == player_column))
				j++;
			else if ((map[i][j] == '0') || (map[i][j] == '1'))
				j++;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

bool	is_line_valid(char *line, int *idx_backup, bool *player_found)
{
	int			i;
	int			j;
	static bool	player_found;
	char		**map;

	i = 0;
	player_found = false;

	i = 0;
	j = 0;

	while (line[i] != '\n')
	{
		while (line[i] == ' ')
		{
			i++;
		}
		if ((line[i] == '1') && (i <= idx_backup[1]))
		{
			idx_backup[0] = i;			// First '1'
			i++;
		}
		else
			return (false);
		while ((line[i] == '1') || (line[i] == '0'))
		{
			/* code */
		}

//			  111111
//		           111111
		else
			return (false);
		while (line[i] == '1') || (line[i] == '1')
		{
			i++;
		}
	}

	// check walls at beg + end
	// Check index matching
	// check if player found - if player_found is true, but another letter is found > error : max 1 player (not required though ...)
}

bool		are_indexes_matching(char *line, int *idx_backup)
{

}

/*	1st line :
		- ignore spaces, then must be consecutive '1'
		- save position of 1st + last '1'
	Last line
		- Index matching + ignore spaces, then must be consecutive '1'
*/
bool	is_full_wall(char *line, int *idx_backup)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
	{
		i++;
	}
	idx_backup[0] = i;			// First '1'
	while (line[i] == '1')
	{
		i++;
	}
	idx_backup[1] = i - 1;		// Last '1'
	if ((i == 0) || (line[i] != '\n'))			// other characters than spaces/walls have been found
		return (false);
	return (true);
}
