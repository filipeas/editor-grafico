/**
 * TUTORIAL:
 *
 * Opcoes no teclado
 * 0 - DESENHAR RETA (atividade A e B)
 * 1 - DESENHAR TRIANGULO (atividade D)
 * 2 - DESENHAR QUADRILATERO (atividade C)
 * 3 - DESENHAR POLIGONO (atividade E e H)
 * 4 - DESENHAR CIRCUNFERENCIA (atividade G)
 * 5 - MUDAR COR PARA PRETO
 * 6 - MUDAR COR PARA VERMELHO
 * 7 - MUDAR COR PARA VERDE
 * 8 - MUDAR COR PARA AZUL
 * 9 - ATIVAR FLOOD FILL (atividade I)
 * - - LIMPAR TELA (não funciona...)
 * ESC - Fechar programa
 *
 * Opcoes no mause:
 * BOTAO ESQUERDO EXECUTA ACAO SELECIONADA
 * BOTAO DIREITO FINALIZA DESENHO DE POLIGONO (OPCAO 3)
 *
 * Observacoes:
 * 1) Para desenhar eh necessario selecionar a forma desejada (0 a 4), e depois clicar
 * na tela com o botao esquerdo para desenha-lo. Caso seja uma reta ou quadrilatero
 * eh preciso 2 cliques.
 * Se for um triangulo, 3 cliques. E se for um poligono, eh possivel desenhar a
 * partir de 3 cliques e logo depois clique com o botao direito para fechar
 * o poligono automaticamente.
 * 2) Para colorir uma figura, primeiro selecione uma cor e depois selecione a
 * opcao de flood fill (opcao 9).  Depois basta clicar com o botao esquerdo dentro da
 * figura e ele ira automaticamente preenche-la.
 * Tomar cuidado para usar o flood fill no fundo branco da tela. Se fizer isso
 * o programa entrará em loop pois ele vai tentar preencher o branco do fundo
 * da tela, que supostamente é infinito.
 * 3) Não foi implementado a atividade F. Não consegui usar os pontos selecionados
 * e aplicar as transformacoes apos um desenho ser feito.
 */


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "structure.h"
#include "bresenham.h"
#include "drawQuadrilateral.h"
#include "drawTriangle.h"
#include "drawPolygon.h"
#include "rasterizeCircumference.h"
#include "floodFill.h"
#include "menu.h"

// Funcoes necessarios do GLUT
void init(void);
void reshape(int w, int h);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

// Funcao que percorre a lista de pontos desenhando-os na tela
void drawPontos();

// Funcao Principal do C
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (width, height);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Editor Grafico");

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard); // funcao callback do teclado
	glRasterPos2f(5, 15);
	glutMouseFunc(mouse); // funcao callback do mouse

	glutDisplayFunc(display); //funcao callback de desenho
	init(); // Chama funcao init();
	glutMainLoop(); // executa o loop do OpenGL
	return 0; // retorna 0 para o tipo inteiro da funcao main();
}

// Funcao com alguns comandos para a inicializacao do OpenGL;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // Limpa a tela com a cor branca;
}

void reshape(int w, int h)
{
	// Reinicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Definindo o Viewport para o tamanho da janela
	glViewport(0, 0, w, h);

	width = w;
	height = h;
	glOrtho (0, w, 0, h, -1 , 1);

	// Muda para o modo GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	click1 = true;
	click2 = true;
	click3 = true;
	click4 = true;
}

// Callback para utilizacao das teclas do teclado
void keyboard(unsigned char key, int x, int y)
{
	switch (key)   // key - variavel que possui valor ASCII da tecla precionada
	{
	case 27: // codigo ASCII da tecla ESC
		exit(0); // comando pra finalizacao do programa
		break;
	case 48: // tecla 0 (desenha reta)
		menuPictures(0);
		break;
	case 49: // tecla 1 (desenha triangulo)
		menuPictures(2);
		break;
	case 50: // tecla 2 (desenha quadrado)
		menuPictures(1);
		break;
	case 51: // tecla 3 (desenha poligono)
		menuPictures(3);
		break;
	case 52: // tecla 4 (desenha circunferencia)
		menuPictures(4);
		break;
	case 53: // tecla 5 (muda para cor preto)
		menufloodFillColors(0);
		break;
	case 54: // tecla 6 (muda para cor vermelho)
		menufloodFillColors(1);
		break;
	case 55: // tecla 7 (muda para cor verde)
		menufloodFillColors(2);
		break;
	case 56: // tecla 8 (muda para cor azul)
		menufloodFillColors(3);
		break;
	case 57: // tecla 9 (ativar flood fill - preenchimento de poligono)
		menuFloodFill(0);
		break;
	}
}

