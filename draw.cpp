#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "scene.h"
#include <cstdio>

#define NUM_TORRES 5
#define RAIO 15.0f // raio das torres ao redor do centro

extern GLuint texChao;
extern GLuint texTorre;
extern GLuint texDegrau;
extern GLuint texEsfera;
extern GLuint texLava;
extern GLuint progEsfera;
extern GLuint progLava;
extern GLuint progLosango;

static void desenhaLosango(float altura)
{
    float h = altura / 2.0f;
    float s = altura / 3.0f;

    

    glBegin(GL_TRIANGLES);
    

    // Triângulo 1 (frente-esquerda)
    // REMOVIDO: glColor3fv(claro);
    glVertex3f(0.0f, h, 0.0f);
    glVertex3f(-s, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, s);

    // Triângulo 2 (frente-direita)
    // REMOVIDO: glColor3fv(escuro);
    glVertex3f(0.0f, h, 0.0f);
    glVertex3f(0.0f, 0.0f, s);
    glVertex3f(s, 0.0f, 0.0f);

    // Triângulo 3 (trás-direita)
    // REMOVIDO: glColor3fv(claro);
    glVertex3f(0.0f, h, 0.0f);
    glVertex3f(s, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -s);

    // Triângulo 4 (trás-esquerda)
    // REMOVIDO: glColor3fv(escuro);
    glVertex3f(0.0f, h, 0.0f);
    glVertex3f(0.0f, 0.0f, -s);
    glVertex3f(-s, 0.0f, 0.0f);


    // Triângulo 5 (frente-esquerda)
    // REMOVIDO: glColor3fv(claro);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(0.0f, 0.0f, s);
    glVertex3f(-s, 0.0f, 0.0f);

    // Triângulo 6 (frente-direita)
    // REMOVIDO: glColor3fv(escuro);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(s, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, s);

    // Triângulo 7 (trás-direita)
    // REMOVIDO: glColor3fv(claro);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(0.0f, 0.0f, -s);
    glVertex3f(s, 0.0f, 0.0f);

    // Triângulo 8 (trás-esquerda)
    // REMOVIDO: glColor3fv(escuro);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(-s, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -s);

    glEnd();
}

void desenhaChao()
{
    glBindTexture(GL_TEXTURE_2D, texChao);
    glColor3f(1, 1, 1);

    float tiles = 75.0f;

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-80, 0, -80);
    glTexCoord2f(tiles, 0);
    glVertex3f(80, 0, -80);
    glTexCoord2f(tiles, tiles);
    glVertex3f(80, 0, 80);
    glTexCoord2f(0, tiles);
    glVertex3f(-80, 0, 80);
    glEnd();
}


// draw.cpp

