//
// Created by Stive on 19/05/2023.
//
#include "shapes.h"
#include <stdlib.h>
#include <stdio.h>
unsigned int global_id = 0;
unsigned int get_next_id() {
    global_id += 1;
    return global_id;
}
//Point-------------------------------------------------
Point * create_point(int px, int py) {
    Point * nouv_point = malloc(sizeof(Point));
    nouv_point->pos_x = px;
    nouv_point->pos_y= py;
    return nouv_point;
}
void delete_point(Point * point) {
    free(point);
    point = NULL;
}
void print_point(Point * p){
    printf("POINT %d %d", p->pos_x, p->pos_y);
}
//------------------------------------------------------------------------------

// Line---------------------------------------------------------------------
Line* create_line(Point * p1, Point * p2){
    Line * nouv_seg = malloc(sizeof(Line));
    nouv_seg -> p1 = p1;
    nouv_seg -> p2 = p2;
    return nouv_seg;
}

void delete_line(Line * line){
    free(line);
    line = NULL;
}

void print_line(Line * line){
    printf("LINE %d %d %d %d",line->p1->pos_x, line->p1->pos_y,line->p2->pos_x,line->p2->pos_y);
}
//----------------------------------------------------

// Square------------------------------------------------------
Square * create_square(Point * point, int length){
    Square * nouv_car = malloc(sizeof(Square));
    nouv_car->pos = point;
    nouv_car -> length = length;
    return nouv_car;
}

void delete_square(Square * square){
    free(square);
    square = NULL;
}

void print_square(Square * square){
    printf("Coin supérieur gauche (Carré) : (%d,%d)\n", square ->pos->pos_x, square-> pos->pos_y);
    printf("Coin supérieur droite (Carré) : (%d,%d)\n", square->pos->pos_x,(square->pos->pos_y)+(square->length));
    printf("Coin inférieur gauche (Carré) : (%d,%d)\n", (square->pos->pos_x)+(square->length),(square->pos->pos_y));
    printf("Coin inférieur droite (Carré) : (%d,%d)\n", (square->pos->pos_x)+(square->length),(square->pos->pos_y)+(square->length));
}
//----------------------------------------------------------------------

// Rectangle--------------------------------
Rectangle * create_rectangle(Point * point, int width, int height){
    Rectangle * nouv_rect = malloc(sizeof(Rectangle));
    nouv_rect->pos = point;
    nouv_rect->longueur = height;
    nouv_rect->largeur = width;
    return nouv_rect;
}
void delete_rectangle(Rectangle * rectangle){
    free(rectangle);
    rectangle = NULL;
}
void print_rectangle(Rectangle * rectangle){
    printf("Coin supérieur gauche (Rectangle) : (%d,%d)\n", rectangle ->pos->pos_x, rectangle-> pos->pos_y);
    printf("Coin supérieur droite (Rectangle) : (%d,%d)\n", rectangle->pos->pos_x,(rectangle->pos->pos_y)+(rectangle->longueur));
    printf("Coin inférieur gauche (Rectangle) : (%d,%d)\n", (rectangle->pos->pos_x)+(rectangle->largeur),(rectangle->pos->pos_y));
    printf("Coin inférieur droite (Rectangle) : (%d,%d)\n", (rectangle->pos->pos_x)+(rectangle->largeur),(rectangle->pos->pos_y)+(rectangle->longueur));
}
//-----------------------------------------------------------------------

//Circle
Circle * create_circle(Point * center, int radius){
    Circle * nouv_cerc = malloc(sizeof(Circle));
    nouv_cerc->pos =center;
    nouv_cerc->rayon = radius;
    return nouv_cerc;
}
void delete_circle(Circle * circle){
    free(circle);
    circle = NULL;
}
void print_circle(Circle * circle){
    printf("CIRCLE (%d,%d) %d \n", circle -> pos->pos_x,circle->pos->pos_y, circle->rayon);
}

