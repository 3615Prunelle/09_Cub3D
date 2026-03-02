/* Notes random
🔴
🟠
🟡
🟢
🔵
🟣
🟤
⚫
⚪

⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

char	**mockup_map(int i)
{
	char	**map;
	int		j;

	j = 0;
	map = (char **)mallock(sizeof(char *) * 10);
	if (!map)
		return(NULL);
	map[9] = NULL;
	while (i < 9)
	{
		map[i] = mallock(sizeof(char) * 11)
		if (!map[i])
			return(breakdown(map));
		while (j < 10)
		{
			if (i == 0 || j == 0 || j == 9)
				map[i][j] = '1';
			else
				map[i][j] = '0';
			j++;
		}
		j = 0;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_cube	game;
	char	**map
	map = mockup_map(0)//so I dont need any checks
	// av[1] = a map in format *.cub
	// 1st function = parsing & checking
	// rendering in minimap
	// set up textures
	// render final map & movements in loop
	return(0);
}
