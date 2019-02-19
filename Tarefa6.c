#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reg celula;

struct reg {
	char conteudo [30];
	celula *prox;
};

celula *list;

// recebe a cabeça de uma lista
// e imprime o conteudo dela

void imprime (celula *le) {
	if (le == NULL) printf("\n");
	else {
		printf("%s ", le->conteudo);
		imprime (le->prox);
	}
}

// recebe uma string e a cabela de uma lista
// e insere a string na lista

void insere (celula *le, char palavra[]) {
	celula *nova = malloc (sizeof (celula));
	strcpy (nova->conteudo, palavra);
	if (le->prox == NULL) {
		nova->prox = le->prox;
		le->prox = nova;
	} else {
		celula *p = le->prox;
		while (p->prox != NULL) p = p->prox;
		nova->prox = p->prox;
		p->prox = nova;
	}
}


// recebe a cabeça de um pilha e um string
// e insere a string na pilha

void empilha (celula *pi, char palavra []){
	celula *nova = malloc (sizeof (celula));
	strcpy (nova->conteudo, palavra);
	nova->prox = pi->prox;
	pi->prox = nova;
}

// recebe a cabeça de uma lista encadeada e um 
// inteiro n, e faz a busca de um conteudo na
// celula n

void busca_na_lista (celula *le, int num) {
	celula *p = le->prox;
	char x[30];
	int i = 0;
	int a = -1;

	while (p != NULL) {
		a++;
		p = p->prox;
	}

	p = le->prox;

	while (p != NULL) {
		if (a == num) break;
		else {
			a--;
			p = p->prox;
		}
	}

	if (a == num) {
		for (int cont = 0; cont <= strlen (p->conteudo); cont++) {
			if ((p->conteudo[cont] >= 'A' && p->conteudo[cont] <= 'Z') || (p->conteudo[cont] >= 'a' && p->conteudo[cont] <= 'z') || p->conteudo[cont] == ' ') {
				x[i] = p->conteudo[cont];
				i++;
				x[i] = '\0';
			} else if (p->conteudo[cont] >= '0' && p->conteudo[cont] <= '9') {
				insere (list, x);
				int n = p->conteudo[cont] - '0';
				busca_na_lista (le, n);
				strcpy (x, "");
				i = 0;
			} 
		}
		insere (list, x);
	}
}

// recebe a cabeça de uma pilha e de uma lista
// e desempilha o conteudo da pilha na lista

celula *desempilha (celula *pi, celula *le) {
	char x[30];
	x[0] = '\0';
	int i = 0;
	int num = 0;
	celula *p = pi->prox;
	for (int cont = 0; cont <= strlen (p->conteudo); cont++) {
		if ((p->conteudo [cont] >= 'a' && p->conteudo[cont] <= 'z') || (p->conteudo [cont] >= 'A' && p->conteudo[cont] <= 'Z') || p->conteudo[cont] == ' ') {
			x[i] = p->conteudo[cont];
			i++;
			x[i] = '\0';
		} else if (p->conteudo[cont] >= '0' && p->conteudo[cont] <= '9') {
			insere (list, x);
			num = p->conteudo[cont] - '0';
			busca_na_lista (le, num);
			strcpy (x, "");
			i = 0;
		} 
	}
	insere (list, x);
	pi->prox = p->prox;
	free (p);
	return pi;
}

// recebe a cabeça de uma pilha e de uma lista
// e devolve um arquivo de texto ascii ordenado
// sem as palvras especiais

void arquivo_ascii (celula *pi, celula *le) {
	celula *p = le->prox;

	while (p != NULL) {
		empilha (pi, p->conteudo);
		p = p->prox;
	}

	p = le->prox;

	while (pi->prox != NULL) {
		 pi = desempilha(pi, le);
	}
}

int main () {
	celula *le = malloc (sizeof (celula));
	celula *pi = malloc (sizeof (celula));
	list = malloc (sizeof (celula));

	list->prox = NULL;
	le->prox = NULL;
	pi->prox = NULL;

	insere (le, "GG hhh");
	insere (le, "FF #2 #4");
	insere (le, "CC #4 DDD #1 ee");
	insere (le, "bbb");
	insere (le, "#4 aaa #2");

	arquivo_ascii (pi, le);

	printf("\n");

	imprime (le->prox);

	imprime (list->prox);


return 0;	
}