#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K 9
#define BASE 1000000000

char* removeZeros(char* str) {
    /*
        This function removes all leading zeros from a given number as a string;

        Args:
            str: input string

        Return:
            pointer to the first non-zero char or "0" if it is empty.
    */
    int i = 0;
    while (str[i] == '0')
        i++;
    if (str[i] == '\0')
        return "0";
    return str + i;
}

// linked list typedef for our big number.
typedef struct Node {
    int bloco;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    bool sinal; // 0 if positive, 1 if negative.
} BigInt;

Node* create_node(int bloco) {

    /*
       create_node receives a block of integer values ​​of up to 9 digits and
       initializes a new linked list node using malloc.

       Args:
           int: block to store in the node.

       Return:
           pointer to the new alocated node.
   */

    Node* n = malloc(sizeof(Node));
    n->bloco = bloco;
    n->next = NULL;
    return n;
}

void insert_tail(BigInt* num, int bloco) {

    /*
        insert_tail receives a bigint and an integer block up to 9 digits,
        creates a new node using create_node and appends it to the end of the
       linked list.

        Args:
            BigInt*: pointer to the BigInt structure where the block will be
       inserted.

            int: block to be stored as the last node.

        Return:
            This function does not return a value, only insert a new node at the
       tail of our linked list.

    */
    Node* n = create_node(bloco);

    if (!num->head) {
        num->head = n;
        return;
    }
    Node* cur = num->head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = n;
}

BigInt* create_bigint() {

    /*
        create_bigint allocates and initializes a new BigInt structure,
        the head pointer is setted as NULL and sinal as positive (0)

        Args:
            (empty)

        Return:
            pointer to the new allocated BigInt structure.

    */
    BigInt* b = malloc(sizeof(BigInt));
    b->head = NULL;
    b->sinal = 0;
    return b;
}

BigInt* converte_str(char* str) {

    /*
        convert_str receives a numeric string (possibly with '-' sign),
        removes leading zeros, split the string into blocks of size K
        starting from LSD (last significant digits), it converts each block
        into an integer and appends to our BigInt linked list using insert_tail.

        Args:
            char*: input numeric string to convert

        Return:
            pointer to the newly created BigInt representing the input string.

    */
    BigInt* num = create_bigint();

    if (str[0] == '-') {
        num->sinal = 1;
        str++;
    }

    str = removeZeros(str);
    int L = strlen(str);

    for (int i = L; i > 0; i -= K) {
        int inicio = i - K;
        if (inicio < 0)
            inicio = 0;

        char temp[16];
        int len = i - inicio;

        strncpy(temp, str + inicio, len);
        temp[len] = '\0';

        int bloco = atoi(temp);
        insert_tail(num, bloco);
    }

    return num;
}

int len(Node* n) {

    /*
        len receives the starting node of our BigInt structure and
        returns the size of our linked list

        Args:
            node *n: node of our linked list

        Return:
            size of our BigInt linked list
    */
    int c = 0;
    while (n) {
        c++;
        n = n->next;
    }
    return c;
}

int compare_blocks(Node* a, Node* b) {

    /*
        compare_blocks compares two BigInt linked lists recursively
        from the most significant block to the least significant block

        Args:
            Node *a: first linked list node
            Node *b: second linked list node

        Return:
            1 if the first number is greater
            -1 if the second number is greater
            0 if they are equal
    */

    if (!a && !b)
        return 0;

    int r = compare_blocks(a->next, b->next);
    if (r != 0)
        return r;

    if (a->bloco > b->bloco)
        return 1;
    if (a->bloco < b->bloco)
        return -1;
    return 0;
}

int greater_value(BigInt* A, BigInt* B) {

    /*
        greater_value compares two BigInt numbers considering both
        their signs and magnitudes

        Args:
            BigInt *A: first bigint to compare
            BigInt *B: second bigint to compare

        Returns:
            1 if A is greater than B
            -1 if B is greater than A
            0 if they are equal

    */
    if (A->sinal != B->sinal) {
        return (A->sinal == 0 ? 1 : -1);
    }

    int tA = len(A->head);
    int tB = len(B->head);

    if (tA > tB) {
        return (A->sinal == 0 ? 1 : -1);
    }
    if (tA < tB) {
        return (A->sinal == 0 ? -1 : 1);
    }

    int r = compare_blocks(A->head, B->head);
    if (A->sinal == 0)
        return r;

    return -r;
}

bool is_equal(BigInt* A, BigInt* B) {
    return greater_value(A, B) == 0;
}
bool is_greater(BigInt* A, BigInt* B) {
    return greater_value(A, B) == 1;
}
bool is_less(BigInt* A, BigInt* B) {
    return greater_value(A, B) == -1;
}

