#pragma once

#include "ListGraph.h"
#include "Vertex.h"
#include "Arc.h"
#include "HashTable.h"
#include "Hash.h"
#include "PriorityQueue.h"
#include "Dijkstra.h"

#include <string>
#include <fstream>
#include <stdio.h>

#include<qstring.h>
#include<qfile.h>
#include<qtextstream.h>

//head for test
#include <iostream>

using namespace std;

int dataProcess() {
	QFile infoFile("SubwayInfoDatabase.txt");
	infoFile.open(QIODevice::ReadOnly);		//open file

	
	QString totalLineNumSTRING = infoFile.readLine();
	int totalLineNum = totalLineNumSTRING.toInt();

	QTextStream cin(stdin, QIODevice::ReadOnly);
	QTextStream cout(stdout, QIODevice::WriteOnly);		//allow qstring could cout
	
	cout << totalLineNum << endl;	//console
	
	ListGraph stationStorageList;
	HashTable stationHashList;

	for (int i = 0; i < totalLineNum; i++)
	{
		QString aLineSTRING = infoFile.readLine();
		QString aLineSTRING_TRIMMED = aLineSTRING.trimmed();		//tail trimmed
		QStringList readLineSpilted = aLineSTRING_TRIMMED.split(' ');		//spilt by space

		int lineNum = readLineSpilted.at(0).toInt();
		QString lineName = readLineSpilted.at(1);
		int lineTotalStationNum = readLineSpilted.at(2).toInt();

		for (int i = 3; i < (readLineSpilted.size()-3+1); i=i+2)
		{
			QString fromStation = readLineSpilted.at(i);
			QString toStation = readLineSpilted.at(i + 2);
			int distance = readLineSpilted.at(i + 1).toInt();
			
			int fromStationHash = stationHashList.insert(fromStation);
			int toStationHash = stationHashList.insert(toStation);

			
			stationStorageList.insert(fromStationHash, toStationHash, distance);
			stationStorageList.insert(toStationHash, fromStationHash, distance);	//exchange direction
		}
	}

	cout << "Type in station name:" << endl;
	QString inName;
	cin >> inName;
	int inNameHash = stationHashList.search(inName);
	cout << inNameHash << endl;

	Dijkstra test(stationHashList.hTable.size());
	test.operate(&stationStorageList, inNameHash);

	for (int i = 0; i < test.dijkstraList.size(); i++)
	{
		if (test.dijkstraList[i][0]!=0)
		{
			cout << stationHashList.hTable[i] << " : ";
			for (int j = 0; j < test.dijkstraList[i].size(); i++)
			{
				cout << stationHashList.hTable[test.dijkstraList[i][j]] << " ";
			}
			cout << endl;
		}
	}

	return 0;
}

