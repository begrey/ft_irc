/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:57:59 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/21 16:35:03 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*tmp_s;

	i = 0;
	tmp_s = (const char*)s;
	while (i < n)
	{
		if (*tmp_s == (char)c)
			return ((void*)tmp_s);
		tmp_s++;
		i++;
	}
	return (NULL);
}
