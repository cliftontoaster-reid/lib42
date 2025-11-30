/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tagged.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:15:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:15:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_tagged, null_returns_false) { cr_assert_not(string_tagged(NULL)); }

Test(string_tagged, valid_string_returns_true) {
  t_string* s = string_from("x");
  cr_assert(string_tagged(s));
  string_free(s);
}

Test(string_tagged, cstr_pointer_returns_false) {
  const char* str = "hello";
  cr_assert_not(string_tagged(str));
}

Test(string_tagged, invalid_magic_returns_false) {
  t_string* inv = sh_make_invalid();
  cr_assert_not(string_tagged(inv));
  sh_free_invalid(inv);
}
