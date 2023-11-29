#include <stdio.h>
#include <stdlib.h>

void printMemory(char *memory, int size) {
    for (int i = 0; i < size; i++) {
        printf("%c ", memory[i]);
    }
    printf("\n");
}

int main() {
    int memorySize;

    printf("Digite a quantidade de memória desejada: ");
    scanf("%d", &memorySize);

    char *memory = (char *)malloc(memorySize * sizeof(char));


    if (memory == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;  
    }

    for (int i = 0; i < memorySize; i++) {
        memory[i] = '.';
    }
    printf("Memória Inicial: ");
    printMemory(memory, memorySize);

    while (1) {
        int ocupacao;

        printf("Digite a quantidade de memória a ser ocupada (-1 para sair, 0 para reset): ");
        scanf("%d", &ocupacao);

        if (ocupacao == -1) {
            break;  
        } else if (ocupacao == 0) {
            for (int i = 0; i < memorySize; i++) {
                memory[i] = '.';
            }
            
            printf("Memória Resetada: ");
            printMemory(memory, memorySize);
            continue;  
        }

        if (ocupacao > memorySize) {
            printf("Erro: A quantidade de memória a ser ocupada excede o tamanho total da memória.\n");
            continue; 
        }

        int espacosDisponiveis = 0;
        for (int i = 0; i < memorySize; i++) {
            if (memory[i] == '.') {
                espacosDisponiveis++;
            }
        }

        if (espacosDisponiveis < ocupacao) {
            printf("Erro: Não há memória suficiente para alocar %d espaços.\n", ocupacao);
            continue; 
        }

       
        for (int i = 0; i < memorySize; i++) {
            if (memory[i] == '.' && ocupacao > 0) {
                memory[i] = '*';
                ocupacao--;
            }
        }

        printf("Memória Após Ocupação: ");
        printMemory(memory, memorySize);

        if (espacosDisponiveis == 0) {
            printf("A memória está completamente ocupada. Não é possível adicionar mais memória.\n");
            break; 
        }
    }

    
    free(memory);

    return 0;
}
