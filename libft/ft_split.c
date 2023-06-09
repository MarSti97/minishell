/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:30:55 by mstiedl           #+#    #+#             */
/*   Updated: 2023/05/10 20:49:58 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	make_str(char const *s, char **split, char c)
{
	int	words;
	int	leng;

	words = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
			words++;
		leng = 0;
		while (s[leng] != c && s[leng] != '\0')
			leng++;
		if (split && leng)
			split[words - 1] = ft_substr(s, 0, leng);
		s += leng;
	}
	if (split)
		split[words] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (ft_strlen(s) == 0)
	{
		split = ft_calloc(2, sizeof(char *));
		split[0] = ft_calloc(1, sizeof(char));
		return (split);
	}
	split = (char **) malloc(sizeof(char *) * (make_str(s, NULL, c) + 1));
	if (!split)
		return (0);
	make_str(s, split, c);
	return (split);
}

// static void	free_data(char **data)
// {
// 	int	i;

// 	i = 0;
// 	while (data[i])
// 	{
// 		free (data[i]);
// 		i++;
// 	}
// 	free (data);
// }

// int main()
// {
//     // char const str[] = "\0";
//     char c = ' ';
// 	char **res = ft_split(NULL, c);
// 	// printf("%i\n", counter(str, c));
// 	printf("Result word 1: %s$\n", res[0]);
// 	printf("Result word 2: %s$\n", res[1]);
// 	// printf("Result word 3: %s$\n", res[2]);
// 	// printf("Result word 4: %s$\n", res[3]);
// 	// printf("Result word 5: %s$\n", res[4]);
// 	// printf("Result word NULL: %s$\n", res[5]);
// 	free_data(res);
// }
