typedef struct  // Struct para armazenar um ponto
{
	float X,Y,Z;
} TPoint;

typedef struct // Struct para armazenar um triângulo
{
	TPoint P1, P2, P3;
} TTriangle;

// Rotina que faz um produto vetorial
void ProdVetorial (TPoint v1, TPoint v2, TPoint &vresult)
{
	vresult.X = v1.Y * v2.Z - (v1.Z * v2.Y);
	vresult.Y = v1.Z * v2.X - (v1.X * v2.Z);
	vresult.Z = v1.X * v2.Y - (v1.Y * v2.X);
}

// Esta rotina tem como funcao calcular um vetor unitario
void VetUnitario(TPoint &vet)
{
	float modulo;

	modulo = sqrt (vet.X * vet.X + vet.Y * vet.Y + vet.Z * vet.Z);

	if (modulo == 0.0) return;

	vet.X /= modulo;
	vet.Y /= modulo;
	vet.Z /= modulo;
}

void ExibeObjeto (TTriangle *Objeto, int NFaces)
{
    glBegin(GL_TRIANGLES);
        for(int i = 0; i < NFaces; i++){
            TPoint v1 = {   Objeto[i].P2.X - Objeto[i].P1.X,
                            Objeto[i].P2.Y - Objeto[i].P1.Y,
                            Objeto[i].P2.Z - Objeto[i].P1.Z};
            TPoint v2 = {   Objeto[i].P3.X - Objeto[i].P1.X,
                            Objeto[i].P3.Y - Objeto[i].P1.Y,
                            Objeto[i].P3.Z - Objeto[i].P1.Z};
            TPoint r;
            ProdVetorial(v1,v2,r);
            VetUnitario(r);
            glColor3f(0,0,0);
            glNormal3f(r.X,r.Y,r.Z);
            glVertex3f(Objeto[i].P1.X,Objeto[i].P1.Z,Objeto[i].P1.Z);
            glColor3f(0,0,0.3);
            glVertex3f(Objeto[i].P2.X,Objeto[i].P2.Z,Objeto[i].P2.Z);
            glColor3f(0,0,0.6);
            glVertex3f(Objeto[i].P3.X,Objeto[i].P3.Z,Objeto[i].P3.Z);
        }
    glEnd();
}

void LeObjeto (char* const Nome, TTriangle Objeto[], int &NFaces)
{
    FILE *arq = fopen(Nome,"r");
    int res = fscanf(arq,"%d", &NFaces);
    char linha[120];
    if(res == EOF)
        printf("erro na leitura");
    for(int i = 0; i < NFaces; i++){
        fgets(linha,sizeof(linha),arq);
        sscanf(linha,"%f %f %f %f %f %f %f %f %f" ,&Objeto[i].P1.X,&Objeto[i].P1.Y,&Objeto[i].P1.Z
                                                ,&Objeto[i].P2.X,&Objeto[i].P2.Y,&Objeto[i].P2.Z
                                                ,&Objeto[i].P3.X,&Objeto[i].P3.Y,&Objeto[i].P3.Z);
        if(i == 0)
            printf("%f %f %f",Objeto[i].P1.X,Objeto[i].P1.Y,Objeto[i].P1.Z);
    }
}

void Paredes(){
    float altura = 8.0;

    glBegin(GL_QUADS);
        glColor3f(0.6f, 0.0f, 0.0f);
        glVertex3f(20, altura, 20);
        glVertex3f(20, -altura, 20);
        glVertex3f(-20, -altura, 20);
        glVertex3f(-20, altura, 20);

        glColor3f(0.7f, 0.0f, 0.0f);
        glVertex3f(20, altura, -20);
        glVertex3f(20, -altura, -20);
        glVertex3f(-20, -altura, -20);
        glVertex3f(-20, altura, -20);

        glColor3f(0.8f, 0.0f, 0.0f);
        glVertex3f(20, altura, -20);
        glVertex3f(20, -altura, -20);
        glVertex3f(20, -altura, 20);
        glVertex3f(20, altura, 20);

        glColor3f(0.9f, 0.0f, 0.0f);
        glVertex3f(-20, altura, 20);
        glVertex3f(-20, -altura, 20);
        glVertex3f(-20, -altura, -20);
        glVertex3f(-20, altura, -20);
    glEnd();
}

void Mesa(){
    glPushMatrix();
    //Mesa
        glBegin(GL_QUADS);
            //Tampos
            glVertex3f(10.0f,-2,10.0f);
            glVertex3f(10.0f,-2,7.5f);
            glVertex3f(7.5f,-2,7.5f);
            glVertex3f(7.5f,-2,10.0f);

            glVertex3f(10.0f,-2.5,10.0f);
            glVertex3f(10.0f,-2.5,7.5f);
            glVertex3f(7.5f,-2.5,7.5f);
            glVertex3f(7.5f,-2.5,10.0f);
            //Partes laterais
            glColor3f(0,1,0);
            glVertex3f(10,-2,10);
            glVertex3f(10,-2.5,10);
            glVertex3f(10,-2.5,7.5);
            glVertex3f(10,-2,7.5);

            glColor3f(1,-2,1);
            glVertex3f(10,-2,7.5);
            glVertex3f(10,-2.5,7.5);
            glVertex3f(7.5,-2.5,7.5);
            glVertex3f(7.5,-2,7.5);

            glColor3f(0,1,1);
            glVertex3f(7.5,-2,10);
            glVertex3f(7.5,-2.5,10);
            glVertex3f(7.5,-2.5,7.5);
            glVertex3f(7.5,-2,7.5);

            glColor3f(1,1,0);
            glVertex3f(10,-2,10);
            glVertex3f(10,-2.5,10);
            glVertex3f(7.5,-2.5,10);
            glVertex3f(7.5,-2,10);
            //Pés
            glColor3f(1,1,1);
            glVertex3f(10,-2,10);
            glVertex3f(10,-8,10);
            glVertex3f(10,-8,7.5);
            glVertex3f(10,-2,7.5);

            glVertex3f(7.5,-2,10);
            glVertex3f(7.5,-8,10);
            glVertex3f(7.5,-8,7.5);
            glVertex3f(7.5,-2,7.5);


        glEnd();
    glPopMatrix();
}

