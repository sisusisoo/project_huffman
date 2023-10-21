#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct TreeNode {//링크용도 밑 말단노드 구별후 안에 ch값 반환시 사용 
	int weight;//빈도수 ->이거 안씀  
	char ch;
	struct TreeNode* left, * right;//이거 되나??
}TreeNode;

typedef struct { //key값이 빈도수인데 이걸 기준으로 heap insert,delete를 함 
	TreeNode* ptree;
	char ch;
	int key;//weight랑 같이 쓰임 
}element;

typedef struct {//heap 빈도수로 레벨을 나누려고 
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}
void print_heap(HeapType *h) {

	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ",h->heap[i].key);
	}
	printf("\n");
}

void insert_min_heap(HeapType* h, element item) {
	int i = ++h->heap_size;


	while (h->heap[i / 2].key > item.key && i != 1) {//추가한값이 부모노드보다 낮을때 부모값을 자식 값에 넣는다
		h->heap[i] = h->heap[i / 2];

		i /= 2;// 다음 기준을 부모노드로 바꾸기 위함

	}
	h->heap[i] = item;//바뀐기준에 넣는다 

}

element delete_min_heap(HeapType* h) {

	int parent, child;
	element temp, item;

	item = h->heap[1]; //맨위의 값 젤작은 값 
	temp = h->heap[(h->heap_size)--];//맨 끝값 이제 맨위로 올라가서 내려올값  heapSize는 할당후에 작아진다 


	parent = 1;
	child = 2;
	while (child <= h->heap_size) {//자식 값이 heap_size보다 커지면 heap외부이다
		if (h->heap[child].key > h->heap[child+1].key && child < h->heap_size) {//둘중에 더 작은 값이 위로 올라가야한다 그리고 child 값은   //     1       이거는 됌   |    1     이거는 안됌
			child++;								//이거 위에서 child+1 대신 child++ 넣어서오류남 																					   //   2   3     heapsize 3  |  2      heapsize 2 
		}
		if (temp.key < h->heap[child].key) break;// 위에서 선택 된 child 값이 추가 될 값보다 크면 break 됨 

		h->heap[parent] = h->heap[child];//아래 값을 위로 올림
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp; // 마지막 까지 올려보내고 부모값에 아래의 값을 넣고 난뒤 부모 인덱스에다가 추가할 값을 넣는다
	return item;//삭제된가장 작은값을 반환 
}

TreeNode* make_tree(TreeNode* left, TreeNode* right) { //그냥  트리 노드 하나 만드는거임 

	TreeNode* node=(TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

void destroy_tree(TreeNode *h) {
	if (h == NULL) return;
	destroy_tree(h->right);
	destroy_tree(h->left);
	free(h);
}

int is_leaf(TreeNode *h) {

	return !(h->left) && !(h->right); //자식이 둘다 없는 경우 1을 반환---> 말단노드 일때 1반환 

}

void print_array(int codes[],int size) {//호프먼 코드가 할당 되고 나면 그걸 반환할때 사용 

	for (int i = 0; i < size; i++) {
		printf("%d", codes[i]);
	}
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {//top은 0에서부터 순환을 시작하려고 
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
		
	}
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	if (is_leaf(root)) {//말단에 도착하면 허프먼 코드를 출력해줌
		printf("%c:", root->ch);
		print_array(codes, top);
	}
}

void huffman_tree(int freq[], char ch_list[], int n) {//n은 글자 갯수 
	
	TreeNode* node,*x;//node,x는 임시노드  굳이 왜 두개로?
	HeapType* heap;
	element e, e1, e2;
	heap = create();
	init(heap);

	int top = 0;//단순 초기화 0을 넘겨줘야함 순환용 
	int codes[100];//10만해도 충분할텐데. 이것도 순환용 단수 초기화

	for (int i = 0; i < n; i++) {//일단 글자의 element들을 먼저 만들어줌 
		node = make_tree(NULL, NULL);//빈 트리를 먼저 만듦
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;//element 값과 동기화 해준 노드를 element안의 구조체 트리로 넣어줌 
		insert_min_heap(heap, e);//heap에다가 element넣어줌 
		print_heap(heap);
	}

	for (int i = 1; i < n;i++) {//글자 갯수 보다 한번적게 첨에 두개를 하나로 묶는거부터 시작하니까 
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		x = make_tree(e1.ptree, e2.ptree);//임시 노드를 내용물을 만들어줌 양쪽 자식노드에는 현재 가장작은 자식노드를 넣은것
		e.key = x->weight = e1.key + e2.key;//현존하는 가장 작은 두개의 노드의 빈도수 합을 넣어줌 
		e.ptree = x;//위에서 초기화 해준 임시 노드를 element의 노드란에 넣어줌 
		printf("///%d +%d->%d\n", e1.key, e2.key, e.key);//위에서 가장 작은 빈도수를 합치는 과정을 출력
		insert_min_heap(heap, e);//위에서 두개 지우고 합치것을 넣어줌 
		print_heap(heap);
	}
	e = delete_min_heap(heap);//기장 작은 빈도수를 가진 젤위 노드 -->root 노드임 
	print_codes(e.ptree,codes,top);//tree를 타고 순환하여 모든 말단 노드들의 code를 출력
	destroy_tree(e.ptree);
	free(heap);

}
void main() {
	char ch_list[] = { 'a','e','i','o','u','s','t'};
	int freq[] = { 10,15,12,3,4,13,1 };
	huffman_tree(freq, ch_list, 7);
	
}