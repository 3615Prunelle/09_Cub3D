#include "cub3d.h"

int	main(int ac, char **av)
{
	t_input	*input_info;
	if (ac != 2)
		print_error_free_exit(NULL, ERR_MSG_01, false, NULL);
	input_info = ft_calloc(sizeof(t_input), 1);				// Ⓜ️
	if(!input_info)
		print_error_free_exit(NULL, strerror(errno), false, NULL);
	parsing(av[1], input_info);
	printf("Parsing & Map creation success\n");

	// rendering in minimap
	// set up textures
	// render final map & movements in loop

	free_input_info_struct(input_info);
	return(0);
}
