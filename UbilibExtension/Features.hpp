/*
����:2015.09.30
����:κ����,��˧ ���
���ܣ�ubilib ������ 
*/

#ifndef Features_h
#define Features_h
#include<stdlib.h>
#include<math.h>
#include <vector>
#include "FFT.hpp"
using namespace std;
class Features
{
		
public :
    //1��������Сֵ
	template<typename T>
	static T miniNum(std::vector<T> data)
	{
		int length = data.size();
		T min = data[0];
		for (int i = 1; i < length; i++)
			min = data[i]<min ? data[i] : min;
		return min;
	}

	//2���������ֵ
	template<typename T>
	static T maxiNum(std::vector<T> data)
	{
		int length = data.size();
		T max = data[0];
		for (int i = 1; i<length; i++)
			max = data[i]<max ? max : data[i];
		return max;
	}

	//3�������ƽ��ֵ
	template<typename T>
	static T mean(std::vector<T> data)
	{
		int length = data.size();
		T sum = 0;
		for (int i = 0; i < length; i++)
			sum = sum + data[i];
		return sum / length;
	}

	//4������ļ�Ȩ��ֵ
	template<typename T>
	static T weightMean(std::vector<T> data)
	{
		//int length = data.size();
		double sum = 0;
		T result;
		double w[5] = { 0.15, 0.15, 0.2, 0.2, 0.3 };
		for (int i = 0; i < 5; i++)
			sum = sum + data[i + 5] * w[i];
		result = T(sum);
		return result;
	}

	//5������ı�׼��
	template<typename T>
	static T standardDeviation(std::vector<T> data)
	{
		int length = data.size();
		T average = 0, s = 0, sum = 0;
		for (int i = 0; i<length; i++)
		{
			sum = sum + data[i];
		}
		average = sum / length;
		for (int i = 0; i<length; i++)
		{
			s = s + pow(data[i] - average, 2);// ƫ��ƽ�����ľ���� 
		}
		s = s / length;//���� 
		s = sqrt(s); //��׼�� 
		return s;
	}

	//6���ź�������ֵ
	template<typename T>
	static T signalVectorMagnitude(std::vector<T> data)
	{
		int length = data.size();
		T maxMagnitude = 0;
		for (int i = 0; i < length; i++){
			if (data[i] < 0)
				maxMagnitude = (-data[i])<maxMagnitude ? maxMagnitude : (-data[i]);
			else
				maxMagnitude = data[i]<maxMagnitude ? maxMagnitude : data[i];
		}
		return maxMagnitude;
	}

	//7���������λ��
	template<typename T>
	static T median(std::vector<T> data)
	{
		int length = data.size();
		T *copydata = new T[length];
		for (int i = 0; i < length; i++)
		{
			copydata[i] = data[i];
		}
		T medium;
		for (int i = 0; i<length; i++)
		{
			for (int j = i + 1; j<length; j++)
			{
				if (copydata[j]<copydata[i])
				{
					T t;
					t = copydata[i];
					copydata[i] = copydata[j];
					copydata[j] = t;
				}
			}
		}

		if (length % 2 == 1)
			medium = copydata[length / 2];
		else
			medium = (copydata[length / 2 - 1] + copydata[length / 2]) / 2;
		return medium;
	}

	//8������1/4��λ��
	template<typename T>
	static T firstQuartile(std::vector<T> data)
	{
		int length = data.size();
		T *copydata = new T[length];
		for (int i = 0; i < length; i++)
		{
			copydata[i] = data[i];
		}
		for (int i = 0; i<length; i++)
		{
			for (int j = i + 1; j<length; j++)
			{
				if (copydata[j]<copydata[i])
				{
					T t;
					t = copydata[i];
					copydata[i] = copydata[j];
					copydata[j] = t;
				}
			}
		}
		T q = 1 + (length - 1) *0.25;
		int b = int(q);
		T d = q - b;
		T quartile1 = copydata[b-1] + (copydata[b] - copydata[b-1])*d;
		return quartile1;
	}

	//9������3/4��λ��
	template<typename T>
	static T thirdQuartile(std::vector<T> data)
	{
		int length = data.size();
		T *copydata = new T[length];
		for (int i = 0; i < length; i++)
		{
			copydata[i] = data[i];
		}
		for (int i = 0; i<length; i++)
		{
			for (int j = i + 1; j<length; j++)
			{
				if (copydata[j]<copydata[i])
				{
					T t;
					t = copydata[i];
					copydata[i] = copydata[j];
					copydata[j] = t;
				}
			}
		}
		T q = 1 + (length - 1) *0.75;
		int b = int(q);
		T d = q - b;
		T quartile3 = copydata[b-1] + (copydata[b] - copydata[b-1])*d;
		return quartile3;
	}

