/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:30:00 by oruban            #+#    #+#             */
/*   Updated: 2024/11/03 17:30:04 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	refacturing after shortening map_rewrite() it was devieded into 5
	functionsthere fore count_tabs() had to be removed file 
	map_rewrite.c into the ceperated file count_tabs.c 
		refactured by roi 1103
 */
int	count_tabs(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == '\t')
			count += 3;
		line++;
	}
	return (count);
}
