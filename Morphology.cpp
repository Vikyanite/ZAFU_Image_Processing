#include "stdafx.h"
#include "Morphology.h"

Morphology::Morphology(int* sourceImg, int width, int height, int flag)
{
	_width = width;
	_height = height;
	_flag = flag;
	_sourceImg = new int[width * height];
	tempImg = new int[width * height];
	for (int i = 0; i < width * height; ++i) {
		_sourceImg[i] = sourceImg[i];
		tempImg[i] = sourceImg[i];
	}
	
	_result = new int[_width * _height];
}

Morphology::~Morphology()
{

}

//��ʴ
//model���ṹԪ
//size���ṹԪ�ĳߴ�(size * size)
void Morphology::erode(int* model, int size)
{
	
	//ȡ������
	int radius = size / 2;
	if (_flag == 1) {
		//�԰�ɫ�ĵ���и�ʴ
		for (int x = radius; x < _width - radius; ++x) {
			for (int y = radius; y < _height - radius; ++y) {
				int index = y * _width + x;
					
				if (tempImg[index] == 0) {
					//��ɫ�ĵ㣬����ԭֵ
					_result[index] = 0;
					continue;
				}
				//(��ɫ)ȡ����
				else {
					int order = 0;
					for (int m = x - radius; m <= x + radius; ++m) {
						for (int n = y - radius; n <= y + radius; ++n) {
							_result[index] = 1;
							if (model[order] == 0) {
								//_result[index] = 0;
								//�õ㲻�������
								++order;
								continue;
							}
							int curIndex = n * _width + m;
							//ֻҪһ���㲻�ǰ�ɫ�ģ���ô�ͽ��丯ʴ
							if (tempImg[curIndex] == 0) {
								order = 0;
								_result[index] = 0;
								break;
							}
							++order;
						}
						if (!order)
							break;
					}
				}				
			}
		}
	}
	else {
		//�Ժ�ɫ�ĵ���и�ʴ
		for (int x = radius; x < _width - radius; ++x) {
			for (int y = radius; y < _height - radius; ++y) {
				int index = y * _width + x;

				if (tempImg[index] == 1) {
					//��ɫ�ĵ㣬����ԭֵ
					_result[index] = 1;
					continue;
				}
				//(��ɫ)ȡ����
				else {
					int order = 0;
					for (int m = x - radius; m <= x + radius; ++m) {
						for (int n = y - radius; n <= y + radius; ++n) {
							_result[index] = 0;
							if (model[order] == 0) {
								//_result[index] = 0;
								//�õ㲻�������
								++order;
								continue;
							}
							int curIndex = n * _width + m;
							//ֻҪһ���㲻�Ǻ�ɫ�ģ���ô�ͽ��丯ʴ
							if (tempImg[curIndex] == 1) {
								order = 0;
								_result[index] = 1;
								break;
							}
							++order;
						}
						if (!order)
							break;
					}
				}
			}
		}
	}
	for (int i = 0; i < size; ++i) {
		tempImg[i] = _result[i];
	}
}

//����(���ø�ʴ��
//model���ṹԪ
//size���ṹԪ�ĳߴ�(size * size)
void Morphology::expand(int* model, int size)
{
	int tempflag = _flag;
	if (_flag == 1)
		_flag = 0;
	else
		_flag = 1;
	erode(model, size);
	_flag = tempflag;
}

//����
void Morphology::union_set(int * img_first, int * img_second, int * result_img, int size, int flag) {
	for (int i = 0; i < size; ++i) {
		if (img_first[i] == flag || img_second[i] == flag) {
			result_img[i] = flag;
		}
		else {
			if (flag == 1) {
				result_img[i] = 0;
			}
			else {
				result_img[i] = 1;
			}
		}
	}
}

//����
void Morphology::intersection_set(int* img_first, int* img_second, int* result_img, int size, int flag) {
	for (int i = 0; i < size; ++i) {
		if (img_first[i] == flag && img_second[i] == flag) {
			result_img[i] = flag;
		}
		else {
			if (flag == 1) {
				result_img[i] = 0;
			}
			else {
				result_img[i] = 1;
			}
		}
	}
}


//�Ƿ����
bool Morphology::is_equal(int* img_first, int* img_second, int size) {
	for (int i = 0; i < size; ++i){
		if (img_first[i] != img_second[i]) {
			return false;
		}
	}

	return true;
}

//����ͼ��
void Morphology::inverse(int* sourceImg, int* resultImg, int size) {
	for (int i = 0; i < size; ++i) {
		if (sourceImg[i] == 0) {
			resultImg[i] = 1;
		}
		else
			resultImg[i] = 0;
	}
}