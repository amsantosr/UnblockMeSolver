#include "Aplicacion.h"
#include <QTextStream>

Aplicacion::Aplicacion()
    : salida(stdout, QIODevice::WriteOnly)
{
}

void Aplicacion::ejecutar()
{
    leerPuzzle();
    if (resolverPuzzle())
        mostrarSolucion();
    else
        salida << "No se pudo resolver el puzzle.\n";
}

void Aplicacion::leerPuzzle()
{
    puzzle.clear();
    puzzle.append({ 0, 3, 2, Vertical });
    puzzle.append({ 0, 4, 2, Horizontal });
    puzzle.append({ 1, 2, 2, Vertical });
    puzzle.append({ 1, 5, 2, Vertical });
    puzzle.append({ 2, 0, 2, Horizontal });
    puzzle.append({ 2, 3, 2, Vertical });
    puzzle.append({ 2, 4, 3, Vertical });
    puzzle.append({ 3, 0, 2, Horizontal });
    puzzle.append({ 3, 5, 2, Vertical });
    puzzle.append({ 4, 0, 2, Vertical });
    puzzle.append({ 4, 1, 3, Horizontal });
    numeroPiezas = puzzle.size();
}

bool Aplicacion::resolverPuzzle()
{
    QMap<Estado, Camino> mapEstados;
    QVector<Estado> pila1, pila2;
    Estado estadoHijo;
    int distancia;

    mapEstados.insert(QVector<int>(numeroPiezas, 0), QVector<Movimiento>());
    pila1.append(QVector<int>(numeroPiezas, 0));

    do {
        pila2.clear();
        for (const Estado &estadoPadre : pila1) {
            for (int i = 0; i < numeroPiezas; ++i) {
                if (puzzle[i].direccion == Horizontal) {
                    estadoHijo = estadoPadre;
                    distancia = 0;
                    while (moverIzquierda(estadoHijo, i)) {
                        --distancia;
                        if (mapEstados.find(estadoHijo) == mapEstados.end()) {
                            pila2.append(estadoHijo);
                            mapEstados[estadoHijo] = mapEstados[estadoPadre];
                            mapEstados[estadoHijo].append({ i, distancia });
                        }
                    }
                    estadoHijo = estadoPadre;
                    distancia = 0;
                    while (moverDerecha(estadoHijo, i)) {
                        ++distancia;
                        if (mapEstados.find(estadoHijo) == mapEstados.end()) {
                            pila2.append(estadoHijo);
                            mapEstados[estadoHijo] = mapEstados[estadoPadre];
                            mapEstados[estadoHijo].append({ i, distancia });
                            if (puzzle[i].fila == 2 && puzzle[i].columna + estadoHijo[i] == 4) {
                                solucion = mapEstados[estadoHijo];
                                return true;
                            }
                        }
                    }
                }
                else if (puzzle[i].direccion == Vertical) {
                    estadoHijo = estadoPadre;
                    distancia = 0;
                    while (moverArriba(estadoHijo, i)) {
                        --distancia;
                        if (mapEstados.find(estadoHijo) == mapEstados.end()) {
                            pila2.append(estadoHijo);
                            mapEstados[estadoHijo] = mapEstados[estadoPadre];
                            mapEstados[estadoHijo].append({ i, distancia });
                        }
                    }
                    estadoHijo = estadoPadre;
                    distancia = 0;
                    while (moverAbajo(estadoHijo, i)) {
                        ++distancia;
                        if (mapEstados.find(estadoHijo) == mapEstados.end()) {
                            pila2.append(estadoHijo);
                            mapEstados[estadoHijo] = mapEstados[estadoPadre];
                            mapEstados[estadoHijo].append({ i, distancia });
                        }
                    }
                }
            }
        }
        pila1.swap(pila2);
    } while (!pila1.empty());
    return false;
}

void Aplicacion::mostrarSolucion()
{
    int numeroMovimiento = 1;
    for (const auto &movimiento : solucion) {
        salida << numeroMovimiento << ": " << "[" << movimiento.indicePieza << ", " << movimiento.distancia << "]\n";
        ++numeroMovimiento;
    }
}

