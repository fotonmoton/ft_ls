#include "libft.h"

int		ft_num_len(long num)
{
	int	len;

	len = 1;
	if (num > 9)
		while (num)
		{
			num /= 10;
			if (num)
				len++;
		}
	return (len);
}