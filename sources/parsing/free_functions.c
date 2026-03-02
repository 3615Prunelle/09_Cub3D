#include "cub3d.h"

void	print_error_free_exit(t_input *map_data, char *error_message, bool free_array, char **array)
{
	perror("Error\n");
	perror(error_message);
	if (free_array)
		free_strings_array(array);
	if (map_data)
		free(map_data);
	exit;
}

void	free_strings_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);		// check if it was allocated. if not, don't free
}
