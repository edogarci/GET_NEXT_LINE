#include "get_next_line.h"

void    f_move_line_to_aux(char *line, char **line_aux, int current_len)
{
    int pos;

    if (line )
    {
        *line_aux = malloc(current_len * sizeof(char));
        if (*line_aux)
        {
            pos = 0;
            while (line[pos] != '\0')
            {
                (*line_aux)[pos] = line[pos];
                pos++;
            }
        }
    }
}

char	*get_next_line(int fd)
{
    static void *buffer;
    char        *line;
	int         read_len;
	char        read_again;

	if (fd < 0)
		return (NULL);
    if (!buffer)
	    buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (NULL);
	f_clean(BUFFER_SIZE, buffer);
    line = NULL;
	read_again = BOOL_YES;
	while (read_again == BOOL_YES)
	{
		read_len = (int)read(fd, buffer, BUFFER_SIZE);
		read_again = f_analyze_read(read_len, (char *)buffer, &line);
	}
	return (line);
}