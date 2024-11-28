#include "libft.h"

static int	uint_base_len(unsigned int n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(unsigned int n, int base)
{
	char	*str;
	char	*digits;
	int		len;

	digits = "0123456789abcdef";
	len = uint_base_len(n, base);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[--len] = digits[n % base];
		n /= base;
	}
	return (str);
}
