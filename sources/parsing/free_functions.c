/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:29:59 by schappuy          #+#    #+#             */
/*   Updated: 2026/05/16 13:55:40 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error_free_exit(t_input *input_info, char *error_message,
		bool free_array, char **array)
{
	printf("Error\n");
	printf("%s", error_message);
	if (free_array)
		free_strings_array(array);
	if (input_info)
		free_input_info_struct(input_info);
	exit(1);
}

// last gnl call avoids memleaks from buffer if exit before reaching EOF
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
	get_next_line(-1);
}

void	free_input_info_struct(t_input *input_info)
{
	if (input_info->north)
		free(input_info->north);
	if (input_info->south)
		free(input_info->south);
	if (input_info->west)
		free(input_info->west);
	if (input_info->east)
		free(input_info->east);
	if (input_info->map_info->map)
		free_strings_array(input_info->map_info->map);
	if (input_info->map_info)
		free(input_info->map_info);
	if (input_info)
		free(input_info);
}
