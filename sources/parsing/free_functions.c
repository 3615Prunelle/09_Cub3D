#include "cub3d.h"

void	print_error_free_exit(t_input *input_info, char *error_message, bool free_array, char **array)
{
	printf("Error\n");
	printf("%s", error_message);

	if (free_array)
		free_strings_array(array);
	if (input_info)
		free_input_info_struct(input_info);
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

void	free_input_info_struct(t_input *input_info)
{
	if (input_info->NO)
		free(input_info->NO);
	if (input_info->SO)
		free(input_info->SO);
	if (input_info->WE)
		free(input_info->WE);
	if (input_info->EA)
		free(input_info->EA);
	if (input_info->map_info->map)
		free_strings_array(input_info->map_info->map);
	if (input_info->map_info)
		free (input_info->map_info);
	if (input_info)
		free(input_info);
}
