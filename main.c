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

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_input	*map_data;
	if (ac != 2)
	{
		perror("Invalid amount of args - Just provide a map in .cub format\n");
		return(1);
	}
	map_data = ft_calloc(sizeof(t_input), 1);
	if (!parsing(av[1], map_data))
	{
		perror("Something went wrong during parsing\n");
		free(map_data);
		return(1);
	}


	// av[1] = a map in format *.cub
	// 1st function = parsing & checking
	// rendering in minimap
	// set up textures
	// render final map & movements in loop
	return(0);
}
