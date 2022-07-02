
#include "../lexer.h"

/* -------------------------------------------------------------------------- */

void	removechar2(char *str, char chartoremmove, int k)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = strlen(str);
	while (i < len)
	{
		if (str[i] == chartoremmove && i == k)
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
}

/* -------------------------------------------------------------------------- */

char	*remove_red_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == IN && str[i + 1] == OUT)
		{
			removechar2(str, str[i + 1], i + 1);
			remove_red_in(str);
		}
		i++;
	}
	return (str);
}