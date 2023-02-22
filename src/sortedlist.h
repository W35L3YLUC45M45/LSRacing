/***********************************************************************************************************************
 *
 * @Proposito: Creado unica y exclusivamente con la intencion de ordenar los grandes premios en base a su turno
 *             correspondiente de ejecucion cada vez que se comience una nueva carrera. Es decir, esta estructura de
 *             datos nos ayuda a ir pasando de grande premio en grande premio cada vez que empecemos o acabemos alguna
 *             de las carreras a realizar.
 *
 * @Autor/es: Wesley Lucas Mas (wesley.lucas@students.salle.url.edu)
 *
 * @Fecha creacion: 02/03/2020
 *
 * @Fecha ultima modificacion: 10/05/2020
 *
 **********************************************************************************************************************/

// Define Guard
#ifndef _PJ2_WESLEY_LUCAS_SORTEDLIST_H_
#define _PJ2_WESLEY_LUCAS_SORTEDLIST_H_

// Libraries
#include <stdlib.h>
#include "estructuras.h"

// Constants to manage the list's error codes.
#define LIST_NO_ERROR 0
#define LIST_ERROR_FULL 1		// Error, the list is full.
#define LIST_ERROR_EMPTY 2		// Error, the list is empty.
#define LIST_ERROR_MALLOC 3		// Error, a malloc failed.
#define LIST_ERROR_END 4		// Error, the POV is at the end.

// Data types
typedef InfoGPs GPese;

/*
 * Node is a recursive structure that will contain each one of the elements.
 * A node has two main fields, the element to store and a pointer to the next
 *  node in the Linear Data Structure.
 * The structure is recursively defined (a Node has a pointer to another node),
 *  so we need to define a new type (typedef) from a structure (struct _Node).
 */
typedef struct _Node {
    GPese gpese; // = Element element
    struct _Node * next;
} Node;

/*
 * A sorted list is a linear data structure, in which the elements are not
 *  stored at contiguous memory locations. The elements in a sorted list
 *  are stored inside Nodes that are sorted using pointers.
 *
 *  +---+----+     +---+----+     +----+----+
 *  | 1 |  o-|---> | 2 |  o-|---> | 3  |NULL|
 *  +---+----+     +---+----+     +----+----+
 *
 * This implementation of the sorted list will be using an auxiliary Node
 *  we call the "phantom node". This auxiliary node will help us with the
 *  different operations from the list. It solves the problem of the list
 *  being empty (empty == no nodes) and let us assume that we will always
 *  have one node in the list.
 *
 * Example of an empty list:
 *
 *               Phantom node
 *       +---+   +---+----+
 *  head | o-|-->|   |NULL|
 *       +---+   +---+----+
 *
 * The sorted list will have a "Point of View" (POV). This point of view is the
 *  element (Node) we are visiting at the moment from the list. Whenever
 *  we decide to add, remove or get an element, we will work from the point
 *  of view. This point of view is represented by the "previous" pointer in
 *  the SortedList type. This previous pointer will always point to "the
 *  element before the point of view". That is why is called previous. We need
 *  to point to the element before the point of view to be able to add new
 *  elements before the first element.
 *
 *        +---+
 *   head | o-|---------
 *        +---+         |
 *   prev | o-|---------|-----------
 *        +---+         |           |
 *                      v           v          Point of View
 *                    +---+---+   +---+---+     +---+---+     +---+----+
 *                    |   | o-|-->| 1 | o-|---> | 2 | o-|---> | 3 |NULL|
 *                    +---+---+   +---+---+     +---+---+     +---+----+
 *
 */
typedef struct {
    int error;			// Error code to keep track of failing operations;
    Node * head;	 	// Head/First element or Phantom node;
    Node * previous; 	// Previous node before the point of view;
} SortedList;


// Procedures & Functions
/****************************************************************************
 *
 * @Objective: Creates an empty sorted list.
 *			   If the list fails to create the phantom node, it will set
 *				the error code to LIST_ERROR_MALLOC.
 *
 *        +---+
 *   head | o-|---------
 *        +---+         |
 *   prev | o-|---------|--
 *        +---+         | |
 *                      v v          Point of View (After the last element)
 *                    +---+----+
 *                    |   |NULL|
 *                    +---+----+
 *
 * @Parameters: ---
 * @Return: An empty sorted list
 *
 ****************************************************************************/
