#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct TreeNode {//��ũ�뵵 �� ���ܳ�� ������ �ȿ� ch�� ��ȯ�� ��� 
	int weight;//�󵵼� ->�̰� �Ⱦ�  
	char ch;
	struct TreeNode* left, * right;//�̰� �ǳ�??
}TreeNode;

typedef struct { //key���� �󵵼��ε� �̰� �������� heap insert,delete�� �� 
	TreeNode* ptree;
	char ch;
	int key;//weight�� ���� ���� 
}element;

typedef struct {//heap �󵵼��� ������ �������� 
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


	while (h->heap[i / 2].key > item.key && i != 1) {//�߰��Ѱ��� �θ��庸�� ������ �θ��� �ڽ� ���� �ִ´�
		h->heap[i] = h->heap[i / 2];

		i /= 2;// ���� ������ �θ���� �ٲٱ� ����

	}
	h->heap[i] = item;//�ٲ���ؿ� �ִ´� 

}

element delete_min_heap(HeapType* h) {

	int parent, child;
	element temp, item;

	item = h->heap[1]; //������ �� ������ �� 
	temp = h->heap[(h->heap_size)--];//�� ���� ���� ������ �ö󰡼� �����ð�  heapSize�� �Ҵ��Ŀ� �۾����� 


	parent = 1;
	child = 2;
	while (child <= h->heap_size) {//�ڽ� ���� heap_size���� Ŀ���� heap�ܺ��̴�
		if (h->heap[child].key > h->heap[child+1].key && child < h->heap_size) {//���߿� �� ���� ���� ���� �ö󰡾��Ѵ� �׸��� child ����   //     1       �̰Ŵ� ��   |    1     �̰Ŵ� �ȉ�
			child++;								//�̰� ������ child+1 ��� child++ �־������ 																					   //   2   3     heapsize 3  |  2      heapsize 2 
		}
		if (temp.key < h->heap[child].key) break;// ������ ���� �� child ���� �߰� �� ������ ũ�� break �� 

		h->heap[parent] = h->heap[child];//�Ʒ� ���� ���� �ø�
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp; // ������ ���� �÷������� �θ𰪿� �Ʒ��� ���� �ְ� ���� �θ� �ε������ٰ� �߰��� ���� �ִ´�
	return item;//�����Ȱ��� �������� ��ȯ 
}

TreeNode* make_tree(TreeNode* left, TreeNode* right) { //�׳�  Ʈ�� ��� �ϳ� ����°��� 

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

	return !(h->left) && !(h->right); //�ڽ��� �Ѵ� ���� ��� 1�� ��ȯ---> ���ܳ�� �϶� 1��ȯ 

}

void print_array(int codes[],int size) {//ȣ���� �ڵ尡 �Ҵ� �ǰ� ���� �װ� ��ȯ�Ҷ� ��� 

	for (int i = 0; i < size; i++) {
		printf("%d", codes[i]);
	}
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {//top�� 0�������� ��ȯ�� �����Ϸ��� 
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
		
	}
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	if (is_leaf(root)) {//���ܿ� �����ϸ� ������ �ڵ带 �������
		printf("%c:", root->ch);
		print_array(codes, top);
	}
}

void huffman_tree(int freq[], char ch_list[], int n) {//n�� ���� ���� 
	
	TreeNode* node,*x;//node,x�� �ӽó��  ���� �� �ΰ���?
	HeapType* heap;
	element e, e1, e2;
	heap = create();
	init(heap);

	int top = 0;//�ܼ� �ʱ�ȭ 0�� �Ѱ������ ��ȯ�� 
	int codes[100];//10���ص� ������ٵ�. �̰͵� ��ȯ�� �ܼ� �ʱ�ȭ

	for (int i = 0; i < n; i++) {//�ϴ� ������ element���� ���� ������� 
		node = make_tree(NULL, NULL);//�� Ʈ���� ���� ����
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;//element ���� ����ȭ ���� ��带 element���� ����ü Ʈ���� �־��� 
		insert_min_heap(heap, e);//heap���ٰ� element�־��� 
		print_heap(heap);
	}

	for (int i = 1; i < n;i++) {//���� ���� ���� �ѹ����� ÷�� �ΰ��� �ϳ��� ���°ź��� �����ϴϱ� 
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		x = make_tree(e1.ptree, e2.ptree);//�ӽ� ��带 ���빰�� ������� ���� �ڽĳ�忡�� ���� �������� �ڽĳ�带 ������
		e.key = x->weight = e1.key + e2.key;//�����ϴ� ���� ���� �ΰ��� ����� �󵵼� ���� �־��� 
		e.ptree = x;//������ �ʱ�ȭ ���� �ӽ� ��带 element�� ������ �־��� 
		printf("///%d +%d->%d\n", e1.key, e2.key, e.key);//������ ���� ���� �󵵼��� ��ġ�� ������ ���
		insert_min_heap(heap, e);//������ �ΰ� ����� ��ġ���� �־��� 
		print_heap(heap);
	}
	e = delete_min_heap(heap);//���� ���� �󵵼��� ���� ���� ��� -->root ����� 
	print_codes(e.ptree,codes,top);//tree�� Ÿ�� ��ȯ�Ͽ� ��� ���� ������ code�� ���
	destroy_tree(e.ptree);
	free(heap);

}
void main() {
	char ch_list[] = { 'a','e','i','o','u','s','t'};
	int freq[] = { 10,15,12,3,4,13,1 };
	huffman_tree(freq, ch_list, 7);
	
}