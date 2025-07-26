/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstadd_front.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yuknakas <yuknakas@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/20 09:44:19 by yuknakas		  #+#	#+#			 */
/*   Updated: 2024/11/20 09:44:19 by yuknakas		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../header/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	if (new_node == NULL || lst == NULL)
		return ;
	new_node->next = *lst;
	*lst = new_node;
}
