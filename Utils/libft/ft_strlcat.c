/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:55:07 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/22 22:47:13 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t srclen;
	size_t destlen;
	size_t i;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	if (size < destlen + 1)
		return (size + srclen);
	i = 0;
	if (size > destlen + 1)
	{
		while (src[i] != '\0' && (destlen + 1 + i) < size)
		{
			dest[destlen + i] = src[i];
			i++;
		}
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
