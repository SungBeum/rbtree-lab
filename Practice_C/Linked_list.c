#include <stdio.h>
#include <stdlib.h>

// int 라는 자료형을 element로 쓰겠다
typedef int element;
// 노드 타입을 구조체로 정의한다.
typedef struct ListNode {
    // 구조체 멤버 element형 data
    element data;
    // list 라는 멤버로 자기 참조 (구조체)
    struct ListNode* next;
    
}   ListNode;   //구조체 별칭
// 앞부분에 노드 삽입
ListNode* insert_first(ListNode* head, int value)
{   // malloc (동적 메모리 할당함수) _ ListNode* p 라는 포인터가 (ListNode*) 라는 자료형으로(_그냥 malloc 은 void*자료형) ListNode의 크기만큼 메모리 할당
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));  //(1)
    // 구조체 포인터를 사용할 때에 편의상 ListNode *p + (*p).data 대신 p->data 를 쓴다
    p -> data = value;  //(2)
    p -> next = head;   //(3)
    head = p; //(4)
    return head; //(5)
}
// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));  //(1)
    p -> data = value;  //(2)
    p -> next = pre -> next; //(3)
    pre -> next = p; //(4)
    return head; //(5)
}

// 앞부분의 노드 제거
ListNode* delete_first(ListNode* head)
{
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head; //(1)
    head = removed -> next; //(2)
    free(removed);  //(3)
    return head;    //(4)
}

// pre가 가리키는 노드의 다음 노드를 삭제
ListNode* delete(ListNode* head, ListNode* pre)
{
    ListNode* removed;
    removed = pre -> next;  //(1)
    pre -> next = removed -> next;  //(2)
    free(removed);  //(3)
    return head;    //(4)
}

// 리스트 출력
void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p -> next)
        printf("%d->", p -> data);
    printf("NULL \n");
}

// 특정 값 탐색
ListNode* search_list(ListNode *head, element x)
{
    ListNode *p = head;

    while (p != NULL) {
        if ( p -> data == x) return p;
        p = p ->next;
    }
    // 탐색 실패
    return NULL;
}
// 두 리스트를 연결
ListNode* concat_list(ListNode *head1, ListNode *head2)
{
    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;
    else {
        ListNode *p;
        p = head1;
        while (p -> next != NULL)
            p = p -> next;
        p -> next = head2 ;
        return head1 ;
    }
}
// 리스트 역순화
ListNode* reverse(ListNode *head)
{
    // 순회 포인터로 p, q, r 을 사용
    ListNode *p, *q, *r ;

    p = head ;  // p는 역순으로 만들 리스트
    q = NULL ;  // q는 역순으로 만들 노드
    while (p != NULL) {
        r = q;  // r 은 역순으로 된 리스트
        q = p;  // r 은 q, q는 p를 차례로 따라간다
        p = p -> next;
        q -> next = r;  // q의 링크 방향을 바꾼다
    }
    return q;
}
// 리스트 마지막에 삽입
ListNode* insert_last(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p -> data = value;
    if (head == NULL) {
        p -> next = head ;
        head = p ;
    }
    else {
        ListNode* q = head;
        while (q -> next != NULL) { q = q -> next;}
        p -> next = q -> next;
        q -> next = p ;
    }
    return head;
}
// 두 리스트를 병합 ( 기존의 두 리스트는 변경하지 않고, 병합된 결과는 새로운 리스트로 만들어 반환)
ListNode* merge(ListNode* list1, ListNode* list2) {
    ListNode* result = NULL;
    ListNode* p1 = list1, *p2 = list2;
    if (p1 == NULL) return list2;
    if (p2 == NULL) return list1;
    while (p1 != NULL && p2 != NULL) {
        if (p1 -> data < p2 -> data) {
            result = insert_last(result, p1 -> data);
            p1 = p1 -> next ;
        }
        else {
            result = insert_last(result, p2 -> data);
            p2 = p2 -> next;
        }
    }
    while (p1 != NULL) {
        result = insert_last(result, p1 -> data);
        p1 = p1 -> next ;
    }
    while (p2 != NULL) {
        result = insert_last(result, p2 -> data);
        p2 = p2 -> next ;
    }
    return result;
}
// 단순 연결리스트에서 데이터 값이 홀수인 노드들을 추출해서 새로운 단순 연결리스트를 반환
ListNode* odd_extract(ListNode* list)
{
    ListNode* oddList = NULL ;
    ListNode* p;
    for (p = list; p != NULL; p = p -> next)
    {
        if (p -> data % 2 != 0) {
            oddList = insert_first(oddList, p -> data);
            p = p -> next;
        }
    }
    return oddList;
}

// 메인
int main(void)
{
	ListNode *head = NULL;
    // 노드 삽입
	for (int i = 0; i < 5; i++) {
		head = insert_first(head, i);
		print_list(head);
	}
    // 노드 삭제
	for (int i = 0; i < 5; i++) {
		head = delete_first(head);
		print_list(head);
	}

    // 노드 값 10, 20, 30 삽입 후 30 검색
    head = insert_first(head, 10);
    print_list(head);
    head = insert_first(head, 20);
    print_list(head);
    head = insert_first(head, 30);
    print_list(head);
    if (search_list(head, 30) != NULL)
        printf("리스트에서 30을 찾았습니다. \n");
    else
        printf("리스트에서 30을 찾지 못했습니다. \n");
    return 0;


}

/* 실행결과
0->NULL
1->0->NULL
2->1->0->NULL
3->2->1->0->NULL
4->3->2->1->0->NULL
3->2->1->0->NULL
2->1->0->NULL
1->0->NULL
0->NULL
NULL
*/