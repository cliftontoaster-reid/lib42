/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:20:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:20:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_append_cstr, basic_append) {
  t_string* s = string_from("hello");
  cr_assert(string_append_cstr(s, " world"));
  cr_assert_str_eq(string_cstr(s), "hello world");
  string_free(s);
}

Test(string_append_cstr, null_returns_true_noop) {
  t_string* s = string_from("a");
  cr_assert(string_append_cstr(s, NULL));
  cr_assert_str_eq(string_cstr(s), "a");
  string_free(s);
}

Test(string_append, raw_cstr_detects_and_appends) {
  t_string* a = string_from("foo");
  t_string* b = string_from("bar");
  cr_assert(string_append(a, b));
  cr_assert_str_eq(string_cstr(a), "foobar");
  // self-append
  cr_assert(string_append(a, a));
  cr_assert_str_eq(string_cstr(a), "foobarfoobar");
  string_free(a);
  string_free(b);
}

Test(string_append, null_src_returns_false) {
  t_string* s = string_from("x");
  cr_assert_not(string_append(s, NULL));
  string_free(s);
}

Test(string_append, append_cstr_from_non_tagged_pointer) {
  t_string* s = string_from("alpha");
  const char* t = "beta";
  // string_append will attempt to detect tagged; since t is not tagged, it
  // should append as cstr
  cr_assert(string_append(s, t));
  cr_assert_str_eq(string_cstr(s), "alphabeta");
  string_free(s);
}
