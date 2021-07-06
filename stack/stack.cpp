#include <iostream>
#define MAXSIZE 100
typedef struct {
    int data[200]{};
    // top 指向当前栈的最后一个元素
    int top = -1;
} Stack;

int main(){

}

bool push(Stack &stack, int &value){
    if(stack.top != -1){
        value = stack.data[stack.top--];
        return true;
    }
    return false;
}
bool pop(Stack &stack, int value){
    if(stack.top == MAXSIZE - 1){
        return false;
    }
    stack.data[++stack.top] = value;
    return true;
}