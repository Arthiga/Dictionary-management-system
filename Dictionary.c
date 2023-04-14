#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50
#define MAX_MEANING_LEN 100

struct node {
    char word[MAX_WORD_LEN];
    char meaning[MAX_MEANING_LEN];
    struct node *left;
    struct node *right;
};

struct queue {
    struct node *data[MAX_WORDS];
    int front;
    int rear;
};

struct node *root = NULL;
int count = 0;

void enqueue(struct queue *q, struct node *n) {
    if (q->rear == MAX_WORDS - 1) {
        printf("Queue is full!\n");
        return;
    }

    q->rear++;
    q->data[q->rear] = n;
}

struct node *dequeue(struct queue *q) {
    if (q->front == q->rear) {
        printf("Queue is empty!\n");
        return NULL;
    }

    q->front++;
    return q->data[q->front];
}

void insert_word() {
    if (count >= MAX_WORDS) {
        printf("Dictionary is full!\n");
        return;
    }

    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    printf("Enter word: ");
    scanf("%s", new_node->word);
    printf("Enter meaning: ");
    scanf(" %[^\n]s", new_node->meaning);
    new_node->left = NULL;
    new_node->right = NULL;

    if (root == NULL) {
        root = new_node;
    } else {
        struct queue q = {0};
        enqueue(&q, root);

        while (1) {
            struct node *current = dequeue(&q);
            if (current == NULL) {
                break;
            }

            if (strcmp(new_node->word, current->word) < 0) {
                if (current->left == NULL) {
                    current->left = new_node;
                    break;
                } else {
                    enqueue(&q, current->left);
                }
            } else {
                if (current->right == NULL) {
                    current->right = new_node;
                    break;
                } else {
                    enqueue(&q, current->right);
                }
            }
        }
    }

    count++;
    printf("Word added successfully!\n");
}

void search_word() {
    char word[MAX_WORD_LEN];
    printf("Enter word to find meaning: ");
    scanf("%s", word);

    struct node *current = root;
    while (current != NULL) {
        if (strcmp(word, current->word) < 0) {
            current = current->left;
        } else if (strcmp(word, current->word) > 0) {
            current = current->right;
        } else {
            printf("%s\n", current->meaning);
            return;
        }
    }

    printf("Word not found in dictionary!\n");
}

void destroy_tree(struct node *n) {
    if (n == NULL) {
        return;
    }

    destroy_tree(n->left);
    destroy_tree(n->right);
    free(n);
}

int main() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add word\n");
        printf("2. Search word\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert_word();
                break;
            case 2:
                search_word();
                break;
            case 3:
            	exit(0);
        }
    }while(1);
    return 0;
}
               

