#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "xstddef.h"
#include "avltree.h"


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

static int32 avl_erase_cmp(void *node, void *arg) {
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
	struct Test_avl *avl = NULL;

	int r = 0, t = 0;
	for (int i = 0; i < 1024; i++) {
e:
		if (t == 0) {
			printf("insert> ");
		} else {
			printf("erase> ");
		}

		fflush(stdout);
		if (scanf("%d", &r) < 0)
			break;

		printf("\n> %d\n\n", r);
		if (r == -9990) {
			t = 0;
			goto e;
		} else if (r == -9999) {
			t = 2;
			goto e;
		} else if (r == -99999) {
			break;
		}

		if (t == 0) {
			avl = malloc(sizeof(struct Test_avl));
			avl->key = r;
			FSYMBOL(avl_insert_wrap)(&root, &avl->avl, avl_cmp);
			avl_each(root.node, 0, -1);
		} else {
			void *p = FSYMBOL(avl_erase2_wrap)(&root, &r, avl_erase_cmp);
			if (p)
				free(container_of(p, struct Test_avl, avl));
			avl_each(root.node, 0, -1);
		}
	}

	return 0;
}
