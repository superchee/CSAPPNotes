/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
    {
        return NULL;
    }
    q->head = NULL;
    q->size = 0;
    q->end = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL)
        return;
    list_ele_t *current = NULL;
    while (q->head != NULL)
    {
        current = q->head;
        q->head = current->next;
        free(current->value);
        free(current);
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    if (s == NULL)
        return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
    {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = malloc(strlen(s)+1);
    if (newh->value == NULL)
    {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    newh->next = q->head;
    q->head = newh;
    q->size = q->size + 1;
    if (q->size == 1)
        q->end = newh;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL)
        return false;

    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newe;

    newe = malloc(sizeof(list_ele_t));
    if (newe == NULL)
    {
        return false;
    }
    newe->value = malloc(strlen(s)+1);
    if (newe->value == NULL)
    {
        free(newe);
        return false;
    }
    strcpy(newe->value, s);
    newe->next = NULL;
    
    if (q->size == 0)
    {
        q->end = newe;
        q->head = newe;

    }
    else
    {
        q->end->next = newe;
        q->end = newe;
    }
    q->size = q->size + 1;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL)
        return false;
    if (sp == NULL)
        return false;

    /* You need to fix up this code. */
    if (q->head == NULL)
    {
        return false;
    }
    list_ele_t *current = q->head;
    q->head = q->head->next;

    if (current->value == NULL)
    {
        free(current);
        return true;
    }

    if (strlen(current->value) < bufsize)
    {
        strcpy(sp,current->value);

    }
    else
    {
        strncpy(sp, current->value, bufsize-1);
        sp[bufsize-1] = '\0';
    }
    free(current->value);
    free(current);

    q->size = q->size - 1;

    if (q->size == 0)
        q->end = NULL;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL)
        return 0;

    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q->head != NULL)
    {
        return q->size;
    }
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL)
        return;

    /* You need to write the code for this function */
    if (q->head == NULL)
    {
        return;
    }
    if (q->size == 1)
        return;

    q->end = q->head;

    list_ele_t *pre = NULL;
    list_ele_t *current = NULL;

    

    while ( q->head != NULL)
    {
        current = q->head;
        q->head = q->head->next;
        current->next = pre;
        pre = current;
    }

    q->head = pre;

    return;

}

