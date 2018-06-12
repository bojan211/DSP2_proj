#include "ImageInterpolation.h"
#include "ColorSpaces.h"
#include <math.h>


void sampleAndHold(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
	double scaleX = ((double)xSize) / newXSize;
	double scaleY = ((double)ySize) / newYSize;
	for (int i = 0; i < newXSize; i++)
	{
		for (int j = 0; j < newYSize; j++)
		{
			int I_za_malu_sliku = floor((i - 1) * scaleX + 1);
			int J_za_malu_sliku = floor((j - 1) * scaleY + 1);
			
			if (I_za_malu_sliku >= xSize) {
				I_za_malu_sliku = xSize - 1;
			}
			
			if (J_za_malu_sliku >= ySize) {
				J_za_malu_sliku = ySize - 1;
			}
			
			output[3 * i + j * newXSize * 3] = input[3 * I_za_malu_sliku + J_za_malu_sliku * xSize * 3];
			output[3 * i + 1 + j * newXSize * 3] = input[3 * I_za_malu_sliku + 1 + J_za_malu_sliku * xSize * 3];
			output[3 * i + 2 + j * newXSize * 3] = input[3 * I_za_malu_sliku + 2 + J_za_malu_sliku * xSize * 3];
		}
	}
}

void bilinearInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
	double scaleX = ((double)xSize) / newXSize;
	double scaleY = ((double)ySize) / newYSize;
	for (int i = 0; i < newXSize; i++)
	{
		for (int j = 0; j < newYSize; j++)
		{
			int I_za_malu_sliku = (i)* scaleX;
			int J_za_malu_sliku = (j)* scaleY;
			double a = j / scaleY - floor(j / scaleY);
			double b = i / scaleX - floor(i / scaleX);

			output[3 * i + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * I_za_malu_sliku + J_za_malu_sliku * xSize * 3] +
				(1 - a) * b * input[3 * (I_za_malu_sliku + 1) + J_za_malu_sliku * xSize * 3] +
				a * (1 - b) * input[3 * I_za_malu_sliku + (J_za_malu_sliku + 1) * xSize * 3] +
				a * b * input[3 * (I_za_malu_sliku + 1) + (J_za_malu_sliku + 1) * xSize * 3];
			output[3 * i + 1 + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * I_za_malu_sliku + 1 + J_za_malu_sliku * xSize * 3] +
				(1 - a) * b * input[3 * (I_za_malu_sliku + 1) + 1 + J_za_malu_sliku * xSize * 3] +
				a * (1 - b) * input[3 * I_za_malu_sliku + 1 + (J_za_malu_sliku + 1) * xSize * 3] +
				a * b * input[3 * (I_za_malu_sliku + 1) + 1 + (J_za_malu_sliku + 1) * xSize * 3];
			output[3 * i + 2 + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * I_za_malu_sliku + 2 + J_za_malu_sliku * xSize * 3] +
				(1 - a) * b * input[3 * (I_za_malu_sliku + 1) + 2 + J_za_malu_sliku * xSize * 3] +
				a * (1 - b) * input[3 * I_za_malu_sliku + 2 + (J_za_malu_sliku + 1) * xSize * 3] +
				a * b * input[3 * (I_za_malu_sliku + 1) + 2 + (J_za_malu_sliku + 1) * xSize * 3];
		}
	}
}

void bicubicInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
}

void imageSwirl(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double k1)
{
	/* TO DO */
	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			double di = i - m;
			double dj = j - n;
			double r = sqrt(pow(di, 2) + pow(dj, 2));
			double ugao = k1 * 3.14159265 * r;
			int I_za_malu_sliku = cos(ugao) * di - sin(ugao) * dj + m;
			int J_za_malu_sliku = sin(ugao) * di + cos(ugao) * dj + n;

			if (I_za_malu_sliku >= 0 && I_za_malu_sliku < xSize && J_za_malu_sliku >= 0 && J_za_malu_sliku < ySize) // provera da li je u opsegu
			{
				output[3 * i + j * xSize * 3] = input[3 * I_za_malu_sliku + J_za_malu_sliku * xSize * 3];
				output[3 * i + 1 + j * xSize * 3] = input[3 * I_za_malu_sliku + 1 + J_za_malu_sliku * xSize * 3];
				output[3 * i + 2 + j * xSize * 3] = input[3 * I_za_malu_sliku + 2 + J_za_malu_sliku * xSize * 3];
			}
			else //Piksele u okviru izlazne slike za koje su izraèunate koordinate van opsega ulazne slike punim crnom bojom. 
			{
				output[3 * i + j * xSize * 3] = 0;
				output[3 * i + 1 + j * xSize * 3] = 0;
				output[3 * i + 2 + j * xSize * 3] = 0;
			}
		}
	}
}

void imageSwirlBilinear(const uchar input[], int xSize, int ySize, uchar output[], int m, int n, double k1)
{
	/* TO DO */
	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			double di = i - m;
			double dj = j - n;
			double r = sqrt(pow(di, 2) + pow(dj, 2));
			double ugao = k1 * 3.14159265 * r;

			double disI = cos(ugao) * di - sin(ugao) * dj + m;
			double disJ = sin(ugao) * di + cos(ugao) * dj + n;

			int I_za_malu_sliku = floor(disI);
			int J_za_malu_sliku = floor(disJ);

			double a = disJ - J_za_malu_sliku;
			double b = disI - I_za_malu_sliku;

			if (I_za_malu_sliku >= 0 && I_za_malu_sliku + 1 < xSize && J_za_malu_sliku >= 0 && J_za_malu_sliku + 1 < ySize)
			{
				output[3 * i + j * xSize * 3] =
					(1 - a) * (1 - b) * input[3 * I_za_malu_sliku + J_za_malu_sliku * xSize * 3] +
					(1 - a) * b * input[3 * (I_za_malu_sliku + 1) + J_za_malu_sliku * xSize * 3] +
					a * (1 - b) * input[3 * I_za_malu_sliku + (J_za_malu_sliku + 1) * xSize * 3] +
					a * b * input[3 * (I_za_malu_sliku + 1) + (J_za_malu_sliku + 1) * xSize * 3];
				output[3 * i + 1 + j * xSize * 3] =
					(1 - a) * (1 - b) * input[3 * I_za_malu_sliku + 1 + J_za_malu_sliku * xSize * 3] +
					(1 - a) * b * input[3 * (I_za_malu_sliku + 1) + 1 + J_za_malu_sliku * xSize * 3] +
					a * (1 - b) * input[3 * I_za_malu_sliku + 1 + (J_za_malu_sliku + 1) * xSize * 3] +
					a * b * input[3 * (I_za_malu_sliku + 1) + 1 + (J_za_malu_sliku + 1) * xSize * 3];
				output[3 * i + 2 + j * xSize * 3] =
					(1 - a) * (1 - b) * input[3 * I_za_malu_sliku + 2 + J_za_malu_sliku * xSize * 3] +
					(1 - a) * b * input[3 * (I_za_malu_sliku + 1) + 2 + J_za_malu_sliku * xSize * 3] +
					a * (1 - b) * input[3 * I_za_malu_sliku + 2 + (J_za_malu_sliku + 1) * xSize * 3] +
					a * b * input[3 * (I_za_malu_sliku + 1) + 2 + (J_za_malu_sliku + 1) * xSize * 3];
			}
			else
			{
				output[3 * i + j * xSize * 3] = 0;
				output[3 * i + 1 + j * xSize * 3] = 0;
				output[3 * i + 2 + j * xSize * 3] = 0;
			}
		}
	}
}