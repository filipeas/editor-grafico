void drawPolygon(std::vector<double> pointsArray)
{
	// enquanto o array de pontos tiver as coordenadas do quarto clique
	for (int i = 0 ; i < pointsArray.size(); i = i + 2)
	{
		if(pointsArray.size() - 2 == i)
		{
			bresenham((int) pointsArray[i], (int) pointsArray[i + 1], (int) pointsArray[0], (int) pointsArray[1]);
		}
		else
			bresenham((int) pointsArray[i], (int) pointsArray[i + 1], (int) pointsArray[i + 2], (int) pointsArray[i + 3]);
	}
}

void rasterizePolybon(double x1, double y1, double x2, double y2)
{
	double tamanho, Dx, Dy, x, y, ymin, xmin;
	int i = 1;
	if (abs(x2 - x1) >= abs(y2 - y1))
	{
		tamanho = abs(x2 - x1);
	}
	else
	{
		tamanho = abs(y2 - y1);
	}

	Dx = (x2 - x1) / tamanho;
	Dy = (y2 - y1) / tamanho;

	ymin = (y1 < y2) ? y1 : y2;
	xmin = (x1 < x2) ? x1 : x2;

	x = xmin;
	y = ymin;

	while(i <= tamanho)
	{
		pushPonto((int) x, (int) y);
		x = x + Dx;
		y = y + Dy;
		i++;
	}
}
