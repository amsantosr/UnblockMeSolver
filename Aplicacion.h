﻿#ifndef APLICACION_H
#define APLICACION_H

#include <QVector>
#include <QMap>
#include <QTextStream>

class Aplicacion
{
public:
    Aplicacion();
    void ejecutar();

private:
    enum Direccion { Horizontal, Vertical };

    struct Pieza {
        int fila, columna;
        int longitud;
        Direccion direccion;
    };

    struct Movimiento {
        int indicePieza, distancia;
    };

    typedef QVector<Pieza> Puzzle;
    typedef QVector<int> Estado;
    typedef QVector<Movimiento> Camino;

private:
    void leerPuzzle();
    bool resolverPuzzle();
    void mostrarSolucion();
    bool moverIzquierda(Estado &estado, int indicePieza) const;
    bool moverDerecha(Estado &estado, int indicePieza) const;
    bool moverArriba(Estado &estado, int indicePieza) const;
    bool moverAbajo(Estado &estado, int indicePieza) const;

private:
    int numeroPiezas;
    Puzzle puzzle;
    Camino solucion;
    QTextStream salida;
};

#endif