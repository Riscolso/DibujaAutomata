# DibujaAutomata
Convierte un expresión regular en un AF con la ayuda de graphviz. Linux
Se da por hecho que la expresión regular esta bien escrita.

-Plantillas de Thompson, crea un AFN
    Compilar: gcc CT.c
    Generar archivo gv: ./a.out "[Expresión regular]" > atomata.gv
    Dibujar imagen gif: dot automata.gv -Tgif > automata.gif
    
-Algoritmo del árbol, crea un AFD (Aún no funciona, errores de compatibilidad de MinGW con GCC)
    Compilar: gcc CA.c
    Generar archivo gv: ./a.out "[Expresión regular]" > atomata.gv
    Dibujar imagen gif: dot automata.gv -Tgif > automata.gif
