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

/* # define BUFFER_SIZE 10 */
# define BOOL_YES 'X'
# define BOOL_NO ' '
# define CONST_EOL 'L'
# define CONST_EOF 'F'

char	*get_next_line(int fd);

#endif