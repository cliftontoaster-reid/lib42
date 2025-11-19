/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:10:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "42/alloc/list.h"

static int* make_int(int v) {
  int* p = malloc(sizeof(*p));
  if (p) *p = v;
  return p;
}

static void free_int(void* p) { free(p); }

Test(ft_lstadd_back, append_to_empty) {
  t_list* head = NULL;
  t_list* n = ft_lstnew(make_int(5));

  ft_lstadd_back(&head, n);
  cr_assert_eq(head, n);
  cr_assert_null(head->next);

  ft_lstdelone(n, free_int);
}

Test(ft_lstadd_back, append_to_non_empty) {
  t_list* head = ft_lstnew(make_int(1));
  t_list* n1 = ft_lstnew(make_int(2));
  t_list* n2 = ft_lstnew(make_int(3));

  ft_lstadd_back(&head, n1);
  ft_lstadd_back(&head, n2);

  t_list* last = head;
  while (last->next) last = last->next;
  cr_assert_eq(last, n2);

  ft_lstclear(&head, free_int);
}

Test(ft_lstadd_back, new_null_noop) {
  t_list* head = ft_lstnew(make_int(7));
  ft_lstadd_back(&head, NULL);
  cr_assert_not_null(head);
  ft_lstclear(&head, free_int);
}
