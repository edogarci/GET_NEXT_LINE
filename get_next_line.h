#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 3
# define BOOL_YES 'X'
# define BOOL_NO ' '
# define CONS_EOL 'L'
# define CONS_EOF 'F'


char	*get_next_line(int fd);
char	f_analyze_read(int read_len, char *buffer, char **line);
void	f_clean(int len, char *line);
int		f_strlen(char *line);
void    f_move_line_to_aux(char *line, char **aux, int current_len);

#endif