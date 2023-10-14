#include <iostream>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* 在链表的节点 n0 之后插入节点 P */
void insert(ListNode* n0, ListNode* ptr){
    ListNode* n1 = n0->next;
    ptr->next = n1;
    n0->next = ptr;
}

/* 删除链表的节点 n0 之后的首个节点 */
void remove(ListNode* n0){
    if(n0->next == nullptr){
        return;
    }
    // 找到n0的下个元素
    ListNode* ptr = n0->next;

    ListNode* n1 = ptr->next;
    n0->next = n1;
    // 释放内存
    delete ptr;
}

/* 访问链表中索引为 index 的节点 */
ListNode* printf(ListNode* head, int index){
    for(int i = 0; i < index; i++){
        if (head == nullptr)
        {
            return nullptr;
        }
        head = head->next;
    }
    return head;
}

/* 在链表中查找值为 target 的首个节点 */
int find(ListNode* head, int target){
    int index = 0;
    while (head->val != target)
    {
        if(head->next == nullptr){
            return -1;
        }
        head = head->next;
        index++;
    }
    return index;
}

int main(){
    ListNode* n0 = new ListNode(1);
    ListNode* n1 = new ListNode(3);
    ListNode* n2 = new ListNode(5);
    ListNode* n3 = new ListNode(7);
    n0->next = n1;
    n1->next = n2;
    n2->next = n3;
    int index = find(n0, 7);
    std::cout <<  index << std::endl;
    return 0;
}