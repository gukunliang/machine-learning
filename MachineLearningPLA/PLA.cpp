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

double* PLA::GetWeightFromPLA(PLA_Data* data, int N, int M)
{
	double *WN = new double[M];
	for (int i = 0; i < M; i++)
	{
		WN[i] = 0.0;
	}
	for (int i = 0; i < N; i++)
	{
		double *XN = data[i].inputX;
		int Y = data[i].outputY;
		if (Sign(MatrixMultiply(WN, XN, M)) != Y)
		{
			MatrixAdd(WN, XN, M);//¸üÐÂW
		}
	}
	delete[] WN;
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

void PLA::MatrixAdd(double* a, double* b, int M)
{
	double *c = new double[M];
	for (int i = 0; i < M; i++)
	{
		a[i] += b[i];
	}
}

int PLA::Sign(double value)
{
	return value <= 0 ? -1 : 1;
}