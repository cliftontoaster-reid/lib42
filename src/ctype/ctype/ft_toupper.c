/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:49:06 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 11:07:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype/ctype.h"

char ft_toupper(char c) {
  unsigned char uc = (unsigned char)c;
  return (uc >= 'a' && uc <= 'z') ? (uc - 32) : uc;
}
