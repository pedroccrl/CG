#ifndef OBJETO_H_INCLUDED
#define OBJETO_H_INCLUDED
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

string PATH = "C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho";

typedef struct cor {
    float r, g, b;
} Cor;

typedef struct vertice {
    float x, y, z;
} Vertice;

typedef struct face {
    int numVertices;
    GLenum tipo;
    GLuint textura;
    Cor cor;
    vector <Vertice> vertices;
    vector <Vertice> normais;
    vector <Vertice> texturas;
} Face;

typedef struct objeto {
    int visivel;
    int numFaces;
    int temText;
    GLuint textura;
    vector <Face> faces;
} Objeto;


typedef struct p3d{
    double x, y, z;
}Point3D;

Face LinhaParaFace(char *linha, vector <Vertice> vertices, vector <Vertice> texturas, vector <Vertice> normais);
GLuint CarregaTextura(string imagem)
{
    string path = PATH + "\\Objetos\\" + imagem;

    char *f = new char[path.length() + 1];
    strcpy(f, path.c_str());
    printf ("lendo %s\n", f);

    GLuint textura = SOIL_load_OGL_texture
        (
            f,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
    /* check for an error during the load process */
    delete[] f;
    if( 0 == textura )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    else
    {
        printf("Textura %d carregada com sucesso!\n", textura);
    }

    return textura;
}


void compVetorNormalTriangulo ( Point3D p1, Point3D p2, Point3D p3, Point3D *n )
{
    Point3D v1, v2;
    double len;
    /* Encontra vetor v1 */
    v1.x = p2.x - p1.x;
    v1.y = p2.y - p1.y;
    v1.z = p2.z - p1.z;
    /* Encontra vetor v2 */
    v2.x = p3.x - p1.x;
    v2.y = p3.y - p1.y;
    v2.z = p3.z - p1.z;
    /* Calculo do produto vetorial de v1 e v2 */
    n->x = (v1.y * v2.z) - (v1.z * v2.y);
    n->y = (v1.z * v2.x) - (v1.x * v2.z);
    n->z = (v1.x * v2.y) - (v1.y * v2.x);
    /* normalizacao de n */
    len = sqrt(n->x*n->x + n->y*n->y + n->z*n->z);
    n->x /= len;
    n->y /= len;
    n->z /= len;
}


Objeto LoadObj(char *arquivo)
{
    cout << "lendo " << arquivo << "\n";
    Objeto nobj;
    int tipo;
    float x,y,z,k;
    vector <Vertice> vertices, normais, texturas;
    int vtcs=0;
    cout << "lendo " << arquivo << endl;
    FILE *f = fopen(arquivo, "rt");

    vector<Face> faces;
    int v1,v2,v3,v4,l=0,n;
    int contagemLinhas=0;
    char linha[500], skip[25];
    while (fgets(linha, 256, f) != NULL)
    {
        string line (linha);
        if (linha[0] == 'v')
        {
            if (linha[1] == ' ')
            {
                sscanf(linha, "%s %f %f %f", skip, &x, &y, &z);
                //printf("%c %f %f %f\n", tipo, x, y, z);
                Vertice v;
                v.x = x;
                v.y = y;
                v.z = z;
                vertices.push_back(v);
            }
            else if (linha[1] == 'n')
            {
                system("pause");
                sscanf(linha, "%s %f %f %f", skip, &x, &y, &z);
                //printf("%c %f %f %f\n", tipo, x, y, z);
                Vertice v;
                v.x = x;
                v.y = y;
                v.z = z;
                normais.push_back(v);
            }
            else if (linha[1] == 't')
            {
                sscanf(linha, "%s %f %f", skip, &x, &y);
                //printf("%c %f %f %f\n", tipo, x, y, z);
                Vertice v;
                v.x = x;
                v.y = y;
                texturas.push_back(v);
            }

        }
        else if (linha[0] == 'f')
        {
            faces.push_back(LinhaParaFace(linha, vertices, texturas, normais));
        }
        else if (linha[0] == '#')
        {
            continue;
        }
        else if (line.find("mtllib") != -1)
        {
            char mtl[50];
            sscanf(linha, "mtllib %s", mtl);
            string fmtl (mtl);
            fmtl.replace(fmtl.length()-4, 4, ".jpg");
            cout << fmtl;
            nobj.temText = 1;
            nobj.textura = CarregaTextura(fmtl);
            printf ("textura: %d\n", nobj.textura);
        }
        else
        {
            contagemLinhas++;
            continue;
        }
        //if (contagemLinhas % 5000) printf ("Ainda carregando....\n");
    }
    cout << vertices.size() << endl;
    cout << faces.size() << endl;
    cout << "JAJAJA\n";
    fclose(f);
    nobj.faces = faces;
    return nobj;
}

void DesenhaObj(Objeto obj)
{
    vector<Face> f = obj.faces;
    for (int i=0; i<f.size(); i++)
    {
        if (obj.temText == 1)
        {
            glBindTexture(GL_TEXTURE_2D, obj.textura);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        if (f[i].numVertices==3)
        {
            glBegin(GL_TRIANGLES);

            int j=0;
            Point3D p1, p2, p3, normal;
            p1.x = f[i].vertices[j].x;
            p1.y = f[i].vertices[j].y;
            p1.z = f[i].vertices[j].z;

            p2.x = f[i].vertices[j+1].x;
            p2.y = f[i].vertices[j+1].y;
            p2.z = f[i].vertices[j+1].z;

            p3.x = f[i].vertices[j+2].x;
            p3.y = f[i].vertices[j+2].y;
            p3.z = f[i].vertices[j+2].z;

            compVetorNormalTriangulo(p1,p2,p3,&normal);
            glNormal3f(normal.x,normal.y,normal.z);

           // printf ("VTs: %d\n", f[i].texturas.size());

            if (obj.temText == 1)
            {
                glTexCoord2d(f[i].texturas[0].x, f[i].texturas[0].y);
            }
            glVertex3f(p1.x,p1.y,p1.z);
            if (obj.temText == 1)
            {
                glTexCoord2d(f[i].texturas[1].x, f[i].texturas[1].y);
            }
            glVertex3f(p2.x,p2.y,p2.z);
            if (obj.temText == 1)
            {
                glTexCoord2d(f[i].texturas[2].x, f[i].texturas[2].y);
            }
            glVertex3f(p3.x,p3.y,p3.z);


        }
        else if (f[i].numVertices==4)
        {
            glBegin(GL_QUADS);
            //printf ("Face %d:\n", i+1);

            for (int j=0; j<f[i].vertices.size() ; j++)
            {
                //printf ("\t%d %f %f %f\n", j, f[i].vertices[j].x, f[i].vertices[j].y, f[i].vertices[j].z);
                if (obj.temText == 1)
                {
                    glTexCoord2d(f[i].texturas[j].x, f[i].texturas[j].y);
                }
                glVertex3f(f[i].vertices[j].x, f[i].vertices[j].y, f[i].vertices[j].z);
            }
        }
        glEnd();
    }


}

Face LinhaParaFace(char *linha, vector <Vertice> vertices, vector <Vertice> texturas, vector <Vertice> normais)
{
    Face fc;
    char skip[25];
    int v1,v2,v3,v4;
    int vt1,vt2,vt3,vt4;
    int vn1,vn2,vn3,vn4;
    int n = sscanf(linha, "%s %d %d %d %d", skip, &v1, &v2, &v3, &v4);
    if (n-1 == 3 || n-1 == 4)
    {
        //printf("f %d %d %d\n", v1, v2, v3);
        if (n-1==3) fc.numVertices = 3;
        if (n-1==4) fc.numVertices = 4;
    }
    else
    {
        n = sscanf(linha, "%s %d/%d %d/%d %d/%d %d/%d", skip, &v1, &vt1, &v2, &vt2, &v3, &vt3, &v4, &vt4);
        if (n-1 == 6 || n-1 == 8)
        {

            fc.numVertices = 3;
            Vertice v;
            v.x = texturas[vt1-1].x;
            v.y = texturas[vt1-1].y;
            v.z = texturas[vt1-1].z;
            fc.texturas.push_back(v);

            v.x = texturas[vt2-1].x;
            v.y = texturas[vt2-1].y;
            v.z = texturas[vt2-1].z;
            fc.texturas.push_back(v);

            v.x = texturas[vt3-1].x;
            v.y = texturas[vt3-1].y;
            v.z = texturas[vt3-1].z;
            fc.texturas.push_back(v);

            if (n-1==8)
            {
                fc.numVertices = 4;
                v.x = texturas[vt4-1].x;
                v.y = texturas[vt4-1].y;
                v.z = texturas[vt4-1].z;
                fc.texturas.push_back(v);
            }
        }
    }

    Vertice v;
    v.x = vertices[v1-1].x;
    v.y = vertices[v1-1].y;
    v.z = vertices[v1-1].z;
    fc.vertices.push_back(v);

    v.x = vertices[v2-1].x;
    v.y = vertices[v2-1].y;
    v.z = vertices[v2-1].z;
    fc.vertices.push_back(v);

    v.x = vertices[v3-1].x;
    v.y = vertices[v3-1].y;
    v.z = vertices[v3-1].z;
    fc.vertices.push_back(v);

    if ((n-1) % 4 == 0)
    {
        fc.numVertices = 4;
        v.x = vertices[v4-1].x;
        v.y = vertices[v4-1].y;
        v.z = vertices[v4-1].z;
        fc.vertices.push_back(v);
    }

    return fc;
}
#endif // OBJETO_H_INCLUDED

