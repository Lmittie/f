/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:52:43 by lmittie           #+#    #+#             */
/*   Updated: 2019/10/22 15:51:11 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# define BUFF_SIZE 4096

# include "libft/libft.h"
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_fdf
{
	void *win_ptr;
	void *mlx_ptr;

	int **map;
	int hight;
	int width;
	int zoom;
	int color;
}				t_fdf;

typedef struct	s_coord
{
	float x;
	float y;
	float z;
}				t_coord;

void	read_map(int fd, t_fdf *data);
void	error(void);
void	check_valid(char *tmp, t_fdf *data);
void	init_win(t_fdf *data);
void	draw_line(t_coord crds, float x1, float y1, t_fdf *data);
void	draw(t_fdf *data);

#endif
