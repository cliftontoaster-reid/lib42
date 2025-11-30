/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:07:39 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 15:18:06 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

/**
 * @brief Singly linked list node structure.
 *
 * \ref t_list represents a single node in a singly linked list. Each node
 * contains a pointer to arbitrary content and a pointer to the next node
 * in the list.
 *
 * @warning It is highly discouraged to manipulate the internal pointers
 *          directly. Use the provided list functions to ensure correct
 *          behavior and to avoid memory corruption.
 */
typedef struct s_list {
  /// @publicsection

  /// @brief Pointer to the content stored in the node.
  ///
  /// This pointer is NOT owned by the t_list instance and should be
  /// provided a del function when freeing the list if the content needs to be
  /// freed.
  ///
  /// @warning If a del function is not provided, the content will not be freed
  ///          when the node is deleted, potentially causing memory leaks.
  ///          see \ref ft_lstdelone and \ref ft_lstclear for details.
  ///
  /// @see ft_lstdelone
  /// @see ft_lstclear
  void* content;
  /// @brief Pointer to the next node in the list.
  ///
  /// This pointer is NULL if this node is the last in the list.
  ///
  /// @warning Do not modify this field directly. If a node has this pointer
  ///          changed to a NULL for example, the children nodes will be left
  ///          dangling and inaccessible, causing memory leaks.
  struct s_list* next;
} t_list;

/**
 * @brief Create a new list node.
 * @memberof s_list
 *
 * Allocates a new t_list node and sets its content pointer to @p content.
 * The new node's next pointer is initialized to NULL.
 *
 * @param content Pointer to the data to store in the node. May be NULL.
 *
 * @return A pointer to the newly allocated node on success, or NULL if
 *         allocation fails.
 *
 * @warning The caller takes ownership of the returned node and is
 *          responsible for freeing it with ft_lstdelone() or ft_lstclear().
 *
 * @par Example
 * @code
 * // Create a node holding an integer
 * int* num = malloc(sizeof(int));
 * *num = 42;
 * t_list* node = ft_lstnew(num);
 *
 * // Create a node holding a string literal (not owned)
 * t_list* str_node = ft_lstnew("hello");
 * @endcode
 */
t_list* ft_lstnew(void* content);

/**
 * @brief Insert a node at the beginning of a list.
 * @memberof s_list
 *
 * Adds the node @p new at the start of the list pointed to by @p lst.
 * If @p lst is NULL or *lst is NULL, @p new becomes the first node.
 *
 * @param lst Address of a pointer to the first node of the list.
 *            If NULL, the function does nothing.
 * @param new The node to insert. If NULL, the list is unchanged.
 *
 * @par Example
 * @code
 * t_list* list = NULL;
 *
 * ft_lstadd_front(&list, ft_lstnew("world"));
 * ft_lstadd_front(&list, ft_lstnew("hello"));
 * // list now contains: "hello" -> "world" -> NULL
 * @endcode
 */
void ft_lstadd_front(t_list** lst, t_list* new);

/**
 * @brief Append a node to the end of a list.
 * @memberof s_list
 *
 * Traverses the list pointed to by @p lst and appends the node @p new as the
 * last element. If the list is empty, @p new becomes the first node.
 *
 * @param lst Address of a pointer to the first node of the list.
 *            If NULL, the function does nothing.
 * @param new The node to append. If NULL, the list is left unchanged.
 *
 * @note This operation is O(n) as it must traverse the entire list.
 *
 * @par Example
 * @code
 * t_list* list = NULL;
 *
 * ft_lstadd_back(&list, ft_lstnew("first"));
 * ft_lstadd_back(&list, ft_lstnew("second"));
 * ft_lstadd_back(&list, ft_lstnew("third"));
 * // list: "first" -> "second" -> "third" -> NULL
 * @endcode
 */
void ft_lstadd_back(t_list** lst, t_list* new);

/**
 * @brief Compute the number of nodes in a list.
 * @memberof s_list
 *
 * Iterates through the list starting at @p lst and returns the count.
 *
 * @param lst Pointer to the first node of the list (may be NULL).
 *
 * @return The number of nodes in the list. Returns 0 if @p lst is NULL.
 *
 * @par Example
 * @code
 * t_list* list = ft_lstnew("a");
 * ft_lstadd_back(&list, ft_lstnew("b"));
 * ft_lstadd_back(&list, ft_lstnew("c"));
 *
 * size_t len = ft_lstsize(list);  // len == 3
 * @endcode
 */
size_t ft_lstsize(t_list* lst);

