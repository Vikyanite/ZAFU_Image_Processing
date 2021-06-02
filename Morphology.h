#pragma once
class Morphology
{
public:
	Morphology(int* sourceImg, int width, int height, int flag);
	virtual ~Morphology();
private:
	//����
	int* _sourceImg;
	int _width;
	int _height;
	int _flag; //1.�԰�ɫ������0.�Ժ�ɫ����

	//���
	int* _result;

	//�м����
	int* tempImg;

public:
	//��ʴ���ٶ��԰�ɫ��ʴ��
	void erode(int* model, int size);
	//���ͣ��ٶ��԰�ɫ���ͣ�
	void expand(int* model, int size);
	//����
	static void intersection_set(int* img_first, int* img_second, int* result_img, int size, int flag);
	//����
	static void union_set(int * img_first, int * img_second, int* result_img , int size, int flag);


	//�Ƿ����
	static bool is_equal(int* img_first, int* img_second, int size);
	//����ͼ��
	static void inverse(int* sourceImg, int* resultImg, int size);
	
	//�õ����
	int * getResult() {
		return _result;
	}
	int * getTemp() {
		return tempImg;
	}
};

