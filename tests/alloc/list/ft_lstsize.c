/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:35:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:35:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "support/list_helpers.h"

Test(ft_lstsize, empty_returns_zero) { cr_assert_eq(ft_lstsize(NULL), 0); }

Test(ft_lstsize, single_node_returns_one) {
  t_list* n = make_int_node(1);
  cr_assert_eq(ft_lstsize(n), 1);
  ft_lstclear(&n, free_int_content);
}

Test(ft_lstsize, multiple_nodes_counts_correct) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  ft_lstadd_back(&list, make_int_node(2));
  ft_lstadd_back(&list, make_int_node(3));
  cr_assert_eq(ft_lstsize(list), 3);
  ft_lstclear(&list, free_int_content);
}
