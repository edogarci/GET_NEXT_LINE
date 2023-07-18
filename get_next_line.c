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

int	f_find_buff_eol(char **buffer, char **end_type)
{
	int		pos;
	int		buff_len;

	pos = 0;
	buff_len = 0;
	while (buff_len < f_strlen(*buffer))
	{
		if ((*buffer)[buff_len] == '\n')
		{
			**end_type = 'L';
			break ;
		}
		if ((*buffer)[pos] == '\0')
		{
			**end_type = ' ';
			break ;
		}
		buff_len++;
	}
	return (buff_len);
}

char	*f_add_buffer_to_line(char *buffer, char *line, char *end_type)
{
	char	*aux;
	int		pos;
	int		cont;
	int		buff_len;

	buff_len = f_find_buff_eol(&buffer, &end_type);
	if (buff_len != 0)
	{
		if (!line)
			line = f_alloc(buff_len + 1, sizeof(char), ' ');
		else
		{
			aux = f_alloc(f_strlen(line) + 1, sizeof(char), ' ');
			aux = f_str1_to_str2(line, aux);
			free(line);
			line = f_alloc(f_strlen(aux) + buff_len + 1, sizeof(char), ' ');
			line = f_str1_to_str2(aux, line);
			free(aux);
		}
		cont = f_strlen(line);
		pos = 0;
		while (pos < buff_len)
			line[cont++] = buffer[pos++];
	}
	return (line);
}

int	f_read_from_file(int fd, char flag, char **buff)
{
	int	read_len;

	read_len = 1;
	if (flag == ' ')
	{
		f_clean_ptr(&*buff);
		if (*buff)
			read_len = read(fd, *buff, BUFFER_SIZE);
	}
	return (read_len);
}

char	*f_get_line(int fd, char *lastline, int read_len)
{
	static char	*buffer;
	char		*line;
	char		end_type;
	char		upd_flag;

	buffer = f_upd_buff(buffer, &upd_flag, &line, &end_type);
	while (read_len > 0)
	{
		read_len = f_read_from_file(fd, upd_flag, &buffer);
		if (read_len < 0)
			return (free(line), line = NULL, free(buffer), buffer = NULL, NULL);
		else if (read_len == 0 && f_strlen(line) == 0)
			return (free(buffer), buffer = NULL, NULL);
		else if (read_len == 0 && f_strlen(line) != 0)
			return (*lastline = 'X', free(buffer), buffer = NULL, line);
		line = f_add_buffer_to_line(buffer, line, &end_type);
		if (end_type == 'L' && f_strlen(line) == 0)
			line = f_alloc(BUFFER_SIZE + 1, sizeof(char), 'X');
		if (end_type == 'L')
			return (line);
		upd_flag = ' ';
	}
	return (NULL);
}
/* char	*f_get_line(int fd, char *lastline)
{
	static char	*buffer;
	char		*line;
	int			read_len;
	char		end_type;
	char		upd_flag;

	line = NULL;
	read_len = 1;
	end_type = ' ';
	upd_flag = ' ';
	if (buffer)
		buffer = f_upd_buffer(buffer, &upd_flag);
	while (read_len > 0)
	{
		if (upd_flag == ' ')
		{
			f_clean_ptr(&buffer);
			if (!buffer)
				return (NULL);
			read_len = read(fd, buffer, BUFFER_SIZE);
		}
		if (read_len < 0)
			return (free(line), line = NULL, free(buffer), buffer = NULL, NULL);
		if (read_len == 0)
		{
			if (f_strlen(line) == 0)
				return (free(buffer), buffer = NULL, NULL);
			else
				return (*lastline = 'X', free(buffer),
					buffer = NULL, line);
		}
		line = f_add_buffer_to_line(buffer, line, &end_type);
		if (end_type == 'L')
		{
			if (f_strlen(line) == 0)
			{
				line = f_alloc(BUFFER_SIZE + 1, sizeof(char));
				line[0] = '\n';
			}
			return (line);
		}
		upd_flag = ' ';
	}
	return (NULL);
} */

char	*get_next_line(int fd)
{
	char	*res;
	char	lastline;
	int		len;
	char	*aux;

	lastline = ' ';
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	res = f_get_line(fd, &lastline, 1);
	if (!res)
		return (NULL);
	else if (res[0] != '\n' && lastline == ' ')
	{
		len = f_strlen(res);
		aux = f_alloc((len + 1), sizeof(char), ' ');
		if (!aux)
			return (NULL);
		f_str1_to_str2(res, aux);
		free(res);
		res = f_alloc((len + 2), sizeof(char), ' ');
		f_str1_to_str2(aux, res);
		res[len] = '\n';
		free(aux);
	}
	return (res);
}

/* #include <stdio.h>
int	main(void)
{
	int		fd;
	char	*str;
	int		i = 0;

	fd = open("test_file.txt", O_RDONLY);
	while (i < 12)
	{
		str = get_next_line(fd);
		printf("%s", str);
		i++;
	}
	close(fd);
	return (0);
}
 */