bool Aplicacion::moverIzquierda(Aplicacion::Estado &estado, int indicePieza) const
{
    const auto &pieza = puzzle[indicePieza];
    int nuevaColumna = pieza.columna + estado[indicePieza] - 1;
    if (nuevaColumna < 0)
        return false;
    for (int i = 0; i < numeroPiezas; ++i) {
        if (i != indicePieza) {
            const auto &piezaI = puzzle[i];
            if (piezaI.direccion == Horizontal) {
                if (pieza.fila == piezaI.fila && nuevaColumna == piezaI.columna + estado[i] + piezaI.longitud - 1)
                    return false;
            }
            else if (piezaI.direccion == Vertical) {
                if (nuevaColumna == piezaI.columna) {
                    int filaI = piezaI.fila + estado[i];
                    if (pieza.fila >= filaI && pieza.fila < filaI + piezaI.longitud)
                        return false;
                }
            }
        }
    }
    --estado[indicePieza];
    return true;
}

bool Aplicacion::moverDerecha(Aplicacion::Estado &estado, int indicePieza) const
{
    const auto &pieza = puzzle[indicePieza];
    int nuevaColumna = pieza.columna + estado[indicePieza] + pieza.longitud;
    if (nuevaColumna >= 6)
        return false;
    for (int i = 0; i < numeroPiezas; ++i) {
        if (i != indicePieza) {
            const auto &piezaI = puzzle[i];
            if (piezaI.direccion == Horizontal) {
                if (pieza.fila == piezaI.fila && nuevaColumna == piezaI.columna + estado[i])
                    return false;
            }
            else if (piezaI.direccion == Vertical) {
                if (nuevaColumna == piezaI.columna) {
                    int filaI = piezaI.fila + estado[i];
                    if (pieza.fila >= filaI && pieza.fila < filaI + piezaI.longitud)
                        return false;
                }
            }
        }
    }
    ++estado[indicePieza];
    return true;
}

bool Aplicacion::moverArriba(Aplicacion::Estado &estado, int indicePieza) const
{
    const auto &pieza = puzzle[indicePieza];
    int nuevaFila = pieza.fila + estado[indicePieza] - 1;
    if (nuevaFila < 0)
        return false;
    for (int i = 0; i < numeroPiezas; ++i) {
        if (i != indicePieza) {
            const auto &piezaI = puzzle[i];
            if (piezaI.direccion == Horizontal) {
                if (nuevaFila == piezaI.fila) {
                    int columnaI = piezaI.columna + estado[i];
                    if (pieza.columna >= columnaI && pieza.columna < columnaI + piezaI.longitud)
                        return false;
                }
            }
            else if (piezaI.direccion == Vertical) {
                if (pieza.columna == piezaI.columna && nuevaFila == piezaI.fila + estado[i] + piezaI.longitud - 1)
                    return false;
            }
        }
    }
    --estado[indicePieza];
    return true;
}

bool Aplicacion::moverAbajo(Aplicacion::Estado &estado, int indicePieza) const
{
    const auto &pieza = puzzle[indicePieza];
    int nuevaFila = pieza.fila + estado[indicePieza] + pieza.longitud;
    if (nuevaFila >= 6)
        return false;
    for (int i = 0; i < numeroPiezas; ++i) {
        if (i != indicePieza) {
            const auto &piezaI = puzzle[i];
            if (piezaI.direccion == Horizontal) {
                if (nuevaFila == piezaI.fila) {
                    int columnaI = piezaI.columna + estado[i];
                    if (pieza.columna >= columnaI &&pieza.columna < columnaI + piezaI.longitud)
                        return false;
                }
            }
            else if (piezaI.direccion == Vertical) {
                if (pieza.columna == piezaI.columna && nuevaFila == piezaI.fila + estado[i])
                    return false;
            }
        }
    }
    ++estado[indicePieza];
    return true;
}

int main()
{
    Aplicacion aplicacion;
    aplicacion.ejecutar();
    return 0;
}
