/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:47:06 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/25 16:21:42 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			buf[n];
	size_t			i;
	unsigned char	*tmp_dest;

	if (dest == src || n == 0)
		return (dest);
	i = 0;
	tmp_dest = (unsigned char*)dest;
	ft_memcpy(buf, src, n);
	i = 0;
	while (i < n)
		*(tmp_dest++) = buf[i++];
	return (dest);
}
