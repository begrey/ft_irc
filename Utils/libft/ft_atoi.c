/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:49:08 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/24 09:54:24 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	long long	result;
	int			neg_flag;

	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v' ||
			*nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	result = 0;
	neg_flag = 1;
	if (*nptr == '+' || *nptr == '-')
		if (*(nptr++) == '-')
			neg_flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (long long)(*nptr - '0');
		nptr++;
	}
	return ((int)(result * (long long)neg_flag));
}
