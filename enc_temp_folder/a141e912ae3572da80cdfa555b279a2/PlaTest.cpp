// PlaTest.cpp : 定义控制台应用程序的入口点。
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
//定义数据维度，注意：这里的维度包括了x0那一维
#define DIMENSION 5

void DeletePlaData(PLA_Data* plaData, int dataNum)
{
	for (int i = 0; i < dataNum; i++)
	{
		delete[] plaData[i].inputX;
	}
	delete[] plaData;
}

void CalculatePLA()
{
	vector<PLA_Data> dataList;
	dataList.clear();
	PLA *instance = PLA::GetInstance();
	//char *fileName = "hw1_15_train.dat";
	//string file = "hw1_15_train.dat";
	ifstream fin("hw1_15_train.dat");
	if (!fin.is_open())
	{
		return;
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
	size_t dataNum = dataList.size();
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
		cout << "第" << i << "次迭代：" << IterationNum << '\n';
		totalSum += IterationNum;
	}

	int aver = totalSum / 2000;
	cout << "平均迭代次数：" << aver << '\n';

	DeletePlaData(plaData, dataNum);
	delete[] WN;
	fin.close();
}

vector<PLA_Data> GetDataFromFile(string fileName)
{
	vector<PLA_Data> dataList;
	dataList.clear();
	ifstream fin("hw1_18_train.dat");
	if (!fin.is_open())
	{
		return dataList;
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
	fin.close();
	return dataList;
}

void CalculatePocketPLA()
{
	
	PLA *instance = PLA::GetInstance();
	string trainFileName = "hw1_18_train.dat";
	vector<PLA_Data> dataList = GetDataFromFile(trainFileName);
	vector<PLA_Data> testDataList = GetDataFromFile("hw1_18_test.dat");
	size_t dataNum = dataList.size();
	double* WN = new double[DIMENSION];
	PLA_Data *plaData = new PLA_Data[dataNum];
	PLA_Data *testPlaData = new PLA_Data[dataNum];
	vector<PLA_Data>::iterator iter;
	int index = 0;
	for (iter = testDataList.begin(); iter != testDataList.end(); iter++)
	{
		testPlaData[index].inputX = iter->inputX;
		testPlaData[index].outputY = iter->outputY;
		index++;
	}

	double totalSum = 0;
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

		instance->PocketPLA(plaData, WN, dataNum, DIMENSION, 49);
		double averError = instance->AverErrorOfPocketPLA(testPlaData, WN, dataNum, DIMENSION);
		cout << "第" << i << "次迭代误差：" << averError << '\n';
		totalSum += averError;
	}

	double aver = totalSum / 2000;
	cout << "平均误差：" << aver << '\n';

	DeletePlaData(plaData, dataNum);
	DeletePlaData(testPlaData, dataNum);
	delete[] WN;
	
}

int main()
{
	CalculatePocketPLA();
	while(1){}
    return 0;
}

