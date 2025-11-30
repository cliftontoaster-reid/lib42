/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:55:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:55:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_cstr, empty_returns_null) {
  t_string* s = string_new();
  cr_assert_null(string_cstr(s));
  string_free(s);
}

Test(string_cstr, non_empty_returns_valid_pointer) {
  t_string* s = string_from("abc");
  cr_assert_not_null(string_cstr(s));
  cr_assert_str_eq(string_cstr(s), "abc");
  string_free(s);
}
