/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:59:51 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/23 22:52:29 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;

	i = 0;
	if (!dest && !src)
		return (NULL);
	tmp_dest = (unsigned char*)dest;
	tmp_src = (unsigned char*)src;
	while (i++ < n)
		*(tmp_dest++) = *(tmp_src++);
	return (dest);
}
