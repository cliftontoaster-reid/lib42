/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
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

Test(ft_strstr, needle_found_at_start) {
  const char* haystack = "hello world";
  const char* needle = "hello";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack);
}

Test(ft_strstr, needle_found_at_end) {
  const char* haystack = "hello world";
  const char* needle = "world";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack + 6);
}

Test(ft_strstr, needle_found_in_middle) {
  const char* haystack = "hello world";
  const char* needle = "lo wo";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack + 3);
}

Test(ft_strstr, needle_not_found) {
  const char* haystack = "hello world";
  const char* needle = "xyz";
  char* result = ft_strstr(haystack, needle);
  cr_assert_null(result);
}

Test(ft_strstr, empty_needle) {
  const char* haystack = "hello";
  const char* needle = "";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack);
}

Test(ft_strstr, empty_haystack_empty_needle) {
  const char* haystack = "";
  const char* needle = "";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack);
}

Test(ft_strstr, empty_haystack_nonempty_needle) {
  const char* haystack = "";
  const char* needle = "test";
  char* result = ft_strstr(haystack, needle);
  cr_assert_null(result);
}

Test(ft_strstr, needle_equals_haystack) {
  const char* haystack = "test";
  const char* needle = "test";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack);
}

Test(ft_strstr, partial_match_not_complete) {
  const char* haystack = "aaab";
  const char* needle = "aab";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack + 1);
}

Test(ft_strstr, multiple_occurrences_returns_first) {
  const char* haystack = "abc abc abc";
  const char* needle = "abc";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack);
}

Test(ft_strstr, needle_longer_than_haystack) {
  const char* haystack = "hi";
  const char* needle = "hello";
  char* result = ft_strstr(haystack, needle);
  cr_assert_null(result);
}

Test(ft_strstr, comparison_with_libc) {
  const char* haystacks[] = {"hello world", "test", "", "aaaa", "find me"};
  const char* needles[] = {"world", "st", "", "aa", "me", "xyz", "e"};
  for (size_t i = 0; i < sizeof(haystacks) / sizeof(haystacks[0]); i++) {
    for (size_t j = 0; j < sizeof(needles) / sizeof(needles[0]); j++) {
      char* ft_result = ft_strstr(haystacks[i], needles[j]);
      char* libc_result = strstr(haystacks[i], needles[j]);
      cr_assert_eq(ft_result, libc_result);
    }
  }
}

Test(ft_strstr, single_char_needle) {
  const char* haystack = "hello";
  const char* needle = "l";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack + 2);
}

Test(ft_strstr, repeated_pattern) {
  const char* haystack = "ababababab";
  const char* needle = "abab";
  char* result = ft_strstr(haystack, needle);
  cr_assert_eq(result, haystack);
}
