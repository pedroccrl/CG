#include <vector>
#include <iostream>
#include <stdio.h>


using namespace std;

typedef struct cor {
    float r, g, b;
} Cor;

typedef struct vertice {
    float x, y, z;
} Vertice;

typedef struct face {
    int numVertices;
    GLenum tipo;
    Cor cor;
    vector <Vertice> vertices;
} Face;

typedef struct objeto {
    int visivel=1;
    int numFaces=0;
    Face faces[34];
} Objeto;


typedef struct p3d{
    double x, y, z;
}Point3D;


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


vector<face> LoadObj(char *arquivo)
{
    cout << "lendo " << arquivo << "\n";
    string line;
    Objeto obj;
    int tipo;
    float x,y,z, k;
    vector <vertice> vertices;
    int vtcs=0;
    cout << "lendo " << arquivo << endl;
    FILE *f = fopen(arquivo, "rt");

    vector<face> faces;
    int v1,v2,v3,v4,l=0,n;

    while (fscanf(f, "%c", &tipo) != EOF)
    {
        if ((char)tipo == 'v')
        {
            fscanf(f, "%f %f %f\n", &x, &y, &z);
            //printf("%c %f %f %f\n", tipo, x, y, z);
            Vertice v;
            v.x = x;
            v.y = y;
            v.z = z;
            vertices.push_back(v);
        }
        else if ((char)tipo == 'f')
        {
            n = fscanf(f, "%d %d %d %d\n", &v1, &v2, &v3, &v4);
            //printf("f %d %d %d\n", v1, v2, v3);
            Face f;
            f.numVertices = n;
            Vertice v;
            v.x = vertices[v1-1].x;
            v.y = vertices[v1-1].y;
            v.z = vertices[v1-1].z;
            f.vertices.push_back(v);

            v.x = vertices[v2-1].x;
            v.y = vertices[v2-1].y;
            v.z = vertices[v2-1].z;
            f.vertices.push_back(v);

            v.x = vertices[v3-1].x;
            v.y = vertices[v3-1].y;
            v.z = vertices[v3-1].z;
            f.vertices.push_back(v);

            if (n==4)
            {
                v.x = vertices[v4-1].x;
                v.y = vertices[v4-1].y;
                v.z = vertices[v4-1].z;
                f.vertices.push_back(v);
            }
            faces.push_back(f);
        }

    }
    cout << vertices.size() << endl;
    cout << faces.size() << endl;
    cout << "JAJAJA\n";
    fclose(f);
    return faces;
}

void DesenhaObj(vector<face> f)
{
    int vAnterior=0;
    for (int i=0; i<f.size(); i++)
    {
        if (f[i].numVertices==3){
            glBegin(GL_TRIANGLES);
            for (int j=0; j<f[i].vertices.size() ; j+=3)
            {
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

                glVertex3f(p1.x,p1.y,p1.z);
                glVertex3f(p2.x,p2.y,p2.z);
                glVertex3f(p3.x,p3.y,p3.z);
            }
        }
        if (f[i].numVertices==4) glBegin(GL_QUADS);
        //printf ("Face %d:\n", i+1);

        for (int j=0; j<f[i].vertices.size() ; j++)
        {
            //printf ("\t%d %f %f %f\n", j, f[i].vertices[j].x, f[i].vertices[j].y, f[i].vertices[j].z);
            glVertex3f(f[i].vertices[j].x, f[i].vertices[j].y, f[i].vertices[j].z);
        }
        vAnterior += f[i].numVertices;
        glEnd();
    }

}
