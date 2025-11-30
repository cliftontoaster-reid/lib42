/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_casecmp.c                                        :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>
#include <strings.h>

#include "42/memory/cstr.h"

Test(ft_casecmp, equal_strings) {
  cr_assert_eq(ft_casecmp("hello", "hello"), 0);
}

Test(ft_casecmp, empty_strings) { cr_assert_eq(ft_casecmp("", ""), 0); }

Test(ft_casecmp, first_less_than_second) {
  cr_assert_lt(ft_casecmp("abc", "abd"), 0);
}

Test(ft_casecmp, first_greater_than_second) {
  cr_assert_gt(ft_casecmp("abd", "abc"), 0);
}

Test(ft_casecmp, different_lengths_prefix) {
  cr_assert_lt(ft_casecmp("abc", "abcd"), 0);
}

Test(ft_casecmp, different_lengths_prefix_reverse) {
  cr_assert_gt(ft_casecmp("abcd", "abc"), 0);
}

Test(ft_casecmp, first_char_differs) { cr_assert_lt(ft_casecmp("a", "b"), 0); }

Test(ft_casecmp, single_char_equal) { cr_assert_eq(ft_casecmp("x", "x"), 0); }

Test(ft_casecmp, empty_vs_nonempty) { cr_assert_lt(ft_casecmp("", "a"), 0); }

Test(ft_casecmp, nonempty_vs_empty) { cr_assert_gt(ft_casecmp("a", ""), 0); }

Test(ft_casecmp, unsigned_char_comparison) {
  /* test that comparison treats chars as unsigned */
  const char s1[] = {(char)200, '\0'};
  const char s2[] = {(char)100, '\0'};
  int result = ft_casecmp(s1, s2);
  cr_assert_gt(
      result, 0,
      "Expected %d to be greater than %d when treated as unsigned chars",
      (char)s1[0], (char)s2[0]); /* 200 > 100 when unsigned */
}

Test(ft_casecmp, comparison_with_libc) {
  const char* pairs[][2] = {
      {"hello", "hello"}, {"abc", "def"}, {"test", "testing"},
      {"", ""},           {"a", ""},      {"", "b"},
      {"same", "same"},   {"xyz", "abc"}, {"longer", "long"},
      {"123", "124"},     {"zzz", "aaa"}, {"Test", "test"}};
  for (size_t i = 0; i < sizeof(pairs) / sizeof(pairs[0]); i++) {
    int ft_result = ft_casecmp(pairs[i][0], pairs[i][1]);
    int libc_result = strcasecmp(pairs[i][0], pairs[i][1]);
    /* ensure sign matches */
    if (ft_result < 0)
      cr_assert_lt(libc_result, 0);
    else if (ft_result > 0)
      cr_assert_gt(libc_result, 0);
    else
      cr_assert_eq(libc_result, 0);
  }
}

Test(ft_casecmp, case_insensitive_single_char) {
  cr_assert_eq(ft_casecmp("A", "a"), 0);
}

Test(ft_casecmp, case_insensitive_equal) {
  cr_assert_eq(ft_casecmp("Hello", "hELLo"), 0);
}

Test(ft_casecmp, case_insensitive_ordering) {
  /* 'a' < 'B' when compared case-insensitively */
  cr_assert_lt(ft_casecmp("apple", "Banana"), 0);
  cr_assert_gt(ft_casecmp("Zoo", "apple"), 0);
}

Test(ft_casecmp, special_characters) {
  cr_assert_eq(ft_casecmp("\t\n", "\t\n"), 0);
  cr_assert_neq(ft_casecmp("\t", "\n"), 0);
}

Test(ft_casecmp, numbers_as_strings) {
  cr_assert_eq(ft_casecmp("123", "123"), 0);
  cr_assert_lt(ft_casecmp("123", "124"), 0);
  cr_assert_gt(ft_casecmp("200", "199"), 0);
}
