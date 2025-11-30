/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:50:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:50:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "support/list_helpers.h"

Test(ft_lstdelone, del_called_and_frees_content_on_standalone_node) {
  t_list* node = make_int_node(42);
  spy_del_reset();
  ft_lstdelone(node, spy_and_free_del);
  cr_assert_eq(spy_del_count(), 1);
}

Test(ft_lstdelone, del_not_called_when_del_is_null) {
  t_list* node = make_int_node(1);
  spy_del_reset();
  ft_lstdelone(node, NULL);
  cr_assert_eq(spy_del_count(), 0);
}

Test(ft_lstdelone, deletes_middle_node_and_preserves_list) {
  t_list* list = make_int_node(1);
  ft_lstadd_back(&list, make_int_node(2));
  ft_lstadd_back(&list, make_int_node(3));
  t_list* mid = list->next;
  spy_del_reset();
  ft_lstdelone(mid, spy_and_free_del);
  cr_assert_eq(spy_del_count(), 1);
  int expected[] = {1, 3};
  cr_assert(assert_list_ints(list, expected, 2));
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstdelone, deletes_middle_node_without_del) {
  t_list* list = make_int_node(1);
  ft_lstadd_back(&list, make_int_node(2));
  ft_lstadd_back(&list, make_int_node(3));
  t_list* mid = list->next;
  spy_del_reset();
  ft_lstdelone(mid, NULL);
  cr_assert_eq(spy_del_count(), 0);
  int expected[] = {1, 3};
  cr_assert(assert_list_ints(list, expected, 2));
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstdelone, deletes_head_and_moves_content) {
  t_list* list = make_int_node(1);
  ft_lstadd_back(&list, make_int_node(2));
  ft_lstadd_back(&list, make_int_node(3));
  spy_del_reset();
  ft_lstdelone(list, spy_and_free_del);
  cr_assert_eq(spy_del_count(), 1);
  int expected[] = {2, 3};
  cr_assert(assert_list_ints(list, expected, 2));
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstdelone, deletes_head_without_del) {
  t_list* list = make_int_node(1);
  ft_lstadd_back(&list, make_int_node(2));
  spy_del_reset();
  ft_lstdelone(list, NULL);
  cr_assert_eq(spy_del_count(), 0);
  int expected[] = {2};
  cr_assert(assert_list_ints(list, expected, 1));
  ft_lstclear(&list, free_int_content);
}