void desenhaTorresELosangos(void)
{
    // Variáveis globais necessárias (assumindo que estão definidas como 'extern')
    extern GLuint progLosango; 
    extern float tempoEsfera;
    extern float anguloPiramide;
    extern GLuint texTorre;
    
    // Constantes (se não estiverem no cabeçalho)
    #define NUM_TORRES 5
    #define RAIO 15.0f 
    
    // Parâmetros da Torre (usando os valores que você especificou)
    float alturaTorre = 2.5f; 
    float w = 0.7f;
    
    float ang0 = -M_PI / 2.0f;
    float passo = 2.0f * M_PI / NUM_TORRES;
    
    // Configuração de Material Padrão para Fixed Function (Torres)
    float corTorre[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, corTorre);
    
    for (int i = 0; i < NUM_TORRES; i++)
    {
        float ang = ang0 + passo * i;
        float x = RAIO * cosf(ang);
        float z = RAIO * sinf(ang);

        glPushMatrix();
        glTranslatef(x, 0.0f, z);

        // ----------------------------------------------------
        // 1. Torre (Cubo Texturizado - Fixed Function)
        // ----------------------------------------------------
        glPushMatrix();
        glEnable(GL_LIGHTING); 
        
        float corEmissao[4] = {0.4f, 0.4f, 0.4f, 1.0f}; 
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, corEmissao); 

        glBindTexture(GL_TEXTURE_2D, texTorre);
        glColor3f(1.0f, 1.0f, 1.0f); 
        glTranslatef(0.0f, alturaTorre / 2.0f, 0.0f);
        glScalef(w, alturaTorre, w);

        float half = 0.5f;
        float tilesX = 1.0f;
        float tilesY = 2.0f;

        glBegin(GL_QUADS);
        // Frente (z positivo)
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-half, -half, half);
        glTexCoord2f(tilesX, 0.0f); glVertex3f(half, -half, half);
        glTexCoord2f(tilesX, tilesY); glVertex3f(half, half, half);
        glTexCoord2f(0.0f, tilesY); glVertex3f(-half, half, half);

        // Trás (z negativo)
        glTexCoord2f(0.0f, 0.0f); glVertex3f(half, -half, -half);
        glTexCoord2f(tilesX, 0.0f); glVertex3f(-half, -half, -half);
        glTexCoord2f(tilesX, tilesY); glVertex3f(-half, half, -half);
        glTexCoord2f(0.0f, tilesY); glVertex3f(half, half, -half);

        // Direita (x positivo)
        glTexCoord2f(0.0f, 0.0f); glVertex3f(half, -half, half);
        glTexCoord2f(tilesX, 0.0f); glVertex3f(half, -half, -half);
        glTexCoord2f(tilesX, tilesY); glVertex3f(half, half, -half);
        glTexCoord2f(0.0f, tilesY); glVertex3f(half, half, half);

        // Esquerda (x negativo)
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-half, -half, -half);
        glTexCoord2f(tilesX, 0.0f); glVertex3f(-half, -half, half);
        glTexCoord2f(tilesX, tilesY); glVertex3f(-half, half, half);
        glTexCoord2f(0.0f, tilesY); glVertex3f(-half, half, -half);

        // Topo
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-half, half, half);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(half, half, half);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(half, half, -half);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-half, half, -half);

        glEnd();
        
        // === REMOVE A EMISSÃO APÓS DESENHAR O CUBO ===
        // Zera o componente de emissão para que o próximo objeto (Losango) não brilhe
        float corZero[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, corZero); 
        
        glPopMatrix();
        glDisable(GL_LIGHTING); 
        

        // ----------------------------------------------------
        // 2. Losango (Com Shader de Scanline Multicor)
        // ----------------------------------------------------
        glUseProgram(progLosango); 
        
        // 1. Uniforms de Tempo
        extern float tempoEsfera;
        GLint locTime = glGetUniformLocation(progLosango, "uTime");
        glUniform1f(locTime, tempoEsfera); 

        // 2. Uniforms de Scanline (Velocidade, Largura, Cor, Pausa, Offset)
        GLint locSpeed = glGetUniformLocation(progLosango, "uSpeed");
        GLint locWidth = glGetUniformLocation(progLosango, "uLineWidth");
        GLint locColor = glGetUniformLocation(progLosango, "uLineColor");
        GLint locPause = glGetUniformLocation(progLosango, "uPauseDuration");
        GLint locOffset = glGetUniformLocation(progLosango, "uOffset");

        glUniform1f(locSpeed, 1.0f);         // Velocidade normal
        glUniform1f(locWidth, 0.15f);        // Largura da linha
        
        glUniform4f(locColor, 0.9f, 1.0f, 1.0f, 1.0f); 
        
        glUniform1f(locPause, 0.15f);        // Duração da pausa
        glUniform1f(locOffset, 2.0f);        // Distância do ciclo
        
        // 3. Desenho do Losango
        glPushMatrix();
        glTranslatef(0.0f, alturaTorre + 1.2f, 0.0f); // Posição acima da torre
        glRotatef(anguloPiramide * 2.0f, 0.0f, 1.0f, 0.0f); // Rotação
        desenhaLosango(1.5f); // Chama a função que define a geometria
        glPopMatrix();

        glUseProgram(0); // Desativa o shader
        
        glPopMatrix();
    }
}