// Callback para a utilizacao dos botoes do mouse
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:// Clique com o botao esquerdo identificado

		if (state == GLUT_DOWN)
		{
			if(click1 && !click2) // quando fizer o primeiro clique
			{
				click2 = true;
				pointsArray.push_back(x);
				x_2 = x;
				pointsArray.push_back(height - y);
				y_2 = height - y;
				glutPostRedisplay();
			}
			else if(click1 && click2 && !click3) // quando fizer o segundo clique
			{
				click3 = true;
				pointsArray.push_back(x);
				pointsArray.push_back(height - y);
				glutPostRedisplay();
			}
			else // quando fizer todos os cliques
			{
				click1 = true;
				pointsArray.push_back(x);
				x_1 = x;
				pointsArray.push_back(height - y);
				y_1 = height - y;
				glutPostRedisplay();
			}

		}
		break;
	case GLUT_RIGHT_BUTTON:// Clique com o botao direito identificado
		if (state == GLUT_DOWN)
		{
			// se houver 3 cliques e for maior que 3 permitir desenho (caso poligono)
			// necessario para preencher o poligo			
			if(click1 && click2 && click3 && pointsArray.size() > 3 && !click4)
			{
				aux = true;
			}
			click4 = true;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}


// Funcao usada na funcao callback para desenhar na tela
void display(void)
{
	float cor1 = 0, cor2 = 0, cor3 = 0;
	// glColor3f (0.0, 0.0, 0.0); // menu preto
	glClear(GL_COLOR_BUFFER_BIT); // Limpa o Buffer de Cores

	// barra de menu (descontinado pois nao foi possivel inserir uma imagem)
	// glBegin(GL_QUADS);
	// glVertex2f(200, 1000);
	// glVertex2f(0, 1000);
	// glVertex2f(0, 0);
	// glVertex2f(200, 0);
	// glEnd();

	glColor3f (1.0, 1.0, 1.0); // quadro branco
	// quadro de desenho
	// glBegin(GL_QUADS);
	// glVertex2f(2000, 1000);
	// glVertex2f(150, 1000);
	// glVertex2f(150, 0);
	// glVertex2f(2000, 0);
	// glEnd();

	// necessario por tamanho 5 para forcar o flood fill ficar dentro da figura
	glPointSize(5);

	if(reta && !quadrilatero && !triangulo && !poligono && !circunferencia)
	{
		// identificar cliques da reta
		if(click1 && click2)
		{
			bresenham(x_1, y_1, x_2, y_2);
			drawPontos();
			click1 = false;
			click2 = false;
			click3 = false;
			pointsArray.clear();// Limpa o vetor de pontos
		}
	}
	else if(!reta && quadrilatero && !triangulo && !poligono && !circunferencia)
	{
		// identifica cliques do poligono
		if(click1 && click2)
		{
			drawQuadrilateral(pointsArray);
			drawPontos();
			click1 = false;
			click2 = false;
			click3 = false;
			pointsArray.clear();//Limpa o vetor de pontos
		}

	}

	else if(!reta && !quadrilatero && triangulo && !poligono && !circunferencia)
	{
		// identificar sequencia de cliques do triangulo
		if(click1 && click2 && click3)
		{
			drawTriangle(pointsArray);
			drawPontos();
			click1 = false;
			click2 = false;
			click3 = false;
			click4 = false;
			pointsArray.clear();//Limpa o vetor de pontos


		}
	}
	else if(!reta && !quadrilatero && !triangulo && poligono && !circunferencia)
	{
		// identifica 3 ou mais cliques para o poligono
		if(click1 && click2 && click3 && click4)
		{
			click1 = false;
			click2 = false;
			click3 = false;
			click4 = false;
			drawPolygon(pointsArray);
			drawPontos();
			pointsArray.clear();//limpa o vetor de pontos

		}

		if(click1 && click2 && click3 && click4)
		{
			click4 = false;
		}
	}
	else if(!reta && !quadrilatero && !triangulo && !poligono && circunferencia)
	{
		// clique unico para a circunferencia
		if(click1)
		{
			rasterizeCircumference(x_1, y_1, raio);
			drawPontos();
			click1 = false;
			click2 = false;
			pointsArray.clear();//Limpa o vetor de pontos

		}

	}
	else if(floodFill_aux && !reta && !quadrilatero && !triangulo && !poligono && !circunferencia)
	{
		// identifica clique para aplicacao do flood fill
		if(click1)
		{
			float floodColor[] = {0, 0, 0};

			glPointSize(3);
			floodFill(x_1, y_1, floodFillColor, floodColor);
			click1 = false;
			click2 = false;

			pointsArray.clear();//Limpa o vetor de pontos

		}
	}
	glutSwapBuffers();
}

//Funcao que desenha os pontos contidos em uma lista de pontos
void drawPontos()
{
	ponto * pnt;
	pnt = pontos;
	glBegin(GL_POINTS); // Seleciona a primitiva GL_POINTS para desenhar
	while(pnt != NULL)
	{
		glColor3f(0, 0, 0);
		glVertex2i(pnt->x, pnt->y);
		pnt = pnt->prox;
	}
	glEnd();  // indica o fim do desenho
}
