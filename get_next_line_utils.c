/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edogarci <edogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:36:45 by edogarci          #+#    #+#             */
/*   Updated: 2023/06/06 09:36:45 by edogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	f_strlen(char *str)
{
	int	cont;

	cont = 0;
	if (str)
	{
		while (str[cont] != '\0')
			cont++;
	}
	return (cont);
}

void	*f_alloc(size_t count, size_t size, char add_eol)
{
	char	*str;
	size_t	pos;

	str = NULL;
	str = malloc(count * size);
	if (!str)
		return (NULL);
	pos = 0;
	while (pos < count)
	{
		str[pos] = '\0';
		pos++;
	}
	if (add_eol == 'X')
		str[0] = '\n';
	return (str);
}

char	*f_str1_to_str2(char *str1, char *str2)
{
	int	cont1;
	int	pos;

	cont1 = f_strlen(str1);
	if (cont1 > 0)
	{
		pos = 0;
		while (str1[pos] != '\0')
		{
			str2[pos] = str1[pos];
			pos++;
		}
	}
	return (str2);
}

char	*f_upd_buff(char *buff, char *upd_flag, char **line, char *end_type)
{
	char	*aux;
	int		pos;
	int		buff_pos;

	*line = NULL;
	*end_type = ' ';
	*upd_flag = ' ';
	if (buff)
	{
		aux = f_alloc(BUFFER_SIZE + 1, sizeof(char), ' ');
		if (!aux)
			return (NULL);
		aux = f_str1_to_str2(buff, aux);
		pos = 0;
		while (aux[pos] != '\n')
			pos++;
		buff_pos = 0;
		while (aux[pos + 1] != '\0')
			buff[buff_pos++] = aux[(pos++) + 1];
		while (buff_pos < BUFFER_SIZE)
			buff[buff_pos++] = '\0';
		*upd_flag = 'X';
		return (free(aux), aux = NULL, buff);
	}
	return (buff);
}

char	*f_clean_ptr(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	*ptr = f_alloc(BUFFER_SIZE + 1, sizeof(char), ' ');
	if (!*ptr)
		return (NULL);
	return (*ptr);
}
