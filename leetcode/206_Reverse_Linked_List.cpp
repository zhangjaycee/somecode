/****
  by jc 20181018
 ****/

/*
Reverse a singly linked list.

Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *ret = NULL;
        ListNode *l = NULL;
        if (NULL == head) return NULL;
        if (NULL == head->next) return head;
        // each time find the last node, not good
        while (head->next) {
            ListNode *p = head;
            while (p->next->next) p = p->next; // find the last-1 Node
            if (NULL == ret) {
                l = p->next;
                ret = l;
            } else {
                l->next = p->next;
                l = l->next;
            }
            p->next = NULL;
        }
        l->next = head;
        return ret;
    }
    /* Solution 2 */
    //           a --> b --> c --> d --> NULL (prev == NULL)
    // NULL <--  a     b --> c --> d --> NULL (prev == a)
    // NULL <--  a <-- b     c --> d --> NULL (prev == b)
    // ...
    ListNode* reverseList(ListNode* head) {
        ListNode *ret = NULL;
        ListNode *prev = NULL;
        ListNode *p = head;
        if (NULL == p) return NULL;
        while (p) {
            ListNode *tmp = p->next;
            p->next = prev;
            prev = p;
            p = tmp;
        }
        return prev;
    }
};
