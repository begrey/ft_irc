/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:07:44 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/21 16:33:41 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t		i;
	char		*tmp_dest;
	const char	*tmp_src;

	i = 0;
	tmp_dest = (char*)dest;
	tmp_src = (const char*)src;
	while (i < n)
	{
		*tmp_dest = *tmp_src;
		if (*tmp_dest == (char)c)
			return (++tmp_dest);
		tmp_dest++;
		tmp_src++;
		i++;
	}
	return (NULL);
}
