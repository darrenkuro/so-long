/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 23:35:39 by dlu               #+#    #+#             */
/*   Updated: 2023/06/09 10:22:03 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	file_len(const char *filename)
{
	int		fd;
	int		len;
	int		size_read;
	char	buffer[BUFFER_SIZE];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	len = 0;
	while (TRUE)
	{
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (!size_read)
			break ;
		len += size_read;
	}
	close(fd);
	return (len);
}

char	*ft_read_file(const char *filename)
{
	int		fd;
	int		idx;
	char	*ret;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	ret = malloc((file_len(filename) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	idx = 0;
	while (read(fd, buffer, 1))
		ret[idx++] = *buffer;
	ret[idx] = '\0';
	close(fd);
	return (ret);
}
