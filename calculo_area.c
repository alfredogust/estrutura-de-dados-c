#include <stdio.h>
#include <stdlib.h>

// Struct para representar um ponto no plano cartesiano
typedef struct {
    float X;
    float Y;
} Ponto;

// Declaração da função AreaTriangulo
float AreaTriangulo(Ponto A, Ponto B, Ponto C);

// Função para criar o arquivo "vertices.txt" se ele não existir
void CriarArquivoSeNaoExistir() {
    FILE *arquivo = fopen("vertices.txt", "r");
    if (arquivo == NULL) {
        arquivo = fopen("vertices.txt", "w");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo vertices.txt.\n");
            exit(1);
        }
        // Escreva o número de vértices e suas coordenadas fictícias no arquivo
        fprintf(arquivo, "4\n"); // Exemplo: 4 vértices no polígono
        fprintf(arquivo, "0.0 0.0\n"); // Coordenadas dos vértices
        fprintf(arquivo, "1.0 0.0\n");
        fprintf(arquivo, "1.0 1.0\n");
        fprintf(arquivo, "0.0 1.0\n");
        fclose(arquivo);
    } else {
        fclose(arquivo);
    }
}

// Lendo os vértices do polígono de um arquivo
Ponto* LerVertices(int* numVertices) {
    FILE *arquivo;
    char nomeArquivo[] = "vertices.txt";

    CriarArquivoSeNaoExistir(); // Criar o arquivo se ele não existir

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(1);
    }

    fscanf(arquivo, "%d", numVertices);
    Ponto* vertices = (Ponto *)malloc(*numVertices * sizeof(Ponto));
    if (vertices == NULL) {
        printf("Erro ao alocar memória.");
        exit(1);
    }

    for (int i = 0; i < *numVertices; i++) {
        fscanf(arquivo, "%f %f", &vertices[i].X, &vertices[i].Y);
    }

    fclose(arquivo);
    return vertices;
}

// Calculando a área total do polígono
float CalcularAreaPoligono(Ponto* vertices, int numVertices) {
    float areaTotal = 0;
    for (int i = 1; i < numVertices - 1; i++) {
        areaTotal += AreaTriangulo(vertices[0], vertices[i], vertices[i + 1]);
    }
    return areaTotal;
}

// Definição da função AreaTriangulo
float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    float area = (A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y)) / 2.0;
    return (area < 0) ? -area : area; // Garantindo o valor absoluto da área
}

int main() {
    int numVertices;
    Ponto *vertices = LerVertices(&numVertices);
    float areaTotal = CalcularAreaPoligono(vertices, numVertices);

    printf("A área do polígono é: %.2f\n", areaTotal);

    free(vertices);
    return 0;
}
