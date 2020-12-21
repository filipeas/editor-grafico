// Funcao responsavel por rasterizar (desenhar) circunferencia.
// o raio tem tamanho fixo no structure.h  
// em variavel padrao. Atividade (h))
void rasterizeCircumference(double x1, double y1, double rcirc)
{
	double x, y, d, de, dse;

	if(x1 != 0 && y1 != 0)
	{
		d = 1 - rcirc;
		de = 3;
		dse = -2 * rcirc + 5;
		x = 0, y = rcirc;
		
		pontos = pushPonto(x1, y1 + (int) rcirc);
		pontos = pushPonto(x1, y1 - (int) rcirc);
		pontos = pushPonto(x1 + (int) rcirc, y1);
		pontos = pushPonto(x1 - (int) rcirc, y1);

		while(y > x)
		{
			if (d < 0)
			{
				d += de;
				de += 2;
				dse += 2;
			}
			else
			{
				d += dse;
				de += 2;
				dse += 4;
				y--;
			}

			x++;
			pontos = pushPonto((int)x + x1, (int) y + y1);
			pontos = pushPonto((int)y + x1, (int) x + y1);
			pontos = pushPonto((int)y + x1, (int) - x + y1);
			pontos = pushPonto((int)x + x1, (int) - y + y1);
			pontos = pushPonto((int) - x + x1, (int) - y + y1);
			pontos = pushPonto((int) - y + x1, (int) - x + y1);
			pontos = pushPonto((int) - y + x1, (int) x + y1);
			pontos = pushPonto((int) - x + x1, (int) y + y1);
		}
	}

}