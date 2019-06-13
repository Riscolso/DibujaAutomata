# DibujaAutomata
Convierte un expresión regular en un AF con la ayuda de graphviz. Linux <br>
Se da por hecho que la expresión regular esta bien escrita. <br>

-Plantillas de Thompson, crea un AFN <br>
    Compilar: gcc CT.c<br>
    Generar archivo gv: ./a.out "[Expresión regular]" > atomata.gv<br>
    Dibujar imagen gif: dot automata.gv -Tgif > automata.gif<br>
    <br>
-Algoritmo del árbol, crea un AFD (Aún no funciona, errores de compatibilidad de MinGW con GCC)<br>
    Compilar: gcc CA.c<br>
    Generar archivo gv: ./a.out "[Expresión regular]" > atomata.gv<br>
    Dibujar imagen gif: dot automata.gv -Tgif > automata.gif<br>
