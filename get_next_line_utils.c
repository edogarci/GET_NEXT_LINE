#include "get_next_line.h"

static char	f_find_eol_eof(int read_len, char *buffer, int *pos, char *type)
{
	char	found;

	found = BOOL_NO;
	*pos = 0;
	while (*pos < read_len)
	{
		if (buffer[*pos] == '\n' || buffer[*pos] == '\0')
		{
			if (buffer[*pos] == '\n')
				*type = CONS_EOL;
			else
				*type = CONS_EOF;
			found = BOOL_YES;
			return (found);
		}
		(*pos)++;
	}
	return (found);
}

void	f_clean(int len, char *line)
{
	int	pos;

	pos = 0;
	while (pos < len)
	{
		line[pos] = '\0';
		pos++;
	}
}

static void	f_add_buffer_to_line(char *line, char *buffer, int read_len, char **aux)
{
	int	cont;
	int pos;

	cont = 0;
	pos = 0;

    if (*aux)
    {
        while (pos < read_len)
        {
            line[cont] = (*aux)[pos];
            cont++;
            pos++;
        }
    }
    if (buffer)
    {
        pos = 0;
        while (pos < read_len) {
            line[cont] = buffer[pos];
            cont++;
            pos++;
        }
    }
}

int	f_strlen(char *line)
{
	int cont;

	cont = 0;
	if (line)
	{
		while (line[cont] != '\0')
			cont++;
		return (cont);
	}
}

char	f_analyze_read(int read_len, char *buffer, char **line)
{
	char	found;
	char	type;
	int 	pos;
	int 	current_len;
    char    *line_aux;

	found = f_find_eol_eof(read_len, buffer, &pos, &type);
	if (found == BOOL_YES)
	{
		return (BOOL_NO);
	}
	else if (found == BOOL_NO)
	{
		current_len = f_strlen(*line);
        f_move_line_to_aux(*line, &line_aux, current_len);
		if (*line)
			free(*line);
		*line = malloc((current_len + pos) * sizeof(char));
		f_clean((pos + current_len), *line);
		f_add_buffer_to_line(*line, buffer, read_len, &line_aux);
        if (line_aux)
            free (line_aux);
		return (BOOL_YES);
	}
}