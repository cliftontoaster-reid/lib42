/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:00:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:00:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_resize, grow_and_fill) {
  t_string* s = string_from("abc");
  cr_assert(string_resize(s, 6, 'x'));
  cr_assert_eq(s->size, 6);
  // cstr returns pointer to buffer; since size > 0 it should be non-NULL
  cr_assert_not_null(string_cstr(s));
  // Check the content
  cr_assert_str_eq(string_cstr(s), "abcxxx");
  string_free(s);
}

Test(string_resize, shrink_truncates) {
  t_string* s = string_from("abcdef");
  cr_assert(string_resize(s, 3, 'x'));
  cr_assert_eq(s->size, 3);
  cr_assert_str_eq(string_cstr(s), "abc");
  string_free(s);
}

Test(string_resize, null_argument_returns_false) {
  cr_assert_not(string_resize(NULL, 4, 'x'));
}

Test(string_resize, to_zero_results_empty) {
  t_string* s = string_from("hello");
  cr_assert(string_resize(s, 0, 'x'));
  cr_assert_eq(s->size, 0);
  cr_assert_null(string_cstr(s));
  string_free(s);
}
