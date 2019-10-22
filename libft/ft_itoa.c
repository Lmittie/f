/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:52:13 by fmallist          #+#    #+#             */
/*   Updated: 2019/09/19 20:48:46 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_numlen(int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int			count;
	char		*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_numlen(n);
	if ((res = (char *)malloc(sizeof(char) * (count + 1))) == NULL)
		return (NULL);
	res[count--] = '\0';
	if (n == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (n < 0)
	{
		n = n * (-1);
		res[0] = '-';
	}
	while (n > 0)
	{
		res[count--] = '0' + (n % 10);
		n = n / 10;
	}
	return (res);
}
