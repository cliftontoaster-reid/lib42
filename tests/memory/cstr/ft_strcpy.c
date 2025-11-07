/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
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

Test(ft_strcpy, empty_string) {
  char dest[10];
  const char* src = "";
  char* ret = ft_strcpy(dest, src);
  cr_assert_eq(ret, dest);
  cr_assert_str_eq(dest, src);
}

Test(ft_strcpy, simple_string) {
  char dest[20];
  const char* src = "hello";
  char* ret = ft_strcpy(dest, src);
  cr_assert_eq(ret, dest);
  cr_assert_str_eq(dest, "hello");
}

Test(ft_strcpy, returns_dest_pointer) {
  char dest[10];
  const char* src = "test";
  char* ret = ft_strcpy(dest, src);
  cr_assert_eq(ret, dest);
}

Test(ft_strcpy, single_char) {
  char dest[5];
  const char* src = "a";
  ft_strcpy(dest, src);
  cr_assert_str_eq(dest, "a");
}

Test(ft_strcpy, with_spaces) {
  char dest[20];
  const char* src = "hello world";
  ft_strcpy(dest, src);
  cr_assert_str_eq(dest, "hello world");
}

Test(ft_strcpy, with_special_chars) {
  char dest[30];
  const char* src = "hello\tworld\n!";
  ft_strcpy(dest, src);
  cr_assert_str_eq(dest, src);
}

Test(ft_strcpy, overwrites_dest) {
  char dest[20] = "original";
  const char* src = "new";
  ft_strcpy(dest, src);
  cr_assert_str_eq(dest, "new");
}

Test(ft_strcpy, null_terminator_copied) {
  char dest[10] = "xxxxxxxxx";
  const char* src = "hi";
  ft_strcpy(dest, src);
  cr_assert_eq(dest[0], 'h');
  cr_assert_eq(dest[1], 'i');
  cr_assert_eq(dest[2], '\0');
}

Test(ft_strcpy, long_string) {
  char dest[100];
  const char* src = "This is a longer string with many characters to test";
  ft_strcpy(dest, src);
  cr_assert_str_eq(dest, src);
}

Test(ft_strcpy, comparison_with_libc) {
  char dest1[50];
  char dest2[50];
  const char* src = "test string";
  ft_strcpy(dest1, src);
  strcpy(dest2, src);
  cr_assert_str_eq(dest1, dest2);
}

Test(ft_strcpy, numbers_and_symbols) {
  char dest[30];
  const char* src = "123!@#$%^&*()";
  ft_strcpy(dest, src);
  cr_assert_str_eq(dest, src);
}
