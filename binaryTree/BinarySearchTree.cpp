#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Tree {
    int value;
    Tree *left;
    Tree *right;

    Tree(int value, Tree *left, Tree *right) : value(value), left(left), right(right) {
        this->value = value;
        this->left = left;
        this->right = right;
    }
};

void visitP(const Tree *p);

Tree *getPrev(Tree *tree);

Tree *getLast(Tree *tree);

Tree *getLast(Tree *tree) {
    if (tree->right != nullptr) {
        if (tree->right->left == nullptr)
            return tree->right;
        else {
            tree = tree->right;
            while (tree->left != nullptr) {
                tree = tree->left;
            }
            return tree;
        }
    } else {
        return nullptr;
    }
}

Tree *getPrev(Tree *tree) {
    if (tree->left != nullptr) {
        if (tree->left->right == nullptr)
            return tree->left;
        else {
            tree = tree->left;
            while (tree->right != nullptr) {
                tree = tree->right;
            }
            return tree;
        }
    } else {
        return nullptr;
    }
}

void preOrder(Tree *tree) {
    Tree *trees[100];
    int n = 0;
    if (tree != nullptr) {
        trees[n++] = tree;
        while (n > 0) {
            Tree *p = trees[--n];
            visitP(p);
            if (p->right != nullptr) {
                trees[n++] = p->right;
            }
            if (p->left != nullptr) {
                trees[n++] = p->left;
            }
        }
    }
}


void inOrder(Tree *tree) {
    Tree *trees[100];
    int n = 0;
    if (tree != nullptr) {
        Tree *p = tree;
        while (p != nullptr || n > 0) {
            if (p != nullptr) {
                trees[n++] = p;
                p = p->left;
            } else {
                p = trees[--n];
                visitP(p);
                p = p->right;
            }
        }
    }
}

void postOrder(Tree *tree) {
    Tree *trees[100];
    int n = 0;
    Tree *cur = tree;
    Tree *prev = nullptr;
    while (n > 0 || cur != nullptr) {
        while (cur != nullptr) {
            trees[n++] = cur;
            cur = cur->left;
        }
        if (n > 0) {
            // 此时已经遍历完了所有的左结点
            cur = trees[n - 1];
            // 如果右结点为 null，或者右结点刚刚访问过了才能访问当前结点
            if (cur->right == nullptr || prev == cur->right) {
                // 出栈
                n--;
                // 当前结点并访问
                visitP(prev = cur);
                //为了防止继续访问当前结点，需要将 cur 设为 null，下次遍历就直接访问栈顶元素了
                cur = nullptr;
            } else {//不然的话，就需要继续遍历右结点了
                cur = cur->right;
            }
        }
    }
}

void postOrderPro(Tree *tree) {
    Tree *trees[100];
    int n = 0;
    Tree *prev = nullptr;
    trees[n++] = tree;
    while (n > 0) {
        Tree *cur = trees[n - 1];
        Tree *cRight = cur->right;
        Tree *cLeft = cur->left;
        if (cLeft == nullptr) {
            // 左 NULL，右不 NULL，需要判断右边是不是前一个处理的结点
            if (cRight != nullptr) {
                // 说明左右都处理完了，就可以处理当前结点了
                if (prev == cRight) {
                    visitP(trees[--n]);
                    prev = cur;
                } else {//说明右边还没处理，直接把右结点入栈即可
                    trees[n++] = cRight;
                }
            } else {// 左 NULL，右 NULL，这种情况直接处理当前结点就好了
                visitP(trees[--n]);
                prev = cur;
            }
        } else {
            // 左不 NULL，右不 NULL，如果右边是上一个处理过的，则直接处理当前结点，不然则优先处理左边
            if (cRight != nullptr) {
                if (cRight == prev) {
                    visitP(trees[--n]);
                    prev = cur;
                } else {
                    // 如果左边是上一个处理过的，则直接将右边入栈就好
                    if (cLeft == prev) {
                        trees[n++] = cRight;
                    } else {//说明左边还没来得及处理，那就将左边入栈
                        trees[n++] = cLeft;
                    }
                }
            } else {// 右结点如果为 NULL，则不需要考虑右结点入栈的事情
                //如果左结点是上一个处理过的，直接处理当前结点就好
                if (cLeft == prev) {
                    visitP(trees[--n]);
                    prev = cur;
                } else {//说明左边还没来得及处理，那就将左边入栈
                    trees[n++] = cLeft;
                }
            }
        }
    }
}

void levelOrder(Tree *tree) {
    queue<Tree *> queue;
    queue.push(tree);
    while (!queue.empty()) {
        Tree *&front = queue.front();
        queue.pop();
        visitP(front);
        if (front->left != nullptr) {
            queue.push(front->left);
        }
        if (front->right != nullptr) {
            queue.push(front->right);
        }
    }
}


void insert(Tree *&tree, int value) {
    if (tree == nullptr) {
        tree = new Tree(value, nullptr, nullptr);
        return;
    }
    int sourceValue = tree->value;
    if (sourceValue == value) {
        return;
    } else if (sourceValue < value) {
        if (tree->right == nullptr) {
            tree->right = new Tree(value, nullptr, nullptr);
        } else {
            insert(tree->right, value);
        }
    } else if (sourceValue > value) {
        if (tree->left == nullptr) {
            tree->left = new Tree(value, nullptr, nullptr);
        } else {
            insert(tree->left, value);
        }
    }
}

Tree *search(Tree *&tree, int value) {
    return (value == tree->value) ? tree :
           (value > tree->value ?
            search(tree->right, value) : search(tree->left, value));

}

void del(Tree *&tree, int value) {
    if (tree->value == value && tree->left == nullptr && tree->right == nullptr) {
        tree = nullptr;
        return;
    }

    Tree *pre = nullptr;
    Tree *search = tree;
    while (search->value != value) {
        if (value > search->value) {
            pre = search;
            search = search->right;
        } else {
            pre = search;
            search = search->left;
        }
    }
    bool isLeft = false;
    if (search->value < pre->value)
        isLeft = true;

    if (search->left == nullptr) {
        if (search->right == nullptr) {
            if (isLeft) {
                pre->left = nullptr;
            } else {
                pre->right = nullptr;
            }
        } else {
            if (isLeft) {
                pre->left = search->right;
            } else {
                pre->right = search->right;
            }
        }
    } else {
        if (search->right == nullptr) {
            if (isLeft) {
                pre->left = search->left;
            } else {
                pre->right = search->left;
            }
        } else {
            Tree *lastP = getLast(search);
            del(search, lastP->value);
            if (isLeft) {
                pre->left = lastP;
            } else {
                pre->right = lastP;
            }
            lastP->left = search->left;
            lastP->right = search->left;
        }
    }

}


void visitP(const Tree *p) { cout << p->value << " "; }

int main() {
    Tree *p = nullptr;
    insert(p, 6);
    insert(p, 4);
    insert(p, 8);
    insert(p, 2);
    insert(p, 5);
    insert(p, 7);
    insert(p, 9);
//    6 4 2 5 8 7 9
//    2 4 5 6 7 8 9
//    2 5 4 7 9 8 6
    preOrder(p);
    std::cout << std::endl;
    inOrder(p);
    std::cout << std::endl;
    postOrderPro(p);
    std::cout << std::endl;
    levelOrder(p);
    std::cout << std::endl;
}

