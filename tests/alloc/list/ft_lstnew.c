/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:20:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:20:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "support/list_helpers.h"

Test(ft_lstnew, creates_node_with_content_and_null_next) {
  int* n = make_int_content(42);
  t_list* node = ft_lstnew(n);
  cr_assert_not_null(node);
  cr_assert_eq(node->content, n);
  cr_assert_null(node->next);
  /* cleanup */
  ft_lstdelone(node, free_int_content);
}

Test(ft_lstnew, creates_node_with_null_content) {
  t_list* node = ft_lstnew(NULL);
  cr_assert_not_null(node);
  cr_assert_null(node->content);
  cr_assert_null(node->next);
  ft_lstdelone(node, NULL);
}