	//10�����������
	template<typename T>
	static T zeroCrossingRate(std::vector<T> data)
	{
		int length = data.size();
		T num = 0;
		for (int i = 0; i < length - 1; i++)
		{
			if (data[i] * data[i + 1]< 0){
				num++;
			}
		}
		return num / length;
	}

	//11���������ֵ��
	template<typename T>
	static T meanCrossingsRate(std::vector<T> data)
	{
		int length = data.size();
		T sum = 0;
		int num = 0;
		T *copydata = new T[length];
		for (int i = 0; i < length; i++)
		{
			copydata[i] = data[i];
			sum = sum + data[i];
		}
		T avg = sum / length;
		for (int i = 0; i < length; i++)
		{
			copydata[i] = copydata[i] - avg;
		}
		for (int i = 0; i < length - 1; i++)
		{
			if (copydata[i] * copydata[i+1]< 0){
				num++;
			}
		}
		return (T)num / length;
	}

	//12�����ϵ��
	template<typename T>
	static T correlationCoefficient(std::vector<T> data1, std::vector<T> data2)
	{
		int length1=data1.size();
		//int length2=data2.size();
		T mean1 = Features::mean(data1);
		T mean2 = Features::mean(data2);
		T covariance = 0.0;
		for (int i = 0; i < length1; i++)
		{
			covariance += (data1[i] - mean1)*(data2[i] - mean2);
		}
		T standarddeviation1 = Features::standardDeviation(data1);
		T standarddeviation2 = Features::standardDeviation(data2);
		return (covariance / length1) / (standarddeviation1*standarddeviation2);
	}

	
	//15������ķ���
	template<typename T>
	static T variance(std::vector<T> data)
	{
		int length = data.size();
		if (length == 0) return 0;
		T average = 0, s = 0, sum = 0;
		for (int i = 0; i<length; i++)
		{
			sum = sum + data[i];
		}
		average = sum / length;
		for (int i = 0; i<length; i++)
		{
			s = s + pow(data[i] - average, 2);// ƫ��ƽ�����ľ���� 
		}
		s = s / length;//���� 
		return s;
	}

	//16�����е����ֵ���ڵ�λ��-�׷�λ��
	template<typename T>
	static T spectrumPeakPosition(std::vector<T> data)
	{
		int length = data.size();
		if (length == 0)return 0;
		T max = data[0];
		int location = 0;
		for (int i = 1; i < length; i++){
			if (data[i] > max) {
				location = i;
				max = data[i];
			}
		}
		return location;
	}

	//17Ƶ������
	template<typename T>
	static T spectralEnergy(std::vector<T> data){
		int length = data.size();
		if ( length == 0) return 0;
		T sum = 0;
		for (int i = 0; i<length; i++){
			sum += pow(data[i], 2);
		}
		return sum / length;
	}

	//18����
	template<typename T>
	static T spectralEntropy(std::vector<T> data){
		int length = data.size();
		if ( length == 0) return 0;
		T temp;
		T sum = 0;
		for (int i = 0; i<length; i++){
			temp = data[i];
			if (temp > 0){
				sum += log(temp)*temp;
			}
		}
		return sum*-1;
	}

	//19����
	template<typename T>
	static T centroid(std::vector<T> data){
		int length = data.size();
		if ( length == 0) return 0;
		T sum1 = 0;
		T sum2 = 0;
		T temp;
		T tempPow;
		for (int i = 0; i<length; i++){
			temp = data[i];
			tempPow = temp*temp;
			sum1 += tempPow;
			sum2 += tempPow*i;
		}
		return sum2 / sum1;
	}

	//20��������ֵ
	template<typename T>
	static T rms(std::vector<T> data){
		int length = data.size();
		T rms = 0;
		T sum = 0;
		for (int i = 0; i<length; i++){
			sum += pow(data[i], 2);
		}
		rms = sqrt(sum / length);
		return rms;
	}

	//21������ֵ��� ����ɢֵ����ۼ�����Ȼ������ܳ��ȡ�ʵ����ƽ��ÿʱ�̵������
	template<typename T>
	static T sma(std::vector<T> data, T interval){
		int length = data.size();
		T sum = 0;
		T lot = length * interval;
		int i;
		for (i = 0; i<length; i++){
			sum += data[i] * interval;
		}
		return sum / lot;
	}

