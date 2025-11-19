/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:49:06 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 12:27:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/ctype/ctype.h"

char ft_toupper(char c) {
  unsigned char uc = (unsigned char)c;
  return (char)((uc >= 'a' && uc <= 'z') ? (uc - 32) : uc);
}
