/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:26 by lmittie           #+#    #+#             */
/*   Updated: 2019/10/22 17:57:43 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	int		fd;
	t_fdf	data;

	if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
			error();
		read_map(fd, &data);
		close(fd);
		init_win(&data);
		draw(&data);
		mlx_loop(data.mlx_ptr);
	}
	else
		ft_putendl("usage ./fdf");
	exit(1);
	return (0);
}
