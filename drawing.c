/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:57:55 by lmittie           #+#    #+#             */
/*   Updated: 2019/10/22 18:00:09 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

float		max_step(float x, float y)
{
	if (x < 0)
		x = x * -1;
	if (y < 0)
		y = y * -1;
	if (x > y)
		return (x);
	else
		return (y);
}

void		isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.5222);
	*y = (*x + *y) * sin(0.5222) - z;
}

void		zoom(t_coord *crds, float *x1, float *y1, t_fdf *data)
{
	crds->x *= data->zoom;
	crds->y *= data->zoom;
	*x1 *= data->zoom;
	*y1 *= data->zoom;
}

void		shift(t_coord *crds, float *x1, float *y1)
{
	crds->x += 500;
	crds->y += 500;
	*x1 += 500;
	*y1 += 500;
}

void		draw_line(t_coord crds, float x1, float y1, t_fdf *data)
{
	float	x_step;
	float	y_step;
	float	max;
	int		z1;

	crds.z = data->map[(int)crds.y][(int)crds.x] * 2;
	z1 = data->map[(int)y1][(int)x1] * 2;
	zoom(&crds, &x1, &y1, data);
	data->color = (crds.z || z1) ? 0xF00000 : 0xFFF000;
	isometric(&crds.x, &crds.y, crds.z);
	isometric(&x1, &y1, z1);
	shift(&crds, &x1, &y1);
	x_step = x1 - crds.x;
	y_step = y1 - crds.y;
	max = max_step(x_step, y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(x1 - crds.x) || (int)(y1 - crds.y))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr,
		crds.x, crds.y, data->color);
		crds.x += x_step;
		crds.y += y_step;
	}
}

static void	delete_map(int ***map)
{
	int i;

	i = 0;
	while ((*map)[i] != NULL)
	{
		free((*map)[i]);
		(*map)[i++] = NULL;
	}
	free(*map);
	*map = NULL;
}

void		draw(t_fdf *data)
{
	t_coord crds;

	crds.y = 0;
	while (crds.y < data->hight)
	{
		crds.x = 0;
		while (crds.x < data->width)
		{
			if (crds.x < data->width - 1)
				draw_line(crds, crds.x + 1, crds.y, data);
			if (crds.y < data->hight - 1)
				draw_line(crds, crds.x, crds.y + 1, data);
			crds.x++;
		}
		crds.y++;
	}
	delete_map(&(data->map));
}
