// PlaTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../MachineLearningPLA/PLA.h"
#include "string.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
//#pragma comment(lib, "MachineLearningPLA.lib")
using namespace std;
//��������ά�ȣ�ע�⣺�����ά�Ȱ�����x0��һά
#define DIMENSION 5

void DeletePlaData(PLA_Data* plaData, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		delete[] plaData[i].inputX;
	}
	delete[] plaData;
}

int main()
{
	vector<PLA_Data> dataList;
	dataList.clear();
	PLA *instance = PLA::GetInstance();
	//char *fileName = "hw1_15_train.dat";
	//string file = "hw1_15_train.dat";
	ifstream fin("F:/machineLearning/PLA/Lib/x86_Debug/hw1_15_train.dat");
	if (!fin.is_open())
	{
		return -1;
	}
	while (!fin.eof())
	{
		PLA_Data data;
		data.inputX = new double[DIMENSION];
		data.inputX[0] = 1.0;
		for (int i = 1; i < DIMENSION; i++)
		{
			fin >> data.inputX[i];
		}
		fin >> data.outputY;
		dataList.push_back(data);
	}
	const int dataNum = dataList.size();
	double* WN = new double[DIMENSION];
	PLA_Data *plaData = new PLA_Data[dataNum];
	int totalSum = 0;
	for (int i = 1; i < 2001; i++)
	{
		random_shuffle(dataList.begin(), dataList.end());
		vector<PLA_Data>::iterator iter;
		int index = 0;
		for (iter = dataList.begin(); iter != dataList.end(); iter++)
		{
			plaData[index].inputX = iter->inputX;
			plaData[index].outputY = iter->outputY;
			index++;
		}

		int IterationNum = instance->GetWeightFromPLA(plaData, WN, dataNum, DIMENSION);
		cout << "��" << i << "�ε�����" << IterationNum << '\n';
		totalSum += IterationNum;
	}
	
	int aver = totalSum / 2000;
	cout << "ƽ������������" << aver << '\n';

	DeletePlaData(plaData, dataNum);
	delete [] WN;
	fin.close();
	while(1){}
    return 0;
}

