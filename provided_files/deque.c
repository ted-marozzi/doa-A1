/* * * * * * *
 * Deque module (i.e., double ended queue) for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

// You must not change any of the code already provided in this file, such as
// type definitions, constants or functions.
//
// You may, however, add additional functions and/or types which you may need
// while implementing your algorithms and data structures.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "deque.h"
#include "util.h"

// Create a new empty Deque and return a pointer to it
Deque *new_deque() {
	Deque *deque = malloc(sizeof(*deque));
	assert(deque);

	deque->top = NULL;
	deque->bottom = NULL;
	deque->size = 0;

	return deque;
}

// Free the memory associated with a Deque
void free_deque(Deque *deque) {
  // Remove (and thus free) all of the nodes in the Deque.
  while (deque->size > 0) {
    deque_remove(deque);
  }

	// Free the deque struct itself
	free(deque);
}

// Create a new Node with a given piece of data
Node* new_node(Data data) {
  Node *node = malloc(sizeof(*node));
  assert(node);

  node->next = NULL;
  node->prev = NULL;
  node->data = data;

  return node;
}

// Free the memory associated with a Node
void free_node(Node *node) {
  free(node);
}

// Add an element to the top of a Deque
void deque_push(Deque *deque, Data data) {
  Node *new = new_node(data);

  if (deque->size > 0) {
    new->next = deque->top;
    deque->top->prev = new;
  } else {
    // If the Deque was initially empty then new is both the top and bottom
    deque->bottom = new;
  }

  deque->top = new;
  deque->size++;
}

// Add an element to the bottom of a Deque
void deque_insert(Deque *deque, Data data) {
  Node *new = new_node(data);

  if (deque->size > 0) {
    new->prev = deque->bottom;
    deque->bottom->next = new;
  } else {
    // If the Deque was initially empty then new is both the top and bottom
    deque->top = new;
  }

  deque->bottom = new;
  deque->size++;
}

// Remove and return the top element from a Deque
Data deque_pop(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't pop from empty Deque");
  }

  Data data = deque->top->data;
  Node *old_top = deque->top;

  if (deque->size == 1) {
    deque->top = NULL;
    deque->bottom = NULL;
  } else {
    deque->top = old_top->next;
    deque->top->prev = NULL;
  }

  deque->size--;

  free(old_top);

  return data;
}



// Remove and return the bottom element from a Deque
Data deque_remove(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't remove from empty Deque");
  }

  Data data = deque->bottom->data;
  Node *old_bottom = deque->bottom;

  if (deque->size == 1) {
    deque->top = NULL;
    deque->bottom = NULL;
  } else {
    deque->bottom = old_bottom->prev;
    deque->bottom->next = NULL;
  }

  deque->size--;

  free(old_bottom);

  return data;
}

// Return the number of elements in a Deque
int deque_size(Deque *deque) {
  return deque->size;
}

// Print the Deque on its own line with the following format:
//   [x_1, x_2, ..., x_n]
//     ^              ^
//    top           bottom
void print_deque(Deque *deque) {
  Node *current = deque->top;
  int i = 0;

  printf("[");

  while (current) {
    printf("%d", current->data);
    // Print a comma unless we just printed the final element
    if (i < deque->size - 1) {
      printf(", ");
    }
    current = current->next;
    i++;
  }

  printf("]\n");
}

// Reverse the Deque using an iterative approach
void iterative_reverse(Deque *deque) {
  // You should remove this line and replace it with your own code:
  //exit_with_error("iterative_reverse not implemented");
  
  Deque *tmp_deque = new_deque();

  while(deque->size > 0)
  {
    deque_push(tmp_deque, deque_pop(deque));
  }

  while(tmp_deque->size > 0)
  {
    deque_insert(deque, deque_pop(tmp_deque));
  }
  free_deque(tmp_deque);
}

// Reverse the Deque using a recursive approach
void recursive_reverse(Deque *deque) {
  // You should remove this line and replace it with your own code:
  Deque *tmp_deque = new_deque();
  recursive_push(deque, tmp_deque);
  free_deque(tmp_deque);

}

// Split the Deque given a critical value k, such that the Deque contains
// all elements greater than equal to k above (i.e., closer to the top)
// the elements less than k.
//
// Within the two parts of the array (>= k and < k) the elements should
// be in their original order.
//
// This function must run in linear time.
void split_deque(Deque *deque, int k) {
  // You should remove this line and replace it with your own code:
  Deque *greater = new_deque(), *less = new_deque();
  int i, len_deq =  deque->size;

  for(i=0; i < len_deq; i++)
  {
    if(deque_top(deque) >= k)
    {
      deque_insert(greater, deque_pop(deque));
    }
    else if( deque_top(deque) < k)
    {
      deque_insert(less, deque_pop(deque));
    } 
  }
  
  while(less->size > 0)
  {
    deque_insert(greater, deque_pop(less));
  }

  while(greater->size > 0)
  {
    deque_insert(deque, deque_pop(greater));
  }
  free_deque(greater);
  free_deque(less);
}

// TODO: Add any other functions you might need for your Deque module
void recursive_insert(Deque *deque, Deque *tmp_deque)
{
  if(tmp_deque->size == 0)
  {
    return;
  }

  deque_insert(deque, deque_pop(tmp_deque));
  recursive_insert(deque, tmp_deque);

}

void recursive_push(Deque *deque, Deque *tmp_deque)
{
  if(deque->size == 0)
  {
    recursive_insert(deque, tmp_deque);
    return;
  }

  deque_push(tmp_deque, deque_pop(deque));
  recursive_push(deque, tmp_deque);

}

Data deque_top(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't peek top from empty Deque");
  }
  Data data = deque->top->data;

  return data;
}