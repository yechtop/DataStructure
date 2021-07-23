#include <iostream>

//边表结点
typedef struct ArcNode {
    //该弧锁所指向的顶点的位置
    int adjVex;
    //下一条弧的指针
    ArcNode *next;
    //网的边权值
    int value;
} ArcNode;
//顶点表结点
typedef struct VNode {
    char data;
    ArcNode *first;
} VNode, AdjList[100];
//图
typedef struct {
    //邻接表
    AdjList vertices;
    // 顶点信息
    int vexNum;
    // 边信息
    int arcNum;
} ALGraph;

int main() {

}