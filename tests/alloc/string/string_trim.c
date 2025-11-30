/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:30:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:30:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_trim, whitespace_and_custom) {
  t_string* s = string_from("   hello world  \n\t");
  t_string* trimmed = string_trim(s, NULL);
  cr_assert_not_null(trimmed);
  cr_assert_str_eq(string_cstr(trimmed), "hello world");
  string_free(trimmed);

  t_string* p = string_from("///path///");
  t_string* cleaned = string_trim(p, "/");
  cr_assert_not_null(cleaned);
  cr_assert_str_eq(string_cstr(cleaned), "path");
  string_free(cleaned);

  string_free(s);
  string_free(p);
}

Test(string_trim, trims_all_chars_returns_empty) {
  t_string* s = string_from("////");
  t_string* r = string_trim(s, "/");
  cr_assert_not_null(r);
  cr_assert_eq(r->size, 0);
  cr_assert_null(string_cstr(r));
  string_free(s);
  string_free(r);
}
