#include <iostream>
#define MAXSIZE 100

typedef struct {
    int data[MAXSIZE]{};
    // rear 代表最后一个元素的尾元素节点
    int front = 0, rear = 0;
} SqQueue;

struct LinkNode{
    int value;
    LinkNode * next;
};

typedef struct {
    // 头结点恒定不变，代表头结点的前一结点
    // 尾结点代表最后一个入队的结点，当 front = rear 时，队为空
    LinkNode *front, *rear;
} LinkQueue;

bool enQueue(LinkQueue &q, int value){
    // 链式队列不会满，所以不用判断，直接插入就绪
    LinkNode *s = new LinkNode();
    s->value = value;
    s->next = nullptr;
    q.rear->next = s;
    q.rear = s;
    return true;
}

bool deQueue(LinkQueue &q, int &value){
    // 首先判断队是否为空
    if(q.front->next == nullptr || q.front == q.rear){
        return false;
    }
    LinkNode *out = q.front->next;
    value = out->value;
    q.front->next = out->next;
    // 注意，虽然是出队，但也可能改变尾节点(出最后一个结点时)
    if(out == q.rear)
        q.rear = q.front;
    free(out);
    return true;
}
bool enQueue(SqQueue &q, int value){
    //首先判断队是否满
    if((q.rear + 1) % MAXSIZE == q.front){
        return false;
    }
    q.data[q.rear] = value;
    q.rear = (q.rear + 1) % MAXSIZE;
    return true;
}

bool deQueue(SqQueue &q, int &value){
    //首先判断队是否空
    if(q.rear == q.front){
        return false;
    }
    value = q.data[q.front];
    q.front = (q.front + 1) % MAXSIZE;
    return true;
}
