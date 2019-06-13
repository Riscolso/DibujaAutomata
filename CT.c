//Epsilon
//c.b|(a.b|c+)
//Se acaba el abcedario para los estados
//(a.b|a.c|a.a)+.(a.b)*
//(ab|ac|aa)+(ab)*
//Parentesis (ab|ac|aa)+(ab)*.c
//Comentar
//pruebas

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct pila{
	char c;
	struct pila *s;
};
typedef struct pila pila;

pila *expr = NULL;

//Variable global para dar nombre a los estados
int edo = 1;
//Para letras -  cambiar %d a %c
//char edo = 65;


pila *push(char l, pila *pi);
void verPila(pila *pi);
int jerar(char g, char l);
int esOperador(char c);
void automata();
int com(char c, char c2);


int main(int arg, char* argv[]){
	if(arg<2){
		printf("Faltan parámetros. \nEjemplo (a|b+)");
		return 1;	
	}
	//Pila con la notación
	//pila *p = NULL;
	//Pila auxiliar
	pila *a = NULL;
	
	//Meter los elementos a la pila
	int i=0;
	int e=0;
	char eraux[strlen(argv[1])*2];
	//Es necesario un caracter para denotar la concatenación
	//Así que se agregan
	for(i=0;i<strlen(argv[1]);i++){
		if(!esOperador(argv[1][i]) && !esOperador(argv[1][i+1]) && argv[1][i+1] != '\0'){
			eraux[e] = argv[1][i];
			eraux[++e] = '.';
		}
		else if(argv[1][i] == ')' && argv[1][i+1] != '\0' && !esOperador(argv[1][i+1])){
			eraux[e] = argv[1][i];
			eraux[++e] = '.';
		}
		else if(!esOperador(argv[1][i]) && argv[1][i+1] == '('){
			eraux[e] = argv[1][i];
			eraux[++e] = '.';
		}
		//Usando una función por que no me deja poner todas las condiciones en una sola línea :C
		else if(com(argv[1][i], argv[1][i+1])){
			eraux[e] = argv[1][i];
			eraux[++e] = '.';
		}
		else{
			eraux[e] = argv[1][i];
		}
		e++;
		
	}
	
	char er[e];
	eraux[e] = '\0';
	//printf("Cadena: %s\n", eraux);
	
	//Ya que convertir a postfija invierte los operandos
	//Invertimos primero la cadena
	e=0;
	for(i=strlen(eraux)-1;i>=0;i--){
		//Los parentesis se cambian por su contrario
		if(eraux[i] == '(') er[e] = ')';
		else if(eraux[i] == ')') er[e] = '(';
		else er[e] = eraux[i];
		e++;
	}
	er[e] = 0;
	
	a = push('(', a);
	strcat(er,")");
	
	//Convertir a notación postFija
	for(i=0;i<er[i];i++){
		//printf("interacción %d analizo %c\n", i, er[i]);
		//Si es parentesis izquierdo
		if(er[i]=='(') a = push('(', a);
		
		//Parentesis derecho
		else if(er[i]==')'){
				if(esOperador(a->c)){
					while(a->c!='('){
						expr = push(a->c, expr);
						a = a->s;
					}
					a = a->s; /*Se elimina el parentesis izq*/
				}
			}
		//Si es operador
		else if(esOperador(er[i])){
			do{
				//printf("P->c vale %c\n", p->c);
				if(jerar(er[i],a->c) == 1){
					expr = push(a->c, expr);
					a = a->s;
				}
				else{
					a = push(er[i],a);
					break;
				}
			}while(expr!=NULL);
		}
		//Si es operando
		else expr = push(er[i],expr);
	}
	free(a);
	/*puts("La notación post fija es:");
	verPila(expr);*/
	
	//Dar formato
	puts("digraph AFD {");
	//Primer cículo invisible
	puts("\"\"[style=invis]");
	
	//Rota el Automata
	puts("rankdir=LR;");
	
	//Cambiar óvalos, por círculos
	puts("node[shape=circle];");
	
	//Nodo inicial
	printf("\"\"->%d;\n", edo);
	automata();
	
	//Estado final
	printf("%d[shape=doublecircle]\n", edo);
	puts("}");
	free(expr);
}


//Retorna 1 si es operador 
int esOperador(char c){
	if(c == '|' || c == '(' || c == '*' || c == '+' || c=='.' || c==')') return 1;
	else return 0;
}

int com(char c, char c2){
	if((c == '*' || c == '+') && c2 != ')'){
		if(c2 != '\0' && c2 != '.'){
			return 1;
		}
	}
	return 0;
}

pila *push(char l, pila *pi){
	pila *aux;
	aux = (pila*)malloc(sizeof(pila));
	aux->c = l;
	if(pi == NULL){
		pi = aux;
		pi->s=NULL;
	}	
	else{
		aux->s=pi;
		pi=aux;
	}
	return pi;
}


void verPila(pila *pi){
	pila *ptrRec;
	if(pi == NULL) puts("La pila está vacía");
	else {
		ptrRec = pi;
		//printf("Los elementos son: ");
		while(ptrRec!=NULL){
			printf(" %c ", ptrRec->c);
			ptrRec = ptrRec->s;
		}
	puts("");
	}
}

//Analizar, pila
int jerar(char g, char l){
	if(g == l) return 1;
	else if (l == '(' || l == ')') return 0;
	else if(g=='|') return 1;
	else if(g == '.' && l != '|') return 1;
	else if(g == '+' || g == '*') return 0;
	else return 0;
}

//Función recursiva para imprimir
void automata(){
	if(expr == NULL) printf("Changos, algo salió mal, la pila esta vacía :c\n");
	else{
		if(expr->c == '|'){
			int in, fi;
			in = edo;
			printf("%d -> %d [label=\"&epsilon;\"];\n", in, ++edo);
			expr = expr->s;
			automata();
			fi = edo;
			printf("%d -> %d [label=\"&epsilon;\"];\n", in, ++edo);
			expr = expr->s;
			automata();
			printf("%d -> ", edo);
			printf("%d [label=\"&epsilon;\"];\n", ++edo);
			printf("%d -> %d [label=\"&epsilon;\"];\n", fi, edo);
		}
		else if(expr->c == '*'){
			int m, c;
			m = edo;
			printf("%d -> %d [label=\"&epsilon;\"];\n", m, ++edo);
			c = edo;
			expr = expr->s;
			automata();
			printf("%d -> %d [label=\"&epsilon;\"];\n", edo, c);
			printf("%d -> ", edo);
			printf("%d [label=\"&epsilon;\"];\n", ++edo);
			printf("%d -> %d [label=\"&epsilon;\"];\n", m, edo);
		}
		else if(expr->c == '+'){
			int m;
			printf("%d -> ", edo);
			printf("%d [label=\"&epsilon;\"];\n", ++edo);
			m = edo;
			expr = expr->s;
			automata();
			printf("%d -> %d [label=\"&epsilon;\"];\n", edo, m);
			printf("%d -> ", edo);
			printf("%d [label=\"&epsilon;\"];\n", ++edo);
		}
		
		else if(expr->c == '.'){
			expr = expr->s;
			automata();
			expr = expr->s;
			automata();
		}
		else if(expr->c == 'E'){
			printf("%d ->", edo);
			printf("%d [label=\"&epsilon;\"];\n", ++edo);
		}
		//Caso base - si es un símbolo 
		else{
			//Se dividen los printf por que sino toma el valor de ++edo en los
			//dos casos >:C
			printf("%d ->", edo);
			printf(" %d [label=%c];\n",++edo, expr->c);
		}
	}
}

