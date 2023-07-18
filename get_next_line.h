/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edogarci <edogarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:36:13 by edogarci          #+#    #+#             */
/*   Updated: 2023/06/06 09:36:13 by edogarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char	*f_add_buffer_to_line(char *buffer, char *line, char *end_type);
char	*f_get_line(int fd, char *is_last_line, int read_len);
char	*get_next_line(int fd);
int		f_strlen(char *str);
void	*f_alloc(size_t count, size_t size, char add_eol);
char	*f_str1_to_str2(char *str1, char *str2);
char	*f_upd_buff(char *buff, char *upd_flag, char **line, char *end_type);
char	*f_clean_ptr(char **ptr);
int		f_find_buff_eol(char **buffer, char **end_type);
int		f_read_from_file(int fd, char flag, char **buff);

#endif