#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura para representar um bloco de memória
typedef struct Node {
    char data;
    int size;
    struct Node *next;
} Node;

// Função para inicializar a memória aleatoriamente
Node *initializeMemoryRandom(int size) {
    srand(time(NULL));

    Node *memory = NULL;

    for (int i = 0; i < size; i++) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->size = 1;  // Tamanho inicial de cada bloco é 1
        newNode->data = rand() % 2 == 0 ? '.' : '*';
        newNode->next = memory;
        memory = newNode;
    }

    return memory;
}

// Função para liberar toda a memória
void freeMemory(Node *memory) {
    Node *current = memory;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

// Função para alocar memória com First Fit
int allocateMemoryFirstFit(Node *memory, int demand) {
    Node *current = memory;
    while (current != NULL) {
        if (current->data == '.' && current->size >= demand) {
            if (current->size > demand) {
                // Dividir o bloco se for maior que a demanda
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->size = current->size - demand;
                newNode->data = '.';
                newNode->next = current->next;
                current->next = newNode;
                current->size = demand;
            }
            current->data = '*';
            return 1; // Memória alocada com sucesso
        }
        current = current->next;
    }

    return 0; // Não há espaço suficiente
}

// Função para resetar a memória aleatoriamente
Node *resetMemory(Node *memory, int size) {
    freeMemory(memory);
    return initializeMemoryRandom(size);
}

// Função para imprimir a memória
void printMemory(Node *memory) {
    while (memory != NULL) {
        printf("%c ", memory->data);
        memory = memory->next;
    }
    printf("\n");
}

// Função para alocar uma quantidade específica de memória
int allocateMemory(Node *memory, int demand) {
    int totalAllocated = 0;

    while (totalAllocated < demand) {
        if (!allocateMemoryFirstFit(memory, 1)) {
            printf("Erro: Não há memória suficiente para alocar %d unidades.\n", demand);
            break;
        }
        totalAllocated++;
    }

    return totalAllocated;
}

int main() {
    int memorySize;

    printf("Digite a quantidade de memória desejada: ");
    scanf("%d", &memorySize);

    // Inicializando a memória aleatoriamente
    Node *memory = initializeMemoryRandom(memorySize);

    printf("Memória Inicial: ");
    printMemory(memory);

    while (1) {
        int demand;

        printf("Digite a quantidade de memória a ser alocada (-1 para sair, 0 para reset): ");
        scanf("%d", &demand);

        if (demand == -1) {
            break;
        } else if (demand == 0) {
            // Resetar a memória aleatoriamente
            memory = resetMemory(memory, memorySize);

            printf("Memória Resetada: ");
            printMemory(memory);
            continue;
        }

        // Alocar uma quantidade específica de memória
        int totalAllocated = allocateMemory(memory, demand);

        if (totalAllocated > 0) {
            printf("Memória Após Alocar %d unidades (First Fit): ", totalAllocated);
            printMemory(memory);
        }
    }

    // Liberar a memória alocada
    freeMemory(memory);

    return 0;
}
