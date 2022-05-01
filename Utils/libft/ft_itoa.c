/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungyyo <hyungyyo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:45:32 by hyungyyo          #+#    #+#             */
/*   Updated: 2020/12/23 20:38:03 by hyungyyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reverse(char *str)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < (int)ft_strlen(str) / 2)
	{
		tmp = str[i];
		str[i] = str[(int)ft_strlen(str) - i - 1];
		str[(int)ft_strlen(str) - i - 1] = tmp;
		i++;
	}
	return (str);
}

static char	*itoa_sub(int *n, char **ret, int len, int *is_neg)
{
	char *result;

	result = NULL;
	if (*n == -2147483648)
	{
		result = (char*)malloc(12);
		ft_strlcpy(result, "-2147483648", 12);
		return (result);
	}
	if (*n < 0)
	{
		*n *= -1;
		*is_neg += 1;
		*ret = (char*)malloc(len + *is_neg);
	}
	else if (*n == 0)
	{
		result = (char*)malloc(2);
		ft_strlcpy(result, "0", 2);
		return (result);
	}
	else
		*ret = (char*)malloc(len + *is_neg);
	return (result);
}

char		*ft_itoa(int n)
{
	int		len;
	int		is_neg;
	int		i;
	char	*result;
	char	*tmp;

	len = 0;
	i = n;
	is_neg = 1;
	while (i != 0 && (len++) + 1)
		i /= 10;
	i = 0;
	if ((tmp = itoa_sub(&n, &result, len, &is_neg)) != NULL)
		return (tmp);
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i++] = n % 10 + '0';
		n /= 10;
	}
	if (is_neg == 2)
		result[len++] = '-';
	result[len] = '\0';
	return (reverse(result));
}
