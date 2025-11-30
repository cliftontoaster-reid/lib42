/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:10:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:10:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_free, frees_without_crash) {
  t_string* s = string_from("temp");
  cr_assert_not_null(s);
  string_free(s);
  // No further assertions available besides not crashing
}

Test(string_free, free_null_is_noop) {
  string_free(NULL);  // should not crash
}

Test(string_free, free_invalid_tagged_pointer) {
  t_string* inv = sh_make_invalid();
  cr_assert_not_null(inv);
  // Behavior undefined, but ensure free handles gracefully
  string_free(inv);
  sh_free_invalid(inv);  // free helper also frees if not cleaned up
}
