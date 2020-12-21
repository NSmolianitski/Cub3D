#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "cub_image.h"
#include "libft.h"

void	fill_bmp_header(unsigned char *bmp, int width, int height)
{
	int				size;
	int 			y;
	int 			x;
	unsigned char	*colors;
	int 			coords;

	size = width * height * 4;
	ft_strlcpy((char *)bmp, "BM", 3);
	ft_memset(&bmp[2], 54 + size, 1);
	ft_memset(&bmp[6], 0, 1);
	ft_memset(&bmp[8], 0, 1);
	ft_memset(&bmp[10], 54, 1);
	ft_memset(&bmp[14], 40, 1);
	ft_memset(&bmp[18], width, 1);
	ft_memset(&bmp[22], height, 1);
	ft_memset(&bmp[26], 1, 1);
	ft_memset(&bmp[28], 32, 1);
	ft_memset(&bmp[30], 0, 1);
	ft_memset(&bmp[34], size, 1);
	ft_memset(&bmp[38], 0, 1);
	ft_memset(&bmp[42], 0, 1);
	ft_memset(&bmp[46], 0, 1);
	ft_memset(&bmp[50], 0, 1);

	colors = malloc(size);
	y = height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < width)
		{
			coords = (y * width + x) * 4;
			colors[coords + 0] = 255;
			colors[coords + 1] = 255;
			colors[coords + 2] = 192;
			++x;
		}
		--y;
	}

	int fd = open("1.bmp", O_RDWR | O_CREAT, 0755);
	write(fd, bmp, 54);
	write(fd, colors, size);
	free(colors);
	close(fd);
}

void		create_bmp()
{
	int width = 1920;
	int height = 1080;

	unsigned char bmp[54];
	fill_bmp_header(bmp, width, height);
}