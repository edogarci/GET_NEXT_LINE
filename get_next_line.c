#include "get_next_line.h"

void    f_move_line_to_aux(char *line, char **line_aux, int current_len)
{
    int pos;

    if (line && current_len != 0)
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

static char f_previous_call_exists(void **buffer)
{
    int     len;
    char	found;
    char	type;
    int 	pos;

    len = f_strlen((char *)*buffer);
    if (len > 0)
    {
        found = f_find_eol_eof(len, (char *)*buffer, &pos, &type);
        if (type == CONS_EOL)
        {
            *buffer = *buffer + pos + 1;
            return (BOOL_YES);
        }
    }
    return (BOOL_NO);
}

char	*get_next_line(int fd)
{
    static void *buffer;
    char        *line;
	int         read_len;
	char        read_again;
    char        prev_call;

	if (fd < 0)
		return (NULL);
    if (!buffer)
    {
        buffer = malloc(BUFFER_SIZE * sizeof(char));
        f_clean(BUFFER_SIZE, (char *)buffer);
    }
	if (!buffer)
		return (NULL);
    line = NULL;
	read_again = BOOL_YES;
    prev_call = f_previous_call_exists(&buffer);
	while (read_again == BOOL_YES)
	{
        if  (prev_call == BOOL_NO)
		    read_len = (int)read(fd, buffer, BUFFER_SIZE);
		read_again = f_analyze_read(read_len, (char *)buffer, &line);
	    prev_call = BOOL_NO;
    }
	return (line);
}