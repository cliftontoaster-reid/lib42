/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:20:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:20:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_clone, null_src_returns_null) {
  cr_assert_null(string_clone(NULL));
}

Test(string_clone, returns_equal_but_distinct_copy) {
  t_string* a = string_from("hello");
  t_string* b = string_clone(a);
  cr_assert_not_null(b);
  cr_assert_eq(a->size, b->size);
  cr_assert_str_eq(string_cstr(a), string_cstr(b));
  cr_assert_neq(a, b);
  cr_assert_neq(a->data, b->data);
  string_free(a);
  string_free(b);
}
