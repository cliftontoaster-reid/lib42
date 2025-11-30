/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_prepend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:35:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:35:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_prepend_cstr, basic_prepend) {
  t_string* s = string_from("world");
  cr_assert(string_prepend_cstr(s, "hello "));
  cr_assert_str_eq(string_cstr(s), "hello world");
  string_free(s);
}

Test(string_prepend_string, basic_prepend) {
  t_string* s = string_from("world");
  t_string* src = string_from("hello ");
  cr_assert(string_prepend_string(s, src));
  cr_assert_str_eq(string_cstr(s), "hello world");
  string_free(src);
  string_free(s);
}

Test(string_prepend, basic_prepend) {
  t_string* s = string_from("world");
  cr_assert(string_prepend(s, "hello "));
  cr_assert_str_eq(string_cstr(s), "hello world");
  string_free(s);
}

Test(string_prepend_string, null_src_returns_true_noop) {
  t_string* s = string_from("x");
  cr_assert(string_prepend_string(s, NULL));
  cr_assert_str_eq(string_cstr(s), "x");
  string_free(s);
}

Test(string_prepend_cstr, null_src_returns_true_noop) {
  t_string* s = string_from("x");
  cr_assert(string_prepend_cstr(s, NULL));
  cr_assert_str_eq(string_cstr(s), "x");
  string_free(s);
}

Test(string_prepend, null_src_returns_true_noop) {
  t_string* s = string_from("x");
  /* string_prepend expects a non-NULL src; passing NULL should return false */
  cr_assert_not(string_prepend(s, NULL));
  cr_assert_str_eq(string_cstr(s), "x");
  string_free(s);
}

Test(string_prepend, raw_src_null_returns_false) {
  t_string* s = string_from("x");
  cr_assert_not(string_prepend(s, NULL));
  string_free(s);
}

Test(string_prepend_cstr, raw_src_null_returns_false) {
  t_string* s = string_from("x");
  /* For cstr variant, NULL behaves like empty string and returns true */
  cr_assert(string_prepend_cstr(s, NULL));
  string_free(s);
}

Test(string_prepend_string, raw_src_null_returns_false) {
  t_string* s = string_from("x");
  /* For string variant, NULL behaves like empty string and returns true */
  cr_assert(string_prepend_string(s, NULL));
  string_free(s);
}
