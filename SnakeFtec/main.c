#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int i, j, altura = 20, largura = 20;
int fim, pontuacao;
int x, y, pixelx, pixely, flag;

// Gerar o pixel de pontuação
void setup()
{
	fim = 0;

	x = altura / 2;
	y = largura / 2;
label1:
	pixelx = rand() % 20;
	if (pixelx == 0)
		goto label1;
label2:
	pixely = rand() % 20;
	if (pixely == 0)
		goto label2;
	pontuacao = 0;
}

// Desenhar as bordas e o objeto que será movimentado
void quadro()
{
	system("cls");
	for (i = 0; i < altura; i++) {
		for (j = 0; j < largura; j++) {
			if (i == 0 || i == largura - 1
				|| j == 0
				|| j == altura - 1) {
				printf("+");
			}
			else {
				if (i == x && j == y)
					printf("F");
				else if (i == pixelx
						&& j == pixely)
					printf("*");
				else
					printf(" ");
			}
		}
		printf("\n");
	}

	
	printf("Sua pontuacao = %d", pontuacao);
	printf("\n");
	printf("Aperte Z para sair do jogo");
}

// Função de movimentação
void direcoes()
{
	if (kbhit()) {
		switch (getch()) {
		case 'w':
			flag = 4;
			break;
		case 'a':
			flag = 1;
			break;
		case 's':
			flag = 2;
			break;
		case 'd':
			flag = 3;
			break;	
		case 'z':
			fim = 1;
			break;
		}
	}
}

// Conversão do sleep para milisegundos
int msleep(unsigned int tms) {
  return usleep(tms * 1000);
}

// Movimentação
void movimentacao()
{
	msleep(100);
	switch (flag) {
	case 1:
		y--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y++;
		break;
	case 4:
		x--;
		break;
	default:
		break;
	}

	// Se as bordas foram atingidas
	if (x < 0 || x > altura
		|| y < 0 || y > largura)
		fim = 1;

	// Atualiza a pontuação se a posição for a mesma do pixel
	if (x == pixelx && y == pixely) {
	label3:
		pixelx = rand() % 20;
		if (pixelx == 0)
			goto label3;

	// Gera um novo pixel
	label4:
		pixely = rand() % 20;
		if (pixely == 0)
			goto label4;
		pontuacao += 10;
	}
}

// Método main
void main()
{
	int m, n;

	// Gera o quadro
	setup();
	
	
	// Enquanto o jogo não chegar ao fim
	while (!fim) {		
		quadro();
		direcoes();
		movimentacao();
	}
}

