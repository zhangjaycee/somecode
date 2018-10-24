/***
	by jc, 20181018
***/

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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *ret = NULL;
        ListNode *p_ret = NULL;
        ListNode *p = head;
        while (p) {
            if (p->next == NULL || p->next->val != p->val) {
                //printf("1 p->val = %d\n", p->val);
                //add p to ret              
                if (ret == NULL) {
                    p_ret = p;
                    ret = p_ret;
                } else {
                    p_ret->next = p;
                    p_ret = p_ret->next;
                }
                p = p->next;
            } else { //duplicate
                //printf("2 p->val = %d\n", p->val);
                while (p->next != NULL && (p->next->val == p->val)) { 
                    p = p->next;
                }
                p = p->next;
            }
        }
        if (p_ret)
            p_ret->next = NULL;
        return ret;
    }
};
