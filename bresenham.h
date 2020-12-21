// Funcao que implementa bresenham (atividade a) e b))
void bresenham(double x1, double y1, double x2, double y2)
{
	double dx, dy, x, y, d, aux, ince, incne;
	bool dec = false, simc = false;

	dx = x2 - x1; // realizando calculo do delta x
	dy = y2 - y1; // realizando calculo do delta y

	if (dx * dy < 0)
	{
		y1 = -y1;
		y2 = -y2;
		dy = -dy;
		simc = true;
	}

	if(abs(dx) < abs(dy))
	{
		aux = y1;
		y1 = x1;
		x1 = aux;

		aux = y2;
		y2 = x2;
		x2 = aux;

		aux = dx;
		dx = dy;
		dy = aux;
		dec = true;
	}

	if(x1 > x2)
	{
		aux = x1;
		x1 = x2;
		x2 = aux;

		aux = y1;
		y1 = y2;
		y2 = aux;

		dx = -dx;
		dy = -dy;
	}

	d = 2 * dy - dx;
	ince = 2 * dy;
	incne = 2 * (dy - dx);

	while(x1 < x2)
	{
		x = x1;
		y = y1;

		if(dec == true)
		{
			aux = x;
			x = y;
			y = aux;
		}

		if(simc == true)
		{
			y = -y;
		}

		if (d <= 0)
			d += ince;
		else
		{
			d += incne;
			y1++;
		}
		
		x1 += 1;
		pontos = pushPonto(x, y);
	}
}