#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node_t{
    int val;
    struct node_t* next;
} *Node;

Node createList(int val){
    Node list = malloc(sizeof(struct node_t));
    list->next = NULL;
    list->val = val;
    return list;
}

void append(Node list, int val){
    Node temp = list;
    while (temp->next){
        temp = temp->next;
    }
    temp->next = malloc(sizeof(struct node_t));
    temp->next->val = val;
    temp->next->next = NULL;
}

bool isListSorted(Node list){
    if (!list){
        return true;
    }

    int current = list->val;
    Node temporary = list->next;

    while (temporary){
        if (temporary->val < current){
            return false;
        }
    }
    return true;
}

void printList(Node list){
    Node temp = list;
    while (temp->next){
        printf("%d->", temp->val);
        temp = temp->next;
    }
    printf("%d->NULL\n", temp->val);
}

Node mergeSortedLists(Node list1, Node list2){
    if (!list1 || !list2){
        return NULL;
    }
    if (!isListSorted(list1) || !isListSorted(list2)){
        return NULL;
    }

    Node head = (list1->val < list2->val) ? list1 : list2;
    Node other = (head == list1) ? list2 : list1;
    Node currentHead = head;

    while (other->next || currentHead->next){
        if (other->val < currentHead->next->val){
            Node temporary = currentHead->next;
            currentHead->next = other;
            other = temporary;
        }
        currentHead = currentHead->next;
    }
    
    currentHead->next = other;
    return head;
}

int main(){
    Node head = createList(1);
    append(head, 2);
    append(head, 4);
    append(head, 8);


    Node head2 = createList(1);
    append(head2, 3);
    append(head2, 5);
    append(head2, 7);

    printList(head);
    printList(head2);
    Node merge = mergeSortedLists(head, head2);
    printList(merge);
    // free(merge);
}