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

// General system library
#include <stdio.h>

// Include from the header file from the same module
#include "sortedlist.h"

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
SortedList SORTEDLIST_create () {
    SortedList list;

    // Request a Node. This node will be the auxiliary "Phantom" node.
    // The list's head now is the phantom node.
    list.head = (Node*) malloc(sizeof(Node));
    if (NULL != list.head) {
        // There is noone after the phantom node, so next is NULL.
        list.head->next = NULL;
        // We set the previous pointer to the phantom node. Now the point
        //  of view is after the last valid element in the list (there are
        //  no valid elements as the list is empty).
        list.previous = list.head;

        // Everything was fine, so we set the error code to NO_ERROR
        list.error = LIST_NO_ERROR;
    }
    else {
        // Could not get dynamic memory for the phantom node, so we set the
        //  error to malloc error code.
        list.error = LIST_ERROR_MALLOC;
    }

    return list;
}

// Auxiliary function from the LinkedList implementetion that will help us
//  implement the sortedAdd function.
// This function is not described in the .H file, so "no-one knows it exists".
void LINKEDLIST_add (SortedList * list, InfoGPs gps_) {
    // 1- Create a new node.
    Node * new_node = (Node*) malloc(sizeof(Node));
    if (new_node != NULL) {
        // 2- Set the element field in the new node.
        new_node->gpese = gps_;
        // 3- Set the next field in the new node.
        new_node->next = list->previous->next;
        // 4- Link the new node to the list.
        list->previous->next = new_node;
        // 5- Move the previous pointer.
        list->previous = new_node;
    }
}

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
void 	SORTEDLIST_sortedAdd (SortedList * list, InfoGPs gps_, int num_premios) {
    int found = 0, j = 0;
    InfoGPs dummy;

    // We need to know where to place the new element before we can add it
    //  to the list. So the first step would be to go to the first element
    //  and to check all the elements in the list until we find the right
    //  position to place the new element.
    SORTEDLIST_goToHead(list);
    // We will stop the loop when we get to the end of the list (we checked
    //  all the elements and we didn't find any place where to set the new
    //  element), or after we found the place where to set the given element.
    while (!SORTEDLIST_isAtEnd(*list) && !found) {
        dummy = SORTEDLIST_get(list);
        // WE NEED TO CHANGE THIS LINE FROM THE SORTEDLIST THAT WORKED WITH
        //  INTs AS WE NOW NEED TO COMPARE STUDENTS INSTEAD OF INTs.
        if (dummy.i_pos_calend < gps_.i_pos_calend) {
            //if (STUDENT_compareByMark(e, element) < 0) {
            SORTEDLIST_next(list);
        }
        else {
            found = 1;
        }
    }
    // After finding where to place to new element, we reuse the method
    //  defined in the LinkedList to add the new node with the new
    //  element at the designated position.
//    printf("HOLA %s\n", gps_.nom_premio);
    LINKEDLIST_add(list, gps_);
}

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
void 	SORTEDLIST_remove (SortedList * list)  {
    Node * aux = NULL;
    // We cannot remove an element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is noone after PREVIOUS).
    if (SORTEDLIST_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        // We need to set an auxiliary pointer to point the element we want
        //  to remove (the POV).
        aux = list->previous->next;

        // "Remove" the POV. The element after the PREVIOUS node will be the
        //  element after the POV.
        list->previous->next = list->previous->next->next;

        // Free the POV. Remove the element.
        free(aux);

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }
}

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
InfoGPs SORTEDLIST_get (SortedList * list) {
    InfoGPs gpese;

    // We cannot return an element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is noone after PREVIOUS).
    if (SORTEDLIST_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        // The element to return is the element stored in the POV.
        gpese = list->previous->next->gpese;

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }

    return gpese;
}

/****************************************************************************
 *
 * @Objective: Returns true (!0) if this list contains no elements.
 * @Parameters: (in)     list = the sorted list to check
 * @Return: true (!0) if this list contains no elements, false (0) otherwise
 *
 ****************************************************************************/
int 	SORTEDLIST_isEmpty (SortedList list)  {
    // The list will be empty if there are no nodes after the phantom node.
    return NULL == list.head->next;
}

/****************************************************************************
 *
 * @Objective: Moves the point of view to the first element in the list.
 * @Parameters: (in/out) list = the sorted list to move the POV.
 * @Return: ---
 *
 ****************************************************************************/
void 	SORTEDLIST_goToHead (SortedList * list) {
    // To move the POV to the first element in the list, we need to point
    //  whoever is before the first element. That is the phantom node.
    list->previous = list->head;
}

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
void 	SORTEDLIST_next (SortedList * list) {
    // We cannot move to the next element if the POV is not valid.
    // The POV will not be valid when the previous pointer points to the last
    //  node in the list (there is noone after PREVIOUS).
    if (SORTEDLIST_isAtEnd (*list)) {
        list->error = LIST_ERROR_END;
    }
    else {
        // Move the POV to the next element.
        list->previous = list->previous->next;

        // If there are no errors, set error code to NO_ERROR.
        list->error = LIST_NO_ERROR;
    }
}

/****************************************************************************
 *
 * @Objective: Returns true (!0) if the POV is after the last element in the
 *				list.
 * @Parameters: (in)     list = the sorted to check.
 * @Return: true (!0) if the POV is after the last element in the list
 *
 ****************************************************************************/
int 	SORTEDLIST_isAtEnd (SortedList list) {
    // To check if the list is at the end (POV after the last element) we
    //  need to check if there is any Node after the previous pointer.
    return NULL == list.previous->next;
}

/****************************************************************************
 *
 * @Objective: Removes all the elements from the list and frees any dynamic
 *				memory block the list was using. The list must be created
 *				again before usage.
 * @Parameters: (in/out) list = the sorted list to destroy.
 * @Return: ---
 *
 ****************************************************************************/
void 	SORTEDLIST_destroy (SortedList * list) {
    Node * aux;
    // While there are still NODEs in the list.
    while (NULL != list->head) {
        // Take the first node.
        aux = list->head;
        // Now the first node is the next node.
        list->head = list->head->next;
        // Free who was the first node;
        free(aux);
    }
    // Set the pointers to NULL (best practice).
    list->head = NULL;
    list->previous = NULL;
}

/****************************************************************************
 *
 * @Objective: This function returns the error code provided by the last
 *				operation run. The operations that update the error code are:
 *				Create, Add, Remove and Get.
 * @Parameters: (in)     list = the sorted list to check.
 * @Return: an error code from the list of constants defined.
 *
 ****************************************************************************/
int		SORTEDLIST_getErrorCode (SortedList list) {
    return list.error;
}