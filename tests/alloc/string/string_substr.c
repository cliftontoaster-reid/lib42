/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:40:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:40:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_substr, basic_and_truncate) {
  t_string* s = string_from("hello world");
  t_string* sub = string_substr(s, 6, 5);
  cr_assert_not_null(sub);
  cr_assert_str_eq(string_cstr(sub), "world");
  string_free(sub);

  // truncate past end
  t_string* sub2 = string_substr(s, 6, 99);
  cr_assert_not_null(sub2);
  cr_assert_str_eq(string_cstr(sub2), "world");
  string_free(sub2);

  string_free(s);
}

Test(string_substr, pos_equal_size_returns_null) {
  t_string* s = string_from("abc");
  cr_assert_null(string_substr(s, 3, 1));
  string_free(s);
}

Test(string_substr, zero_len_returns_empty) {
  t_string* s = string_from("abcd");
  t_string* sub = string_substr(s, 2, 0);
  cr_assert_not_null(sub);
  cr_assert_eq(sub->size, 0);
  cr_assert_null(string_cstr(sub));
  string_free(s);
  string_free(sub);
}
