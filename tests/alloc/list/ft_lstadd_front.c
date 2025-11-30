/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:25:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:25:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "support/list_helpers.h"

Test(ft_lstadd_front, add_to_empty_list_sets_head) {
  t_list* list = NULL;
  t_list* n = make_int_node(1);
  ft_lstadd_front(&list, n);
  cr_assert_eq(list, n);
  cr_assert_null(list->next);
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstadd_front, add_to_existing_list_prepends) {
  t_list* list = NULL;
  ft_lstadd_front(&list, make_int_node(2));
  ft_lstadd_front(&list, make_int_node(1));
  int expected[] = {1, 2};
  cr_assert(assert_list_ints(list, expected, 2));
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstadd_front, null_new_noop) {
  t_list* list = NULL;
  t_list* n = make_int_node(1);
  ft_lstadd_front(&list, n);
  ft_lstadd_front(&list, NULL);
  int expected[] = {1};
  cr_assert(assert_list_ints(list, expected, 1));
  ft_lstclear(&list, free_int_content);
}
