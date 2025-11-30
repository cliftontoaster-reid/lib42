/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_push_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:10:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:10:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_push_char, push_and_grow) {
  t_string* s = string_new();
  for (int i = 0; i < 200; ++i) {
    cr_assert(string_push_char(s, (char)('a' + (i % 26))));
  }
  cr_assert_eq(s->size, 200);
  // spot check
  cr_assert_eq(s->data[0], 'a');
  cr_assert_eq(s->data[199], (char)('a' + (199 % 26)));
  string_free(s);
}