void normalize(BigInt* N) {

    /*
    normalize removes leading zero blocks from a BigInt, ensuring
    the internal representation does not contain unnecessary blocks
    at the most significant end.

    Args:
        BigInt*: bigint to normalize.

    Return:
        None (the BigInt is modified in place).
  */
    Node* cur = N->head;
    Node* prev = NULL;

    while (cur) {
        if (cur->bloco != 0) {
            prev = cur;
        }
        cur = cur->next;
    }

    if (!prev) {
        N->head = create_node(0);
        N->sinal = 0;
        return;
    }

    prev->next = NULL;
}

BigInt* soma_modulos(BigInt* A, BigInt* B) {

    /*
    soma_modulos computes the sum of the absolute values (modules)
    of two BigInt numbers, ignoring their signs.


    Args:
        BigInt*: first bigint operand
        BigInt*: second bigint operand

    Return:
        pointer to a newly allocated BigInt representing the sum of the magnitudes
        of A and B.
  */

    BigInt* R = create_bigint();

    Node* a = A->head;
    Node* b = B->head;

    long long carry = 0;

    while (a || b || carry) {
        long long va = a ? a->bloco : 0;
        long long vb = b ? b->bloco : 0;

        long long s = va + vb + carry;
        carry = s / BASE;

        insert_tail(R, s % BASE);

        if (a)
            a = a->next;
        if (b)
            b = b->next;
    }

    return R;
}

BigInt* sub_modulos(BigInt* A, BigInt* B) {

    /*
    sub_modulos computes the subtraction of the absolute values
    (modules) of two BigInt numbers, ignoring their signs.

    Args:
        BigInt*: minuend  (A) — must have |A| >= |B|
        BigInt*: subtrahend (B)

    Return:
        pointer to a newly allocated BigInt representing |A| - |B| as a positive
        magnitude.
  */
    BigInt* R = create_bigint();

    Node* a = A->head;
    Node* b = B->head;

    long long borrow = 0;

    while (a) {
        long long va = a->bloco;
        long long vb = b ? b->bloco : 0;

        long long sub = va - vb - borrow;

        if (sub < 0) {
            sub += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insert_tail(R, sub);

        a = a->next;
        if (b)
            b = b->next;
    }

    return R;
}

BigInt* soma(BigInt* A, BigInt* B) {

    // Sinais iguais == soma simples
    if (A->sinal == B->sinal) {
        BigInt* R = soma_modulos(A, B);
        R->sinal = A->sinal;
        normalize(R);
        return R;
    }

    // A + (-B) = A - B
    if (A->sinal == 0 && B->sinal == 1) {
        if (is_greater(A, B)) {
            BigInt* R = sub_modulos(A, B);
            R->sinal = 0;
            normalize(R);
            return R;
        } else {
            BigInt* R = sub_modulos(B, A);
            R->sinal = 1;
            normalize(R);
            return R;
        }
    }

    // (-A) + B = B - A
    if (A->sinal == 1 && B->sinal == 0) {
        if (is_greater(B, A)) {
            BigInt* R = sub_modulos(B, A);
            R->sinal = 0;
            normalize(R);
            return R;
        } else {
            BigInt* R = sub_modulos(A, B);
            R->sinal = 1;
            normalize(R);
            return R;
        }
    }

    return NULL;
}

void print_bigint(BigInt* N) {
    if (N->sinal)
        printf("-");

    Node* stack[4096];
    int top = 0;

    Node* cur = N->head;
    while (cur) {
        stack[top++] = cur;
        cur = cur->next;
    }

    printf("%d", stack[top - 1]->bloco);

    for (int i = top - 2; i >= 0; i--) {
        printf("%09d", stack[i]->bloco);
    }

    printf("\n");
}

int choose_option(char* s) {
    if (s[0] == 's') {
        return 1; // soma
    }
    if (s[0] == 'm' && s[1] == 'e') {
        return 2; // menor
    }
    if (s[0] == 'm' && s[1] == 'a') {
        return 3; // maior
    }
    if (s[0] == 'i') {
        return 4; // igual
    }

    return -1;
}

int main() {

    char optionInput[6];
    scanf("%s", optionInput);

    int option = choose_option(optionInput);

    char str1[256], str2[256];
    scanf("%255s", str1);
    scanf("%255s", str2);

    char* s1 = removeZeros(str1);
    char* s2 = removeZeros(str2);

    BigInt* A = converte_str(s1);
    BigInt* B = converte_str(s2);

    if (option == 1) {
        BigInt* R = soma(A, B);
        print_bigint(R);
    }

    if (option == 2) {
        printf(is_less(A, B) ? "True\n" : "False\n");
    }

    if (option == 3) {
        printf(is_greater(A, B) ? "True\n" : "A <= B\n");
    }

    if (option == 4) {
        printf(is_equal(A, B) ? "True\n" : "False\n");
    }

    return 0;
}
