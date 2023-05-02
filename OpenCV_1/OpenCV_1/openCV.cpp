#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2//imgproc.hpp>


using namespace cv;
using namespace std;

vector<string> Split(string s, char delimeter);
vector<float> ReadFile(string file_name);

int main()
{
	vector<float> parameters = ReadFile("CV_setting.config");

	if (parameters.empty())
	{
		cout << "Set Parameters before start" << endl;
		return 0;
	}

	float width = parameters[0];
	float height = parameters[1];

	cout << "width: " << parameters[0] << endl;
	cout << "height: " << parameters[1] << endl;

    VideoCapture cam(0);

	cam.set(CAP_PROP_FRAME_WIDTH, parameters[0]);
	cam.set(CAP_PROP_FRAME_HEIGHT, parameters[1]);

    Mat frame;

    if (!cam.isOpened())
    {
        cerr << "could not open camera" << endl;
        return -1;
    }

    while (1) { //���¿� ������ ��� sendcommand()�� ���� ��������� �����͸� �����Ѵ�. ���ۿ� ���� �� ��� failed �޽����� ����Ѵ�.

        cam >> frame;

        imshow("camera",frame);
        
        if (waitKey(30) == 27) break;
    }

    return 0;

}

vector<string> Split(string s, char delimeter)
{
	string t;
	vector<string> temp;

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == delimeter)
		{
			temp.push_back(t);
			t.clear();
			continue;
		}
		else
		{
			t.push_back(s[i]);
		}

		if (i == s.size() - 1) temp.push_back(t);
	}

	return temp;
}

/*
Parameter �� Read
txt �������� ���� ��, ����
*/

vector<float> ReadFile(string file_name)
{
	vector<float> parameters;

	ifstream read_file(file_name, ios::in);

	if (read_file.is_open())
	{
		vector<string> split_line;
		string line;
		while (!read_file.eof())
		{
			getline(read_file, line);
			if (line[0] != ' ' || line == "") continue;

			split_line = Split(line, ':');
			parameters.push_back(stof(split_line[1]));
		}

		read_file.close();
	}
	else // �ؽ�Ʈ ������ ���� ������ ��� �ӽ� �ؽ�Ʈ ����
	{
		ofstream write_file(file_name, ios::out);

		write_file << "setting:" << endl;
		write_file << "  width:" << 640 << endl;
		write_file << "  height:" << 480 << endl;

		write_file.close();
	}

	return parameters;
}

