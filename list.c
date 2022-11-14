#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node* next;
};

void Push(struct node** head, int newData) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = newData;
    newNode->next = *head; // The '*' to dereferences back to the real head
    *head = newNode; // ditto
}

void Build(struct node **headRef) {
    for (int i = 3; i > 0; i--) {
        Push(headRef, i);
    }
}

void BuildReverse(struct node **headRef) {
    for (int i = 1; i <= 3; i++) {
        Push(headRef, i);
    }
}

void makeList(struct node** headRef, int length) {
    for (int i = length; i >= 1; i--) {
        Push(headRef, i);
    }
}

int length(struct node* head) {
    int l = 0;
    while (head != NULL) {
        l++;
        head = head->next;
    }
    return l;
}

void printList(struct node *head) {
    while (head != NULL) {
        printf("%i->", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int count(struct node* head, int data) {
    int cnt = 0;
    while (head != NULL) {
        if (head->data == data) {
            cnt++;
        }
        head = head->next;
    }
    return cnt;
}

int GetNth(struct node *head, int index) {
    if (index > (length(head)-1) || index < 0) return -1;

    for (int i = 0; i < index; i++) {
        head = head->next;
    }
    return head->data;
}

void DeleteList(struct node** head) {
    struct node *it = *head;
    while (it != NULL) {
        struct node *temp = it;
        it = it->next;
        free(temp);
    }
    *head = NULL;
}

int Pop(struct node** head) {
    struct node* temp = *head;
    *head = (*head)->next;
    int val = temp->data;
    free(temp);
    return val;
}

void InsertNth(struct node** head, int index, int data) {
    if (index > length(*head)) return;
    while (index != 0) {
        head = &(*head)->next;
        index--;
    }
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void SortedInsert(struct node** headRef, struct node* newNode) {
    if ((*headRef)->data > newNode->data) {
        newNode->next = *headRef;
        *headRef = newNode;
        return;
    }
    while ((*headRef)->data < newNode->data) {
        if ((*headRef)->next == NULL) {
            break;
        }
        headRef = &((*headRef)->next);
    }
    newNode->next = (*headRef)->next;
    (*headRef)->next = newNode;
}

bool Sorted(struct node *head) {
    while (head->next != NULL) {
        if (head->data > head->next->data) {
            return false;
        }
        head = head->next;
    }
    return true;
}

void InsertSort(struct node** headRef) {
    struct node* head = *headRef;
    struct node* it = (*headRef)->next;
    int n = length(head);

    while (!Sorted(head)) {
        if (it == NULL) {
            it = head;
        }
        struct node* temp = it->next;
        SortedInsert(&head, it);
        while (it->next->data >= it->data) {
            if (it->next == it) break;
            it = it->next;
        }
        it->next = temp;
        it = it->next;
    }
    *headRef = head;
}

void Append(struct node** aRef, struct node** bRef) {
    if (*bRef == NULL) return;
    if (*aRef == NULL) {
        *aRef = *bRef;
        *bRef = NULL;
    }
    struct node* it = *aRef;
    while (it->next != NULL) {
        it = it->next;
    }
    it->next = *bRef;
    *bRef = NULL;
}

void FrontBackSplit(struct node* source, struct node** frontRef, struct node** backRef) {
    if (source == NULL) return;
    if (source->next == NULL) {
        *frontRef = source;
        return;
    }
    int len = length(source);
    int mid = len / 2;
    if (len % 2 == 0) mid--;
    *frontRef = source;
    for (int i = 0; i < mid; i++) {
        source = source->next;
    }
    *backRef = source->next;
    source->next = NULL;
}

void RemoveDuplicates(struct node* head) {
    if (head == NULL) return;

    while (head->next != NULL) {
        if (head->data == head->next->data) {
            struct node* temp = head->next;
            head->next = head->next->next;
            free(temp);
        }
        head = head->next;
    }
}

void MoveNode(struct node** destRef, struct node** sourceRef) {
    struct node* temp = *sourceRef;
    *sourceRef = (*sourceRef)->next;
    temp->next = (*destRef);
    *destRef = temp;
}

void AlternatingSplit(struct node* source, struct node** aRef, struct node** bRef) {
    while (source != NULL) {
        MoveNode(aRef, &source);
        if (source == NULL) return;
        MoveNode(bRef, &source);
    }
}

struct node* ShuffleMerge(struct node* a, struct node* b) {
    struct node* h = a;
    while (a != NULL && b != NULL) {
        struct node* tempA = a->next;
        struct node* tempB = b->next;
        a->next = b;
        a->next->next = tempA;
        a = tempA;
        b = tempB;    
    }
    return h;
}

struct node* SortedMerge(struct node* a, struct node* b) {
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }
    struct node* h = a;

    while (a != NULL && b != NULL) {
        struct node* prev;
        if (a->next == NULL && a->data <= b->data) {
            a->next = b;
            b = NULL;
        }
        else if (b->next == NULL && a->data >= b->data) {
            MoveNode(&a,&b);
            prev->next = a;
        }
        else if (a->data >= b->data) {
            if (h == a) {
                MoveNode(&h,&b);
                continue;
            }
            else {
                MoveNode(&a,&b);
            }
            prev->next = a;
            prev = a;
            a = a->next;
        }
        else {
            prev = a;
            a = a->next;
        }
    }
    return h;
}

void Sort(struct node** headRef) {
    struct node* it = *headRef;
    struct node* h = *headRef;

    if (it->data > it->next->data) {
        struct node* temp = it->next;
        it->next = it->next->next;
        temp->next = it;
        h = temp;
        it = temp;
    }

    while (!Sorted(h)) {
        if (it->next->next == NULL) {
            it = h;
            struct node* temp = it->next;
            it->next = it->next->next;
            temp->next = it;
            h = temp;
            it = temp;
        }
        if (it->next->data > it->next->next->data) {
            struct node* temp = it->next->next;
            it->next->next = it->next->next->next;
            temp->next = it->next;
            it->next = temp;
        }
        it = it->next;
    }
    *headRef = h;
}

void recSort(struct node** headPtr, struct node* it) {
    // base case
    if (Sorted(*headPtr)) return;

    // rec case
    if ((*headPtr)->data > (*headPtr)->next->data) {
        struct node* temp = (*headPtr)->next;
        (*headPtr)->next = (*headPtr)->next->next;
        temp->next = *headPtr;
        *headPtr = temp;
    }
    if (it->next != NULL) {
        if (it->next->next == NULL) {
            it = *headPtr;
        }
        if (it->next->data > it->next->next->data) {
            struct node* temp = it->next->next;
            it->next->next = it->next->next->next;
            temp->next = it->next;
            it->next = temp;
        }
    }
    recSort(headPtr, it->next);
}

void MergeSort(struct node** headRef) {
    struct node* h = *headRef;
    int mid = (length(*headRef)-1) / 2;
    struct node* head = *headRef;
    while (mid--) {
        head = head->next;
    }
    struct node* l2 = head->next;
    head->next = NULL;
    recSort(&h,h);
    recSort(&l2,l2);
    struct node* res = SortedMerge(h,l2);
    *headRef = res;
}

void Reverse(struct node** headRef) {
    struct node *s = *headRef;
    struct node *it = *headRef;
    struct node *res = NULL;
    while (it != NULL) {
        MoveNode(&res, &it);
        // it = it->next;
    }
    *headRef = res;
}

struct node* SortedIntersect(struct node* a, struct node* b) {
    struct node* h = NULL;
    while (a != NULL && b != NULL) {
        if (a->data == b->data) {
            Push(&h, a->data);
            a = a->next;
            b = b->next;
            continue;
        }
        if (a->data < b->data) {
            a = a->next;
        }
        else if (a->data > b->data) {
            b = b->next;
        }
    }
    Reverse(&h);
    return h;
}

void RecursiveReverse(struct node** headRef, struct node* next) {
    if (next == NULL) {
        return;
    }

    struct node* temp = next->next;
    next->next = *headRef;
    *headRef = next;
    struct node* it = next;
    while (it->next != next) {
        it = it->next;
    }
    it->next = temp;
    RecursiveReverse(headRef, it->next);
}

void CountTest() {
    struct node *head = NULL;
    Build(&head);
    Push(&head, 2);
    Push(&head, 2);
    printList(head);
    int x = count(head, 2);
    printf("%i", x);
}

void GetNthTest() {
    struct node *head = NULL;
    Build(&head);
    printList(head);
    printf("%i", GetNth(head, 1));
}

void DeleteListTest() {
    struct node *head = NULL;
    Build(&head);
    printList(head);
    DeleteList(&head);
}

void PopTest() {
    struct node *head = NULL;
    Build(&head);
    Push(&head, 3);
    printList(head);
    printf("%i\n", Pop(&head));
    printList(head);
    printf("%i\n", Pop(&head));
    printList(head);
}

void InsertNthTest() {
    struct node *head = NULL;
    Build(&head);
    InsertNth(&head,3,13);
    printList(head);
    InsertNth(&head,1,5);
    printList(head);
    DeleteList(&head);
    printList(head);
}

void SortedInsertTest() {
    struct node *head = NULL;
    Build(&head);
    struct node* nodeN = malloc(sizeof(struct node));
    nodeN->data = 3;
    nodeN->next = NULL;
    SortedInsert(&head,nodeN);
    printList(head);
}

void InsertSortTest() {
    struct node *head = NULL;
    BuildReverse(&head);
    Push(&head, 1);
    Push(&head, 2);
    printList(head);
    InsertSort(&head);
    printList(head);
}

void AppendTest() {
    struct node *head = NULL;
    Build(&head);
    struct node *head2 = NULL;
    BuildReverse(&head2);
    Append(&head, &head2);
    printList(head);
    printList(head2);
}

void FrontBackSplitTest() {
    struct node* head = NULL;
    makeList(&head, 5);
    struct node* l1 = NULL;
    struct node* l2 = NULL;
    FrontBackSplit(head, &l1, &l2);
    printList(l1);
    printList(l2);
}

void RemoveDuplicatesTest() {
    struct node* head = NULL;
    Build(&head);
    Push(&head, 1);
    Push(&head->next->next, 2);
    printList(head);
    RemoveDuplicates(head);
    printList(head);
}

void MoveNodeTest() {
    struct node* head = NULL;
    Build(&head);
    struct node* head2 = NULL;
    Build(&head2);
    MoveNode(&head,&head2);
    printList(head);
}

void AlternatingSplitTest() {
    struct node* head = NULL;
    makeList(&head, 5);
    printList(head);
    struct node* l1 = NULL;
    struct node* l2 = NULL;
    AlternatingSplit(head, &l1, &l2);
    printList(l1);
    printList(l2);
}

void ShuffleMergeTest() {
    struct node* l1 = NULL;
    makeList(&l1, 5);
    struct node* l2 = NULL;
    BuildReverse(&l2);
    printf("List1: ");
    printList(l1);
    printf("List2: ");
    printList(l2);
    struct node* head = ShuffleMerge(l1, l2);
    printList(head);
}

void SortedMergeTest() {
    struct node* l1 = NULL;
    Push(&l1, 5);
    Push(&l1, 3);
    Push(&l1, 1);
    struct node* l2 = NULL;
    Push(&l2, 6);
    Push(&l2, 4);
    Push(&l2, 2);
    struct node* head = SortedMerge(l1,l2);
    printList(head);
}

void MergeSortTest() {
    struct node* head = NULL;
    Push(&head, 1);
    Push(&head, 3);
    Push(&head, 5);
    Push(&head, 2);
    Push(&head, 7);
    printList(head);
    MergeSort(&head);
    printList(head);
}

void SortedIntersectTest() {
    struct node* l1 = NULL;
    Push(&l1, 7);
    Push(&l1, 6);
    Push(&l1, 4);
    Push(&l1, 3);
    Push(&l1, 2);
    struct node* l2 = NULL;
    Push(&l2, 6);
    Push(&l2, 5);
    Push(&l2, 4);
    Push(&l2, 2);
    struct node* l3 = SortedIntersect(l1,l2);
    printList(l3);
}

void ReverseTest() {
    struct node* l1 = NULL;
    Push(&l1, 1);
    Push(&l1, 2);
    Push(&l1, 3);
    Push(&l1, 4);
    Push(&l1, 5);
    Reverse(&l1);
    printList(l1);
}

void RecursiveReverseTest() {
    struct node* l1 = NULL;
    Push(&l1, 1);
    Push(&l1, 2);
    Push(&l1, 3);
    Push(&l1, 4);
    Push(&l1, 5);
    printList(l1);
    RecursiveReverse(&l1,l1->next);
    printList(l1);
}

int main(void) {
    
}