// Polygone
Polygon * create_polygon(int n, int ** tab){
     Polygon * nouv_poly = malloc(sizeof(Polygon));
     nouv_poly -> n = n;
     nouv_poly -> points = malloc((n+1)*sizeof(Point*));
     for (int i = 0;i < n; i++){
         nouv_poly->points[i] = create_point(tab[i][0],tab[i][1]);
     }
     nouv_poly->points[n] = create_point(tab[0][0],tab[0][1]);
     return nouv_poly;

}

void delete_polygon(Polygon * polygon){
    for(int i = 0; i<= polygon -> n; i++ )
    {
        free(polygon->points[i]);
    }
    free(polygon->points);
    free(polygon);
    polygon = NULL;
}

void print_polygon(Polygon * polygon){
    for(int i = 0; i< polygon->n;i++){
        printf("POLYGON pos %d : (%d, %d)\n",i, polygon->points[i]->pos_x,polygon->points[i]->pos_y);
    }
}

// Shape
Shape *create_empty_shape(SHAPE_TYPE shape_type) {
    Shape *shp = (Shape *) malloc(sizeof(Shape));
    shp->id = get_next_id(); // plus tard on appelera get_next_id();
    shp->shape_type = shape_type;
    shp->ptrShape = NULL;
    return shp;
}

Shape *create_point_shape(int px, int py) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(px, py);
    shp->ptrShape = p;
    return shp;
}

Shape *create_line_shape(int px1, int py1, int px2, int py2) {
    Shape * shp = create_empty_shape(LINE);
    Line * l = create_line(create_point(px1,py1), create_point(px2,py2));
    shp -> ptrShape = l;
    return shp;
}

Shape *create_square_shape(int px, int py, int length) {
    Shape * shp = create_empty_shape(SQUARE);
    Square * carre = create_square(create_point(px,py),length);
    shp -> ptrShape = carre;
    return shp;
}

Shape *create_rectangle_shape(int px, int py, int width, int height) {
    Shape * shp = create_empty_shape(RECTANGLE);
    Rectangle * rect = create_rectangle(create_point(px,py),width,height);
    shp -> ptrShape = rect;
    return shp;
}

Shape * create_cercle_shape(int px, int py, int radius) {
    Shape * shp = create_empty_shape(CIRCLE);
    Circle * cercle = create_circle(create_point(px,py),radius);
    shp -> ptrShape = cercle;
    return shp;
}

Shape * create_polygon_shape(int ** lst,int n){
    if (n%2 != 0 ){
        printf("Erreur : le nombre de points doit être un multiple de 2");
        return NULL;
    }
    Shape * shp = create_empty_shape(POLYGON);
    Polygon * poly = create_polygon(n, lst);
    shp -> ptrShape = poly;
    return shp;
}

void delete_shape(Shape * shape){
    switch (shape->shape_type){
        case POINT:{
            delete_point(shape ->ptrShape);
            break;
        }
        case LINE:{
            delete_line(shape->ptrShape);
            break;
        }
        case SQUARE:{
            delete_square(shape->ptrShape);
            break;
        }
        case RECTANGLE:{
            delete_rectangle(shape->ptrShape);
            break;
        }
        case CIRCLE:{
            delete_circle(shape->ptrShape);
            break;
        }
        case POLYGON:{
            delete_polygon(shape->ptrShape);
            break;
        }
        default:{
            break;
        }
    }
    free(shape);

}

void print_shape(Shape * shape){
    switch (shape->shape_type){
        case POINT:{
            print_point(shape ->ptrShape);
            break;
        }
        case LINE:{
            print_line(shape->ptrShape);
            break;
        }
        case SQUARE:{
            print_square(shape->ptrShape);
            break;
        }
        case RECTANGLE:{
            print_rectangle(shape->ptrShape);
            break;

        }
        case CIRCLE:{
            print_circle(shape->ptrShape);
            break;
        }
        case POLYGON:{
            print_polygon(shape->ptrShape);
            break;
        }
        default:{
            break;
        }
    }
}
