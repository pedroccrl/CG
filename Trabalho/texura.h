#ifndef TEXURA_H_INCLUDED
#define TEXURA_H_INCLUDED

#include <SOIL.h>

void LoadTextura()
{
    int largura, altura;
    unsigned char* image = SOIL_load_image("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Imagens\\crate.jpg", &largura, &altura, 0, SOIL_LOAD_RGB);
}

#endif // TEXURA_H_INCLUDED
