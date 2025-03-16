#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "config.h"
#include "xstddef.h"
#include "xstdlib.h"
#include "avltree.h"


#define NODE_SIZE (1 << 20)

struct Test_avl {
	int32 key;
	struct avl_node avl;
};

static void avl_each(struct avl_node *node, int n, int c) {
	if (node) {
		avl_each(node->right, n + 4, 0);

		struct Test_avl *avl = container_of(node, struct Test_avl, avl);
		for (int i = 0; i < n; i++)
			printf(" ");
		if (c == -1) {
			printf("=%d (%d)(p: %p, l: %p, r: %p, n: %p)\n",
				avl->key, node->bf,
				node->parent, node->left, node->right, node);
		} else if (c == 0) {
			printf("/%d (%d)(p: %p, l: %p, r: %p, n: %p)\n",
				avl->key, node->bf,
				node->parent, node->left, node->right, node);
		} else {
			printf("\\%d (%d)(p: %p, l: %p, r: %p, n: %p)\n",
				avl->key, node->bf,
				node->parent, node->left, node->right, node);
		}

		avl_each(node->left, n + 4, 1);
	} else {
		for (int i = 0; i < n; i++)
			printf(" ");
		if (c == -1) {
			printf("=Nil\n");
		} else if (c == 0) {
			printf("/Nil\n");
		} else {
			printf("\\Nil\n");
		}
	}
}

static int32 avl_cmp(void *node, void *arg) {
	int32 parent_key = container_of(node, struct Test_avl, avl)->key;
	int32 new_key = container_of(arg, struct Test_avl, avl)->key;
	if (new_key < parent_key)
		return AVL_LEFT;
	if (new_key > parent_key)
		return AVL_RIGHT;

	return AVL_REPEAT;
}

static int32 avl_search_cmp(void *node, void *arg) {
	int32 parent_key = container_of(node, struct Test_avl, avl)->key;
	int32 old_key = *(int *)arg;
	if (old_key < parent_key)
		return AVL_LEFT;
	if (old_key > parent_key)
		return AVL_RIGHT;

	return AVL_REPEAT;
}

int main() {
	AVL_ROOT_NEW(root);
	struct Test_avl *avl = malloc(sizeof(struct Test_avl) * NODE_SIZE);
	clock_t start, end;
	double time;

	RANDOM_TYPE0_NEW(rand, 123456);
	for (int i = 0; i < NODE_SIZE; i++) {
		XSYMBOL(random_r)(&rand, &avl[i].key);
	}

	/* insert */
	start = clock();
	for (int i = 0; i < NODE_SIZE; i++) {
		FSYMBOL(avl_insert_wrap)(&root, &avl[i].avl, avl_cmp);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("insert: %d, time: %.6fs (%.2f/s), height: %d\n",
		NODE_SIZE, time, NODE_SIZE / time, AVL_HEIGHT(root.node));

/*	avl_each(root.node, 0, -1); */

	/* search */
	start = clock();
	for (int i = 0; i < NODE_SIZE; i++) {
		FSYMBOL(avl_search_wrap)(&root, &avl[i].key, avl_search_cmp);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("search: %d, time: %.6fs (%.2f/s), height: %d\n",
		NODE_SIZE, time, NODE_SIZE / time, AVL_HEIGHT(root.node));

	/* erase */
	start = clock();
	for (int i = 0; i < (NODE_SIZE / 10); i++) {
		FSYMBOL(avl_erase2_wrap)(&root, &avl[i].avl, avl_cmp);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("erase: %d, time: %.6fs (%.2f/s), height: %d\n",
		NODE_SIZE / 10, time, (NODE_SIZE / 10) / time, AVL_HEIGHT(root.node));

/*	avl_each(root.node, 0, -1); */

	/* search */
	start = clock();
	for (int i = (NODE_SIZE / 10); i < ((NODE_SIZE / 10) + 10); i++) {
		printf("search: %d %p %p\n", avl[i - 1].key, &avl[i - 1].avl,
			FSYMBOL(avl_search_wrap)(&root, &avl[i - 1].avl, avl_cmp));
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("search: %d, time: %.6fs (%.2f/s), height: %d\n",
		10, time, 10 / time, AVL_HEIGHT(root.node));

	/* search */
	start = clock();
	for (int i = 0; i < NODE_SIZE; i++) {
		FSYMBOL(avl_search_wrap)(&root, &avl[i].key, avl_search_cmp);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("search: %d, time: %.6fs (%.2f/s), height: %d\n",
		NODE_SIZE, time, NODE_SIZE / time, AVL_HEIGHT(root.node));

	/* erase */
	start = clock();
	for (int i = 0; i < NODE_SIZE; i++) {
		FSYMBOL(avl_erase2_wrap)(&root, &avl[i].avl, avl_cmp);
	}
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("erase: %d, time: %.6fs (%.2f/s), height: %d\n",
		NODE_SIZE, time, NODE_SIZE / time, AVL_HEIGHT(root.node));

	return 0;
}
