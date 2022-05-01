/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:40:46 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/24 09:50:25 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char a, char const *set)
{
	while (*set != '\0')
	{
		if (a == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*get_trim(char *s1)
{
	char	*result;
	int		len;
	char	*tmp;
	int		i;

	len = 0;
	tmp = (char*)s1;
	while (*tmp != '\0')
		if (*(tmp++) != 1)
			len++;
	result = (char*)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	tmp = (char*)s1;
	i = 0;
	while (*tmp != '\0')
	{
		if (*tmp != 1)
			result[i++] = *tmp;
		tmp++;
	}
	result[i] = '\0';
	free(s1);
	return (result);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(s1);
	while (i < ft_strlen(tmp))
	{
		if (isset(tmp[i], set) == 1)
			tmp[i] = 1;
		else
			break ;
		i++;
	}
	i = (int)ft_strlen(tmp) - 1;
	while (i != 0)
	{
		if (isset(tmp[i], set) == 1)
			tmp[i] = 1;
		else
			break ;
		i--;
	}
	return (get_trim(tmp));
}
