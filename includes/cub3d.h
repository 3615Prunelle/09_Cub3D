/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:17:58 by schappuy          #+#    #+#             */
/*   Updated: 2026/02/26 16:29:12 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>		// open
# include <limits.h>	// INT_MAX
# include <stdbool.h>
# include <stdlib.h>	// EXIT_FAILURE, EXIT_SUCCESS
# include <sys/stat.h>	// open
# include <sys/time.h>	// time
# include <sys/types.h>	// opendir
# include <unistd.h>	// close, pipe, fork, read, write, getcwd, chdir
// ADD MLX42

// Structs
typedef	struct	s_input
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		floor[3];
	int		ceiling[3];
	char	**map;
}	t_input;

// main.c

// split by file

#endif
