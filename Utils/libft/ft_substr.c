/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:07:04 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/23 23:22:29 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		result = (char*)malloc(1);
		ft_memcpy(result, "", 1);
		return (result);
	}
	result = (char*)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i++ < start)
		s++;
	i = 0;
	while (i < len && *s != '\0')
		result[i++] = *(s++);
	result[i] = '\0';
	return (result);
}
