#include <iostream>

struct LinkList {
    LinkList *next;
    LinkList *prev;
    int value;
};

LinkList* get_pre_node(LinkList & first, int index){
    LinkList* p = &first;
    int i = 0;
    //循环 i 次，获取第 i 个节点的前驱节点
    while (i++ != index){
        p = p->next;
    }
    return p;
}

LinkList* get_node(LinkList & first, int index){
    return get_pre_node(first, index)->next;
}

void first_insert(LinkList &first, int values[]) {
    for (int i = 0; values[i] != -1; ++i) {
        LinkList *l = (LinkList *) malloc(sizeof(LinkList));
        l->value = values[i];
        l->next = first.next;
        first.next = l;
    }
}

void end_insert(LinkList &first, int values[]) {
    LinkList *f = &first;
    while (f->next != nullptr) {
        f = f->next;
    }
    for (int i = 0; values[i] != -1; ++i) {
        LinkList *l = new LinkList();
        l->value = values[i];
        f->next = l;
        f = f->next;
    }
}

// getStrIndex 以 0 开始
void insert_link(LinkList &first, int index, int insertValue){
    LinkList *p = get_pre_node(first, index);
    LinkList *insertNode = (LinkList *) malloc(sizeof(LinkList));
    insertNode->value = insertValue;
    insertNode->next = p->next;
    p->next = insertNode;
}

void delete_link(LinkList &first, int index){
    LinkList *p = get_pre_node(first, index);
    LinkList *q = p->next;
    p->next = q->next;
    p->next->prev = p;
    free(q);
}

void print_link(LinkList *l) {
    while (l->next != nullptr) {
        std::cout << (l = l->next)->value << "->";
    }
    std::cout << "null" << std::endl;
}

int main() {
    LinkList *pList = new LinkList();
    int *values = new int[4]{1, 2, 4, -1};
    first_insert(*pList, values);
    print_link(pList);
    pList = new LinkList();
    end_insert(*pList, values);
    print_link(pList);
    insert_link(*pList, 2,3);
    insert_link(*pList, 0,0);
    insert_link(*pList, 5,5);
    delete_link(*pList, 3);
    print_link(pList);
    return 0;
}
