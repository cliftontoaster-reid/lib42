/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:05:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "alloc/list.h"

static int* make_int(int v) {
  int* p = malloc(sizeof(*p));
  if (p) *p = v;
  return p;
}

static void free_int(void* p) { free(p); }

Test(ft_lstadd_front, add_to_empty_list) {
  t_list* head = NULL;
  int* v = make_int(1);
  t_list* n = ft_lstnew(v);

  ft_lstadd_front(&head, n);
  cr_assert_eq(head, n);
  cr_assert_null(head->next);

  /* cleanup */
  ft_lstdelone(n, free_int);
}

Test(ft_lstadd_front, add_to_non_empty_list) {
  t_list* a = ft_lstnew(make_int(10));
  t_list* b = ft_lstnew(make_int(20));

  ft_lstadd_front(&a, b);
  cr_assert_eq(a, b);
  cr_assert_not_null(a->next);
  cr_assert_eq(((int*)a->next->content)[0], 10);

  /* cleanup */
  ft_lstclear(&a, free_int);
}

Test(ft_lstadd_front, new_null_noop) {
  t_list* head = NULL;
  ft_lstadd_front(&head, NULL);
  cr_assert_null(head);
}
