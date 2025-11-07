/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@invalid>                   +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 10:12:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "memory/cstr.h"

Test(ft_strcmp, equal_strings) { cr_assert_eq(ft_strcmp("hello", "hello"), 0); }

Test(ft_strcmp, empty_strings) { cr_assert_eq(ft_strcmp("", ""), 0); }

Test(ft_strcmp, first_less_than_second) {
  cr_assert_lt(ft_strcmp("abc", "abd"), 0);
}

Test(ft_strcmp, first_greater_than_second) {
  cr_assert_gt(ft_strcmp("abd", "abc"), 0);
}

Test(ft_strcmp, different_lengths_prefix) {
  cr_assert_lt(ft_strcmp("abc", "abcd"), 0);
}

Test(ft_strcmp, different_lengths_prefix_reverse) {
  cr_assert_gt(ft_strcmp("abcd", "abc"), 0);
}

Test(ft_strcmp, first_char_differs) { cr_assert_lt(ft_strcmp("a", "b"), 0); }

Test(ft_strcmp, single_char_equal) { cr_assert_eq(ft_strcmp("x", "x"), 0); }

Test(ft_strcmp, empty_vs_nonempty) { cr_assert_lt(ft_strcmp("", "a"), 0); }

Test(ft_strcmp, nonempty_vs_empty) { cr_assert_gt(ft_strcmp("a", ""), 0); }

Test(ft_strcmp, unsigned_char_comparison) {
  /* test that comparison treats chars as unsigned */
  const char s1[] = {(char)200, '\0'};
  const char s2[] = {(char)100, '\0'};
  int result = ft_strcmp(s1, s2);
  cr_assert_gt(result, 0); /* 200 > 100 when unsigned */
}

Test(ft_strcmp, comparison_with_libc) {
  const char* pairs[][2] = {
      {"hello", "hello"}, {"abc", "def"}, {"test", "testing"},
      {"", ""},           {"a", ""},      {"", "b"},
      {"same", "same"},   {"xyz", "abc"}, {"longer", "long"},
      {"123", "124"},     {"zzz", "aaa"}, {"Test", "test"}};
  for (size_t i = 0; i < sizeof(pairs) / sizeof(pairs[0]); i++) {
    int ft_result = ft_strcmp(pairs[i][0], pairs[i][1]);
    int libc_result = strcmp(pairs[i][0], pairs[i][1]);
    /* ensure sign matches */
    if (ft_result < 0)
      cr_assert_lt(libc_result, 0);
    else if (ft_result > 0)
      cr_assert_gt(libc_result, 0);
    else
      cr_assert_eq(libc_result, 0);
  }
}

Test(ft_strcmp, special_characters) {
  cr_assert_eq(ft_strcmp("\t\n", "\t\n"), 0);
  cr_assert_neq(ft_strcmp("\t", "\n"), 0);
}

Test(ft_strcmp, numbers_as_strings) {
  cr_assert_eq(ft_strcmp("123", "123"), 0);
  cr_assert_lt(ft_strcmp("123", "124"), 0);
  cr_assert_gt(ft_strcmp("200", "199"), 0);
}
