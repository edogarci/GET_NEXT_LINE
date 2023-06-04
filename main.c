#include "get_next_line.h"

int main() {
	int fd;  // File descriptor
	char *str;

	// Abrir el archivo en modo lectura
	fd = open("C:\\Users\\Edo\\Desktop\\GET_NEXT_LINE\\test_file.txt", O_RDONLY);
	str = get_next_line(fd);
	close(fd);

	return 0;
}
