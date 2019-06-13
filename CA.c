//llenar tam
//free ptr
//problema si se llama varias veces realloc
//Error sí se acaba la expresión en un parentesis

//Epsilon

//c.b|(a.b|c+)
//Se acaba el abcedario para los estados
//(a.b|a.c|a.a)+.(a.b)*
//(ab|ac|aa)+(ab)*
//(a|ab|c+b)*
//((ab+c|ab+c*a|(cba)+)*(b|c*))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pila{
	char c;
	struct pila *s;	
};
typedef struct pila pila;

typedef struct nodo nodo;
struct nodo{
	//Tamaño primeros
	//Tamaño finales
	int tp, tf;
	int* pri;
	int* fin;
	int anu;
	nodo* izq;
	nodo* der;
};

struct tablaS{
	//Número
	int no;
	//posición
	char p;
	//Siguientes
	int *s;
	//tamaño
	int t;
};
typedef struct tablaS tablaS;
tablaS *ts;

pila *expr = NULL;

//Variable global para los estados y para el número de nodos
int edo = 1;
//Para letras -  cambiar %d a %c
//char edo = 65;

void impriC(char* c, int t);
pila *push(char l, pila *pi);
void verPila(pila *pi);
int jerar(char g, char l);
int esOperador(char c);
int com(char c, char c2);
nodo* arbol();
nodo *crearNodo();
int *conAr(int *a, int t1, int *b, int t2);
void imprA(int *a, int t);
int *quitarRep(int *a, int t, int e);
int tiene(int a, int *b, int t);
int tieneC(char a, char *b, int t);
int tieneVector(tablaS* si, int ts, int* b, int t);


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
	int e=1;
	char eraux[(strlen(argv[1])*2)+1];
	//Ya que se va a extender el árbol se necesita poner un parentesis para saber qué parte es la ER normal
	//Esto para que el sígno extendido no se confunda
	eraux[0] = '(';
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
		//Usando una funciï¿½n por que no me deja poner todas las condiciones en una sola lï¿½nea :C
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
	//Agregar símbolo de terminación
	strcat(eraux, ").#");
	printf("Cadena: %s\n", eraux);
	
	//Obtener la cantidad de operandos que hay
	e=0;
	for(i=0;i<strlen(eraux);i++){
		if(!esOperador(eraux[i])) e++;
	}
	//Reservar espacio para las posiciones de la tabla de los siguientes
	ts = (tablaS *)malloc(sizeof(tablaS)*e);
	//Inicializar los tamaï¿½os del arreglo
	printf("TamaÃ±o %d\n", e);
	for(i=0;i<e;i++) ts[i].t = 0;
	
	
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
	
	//Convertir a notaciÃ³n postFija
	for(i=0;i<er[i];i++){
		//printf("interacciï¿½n %d analizo %c\n", i, er[i]);
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
	puts("La notaciÃ³n post fija es:");
	verPila(expr);
	free(expr);
	nodo *n = NULL;
	n = arbol();/*
	//Obtener el estado inicial
	int *a = n->pri;
	//Obtener el tamaï¿½o del estado principal
	int t = n->tp;
	//Quitar repeticiones en la tabla de los siguientes
	for(i=1;i<edo;i++){
		ts[i].s = quitarRep(ts[i].s, ts[i].t, i);
	}
	//Obtener el nï¿½mero de caracteres
	int car;
	for(i=1;i<edo;i++) if( 
	*obtenerPos(char c, int* q)
	*/
	printf("Tabla de los siguientes\n");
	printf("Nodo\tPosicion\tSiguiente\n");
	for(i=1;i<edo;i++){
		printf("%c\t%d\t\t", ts[i].p,i);
		for(e=0;e<ts[i].t;e++){
			printf("%d ", ts[i].s[e]);
		}
		printf("\n");
	}
	//free(ts);
	
	//aqui
	//Arreglo con los simbolos
	char *nd = (char*)malloc(sizeof(char)*edo);
	
	puts("Arreglo de nodos");
	//Arreglo con los nodos sin repeticiones
	int tnd=0;
	for(i = 1;i<edo;i++){
		if(!tieneC(ts[i].p,nd, edo)){
			nd[tnd] = ts[i].p;
			tnd++;	
		}
	}
	tablaS *estados = (tablaS*)malloc(sizeof(tablaS)*30);
	int tamEdos=1, j;
	i=1;
	int k=0;
	//Establecer el estados inicial
	
	estados[0].s = conAr(estados[0].s, 0, n->pri, n->tp);
	estados[0].t = n->tp;
	estados[0].no = 0;
	int q=0;
	
	//Dar formato
	puts("digraph AFD {");
	//Primer cï¿½culo invisible
	puts("\"\"[style=invis]");
	
	//Rota el Automata
	puts("rankdir=LR;");
	
	//Cambiar ï¿½valos, por cï¿½rculos
	puts("node[shape=circle];");
	
	//Nodo inicial
	printf("\"\"->0;\n");
	
	//Determinar si es un estado final o no
	if(tiene(edo, estados[0].s, estados[0].t)) printf("%d[shape=doublecircle]\n",0);
	
	do{
		//estados[i].t = 0;
		for(e=0;e<tnd;e++){
			//Bandera para saber si se creï¿½ un nuevo estado
			int b=0, ta=0;
			int *aux = NULL;
			for(j=1;j<edo;j++){
				//printf("Soy k=%d\n",k);
				//printf("Estoy analizando con k = %d\t", k);
				//imprA(estados[k].s, estados[k].t);
				//puts("");
				if(ts[j].p == nd[e] && tiene(j, estados[k].s, estados[k].t)){
					//Si hay siguientes y no se ha creado el estado en la tabla
					if(!b){ 
						b=1;
						//printf("Se encontro un nuevo estado\n");
						//estados = (tablaS*)realloc(estados, sizeof(tablaS)*tamEdos);
						//estados[tamEdos].t = 0;
					}
					aux = conAr(aux, ta, ts[j].s, ts[j].t);
					ta = ta + ts[j].t;
					//imprA(aux, ta);
					//estados[tamEdos].s = conAr(estados[tamEdos].s, estados[tamEdos].t, ts[j].s, ts[j].t);
					//puts("Entra");
					//estados[tamEdos].t = estados[tamEdos].t + ts[j].t;
					//printf("Meti con tamEdos=%d\t", tamEdos);
					//imprA(estados[tamEdos].s, estados[tamEdos].t);			
				}
			}
			//Si se creó un estado en auxiliar
			if(b){
				int l = tieneVector(estados, tamEdos, aux, ta);
				//Si ya se había encontrado uno igual
				if(l!=-1) printf("%d -> %d [label=\"%c\"];\n",k,l,nd[e]);
				//Si es un estado nuevo
				else{
					i++;
					//printf("Nuevo estado descubierto %d\n", tamEdos);
					estados[tamEdos].s = conAr(estados[tamEdos].s, 0, aux, ta);
					estados[tamEdos].t = ta;
					printf("%d -> %d [label=\"%c\"];\n", k, tamEdos, nd[e]);
					//Determinar si es un estado final o no
					if(tiene(edo, aux, ta)) printf("%d[shape=doublecircle]\n",tamEdos);
					tamEdos++;
				}
			}
		}
		k++;
		i--;
	}while(i>0);
	puts("}");
	
	printf("Tabla de estados\n");
	for(i=0;i< tamEdos;i++){
		imprA(estados[i].s, estados[i].t);
	}
	
	/*
	//Dar formato
	puts("digraph AFD {");
	//Primer cï¿½culo invisible
	puts("\"\"[style=invis]");
	
	//Rota el Automata
	puts("rankdir=LR;");
	
	//Cambiar ï¿½valos, por cï¿½rculos
	puts("node[shape=circle];");
	
	//Nodo inicial
	printf("\"\"->%d;\n", edo);
	automata();
	
	//Estado final
	printf("%d[shape=doublecircle]\n", edo);
	puts("}");
	free(expr);*/
}

