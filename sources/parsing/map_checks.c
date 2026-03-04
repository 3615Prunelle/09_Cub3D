#include "cub3d.h"

/*
The map must be closed/surrounded by walls, if not the program must return an error.
*/

bool	is_map_valid(t_input *map_data)
{
	// Also fill up struct (amount of lines + colums)
	int		i;
	int		idx_backup[2];				// {first '1', last '1'}
	bool	player_found;
	char	**map;

	i = 0;
	player_found = false;
	map = map_data->map_info.map;

	/*
	every next line :
		- ignore spaces/tabs
		- 1st char must be '1'
		- 1st '1' must be at most the same index as last '1' from previous line
		- If 1st '1' is before index as first '1' from previous line, must be '1' till reaching that index
		- ignore every 0 1 coming next
		- if N S E W, save position, update struct variables + make sure there's only one (bool player_found)
		- last char must be '1' + must be at least the same index as first '1' from previous line
		- from there, must be '1' only
		     111111
		111111
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
	map_data->map_info.total_lines = i;

}

bool	is_line_valid(char *line, int *idx_backup, bool *player_found)
{
	// check walls at beg + end
	// Check index matching
	// check if player found - if player_found is true, but another letter is found > error : max 1 player (not required though ...)
}

bool		are_indexes_matching(char *line, int *idx_backup)
{

}

/*	1st line :
		- ignore spaces/tabs, then must be consecutive '1'
		- save position of 1st + last '1'
	Last line
		- Index matching + ignore spaces/tabs, then must be consecutive '1'
*/
bool	is_full_wall(char *line, int *idx_backup)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((line[i] == ' ') || (line[i] == '\t'))
	{
		i++;
	}
	idx_backup[0] = i;			// First '1'
	while (line[i] == '1')
	{
		i++;
	}
	idx_backup[1] = i - 1;		// Last '1'
	if ((i == 0) || (line[i] != '\n'))			// other characters than spaces/tabs/walls have been found
		return (false);
	return (true);
}