SortedList SORTEDLIST_create ();

/****************************************************************************
 *
 * @Objective: Inserts the specified element in this list to the position
 *			    defined by the sorting algorithm. Shifts the point of view
 *				element (if any) and any subsequent elements to the right.
 *			   If the list fails to create the new node to store the element,
 *				it will set	the error code to LIST_ERROR_MALLOC.
 *
 * @Parameters: (in/out) list    = the sorted list where to add the new element
 *				(in)     element = the element to add to the list
 * @Return: ---
 *
 ****************************************************************************/
void 	SORTEDLIST_sortedAdd (SortedList * list, InfoGPs gps_, int num_premios);

/****************************************************************************
 *
 * @Objective: Removes the element currently at the point of view in this
 *				list. Shifts any subsequent elements to the left.
 *			   This operation will fail if the POV is after the last valid
 *				element of the list. That will also happen for an empty list.
 *				In that situation, this operation will set the error code to
 *				LIST_ERROR_END.
  *
 *        +---+
 *   head | o-|---------                        aux (free aux!)
 *        +---+         |                        |
 *   prev | o-|---------|-----------             |
 *        +---+         |           |            |
 *                      v           v          	 v  POV         NEW POV
 *                    +---+---+   +---+---+     +---+---+     +---+----+
 *                    |   | o-|-->| 1 | o-|--X->| 2 | o-|---->| 3 |NULL|
 *                    +---+---+   +---+---+ |   +---+---+     +---+----+
 *										    |                   ^
 *										    |                   |
 *										     -------------------
 *
 * @Parameters: (in/out) list = the sorted list where to remove the element
 * @Return: ---
 *
 ****************************************************************************/
void 	SORTEDLIST_remove (SortedList * list);

/****************************************************************************
 *
 * @Objective: Returns the element currently at the point of view in this list.
 *			   This operation will fail if the POV is after the last valid
 *				element of the list. That will also happen for an empty list.
 *				In that situation, this operation will set the error code to
 *				LIST_ERROR_END.
 * @Parameters: (in/out) list = the sorted list where to get the element.
 *								in/out because we need to set the error code.
 * @Return: ---
 *
 ****************************************************************************/
GPese SORTEDLIST_get (SortedList * list);

/****************************************************************************
 *
 * @Objective: Returns true (!0) if this list contains no elements.
 * @Parameters: (in)     list = the sorted list to check
 * @Return: true (!0) if this list contains no elements, false (0) otherwise
 *
 ****************************************************************************/
int 	SORTEDLIST_isEmpty (SortedList list);

/****************************************************************************
 *
 * @Objective: Moves the point of view to the first element in the list.
 * @Parameters: (in/out) list = the sorted list to move the POV.
 * @Return: ---
 *
 ****************************************************************************/
void 	SORTEDLIST_goToHead (SortedList * list);

/****************************************************************************
 *
 * @Objective: Moves the point of view to the next element in the list.
 *				If the POV is after the last element in the list (or when
 *				the list is empty), this function will set the list's error
 *				to LIST_ERROR_END.
 * @Parameters: (in/out) list = the sorted list to move the POV.
 * @Return: ---
 *
 ****************************************************************************/
void 	SORTEDLIST_next (SortedList * list);

/****************************************************************************
 *
 * @Objective: Returns true (!0) if the POV is after the last element in the
 *				list.
 * @Parameters: (in)     list = the sorted to check.
 * @Return: true (!0) if the POV is after the last element in the list
 *
 ****************************************************************************/
int 	SORTEDLIST_isAtEnd (SortedList list);

/****************************************************************************
 *
 * @Objective: Removes all the elements from the list and frees any dynamic
 *				memory block the list was using. The list must be created
 *				again before usage.
 * @Parameters: (in/out) list = the sorted list to destroy.
 * @Return: ---
 *
 ****************************************************************************/
void 	SORTEDLIST_destroy (SortedList * list);

/****************************************************************************
 *
 * @Objective: This function returns the error code provided by the last
 *				operation run. The operations that update the error code are:
 *				Create, Add, Remove and Get.
 * @Parameters: (in)     list = the sorted list to check.
 * @Return: an error code from the list of constants defined.
 *
 ****************************************************************************/
int		SORTEDLIST_getErrorCode (SortedList list);

#endif
