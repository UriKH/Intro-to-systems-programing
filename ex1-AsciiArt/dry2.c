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
    Node list1 = createList(2);
    append(list1, 4);
    append(list1, 6);
    append(list1, 8);
    Node list2 = createList(1);
    append(list2, 3);
    append(list2, 5);
    append(list2, 7);
    printList(list1);
    printList(list2);
    printList(mergeSortedLists(list1, list2));

    printf("\n\n");
    Node list3 = createList(2);
    append(list3, 3);
    append(list3, 4);
    append(list3, 7);
    Node list4 = createList(2);
    append(list4, 4);
    append(list4, 7);
    append(list4, 8);
    printList(list3);
    printList(list4);
    printList(mergeSortedLists(list3, list4));

    printf("\n\n");
    Node list5 = createList(1);
    append(list5, 4);
    append(list5, 9);
    Node list6 = createList(2);
    append(list6, 4);
    append(list6, 8);
    printList(list5);
    printList(list6);
    printList(mergeSortedLists(list5, list6));
    return 0;
}