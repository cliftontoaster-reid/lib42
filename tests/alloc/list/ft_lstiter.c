/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:05:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 20:05:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "support/list_helpers.h"

void doubler(void* p) {
  if (!p) return;
  *(int*)p *= 2;
}

Test(ft_lstiter, null_list_noop) {
  spy_iter_reset();
  ft_lstiter(NULL, spy_iter_record);
  cr_assert_eq(spy_iter_count(), 0);
}

Test(ft_lstiter, null_function_noop) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  ft_lstiter(list, NULL);
  int expected[] = {1};
  cr_assert(assert_list_ints(list, expected, 1));
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstiter, doubles_all_ints) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  ft_lstadd_back(&list, make_int_node(2));
  ft_lstadd_back(&list, make_int_node(3));
  ft_lstiter(list, doubler);
  int expected[] = {2, 4, 6};
  cr_assert(assert_list_ints(list, expected, 3));
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstiter, spy_function_called_expected_times) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  ft_lstadd_back(&list, make_int_node(2));
  spy_iter_reset();
  ft_lstiter(list, spy_iter_record);
  cr_assert_eq(spy_iter_count(), 2);
  ft_lstclear(&list, free_int_content);
}
