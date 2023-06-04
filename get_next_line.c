#include "get_next_line.h"

char	*get_next_line(int fd)
{
	void	*buffer;
	char	*line;
	int 	read_len;
	char	read_again;

	line = NULL;
	if (fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (NULL);
	f_clean(BUFFER_SIZE, buffer);
	read_again = BOOL_YES;
	while (read_again == BOOL_YES)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		read_again = f_analyze_read(read_len, (char *)buffer, &line);
	}
	return (line);
}