/**
 * @brief Get the last node of a list.
 * @memberof s_list
 *
 * Traverses the list starting at @p lst and returns a pointer to the last
 * node (the node whose next is NULL).
 *
 * @param lst Pointer to the first node of the list (may be NULL).
 *
 * @return Pointer to the last node, or NULL if the list is empty.
 *
 * @par Example
 * @code
 * t_list* list = ft_lstnew("first");
 * ft_lstadd_back(&list, ft_lstnew("last"));
 *
 * t_list* tail = ft_lstlast(list);
 * printf("%s\n", (char*)tail->content);  // prints "last"
 * @endcode
 */
t_list* ft_lstlast(t_list* lst);

/**
 * @brief Delete a single node.
 * @memberof s_list
 *
 * Applies the function @p del to the node's content (if @p del is not NULL)
 * and then frees the node itself. This function only deletes the single node
 * provided.
 *
 * @param lst The node to delete. If NULL, the function does nothing.
 * @param del Function to free the node's content. If NULL, the content is
 *            not freed.
 *
 * @warning This does NOT unlink the node from the list. If you need to remove
 *          a node from the middle of a list, you must update the previous
 *          node's next pointer yourself.
 *
 * @par Example
 * @code
 * // Free a node with dynamically allocated content
 * int* num = malloc(sizeof(int));
 * *num = 42;
 * t_list* node = ft_lstnew(num);
 *
 * ft_lstdelone(node, free);  // frees both num and node
 *
 * // Free a node with static content (don't free content)
 * t_list* static_node = ft_lstnew("literal");
 * ft_lstdelone(static_node, NULL);  // only frees the node
 * @endcode
 */
void ft_lstdelone(t_list* lst, void (*del)(void*));

/**
 * @brief Clear an entire list.
 * @memberof s_list
 *
 * Iterates over the list, applies @p del to each node's content (if @p del
 * is not NULL), frees each node, and finally sets *lst to NULL.
 *
 * @param lst Address of a pointer to the first node. If NULL or *lst is NULL,
 *            the function does nothing.
 * @param del Function to free node content. If NULL, content is not freed.
 *
 * @par Example
 * @code
 * t_list* list = NULL;
 *
 * // Build a list of dynamically allocated integers
 * for (int i = 0; i < 5; i++) {
 *   int* num = malloc(sizeof(int));
 *   *num = i;
 *   ft_lstadd_back(&list, ft_lstnew(num));
 * }
 *
 * // Free everything
 * ft_lstclear(&list, free);
 * // list is now NULL
 * @endcode
 */
void ft_lstclear(t_list** lst, void (*del)(void*));

/**
 * @brief Apply a function to each element of a list.
 * @memberof s_list
 *
 * Iterates through @p lst and calls @p f on the content pointer of each node.
 * This is intended for side-effects (printing, modifying content in-place).
 *
 * @param lst Pointer to the first node of the list. If NULL, does nothing.
 * @param f Function to apply to each node's content. If NULL, does nothing.
 *
 * @par Example
 * @code
 * void print_int(void* content) {
 *   printf("%d ", *(int*)content);
 * }
 *
 * void double_int(void* content) {
 *   *(int*)content *= 2;
 * }
 *
 * // Print all elements
 * ft_lstiter(list, print_int);  // prints: 1 2 3 4 5
 *
 * // Modify all elements in-place
 * ft_lstiter(list, double_int);
 * ft_lstiter(list, print_int);  // prints: 2 4 6 8 10
 * @endcode
 */
void ft_lstiter(t_list* lst, void (*f)(void*));

/**
 * @brief Create a new list by transforming elements of an existing list.
 * @memberof s_list
 *
 * Iterates the list @p lst and applies @p f to each node's content to build
 * a new list. If any allocation fails, @p del is used to free already-created
 * content before returning NULL.
 *
 * @param lst Pointer to the first node of the source list. May be NULL.
 * @param f Function to transform each content. Must not be NULL.
 * @param del Function to free transformed content on error or when freeing
 *            the new list later.
 *
 * @return Pointer to the first node of the new list, or NULL on failure.
 *
 * @warning The caller owns the returned list and must free it with
 *          ft_lstclear() using the same @p del function.
 *
 * @par Example
 * @code
 * void* int_to_string(void* content) {
 *   int num = *(int*)content;
 *   char* str = malloc(16);
 *   snprintf(str, 16, "%d", num);
 *   return str;
 * }
 *
 * // Original list: [1, 2, 3] as integers
 * t_list* strings = ft_lstmap(int_list, int_to_string, free);
 * // New list: ["1", "2", "3"] as strings
 *
 * ft_lstclear(&strings, free);
 * @endcode
 */
t_list* ft_lstmap(t_list* lst, void* (*f)(void*), void (*del)(void*));
