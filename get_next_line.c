/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edogarci <edogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:39:14 by edogarci          #+#    #+#             */
/*   Updated: 2023/06/06 09:39:14 by edogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

void	*f_malloc_clean(size_t count, size_t size)
{
	char	*str;
	int		pos;

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

char	*f_add_buffer_to_line(char *buffer, char *line, char *end_type)
{
	char	*aux;
	int		pos;

	aux = NULL;
	pos = 0;
	while (pos < f_strlen(buffer))
	{
		if (buffer[pos] == '\n')
			return (*end_type = CONST_EOL, line);
		if (buffer[pos] == '\0')
			return (*end_type = CONST_EOF, line);
		if (!line)
			line = f_malloc_clean(2, sizeof(char));
		else
		{
			aux = f_malloc_clean(f_strlen(line) + 1, sizeof(char));
			aux = f_str1_to_str2(line, aux);
			free(line);
			line = NULL;
			line = f_malloc_clean(f_strlen(aux) + 2, sizeof(char));
			line = f_str1_to_str2(aux, line);
			free(aux);
			aux = NULL;
		}
		line[f_strlen(line)] = buffer[pos];
		pos++;
	}
	return (*end_type = ' ', line);
}

char	*f_upd_buffer(char *str)
{
	char	*aux;
	int		pos;
	int		str_pos;

	aux = NULL;
	aux = f_malloc_clean(BUFFER_SIZE, sizeof(char));
	if (!aux)
		return (NULL);
	aux = f_str1_to_str2(str, aux);
	pos = 0;
	while (aux[pos] != '\n')
		pos++;
	str_pos = 0;
	while (aux[pos + 1] != '\0')
	{
		str[str_pos] = aux[pos + 1];
		pos++;
		str_pos++;
	}
	while (str_pos < BUFFER_SIZE)
	{
		str[str_pos] = '\0';
		str_pos++;
	}
	free(aux);
	aux = NULL;
	return (str);
}

char	*f_clean(char *ptr)
{
	int	pos;

	pos = 0;
	while (pos < BUFFER_SIZE)
	{
		ptr[pos] = '\0';
		pos++;
	}
	return (ptr);
}

char	*f_get_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			read_len;
	char		end_type;
	char		upd_flag;

	line = NULL;
	upd_flag = BOOL_NO;
	if (!buffer)
	{
		buffer = f_malloc_clean(BUFFER_SIZE, sizeof(char));
		if (!buffer)
			return (NULL);
	}
	else
	{
		buffer = f_upd_buffer(buffer);
		upd_flag = BOOL_YES;
	}		
	read_len = 1;
	while (read_len > 0)
	{
		if (upd_flag == BOOL_NO)
//			buffer = f_clean(buffer);
			read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len < 0)
			return (free(buffer), buffer = NULL, NULL);
		line = f_add_buffer_to_line(buffer, line, &end_type);
		if (end_type == CONST_EOL || end_type == CONST_EOF)
			return (line);
		upd_flag = BOOL_NO;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*res;

	res = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	res = f_get_line(fd);
	if (!res)
		return (NULL);
	else
		return (res);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test_file.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s\n", str);
	str = get_next_line(fd);
	printf("%s\n", str);
	str = get_next_line(fd);
	printf("%s\n", str);
	str = get_next_line(fd);
	printf("%s\n", str);
	str = get_next_line(fd);
	printf("%s\n", str);
	str = get_next_line(fd);
	printf("%s\n", str);
	str = get_next_line(fd);
	printf("%s\n", str);
	close(fd);
	return (0);
}
