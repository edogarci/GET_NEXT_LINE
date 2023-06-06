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

void	f_init_vars(char *read_again)
{
	*read_again = BOOL_YES;
}

int	f_strlen(char *str)
{
	int	cont;

	cont = 0;
	if (!str)
		return (cont);
	while (str[cont] != '\0')
		cont++;
	return (cont);
}

static void	f_str1_to_str2(char *str1, char *str2)
{
	int	pos;

	if (str1 && str2)
	{
		pos = 0;
		while (str1[pos] != '\0')
		{
			str2[pos] = str1[pos];
			pos++;
		}
	}
}

static void	f_add_to_line(char c, void **line)
{
	int		current_len;
	void	*aux;

	current_len = f_strlen((char *)*line);
	if (current_len != 0)
	{
		aux = malloc((current_len) * sizeof(char));
		if (aux)
		{
			f_str1_to_str2((char *)*line, (char *)aux);
			if (*line)
				free(*line);
			*line = malloc(current_len + 1 * sizeof(char));
			f_str1_to_str2((char *)aux, (char *)*line);
			((char *)*line)[current_len] = c;
		}
		free(aux);
	}
	else
	{
		*line = malloc(1 * sizeof(char));
		((char *)*line)[0] = c;
	}
}

char	f_analyze_read(int read_len, void *buffer, void **line)
{
	int	pos;

	pos = 0;
	while (pos < read_len
		&& ((char *)buffer)[pos] != '\n' && ((char *)buffer)[pos] != '\0')
	{
		f_add_to_line(((char *)buffer)[pos], line);
		pos++;
	}
	if (((char *)buffer)[pos - 1] == '\n' || ((char *)buffer)[pos - 1] == '\0')
		return (BOOL_NO);
	else
		return (BOOL_YES);
}

void	f_upd_buffer(void **buffer)
{
	int		pos;
	int		buff_pos;
	void	*aux;

	aux = malloc(BUFFER_SIZE * sizeof(char));
	f_str1_to_str2((char *)*buffer, (char *)aux);
	pos = 0;
	while (((char *)aux)[pos] != '\n')
		pos++;
	pos++;
	buff_pos = 0;
	while (pos < BUFFER_SIZE)
	{
		((char *)*buffer)[buff_pos] = ((char *)aux)[pos];
		buff_pos++;
		pos++;
	}
	while (buff_pos < BUFFER_SIZE)
	{
		((char *)*buffer)[buff_pos] = '\0';
		buff_pos++;
	}
	free(aux);
}

char	*get_next_line(int fd)
{
	static void	*buffer;
	char		read_again;
	int			read_len;
	void		*line;
	char		read_from_file;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	f_init_vars(&read_again);
	if (!buffer)
	{
		buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
		if (!buffer)
			return (NULL);
		read_from_file = BOOL_YES;
	}
	else
		read_from_file = BOOL_NO;
	while (read_again == BOOL_YES)
	{
		if (read_from_file == BOOL_YES)
		{
			read_len = (int)read(fd, (char *)buffer, BUFFER_SIZE);
			if (read_len < 0)
				return (NULL);
		}
		else
		{
			f_upd_buffer(&buffer);
			read_from_file = BOOL_YES;
			read_len = f_strlen((char *)buffer);
		}
		read_again = f_analyze_read(read_len, buffer, &line);
	}
	f_add_to_line('\n', &line);
	return ((char *)line);
}

int	main(void)
{
	int	fd;

	fd = open("test_file.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