void desenhaPiramideDegraus()
{
    float alturaDegrau = 0.5f;
    float tamanhoBase = 6.0f;
    float reducao = 0.65f;
    float raioLava = 12.0f;
    float elevacao = 0.001f;
    int segmentos = 64;     // mais = círculo mais suave
    float tilesLava = 6.0f; // quantas vezes a textura se repete

    glPushMatrix();

    // Degrau 0
    glUseProgram(progLava);

    GLint locTimeLava = glGetUniformLocation(progLava, "uTime");
    GLint locStrLava = glGetUniformLocation(progLava, "uStrength");
    GLint locScrollLava = glGetUniformLocation(progLava, "uScroll");
    GLint locHeatLava = glGetUniformLocation(progLava, "uHeat");
    GLint locTexLava = glGetUniformLocation(progLava, "uTexture");

    glUniform1f(locTimeLava, tempoEsfera);
    glUniform1f(locStrLava, 1.0f);
    glUniform2f(locScrollLava, 0.1f, 0.0f);
    glUniform1f(locHeatLava, 0.5f);

    glBindTexture(GL_TEXTURE_2D, texLava);
    glUniform1i(locTexLava, 0);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);

    // Centro do círculo
    glTexCoord2f(0.5f, 0.5f);

    glVertex3f(0.0f, elevacao, 0.0f);

    for (int i = 0; i <= segmentos; i++)
    {
        float ang = (float)i / segmentos * 2.0f * M_PI;
        float x = cosf(ang) * raioLava;
        float z = sinf(ang) * raioLava;

        // UV radial
        float u = 0.5f + cosf(ang) * 0.5f * tilesLava;
        float v = 0.5f + sinf(ang) * 0.5f * tilesLava;

        glTexCoord2f(u, v);
        glVertex3f(x, elevacao, z);
    }

    glEnd();

    glUseProgram(0);

    // vamos usar um cubo unitário de -0.5 a 0.5
    float half = 0.5f;

    // Degrau 1
    float larg = tamanhoBase;    // largura/profundidade
    float tilesX = larg;         // repetição em X
    float tilesZ = larg;         // repetição em Z
    float tilesY = alturaDegrau; // repetição em Y (altura)

    glBindTexture(GL_TEXTURE_2D, texDegrau);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, alturaDegrau / 2.0f, 0.0f);
    glScalef(tamanhoBase, alturaDegrau, tamanhoBase);

    glBegin(GL_QUADS);
    // Frente (z+)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, -half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, -half, half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(half, half, half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(-half, half, half);

    // Trás (z-)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(half, -half, -half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(-half, half, -half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(half, half, -half);

    // Direita (x+)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(half, -half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, -half, -half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(half, half, -half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(half, half, half);

    // Esquerda (x-)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(-half, -half, half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(-half, half, half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(-half, half, -half);

    // Topo
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, half, half);
    glTexCoord2f(tilesX, tilesZ);
    glVertex3f(half, half, -half);
    glTexCoord2f(0.0f, tilesZ);
    glVertex3f(-half, half, -half);

    glEnd();

    glPopMatrix();

    // Degrau 2
    larg = tamanhoBase * reducao;
    tilesX = larg;
    tilesZ = larg;
    tilesY = alturaDegrau;

    glBindTexture(GL_TEXTURE_2D, texDegrau);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, alturaDegrau + alturaDegrau / 2.0f, 0.0f);
    glScalef(tamanhoBase * reducao, alturaDegrau, tamanhoBase * reducao);

    glBegin(GL_QUADS);
    // Frente (z+)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, -half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, -half, half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(half, half, half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(-half, half, half);

    // Trás (z-)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(half, -half, -half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(-half, half, -half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(half, half, -half);

    // Direita (x+)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(half, -half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, -half, -half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(half, half, -half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(half, half, half);

    // Esquerda (x-)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(-half, -half, half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(-half, half, half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(-half, half, -half);

    // Topo
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, half, half);
    glTexCoord2f(tilesX, tilesZ);
    glVertex3f(half, half, -half);
    glTexCoord2f(0.0f, tilesZ);
    glVertex3f(-half, half, -half);
    glEnd();

    glPopMatrix();

    // Degrau 3
    larg = tamanhoBase * reducao * reducao;
    tilesX = larg;
    tilesZ = larg;
    tilesY = alturaDegrau;

    glBindTexture(GL_TEXTURE_2D, texDegrau);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 2 * alturaDegrau + alturaDegrau / 2.0f, 0.0f);
    glScalef(tamanhoBase * reducao * reducao,
             alturaDegrau,
             tamanhoBase * reducao * reducao);

    glBegin(GL_QUADS);
    // Frente (z+)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, -half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, -half, half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(half, half, half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(-half, half, half);

    // Trás (z-)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(half, -half, -half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(-half, half, -half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(half, half, -half);

    // Direita (x+)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(half, -half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, -half, -half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(half, half, -half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(half, half, half);

    // Esquerda (x-)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(-half, -half, half);
    glTexCoord2f(tilesX, tilesY);
    glVertex3f(-half, half, half);
    glTexCoord2f(0.0f, tilesY);
    glVertex3f(-half, half, -half);

    // Topo
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-half, half, half);
    glTexCoord2f(tilesX, 0.0f);
    glVertex3f(half, half, half);
    glTexCoord2f(tilesX, tilesZ);
    glVertex3f(half, half, -half);
    glTexCoord2f(0.0f, tilesZ);
    glVertex3f(-half, half, -half);
    glEnd();

    glPopMatrix();

    // Esfera flutuando acima
    float topoDegrausY = 5.0f * alturaDegrau;
    float raioEsfera = 3.0f;

    glUseProgram(progEsfera);

    // uniforms básicos
    GLint locTimeBlood = glGetUniformLocation(progEsfera, "uTime");
    GLint locStrBlood = glGetUniformLocation(progEsfera, "uStrength");
    GLint locSpeedBlood = glGetUniformLocation(progEsfera, "uSpeed");
    GLint locTexBlood = glGetUniformLocation(progEsfera, "uTexture");

    glUniform1f(locTimeBlood, tempoEsfera);
    glUniform1f(locStrBlood, 1.0f);
    glUniform2f(locSpeedBlood, 3.0f, 1.7f);

    glPushMatrix();
    glTranslatef(0.0f, topoDegrausY + raioEsfera + 0.2f, 0.0f);
    glRotatef(anguloEsfera, 1.0f, 1.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, texEsfera);
    glUniform1i(locTexBlood, 0);

    // Ajuste da escala da textura na esfera
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    // valores < 1.0f deixam a textura MENOS repetida (mais esticada)
    glScalef(1.5f, 1.5f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    static GLUquadric *quad = nullptr;
    if (!quad)
    {
        quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);   // gera coordenadas de textura
        gluQuadricNormals(quad, GL_SMOOTH); // normais suaves (pra iluminação no futuro)
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    gluSphere(quad, raioEsfera, 40, 40);

    // voltar a matriz de textura ao normal
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();

    glUseProgram(0);

    glPopMatrix();
}
