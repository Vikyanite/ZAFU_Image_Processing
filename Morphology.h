#pragma once
class Morphology
{
public:
	Morphology(int* sourceImg, int width, int height, int flag);
	virtual ~Morphology();
private:
	//输入
	int* _sourceImg;
	int _width;
	int _height;
	int _flag; //1.对白色操作；0.对黑色操作

	//输出
	int* _result;

	//中间变量
	int* tempImg;

public:
	//腐蚀（假定对白色腐蚀）
	void erode(int* model, int size);
	//膨胀（假定对白色膨胀）
	void expand(int* model, int size);
	//交集
	static void intersection_set(int* img_first, int* img_second, int* result_img, int size, int flag);
	//并集
	static void union_set(int * img_first, int * img_second, int* result_img , int size, int flag);


	//是否相等
	static bool is_equal(int* img_first, int* img_second, int size);
	//反向图像
	static void inverse(int* sourceImg, int* resultImg, int size);
	
	//得到结果
	int * getResult() {
		return _result;
	}
	int * getTemp() {
		return tempImg;
	}
};