	//22�ķ�������
	template<typename T>
	static T iqr(std::vector<T> data){
		//int length = data.size();
		return Features::thirdQuartile(data) - Features::firstQuartile(data);
	}

	//23����ƽ��ֵ
	template<typename T>
	static T  absMean(std::vector<T> data){
		int length = data.size();
		if ( length == 0) return 0;
		T meanD = mean(data);
		T sum = 0;
		int i;
		for (i = 0; i<length; i++){
			sum += fabs(data[i] - meanD);
		}
		return sum / length;
	}

	//24Ƶ��ƫ��
	template<typename T>
	static T  frequencySkew(std::vector<T> data){
		int length = data.size();
		if ( length == 0) return 0;
		T meanD = mean(data);
		T dev = standardDeviation(data);
		T sum = 0;
		int i;
		for (i = 0; i<length; i++){
			sum += pow((data[i] - meanD) / dev, 3);
		}
		return sum / length;
	}

	//25Ƶ����
	template<typename T>
	static T  frequencyKurt(std::vector<T> data){
		int length = data.size();
		if ( length == 0) return 0;
		T meanD = mean(data);
		T dev = standardDeviation(data);
		T sum = 0;
		int i;
		for (i = 0; i<length; i++){
			sum += pow((data[i] - meanD) / dev, 4) - 3;
		}
		return sum / length;
	}
	
	//26ʱ������
	template<typename T>
	static T  tenergy(std::vector<T> data){
		int length = data.size();
		if(length == 0){
			return 0;
		} 
        return spectralEnergy(data);
	}
    
	//27Ƶ���׼��
	template<typename T>
	static T  fdev(std::vector<T> data){
		int length = data.size();
		if(length == 0){
			return 0;
		} 
        return standardDeviation(data);
	}
	
	//28Ƶ��ƽ��ֵ
	template<typename T>
	static T  fmean(std::vector<T> data){
		int length = data.size();
		if(length == 0){
			return 0;
		} 
        return mean(data);
	}
	
	/*
	 * ��ΪFFT������ԶԸ����ⳤ�ȵ�FFT�任������Ϊ�˱�����������ﻹ�ǶԸ���Ҷ�������ж�
	 * ��fft���ƻ�data����,��Ȼ���ô���
	 * ��fft����fftdata���飨�������һ�볤�ȵ�double���飩
    */
    static std::vector<double>   fft(std::vector<double> &data) {
		std::vector<double> fftdata;
		size_t n = data.size();	//data��ʵ�ʳ���
		unsigned int N = n;//data�����ĳ���	
		if (n < 4 )
		{
			return fftdata;
		}else if ((n & (n - 1)) != 0)  // Is not power of 2,/*�����2���ݣ�nһ����100... n-1����01111....*/
		{
			/*************************************** 
			* unsigned int���͵��������������λ1 
			* ��λ�� 
			* ���磺0000 0000 0000 0001�з���0 
			*       0000 0000 1111 0000�з���7������4 
			*****************************************/ 
			//���n������Ķ����Ƶ���ߵ�1
			int position=0;  
			unsigned int m=n;  
			while(m)  
			{  
		        m=m>>1;  
		        if(m)  position++;  
		    } 		 
			N = 1<<(position+1);
		}
		//����real,imag���飬������N
		vector<double> real(n);
		vector<double> imag(n);
		for (vector<double>::iterator it = data.begin(); it != data.end(); ++it)
		{
			real.push_back(*it);
			imag.push_back(0);
		}	
		unsigned int k = N - n;
		while(k--){
			real.push_back(0.0f);
			imag.push_back(0.0f);
		}
		N = real.size();
		if((N & (N - 1)) != 0) 
			throw "fft pre process error";
		else
			FFT::transformRadix2(real, imag);

		//ÿ��fft�㣬����ģֵmath.hypot(img,rel)�����Ƶ����ԭʼ�źŷ��ȵģ�N/2����,
		//���ԣ�Ҫ��ÿ��fft[i].abs()���ԣ�N/2�������źŵ���������
		unsigned  int fN = N/2;
		for(unsigned int i=1;i<fN+1;i++)
		{
			double amp = std::sqrt(real[i]*real[i] + imag[i]*imag[i]);
			amp = amp * 2.0/(double)N;
			fftdata.push_back(amp);
		}
		//������أ�fftdata�ᱻc++����vector��move���¿���һ�����أ��ο�
		//http://stackoverflow.com/questions/22655059/why-it-is-ok-to-return-vector-from-function
		return fftdata;
	}	


};
#endif