//Recibe un arreglo de tablaS, su tamaño, un vector de enteros y su tamaño
//Regresa la posición si uno de los arreglos de tablaS es igual a b, si no -1
int tieneVector(tablaS* si, int ts, int* b, int t){
	int i=0, e=0, j=0, ba=1;
	for(i=0;i<ts;i++){
		//Si tienen diferente tamaño no pueden ser iguales
		if(si[i].t == t){
			for(e=0;e<si[i].t;e++){
				if(si[i].s[e] != b[e]) ba=0;
				if(ba) return i;
			}
		}
	}
	return -1;
}

void impriC(char* c, int t){
	int i=0;
	for(i=0;i<t;i++) printf("%d \n", c[i]);
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
	if(pi == NULL) puts("La pila estï¿½ vacï¿½a");
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



//Funciï¿½n recursiva que genera el ï¿½rbol
nodo* arbol(){
	//printf("Analizando %c", expr->c);
	if(expr == NULL){
		printf("Changos, algo saliï¿½ mal, la pila esta vacï¿½a :c\n");
		nodo *n;
		n = crearNodo();
		return n;
	}	
	else{
		if(expr->c == '|'){
			nodo* n;
			n = crearNodo();
			//Obtener nodo izquierdo
			expr = expr->s;
			n->izq = arbol();
			//Obtener nodo derecho
			expr = expr->s;
			n->der = arbol();
			//Esteblecer datos del nodo actual
			//Si el nodo izquierdo y derecho no son anulables
			if(!n->izq->anu && !n->der->anu) n->anu = 0;
			else n-> anu = 1;
			
			//Concatenar primeros de izq con primeros de derecha
			n->pri = conAr(n->pri, 0, n->izq->pri, n->izq->tp);
			n->pri = conAr(n->pri, n->izq->tp, n->der->pri, n->der->tp);
			//Nuevo tamaï¿½o
			n->tp = n->izq->tp + n->der->tp;
				
			//Concatenar finales de izq con finales de derecha
			n->fin = conAr(n->fin, 0, n->izq->fin, n->izq->tf);
			
			//imprA(n->der->fin, n->der->tf);
			n->fin = conAr(n->fin, n->izq->tf, n->der->fin, n->der->tf);
			//Nuevo tamaï¿½o
			n->tf = n->izq->tf + n->der->tf;
			
			printf("Datos de |\n");
			printf("	INICIO: ");
			imprA(n->pri, n->tp);
			
			printf("	FIN: ");
			imprA(n->fin, n->tf);
			if(n->anu) puts("Anulable");
			else puts("Nope");
			return n;
		}
		else if(expr->c == '*'){
			nodo* n;
			n = crearNodo();
			//Obtener nodo hijo
			expr = expr->s;
			n->izq = arbol();
			//Esteblecer datos del nodo actual
			n->anu = 1;
			//Los principales y finales son los mismos que el hijo
			n->pri = n->izq->pri;
			n->tp = n->izq->tp;
			n->fin = n->izq->fin;
			n->tf = n->izq->tf;
			int i;
			for(i=0;i<n->tf;i++){
				//Obtener posiciï¿½n
				int aux = n->fin[i];
				//Meter en la posiciï¿½n los elementos primeros del nodo derecho
				ts[aux].s = conAr(ts[aux].s, ts[aux].t, n->pri, n->tp);
				//Actualizar tamaï¿½o
				ts[aux].t = n->tp+ts[aux].t;
			}
			printf("Datos de *\n");
			printf("	INICIO: ");
			imprA(n->pri, n->tp);
			
			printf("	FIN: ");
			imprA(n->fin, n->tf);
			if(n->anu) puts("Anulable");
			else puts("Nope");
			return n;
		}
		else if(expr->c == '+'){
			nodo* n;
			n = crearNodo();
			//Obtener nodo hijo
			expr = expr->s;
			n->izq = arbol();
			//Esteblecer datos del nodo actual
			//Si el nodo hijo es anulable
			n->anu = 0;
			//Los principales y finales son los mismos que el hijo
			n->pri = n->izq->pri;
			n->tp = n->izq->tp;
			n->fin = n->izq->fin;
			n->tf = n->izq->tf;
			//Tabla de los siguientes
			int i;
			for(i=0;i<n->tf;i++){
				//Obtener posiciï¿½n
				int aux = n->fin[i];
				//Meter en la posiciï¿½n los elementos primeros del nodo derecho
				ts[aux].s = conAr(ts[aux].s, ts[aux].t, n->pri, n->tp);
				//Actualizar tamaï¿½o
				ts[aux].t = n->tp+ts[aux].t;
			}
			printf("Datos de +\n");
			printf("	INICIO: ");
			imprA(n->pri, n->tp);
			
			printf("	FIN: ");
			imprA(n->fin, n->tf);
			if(n->anu) puts("Anulable");
			else puts("Nope");
			return n;
		}
		
		else if(expr->c == '.'){
			nodo* n;
			n = crearNodo();
			//Obtener nodo izquierdo
			expr = expr->s;
			n->izq = arbol();
			//Obtener nodo derecho
			expr = expr->s;
			n->der = arbol();
			//Tabla de los siguientes
			int i;
			for(i=0;i<n->izq->tf;i++){
				//Obtener posiciï¿½n
				int aux = n->izq->fin[i];
				//Meter en la posiciï¿½n los elementos primeros del nodo derecho
				ts[aux].s = conAr(ts[aux].s, ts[aux].t, n->der->pri, n->der->tp);
				//Actualizar tamaï¿½o
				ts[aux].t = n->der->tp+ts[aux].t;
			}
			//Esteblecer datos del nodo actual
			//Si el nodo izquierdo y derecho son anulables
			if(n->izq->anu && n->der->anu){
				//Concatenar primeros de izq con primeros de derecha
				n->pri = conAr(n->pri, 0, n->izq->pri, n->izq->tp);
				n->pri = conAr(n->pri, n->izq->tp, n->der->pri, n->der->tp);
				//Nuevo tamaï¿½o
				n->tp = n->izq->tp + n->der->tp;
				
				//Concatenar finales de izq con finales de derecha
				n->fin = conAr(n->fin, 0, n->izq->fin, n->izq->tf);
				n->fin = conAr(n->fin, n->izq->tf, n->der->fin, n->der->tf);
				//Nuevo tamaï¿½o
				n->tf = n->izq->tf + n->der->tf;
				
				//Anulabilidad
				n->anu = 1;
			}
			
			//Si el izq es anulable y el derecho no
			else if(n->izq->anu && !n->der->anu){
				//Concatenar primeros de izq con primeros de derecha
				n->pri = conAr(n->pri, 0, n->izq->pri, n->izq->tp);
				n->pri = conAr(n->pri, n->izq->tp, n->der->pri, n->der->tp);
				//Nuevo tamaï¿½o
				n->tp = n->izq->tp + n->der->tp;
				
				//Solo finales de derecha
				n->fin = conAr(n->fin, 0, n->der->fin, n->der->tf);
				//Nuevo tamaï¿½o
				n->tf = n->der->tf;
				//Anulabilidad
				n->anu = 0;
			}			
			//Si el izq = no anu y el der = anu
			else if(!n->izq->anu && n->der->anu){
				//Solo principales de la izquierda
				n->pri = conAr(n->pri, 0, n->izq->pri, n->izq->tp);
				//Nuevo tamaï¿½o
				n->tp = n->izq->tp;
				
				//Concatenar finales de izq con finales de derecha
				n->fin = conAr(n->fin, 0, n->izq->fin, n->izq->tf);
				n->fin = conAr(n->fin, n->izq->tf, n->der->fin, n->der->tf);
				//Nuevo tamaï¿½o
				n->tf = n->izq->tf + n->der->tf;
				//Anulabilidad
				n->anu = 0;
			}
			//Si ninguno es anulable
			else{
				//Solo principales de la izquierda
				n->pri = conAr(n->pri, 0, n->izq->pri, n->izq->tp);
				//Nuevo tamaï¿½o
				n->tp = n->izq->tp;
				
				//Solo finales de derecha
				n->fin = conAr(n->fin, 0, n->der->fin, n->der->tf);
				//Nuevo tamaï¿½o
				n->tf = n->der->tf;
				//Anulabilidad
				n->anu = 0;
			}
			printf("Datos de .\n");
			printf("	INICIO: ");
			imprA(n->pri, n->tp);
			
			printf("	FIN: ");
			imprA(n->fin, n->tf);
			if(n->anu) puts("Anulable");
			else puts("Nope");
			return n;
		}
		else if(expr->c == 'E'){
			printf("%d ->", edo);
			printf("%d [label=\"&epsilon;\"];\n", ++edo);
		}
		//Caso base - si es un sï¿½mbolo 
		else{
			nodo *n;
    		n = crearNodo();
			n->pri = (int *)malloc(sizeof(int));
			n->tp = 1; 
			n->pri[0] = edo;
			n->fin = (int *)malloc(sizeof(int));
			n->tf=1;
			n->fin[0] = edo;
			//Guardar caracter en la tabla de los siguientes
			//# no tiene posiciï¿½n
			if(expr->c!='#'){
				ts[edo].p = expr->c;
				edo++;
			}
			//Anulable 1, no anulable 0
			n->anu = 0;
			printf("Datos de %c\n", expr->c);
			printf("	INICIO: ");
			imprA(n->pri, n->tp);
			
			printf("	FIN: ");
			imprA(n->fin, n->tf);
			if(n->anu) puts("Anulable");
			else puts("Nope");
			return n;
		}
	}
}

nodo *crearNodo(){
	nodo* n;
	n = (nodo*)malloc(sizeof(nodo));
    n->izq = NULL;
    n->der = NULL;
    return n;
}

void imprA(int *a, int t){
	int i;
	for(i=0;i<t;i++){
		printf("%d ", a[i]);
	}
	puts("");
}

void imprAC(char *a, int t){
	int i;
	for(i=0;i<t;i++){
		printf("%c ", a[i]);
	}
	puts("");
}

//Concatenar a+b
int *conAr(int *a, int t1, int *b, int t2){
	int *aux;
	aux = (int *)malloc(sizeof(int)*(t1+t2));
	int i=0, e=0;
	for(i=0;i<t1;i++) aux[i] = a[i];
	if(t1==0) i=0;
	for(e=0;e<t2;e++){
		aux[i] = b[e];
		i++;
	}
	return aux;
} 

int *quitarRep(int *a, int t, int e){
	int *aux;
	int k=0, j=0, i;
	for(i = 0; i < t; i++){
		for(j = i+1; j < t; j++){
			if(a[i] == a[j]){
				k = j;
				while(k < t){
					a[k] = a[k+1];
					++k;
				}
				--t;
				--j;
			}
		}
	}
	ts[e].t = t;
	return a;
}

//Obtiene las posiciones de ts respecto a un caracter
int *obtenerPos(char c, int* q){
	int *aux;
	int i;
	//Variable global
	*q=0;
	for(i=1;i<edo;i++)
		if(ts[i].p == c){
			aux[*q] = i;
			*q = *q+1;
		}
	return aux;
}

int tiene(int a, int *b, int t){
	int i;
	for(i=0;i<t;i++) if(a==b[i]) return 1;
	return 0;
}


int tieneC(char a, char *b, int t){
	int i;
	for(i=0;i<t;i++) if(a==b[i]) return 1;
	return 0;
}
