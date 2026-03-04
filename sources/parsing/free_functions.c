#include "cub3d.h"

void	print_error_free_exit(t_input *map_data, char *error_message, bool free_array, char **array)
{
	printf("Error\n");
	printf("%s", error_message);

	if (free_array)
		free_strings_array(array);
	if (map_data)
		free_map_data_struct(map_data);
	exit (1);
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
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	get_next_line(-1);		// avoids memleaks from buffer if exit before reaching EOF
}

void	free_map_data_struct(t_input *map_data)
{
	if (map_data->NO)
		free(map_data->NO);
	if (map_data->SO)
		free(map_data->SO);
	if (map_data->WE)
		free(map_data->WE);
	if (map_data->EA)
		free(map_data->EA);
	if (map_data->map_info.map)
		free_strings_array(map_data->map_info.map);
	if (map_data)
		free(map_data);
}
