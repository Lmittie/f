/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:08:09 by lmittie           #+#    #+#             */
/*   Updated: 2019/10/22 17:48:32 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void		check_valid(char *tmp, t_fdf *data)
{
	int k;

	data->width = 0;
	data->hight = 0;
	k = 0;
	while (*tmp != '\0')
	{
		if (ft_isdigit(*tmp) && (*(tmp + 1) == ' ' ||
		*(tmp + 1) == '\0' || *(tmp + 1) == '\n'))
			k++;
		if (*(tmp + 1) == '\n' || *(tmp + 1) == '\0')
		{
			if (data->width != 0 && k != data->width)
				error();
			data->width = k;
			k = 0;
			data->hight += 1;
			tmp++;
		}
		if (*tmp != '\0')
			tmp++;
	}
	if (!data->hight || !data->width)
		error();
}

void		create_map(char **future_map, t_fdf *data)
{
	int		i;
	int		j;
	int		k;
	int		hight;
	char	*ptr;

	k = 0;
	i = 0;
	j = 0;
	if (!(data->map = (int**)malloc(sizeof(int*) * (data->hight + 1))))
		error();
	hight = data->hight;
	data->map[hight] = NULL;
	while (hight--)
		data->map[hight] = (int*)malloc(sizeof(int) * data->width);
	while (future_map[k] != NULL)
	{
		data->map[i][j++] = ft_atoi(future_map[k]);
		if ((ptr = ft_strchr(future_map[k], '\n')) && *(ptr + 1) != '\0')
		{
			j = 0;
			data->map[++i][j++] = ft_atoi(ptr);
		}
		k++;
	}
	i = 0;
	while (data->map[i] != NULL)
	{
		for (j = 0; j < data->width; j++)
		{
				printf("%3d ", data->map[i][j]);
		}
		printf("\n");
		i++;
	}
}

static void	delete(char ***arr)
{
	int i;

	i = 0;
	while ((*arr)[i] != NULL)
		ft_strdel(&(*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

void		read_map(int fd, t_fdf *data)
{
	char	**future_map;
	char	buff[BUFF_SIZE + 1];
	char	*tmp_map;
	int		ret;

	tmp_map = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!(tmp_map = ft_strjoin_free(tmp_map, buff, 1, 0)))
			error();
	}
	check_valid(tmp_map, data);
	if (!(future_map = ft_strsplit(tmp_map, ' ')))
		error();
	ft_strdel(&tmp_map);
	create_map(future_map, data);
	delete(&future_map);
}
