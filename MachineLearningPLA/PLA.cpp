#define PLA_EXPORT

#include "stdlib.h"
#include "PLA.h"

PLA::PLA()
{}
PLA::~PLA()
{

}

PLA* PLA::m_instance = NULL;
PLA* PLA::GetInstance()
{
	if (NULL == m_instance)
	{
		m_instance = new PLA();
	}
	return m_instance;
}

int PLA::GetWeightFromPLA(PLA_Data* data, double* WN, int N, int M)
{
	int num = 0;
	for (int i = 0; i < M; i++)
	{
		WN[i] = 0.0;
	}
	while (1)
	{
		
		int j = 0;
		for (int i = 0; i < N; i++)
		{
			double *XN = data[i].inputX;
			int Y = data[i].outputY;
			if (Sign(MatrixMultiply(WN, XN, M)) != Y)
			{
				MatrixAdd(WN, XN, Y, M);//更新W
				j = 0;
				num++;
				//break;               //跳出for循环
			}
			else
			{
				j++;
			}
			if (j == N)
			{
				break;
			}
		}
		if (j == N)//转了一圈大家都合适就停止迭代
		{
			break;
		}
	}

	return num;
}

double PLA::MatrixMultiply(double* a, double* b, int M)
{
	double sum = 0.0;
	for (int i = 0; i < M; i++)
	{
		sum += a[i] * b[i];
	}
	return sum;
}

void PLA::MatrixAdd(double* a, double* b, int y, int M)
{
	double *c = new double[M];
	for (int i = 0; i < M; i++)
	{
		a[i] += b[i] * y;
	}
}

int PLA::Sign(double value)
{
	return value <= 0 ? -1 : 1;

}

void PLA::PocketPLA(PLA_Data* data, double* WN, int N, int M, int itertorNum)
{
	if (itertorNum < 1)
	{
		return;
	}

	int num = 0;
	for (int i = 0; i < M; i++)
	{
		WN[i] = 0.0;
	}
	double *pocketWN = WN;
	double error = AverErrorOfPocketPLA(data, WN, N, M);

	int index = 0;
	while (num < itertorNum)
	{	
		double *XN = data[index].inputX;
		int Y = data[index].outputY;
		if (Sign(MatrixMultiply(XN, WN, M)) != Y)
		{
			MatrixAdd(WN, XN, Y, M); //更新WN
			double newError = AverErrorOfPocketPLA(data, WN, N, M);
			if (newError < error)
			{
				error = newError;
				pocketWN = WN;
			}
			num++;
		}

		if (index >= N - 1)
		{
			index = 0;
		}
		else
		{
			index++;
		}
	}
	WN = pocketWN;
}

double PLA::AverErrorOfPocketPLA(PLA_Data* data, double* WN, int N, int M)
{
	double sum = 0.0;
	for (int i = 0; i < N; i++)
	{
		double *XN = data[i].inputX;
		int Y = data[i].outputY;
		if (Sign(MatrixMultiply(XN, WN, M)) != Y)
		{
			sum++;
		}
	}

	return sum / N;
}