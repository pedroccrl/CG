typedef struct  // Struct para armazenar um ponto
{
	float X,Y,Z;
} TPoint;

typedef struct // Struct para armazenar um triângulo
{
	TPoint P1, P2, P3;
} TTriangle;

void LeObjeto (char* const Nome, TTriangle Objeto[], int &NFaces)
{
    int vertices = 0;
    char str[300];
    char controle;
    FILE *arq = fopen(Nome,"r");
    while(!feof(arq)){
        fgets(str,sizeof(str),arq);
        sscanf(str,"%c %f %f %f",&controle);
        if(controle == 'v')
            vertices++;
    }
    printf("%d",vertices);


}





/*
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
*/
