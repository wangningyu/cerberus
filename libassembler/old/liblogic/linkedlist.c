/*
 * 头文件
 */
#include "linkedlist.h"

/*
 * 函数定义
 */
/*
 * 作者:玩命
 * 开始日期:2009-1-1
 * 完成日期:2009-1-1
 * 参数:
 *    n:要生成链表的节点数目.
 * 返回值:
 *    链表头节点指针.
 * 说明:
 *    初始化一条链表.
 */
PLINKEDLIST_NODE init_linkedlist(dword_t n) {
	PLINKEDLIST_NODE node;
	if (!n) return NULL;
	node = (PLINKEDLIST_NODE)logic_malloc(sizeof(LINKEDLIST_NODE));
	assert(node);
	node->next = init_linkedlist(n-1);
	if (node->next) (node->next)->previous = node;
	node->previous = NULL;	
	return node;
}/* end init_linkedlist */

/*
 * 作者:玩命
 * 开始日期:2009-1-1
 * 完成日期:2009-1-1
 * 参数:
 *    pll:指向链表指针的指针.
 * 返回值:
 *    无.
 * 说明:
 *    释放一条链表.
 */
void free_linkedlist(PLINKEDLIST_NODE *pll) {
	assert(pll);
	if ((*pll)->next) free_linkedlist(&((*pll)->next));
	logic_free(*pll);*pll = NULL;
	return;
}/* end free_linkedlist */

/*
 * 作者:玩命
 * 开始日期:2009-1-1
 * 完成日期:2009-1-1
 * 参数:
 *    ppl:指向链表头指针的指针.
 *	  i:位置,索引从1开始.
 * 返回值:
 *    T:删除成功.
 *    F:删除失败.
 * 说明:
 *	  删除某个位置上的节点.
 */
bool_t del_node_linkedlist(PLINKEDLIST_NODE *ppl, dword_t i) {
	PLINKEDLIST_NODE now = NULL;
	assert(ppl && *ppl);
	if (!i) return F;
	now = query_node_linkedlist(*ppl, i);
	if (!now) return F;
	/* 如果是头节点 */
	if (now == *ppl) {
		PLINKEDLIST_NODE exchange = now->next;
		/* 如果只有头节点 */
		if (!exchange) {
			logic_free(now); *ppl = NULL;
			return T;
		}/* end if */
		logic_free(now);
		_copy_linkedlist_node_(now, exchange);
		now->previous = NULL;
		return T;
	} else {
		(now->previous)->next = (now)->next;
		if (now->next) (now->next)->previous = (now)->previous;
		logic_free(now);
		return T;
	}
}/* end del_node_linkedlist */

/*
 * 作者:玩命
 * 开始日期:2009-1-1
 * 完成日期:2009-1-1
 * 参数:
 *    pll:指向链表头指针.
 *	  i:位置,索引从1开始.
 * 返回值:
 *    查询的节点.
 * 说明:
 *	  获取一个位置的节点,
 *	  超过链表返回NULL.
 */
PLINKEDLIST_NODE query_node_linkedlist(PLINKEDLIST_NODE pll, dword_t i) {
	PLINKEDLIST_NODE now = pll;
	assert(now);
	/* 如果i = 0 */
	if (!i) return NULL;
	now = query_node_linkedlist(now->next, i-1);
	return now;
}/* end query_node_linkedlist */

/*
 * 作者:玩命
 * 开始日期:2009-1-1
 * 完成日期:2009-1-1
 * 参数:
 *    pll:指向链表头指针.
 * 返回值:
 *    链表节点的数量.
 * 说明:
 *	  节点数量.
 */
dword_t get_count_linkedlist(PLINKEDLIST_NODE pll) {
	dword_t count = 1;
	if (!pll) return 0;
	count += get_count_linkedlist(pll->next);
#ifdef DEBUG_LINKEDLIST
	printf("linkedlist_node Index = %d\n", count-1);
	printf("linkedlist_node->previous = 0x%X\n", pll->previous);
	printf("linkedlist_node->next = 0x%X\n", pll->next);
	printf("--------------------\n");
#endif
	return count;
}/* end get_count_linkedlist */

/*
 * 作者:玩命
 * 开始日期:2009-1-1
 * 完成日期:2009-1-1
 * 参数:
 *    pllh:指向链表头指针.
 *	  plli:指向要插入的节点.
 *	  i:要插入的索引.
 * 返回值:
 *    插入后节点的指针.
 * 说明:
 *    在某个位置插入节点,
 *	  这个位置从0开始计算.
 */
PLINKEDLIST_NODE add_node_linkedlist(PLINKEDLIST_NODE pllh, PLINKEDLIST_NODE plli, dword_t i) {
	PLINKEDLIST_NODE now = NULL;
	assert(pllh && plli);
	now = query_node_linkedlist(pllh, i);
	if (!now) return NULL;
	plli->previous = now->previous;
	plli->next = now;
	now->previous = plli;
	return now;
}/* end add_node_linkedlist */

/*
 * 作者:玩命
 * 开始日期:2009-1-1
 * 完成日期:2009-1-1
 * 参数:
 *    pllh:指向链表头指针.
 *	  plli:指向要插入的节点.
 * 返回值:
 *    插入后节点的指针.
 * 说明:
 *	  无.
 */
void add_node_tail_linkedlist(PLINKEDLIST_NODE pllh, PLINKEDLIST_NODE plli) {
	assert(pllh && plli);
	if (pllh->next) add_node_tail_linkedlist(pllh->next, plli);
	else {
		pllh->next = plli;
		plli->previous = pllh;
		plli->next = NULL;
	}
	return;
}/* end add_node_tail_linkedlist */