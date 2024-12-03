cmake_minimum_required(VERSION 3.28)
project(Algoritmos_y_Estructura_de_Datos)

set(CMAKE_CXX_STANDARD 20)

add_executable(Algoritmos_y_Estructura_de_Datos main.cpp
        Sem2_Listas_Enlazadas_Simples/Teoria_26_08.cpp
        Sem_3_Listas_Dobles/Teoria_02_08.cpp
        Sem2_Listas_Enlazadas_Simples/Lab1_27_08.cpp
        Sem_4_Pilas_Colas_Iteradores/Teoria_PILAS_09_09.cpp
        Sem_4_Pilas_Colas_Iteradores/Teoria_COLAS_09_09.cpp
        Sem_4_Pilas_Colas_Iteradores/Teoria_COLAS_CIRCULARES_09_09.cpp
        Sem_5_Tablas_Hash/Teoria_HashTable_16_09.cpp
        Sem_6_BST_ArbolBinario/Teoria_23_09.cpp
        Sem_6_BST_ArbolBinario/forwardlist_to_bst.cpp
        Sem_6_BST_ArbolBinario/array_to_bst.cpp
        Sem_6_BST_ArbolBinario/validate_BST.cpp
        Sem_6_BST_ArbolBinario/BST_iterator.cpp
        Sem_7_AVL_Tree/Teoria_30_09.cpp
        Sem_7_AVL_Tree/node.h
        Grafos/Grafos.cpp
        Grafos/Grafos.h
        ArbolBinario/ArbolBinario.h
        ArbolBinario/ArbolBinario.cpp
        Recorridos/BFS.cpp
        Recorridos/BFS.h
        Recorridos/DFS.h
        Recorridos/DFS.cpp
        CaminoMinimos/BellmanFord.h
        CaminoMinimos/BellmanFord.cpp
        CaminoMinimos/FloydWarshall.h
        CaminoMinimos/FloydWarshall.cpp
        MST/Prim.cpp
        MST/Kruskal.cpp
        Tries/Tries.h
        Tries/Tries.cpp
        ArbolesB/ArbolB+.cpp
        ArbolesB/ArbolB.cpp
        SparseMatrix/SparseMatrix.cpp
        Algoritmos/A+.cpp
        Algoritmos/OrdenamientoTopologico.cpp
        CaminoMinimos/Djikstra.h
        CaminoMinimos/Djikstra.cpp
        ArbolBinario/InOrder.cpp
        ArbolBinario/PostOrder.cpp
        tmy0909/NetworkDelayTime.cpp
        "tmy0909/Detect Negative Cycle in Graph .cpp"
        tmy0909/NumeroIslas.cpp
        tmy0909/ClonarGraph.cpp
        tmy0909/PlanEstudios.cpp
        tmy0909/EscaleraPalabras.cpp
        tmy0909/GrafoArbolValido.cpp
        tmy0909/CaminoMasCortoMatrizBinaria.cpp
        tmy0909/DiccionarioAlienigena.cpp
        tmy0909/MinimumHeightTrees.cpp
        tmy0909/AllPathToTarget.cpp
        tmy0909/EsBipartito.cpp
        tmy0909/ConexionRedundante.cpp
        tmy0909/JuezDelPueblo.cpp
        tmy0909/CiudadZero.cpp
        tmy0909/CaminoCortoNoPonderado.cpp
        tmy0909/CicloGrafoDirigido.cpp
        tmy0909/NodosAlcanzablesFuente.cpp
        tmy0909/CicloGrafoNodirigido.cpp)
