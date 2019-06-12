/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:17:33 by qbackaer          #+#    #+#             */
/*   Updated: 2019/06/12 17:20:48 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_tablen(char **tab)
{
	char	**roam;
	size_t	len;

	if (!tab)
		return (0);
	len = 0;
	roam = tab;
	while (*roam)
	{
		len++;
		roam++;
	}
	return (len);
}