void Esferas(float ang_esfera){
    glPushMatrix();
        glTranslatef(0,5,0);
        glColor3f(1.0f, 0.0f, 1.0f);
        glRotatef(ang_esfera,0,1,0);
        glutWireSphere(2, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,5,0);
        glColor3f(0.0f, 1.0f, 1.0f);
        glRotatef(ang_esfera,1,0,0);
        glutWireSphere(1.5, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,5,0);
        glColor3f(0.2f, 0.2f, 0.2f);
        glRotatef(ang_esfera,0,0,1);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();
}

void Sofa(){
    glPushMatrix();
    glTranslatef(0,-3,0);
    glBegin(GL_QUADS); //DESENHA APOIO DO SOFÁ
    glColor3f(0.59f,0.29f,0.0f);
    // Tampos do apoio
    glVertex3f(13, -5, 0);
    glVertex3f(5, -5, 0);
    glVertex3f(5, -0.5, 0);
    glVertex3f(13, -0.5, 0);

    glVertex3f(13, -5, -0.5);
    glVertex3f(5, -5, -0.5);
    glVertex3f(5, -0.5, -0.5);
    glVertex3f(13, -0.5, -0.5);

    glVertex3f(13, -5, 0);
    glVertex3f(13, -5, -0.5);
    glVertex3f(13, -0.5, -0.5);
    glVertex3f(13, -0.5, 0);

    glVertex3f(5, -5, 0);
    glVertex3f(5, -5, -0.5);
    glVertex3f(5, -0.5, -0.5);
    glVertex3f(5, -0.5, 0);

    glVertex3f(13, -0.5, 0);
    glVertex3f(13, -0.5, -0.5);
    glVertex3f(5, -0.5, -0.5);
    glVertex3f(5, -0.5, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex3f(5, -4.99, 0.01);
    glVertex3f(6, -4.99, 0.01);
    glVertex3f(6, -4.99, 2);
    glVertex3f(5, -4.99, 2);

    glVertex3f(5, -2.5, 2);
    glVertex3f(5, -2.5, 0.01);
    glVertex3f(6, -2.5, 0.01);
    glVertex3f(6, -2.5, 2);

    glVertex3f(5, -2.5, 2);
    glVertex3f(5, -4.99, 2);
    glVertex3f(6, -4.99, 2);
    glVertex3f(6, -2.5, 2);

    glVertex3f(5, -2.5, 2);
    glVertex3f(5, -4.99, 2);
    glVertex3f(5, -4.99, 0.01);
    glVertex3f(5, -2.5, 0.01);//DESENHA LATERAL 1 DO SOFÁ

    glVertex3f(6, -2.5, 2);
    glVertex3f(6, -4.99, 2);
    glVertex3f(6, -4.99, 0.01);
    glVertex3f(6, -2.5, 0.01); //DESENHA CABECEIRA 1

    glVertex3f(12, -2.5, 2);
    glVertex3f(12, -2.5, 0.01);
    glVertex3f(13, -2.5, 0.01);
    glVertex3f(13, -2.5, 2);

    glVertex3f(12, -2.5, 2);
    glVertex3f(12, -4.99, 2);
    glVertex3f(13, -4.99, 2);
    glVertex3f(13, -2.5, 2);

    glVertex3f(12, -2.5, 2);
    glVertex3f(12, -4.99, 2);
    glVertex3f(12, -4.99, 0.01);
    glVertex3f(12, -2.5, 0.01);

    glVertex3f(13, -2.5, 2);
    glVertex3f(13, -4.99, 2);
    glVertex3f(13, -4.99, 0.01);
    glVertex3f(13, -2.5, 0.01); //desenha cabeceira 2

    glColor3f(0.43f,0.21f, 0.1f);
    glVertex3f(6, -4.99, 0.01);
    glVertex3f(6, -4.99, 2);
    glVertex3f(12, -4.99, 2);
    glVertex3f(12, -4.99, 0.01); //DESENHA BASE DO SOFÁ NO CHÃO

    glVertex3f(6, -3.75, 0.01);
    glVertex3f(6, -3.75, 2);
    glVertex3f(12, -3.75, 2);
    glVertex3f(12, -3.75, 0.01); //DESENHA BASE DO SOFÁ NO ALTO

    glVertex3f(6, -3.75, 2);
    glVertex3f(6, -4.99, 2);
    glVertex3f(12, -4.99, 2);
    glVertex3f(12, -3.75, 2); //COMPLETA BASE DO SOFÁ

    glEnd();
    glPopMatrix();
}
