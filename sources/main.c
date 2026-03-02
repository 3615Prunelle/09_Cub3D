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
		print_error_free_exit(NULL, ERR_MSG_01, false, NULL);
	map_data = ft_calloc(sizeof(t_input), 1);				// Ⓜ️
	if(!map_data)
		print_error_free_exit(NULL, strerror(errno), false, NULL);
	parsing(av[1], map_data);



	// 1st function = parsing & checking
	// rendering in minimap
	// set up textures
	// render final map & movements in loop
	return(0);
}
