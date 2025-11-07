/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "memory/cstr.h"

Test(ft_strrstr, needle_found_at_end) {
  const char* haystack = "hello world";
  const char* needle = "world";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack + 6);
}

Test(ft_strrstr, needle_found_at_start) {
  const char* haystack = "hello world";
  const char* needle = "hello";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack);
}

Test(ft_strrstr, last_occurrence) {
  const char* haystack = "abc abc abc";
  const char* needle = "abc";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack + 8); /* last occurrence */
}

Test(ft_strrstr, needle_not_found) {
  const char* haystack = "hello world";
  const char* needle = "xyz";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_null(result);
}

Test(ft_strrstr, empty_needle_returns_end) {
  const char* haystack = "hello";
  const char* needle = "";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack + strlen(haystack));
}

Test(ft_strrstr, empty_haystack_empty_needle) {
  const char* haystack = "";
  const char* needle = "";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack);
}

Test(ft_strrstr, empty_haystack_nonempty_needle) {
  const char* haystack = "";
  const char* needle = "test";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_null(result);
}

Test(ft_strrstr, needle_equals_haystack) {
  const char* haystack = "test";
  const char* needle = "test";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack);
}

Test(ft_strrstr, multiple_overlapping_occurrences) {
  const char* haystack = "aaaa";
  const char* needle = "aa";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack + 2); /* last possible match */
}

Test(ft_strrstr, needle_longer_than_haystack) {
  const char* haystack = "hi";
  const char* needle = "hello";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_null(result);
}

Test(ft_strrstr, single_char_needle_last_occurrence) {
  const char* haystack = "hello";
  const char* needle = "l";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack + 3); /* last 'l' */
}

Test(ft_strrstr, two_occurrences) {
  const char* haystack = "find find";
  const char* needle = "find";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack + 5);
}

Test(ft_strrstr, partial_matches_find_last) {
  const char* haystack = "test testing";
  const char* needle = "test";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack + 5);
}

Test(ft_strrstr, repeated_pattern) {
  const char* haystack = "abababab";
  const char* needle = "ab";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack + 6);
}

Test(ft_strrstr, single_occurrence) {
  const char* haystack = "unique occurrence";
  const char* needle = "unique";
  char* result = ft_strrstr(haystack, needle);
  cr_assert_eq(result, haystack);
}
