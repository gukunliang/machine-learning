#pragma once

#ifdef PLA_EXPORT
#define  PLA_API _declspec(dllexport)
#else
#define PLA_API _declspec(dllimport)
#endif

typedef struct
{
	double* inputX;
	int outputY;
}PLA_Data;

class PLA_API PLA
{
public:
	static PLA* GetInstance();
	~PLA();
public:

	//data为输入输出数据,WN为权矢量，N为数据总数，M为inputX维度，返回为迭代次数
	int GetWeightFromPLA(PLA_Data* data, double* WN, int N, int M);

private:
	double MatrixMultiply(double* a, double* b, int M);
	void MatrixAdd(double* a, double* b, int y, int M);
	int Sign(double value);

private:
	static PLA* m_instance;
	PLA(void);
	class DeleteInstance
	{
	public:
		~DeleteInstance()
		{
			if (PLA::m_instance)
			{
				delete PLA::m_instance;
				PLA::m_instance = NULL;
			}
		}
	};
	static DeleteInstance  deleteInstance;
};

