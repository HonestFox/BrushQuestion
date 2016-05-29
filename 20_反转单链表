#include "BigData.h"
#include <cassert>
#include <cstdlib>
#define MAX_INT64 0x7FFFFFFFFFFFFFFF
#define MIN_INT64 0x8000000000000000

BigData::BigData(INT64 value)
	:_value(value)
{
	//先获取value的位数
	int sz = _GetSize(value);
	_strData.resize(sz + 1);
	_strData[0] = '+';
	if (value < 0)
	{
		_strData[0] = '-';
	}
	char *StrTmp = new char[sz + 2];
	_i64toa_s((INT64)value, StrTmp, sz + 2, 10);
	if (value > 0)
	{
		for (int Idx = 1; Idx <= sz; Idx++)
		{
			_strData[Idx] = StrTmp[Idx - 1];
		}
	}
	else
	{
		for (int Idx = 1; Idx <= sz; Idx++)
		{
			_strData[Idx] = StrTmp[Idx];
		}
	}
	delete []  StrTmp;
}

BigData::BigData(char * pData)
{
	assert(pData);
	char cSymbol = pData[0];
	//处理第一位
	if (cSymbol >= '0' && cSymbol <= '9')
	{
		cSymbol = '+';
	}
	else if(cSymbol == '+' || cSymbol == '-' )
	{
		++pData;
	}
	else
	{
		_value = UN_INIT;
		return;
	}
	//去掉前面的 ‘0’
	while (*pData == '0')
	{
		++pData;
	}
	//转化
	_strData.resize(strlen(pData) + 1);
	_strData[0] = '+';
	int iCount = 1;
	_value = 0;
	while (*pData <= '9' && *pData >= '0')
	{
		_strData[iCount++] = *pData;
		_value = _value * 10 + *pData - '0';
		pData++;
	}
	if (*pData != '\0')
	{
		_strData.resize(iCount + 1);
	}
	if (cSymbol == '-')
	{
		_value = 0 - _value;
		_strData[0] = '-';
	}
}

bool BigData::IsINT64Overflow() const
{
	string temp("+9223372036854775807");
	if ('-' == _strData[0])
	{
		temp = "-9223372036854775807";
	}

	if (_strData.size() < temp.size())
	{
		return false;  //没有溢出 （长度小）
	}
	else if (_strData.size() == temp.size() && _strData <= temp)
	{
		return false;	//没有溢出（长度相等，但在范围内）
	}
	return true;
}

ostream & operator<<(ostream & os, BigData & bd)
{
	if (!bd.IsINT64Overflow())
	{
		os << bd._value;
	}
	else
	{
		char *pData = (char*)bd._strData.c_str();
		if ('+' == bd._strData[0])
		{
			pData++;
		}
		os << pData;
	}
	return os;
}


/*
	加法
	内置类型：
		相加的结果没有超出范围
		相加的结果超出范围
	超出内置类型：

*/
BigData BigData::operator+(const BigData & bigData)
{
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
	{
		if (_strData[0] != bigData._strData[0])		//符号位不同，则可以直接运算，肯定不会溢出的
		{
			return BigData(_value + bigData._value);
		}
		else             //else里面处理符号相同的情况
		{  
			// -10         -7 + -1             -10 - -7 
			if(
				(_strData[0] == '+' && (MAX_INT64 - _value) >= bigData._value)
			||( _strData[0] == '-' &&   (MIN_INT64 - _value) <= bigData._value)
				)			//保证在范围内，直接运算
			{
				return BigData(_value + bigData._value);
			}
		}
	}
	//操作数至少有一个溢出
	//或相加的结果溢出
	if (_strData[0] == bigData._strData[0] )
	{
		return BigData((char*)Add(_strData, bigData._strData).c_str());
	}
	//符号相反
	return BigData((char*)Sub(_strData, bigData._strData).c_str());
}

//只要进入Add，则一定符号相同
string BigData::Add(string left, string right)
{
	int LSize = left.size();
	int RSize = right.size();
	char cStep = 0;  //进位
	if (LSize < RSize)	//保证左边数大
	{
		swap(left, right);
		swap(LSize, RSize);
	}
	string strRet;
	strRet.resize(LSize + 1);
	strRet[0] = left[0];
	//从低位到高位，逐位相加
	for (int index = 1; index < LSize; index++)
	{
		char cRet = left[LSize - index] + cStep - '0';
		if (RSize - index > 0)
		{
			cRet += right[RSize - index] - '0';
		}
		strRet[LSize - index + 1] = cRet % 10 + '0';  //考虑到符号位，因此下标需要+1
		cStep = cRet / 10;
	}
	strRet[1] = cStep + '0';
	return strRet;
}

/*
	减法
	如果两个数据都没有溢出
		同号：直接相减
		异号：
	如果两个数据中至少有一个数据超出，或者相减结果超出
*/
BigData BigData::operator-(const BigData & bigData)
{
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow() )
	{
		if (_strData[0] == bigData._strData[0])			//都在范围内，符号相同
		{
			return BigData(_value - bigData._value);
		}
		else                     //都在范围内，但符号不同
		{
			if (				//  保证在范围内的情况															
				(_strData[0] == '+' && (MAX_INT64 - _value) >= (bigData._value * -1) )
				|| (_strData[0] == '-' && (MIN_INT64 - _value) <= (bigData._value * -1) )
				)
			{
				return BigData(_value - bigData._value);
			}
			else    //可能在范围外的情况
			{
				return BigData((char*)Sub(_strData, bigData._strData).c_str());
			}
		}
	}
	else if (_strData[0] != bigData._strData[0])	//一定在范围外的情况
	{
		return BigData((char*)Sub(_strData, bigData._strData).c_str() );
	}
	return BigData((char*)Sub(_strData, bigData._strData).c_str());

}

string BigData::Sub(string left, string right)
{
	//发生调用该函数时，left和right两个参数一定是相同符号的
	int LSize = left.size();
	int RSize = right.size();
	char cSymbol = left[0];
	if (LSize < RSize || LSize == RSize && left < right)		//这种情况下，减出来的结果一定为负数
	{
		swap(left, right);				//有问题
		swap(LSize, RSize);
		if (cSymbol = '+')
		{
			cSymbol = '-';				//所以每次符号都一定是负号
		}
		else
		{
			cSymbol = '+';
		}
	}

	string strRet;
	strRet.resize(left.size() );
	strRet[0] = cSymbol;
	//逐位做减法
	for (int iIdx = 1; iIdx < LSize; iIdx++)
	{
		char cRet = left[LSize - iIdx] - '0';
		if (RSize - iIdx > 0)
		{
			cRet -= right[RSize - iIdx] - '0';
		}
		//借位
		if (cRet < 0)
		{
			left[LSize - iIdx - 1]--;
			cRet += 10;
		}
		strRet[LSize - iIdx] = cRet + '0';
	}
	return strRet;
}


/*
		乘法
		两个数都没有超出结果也没有超出：
			直接乘（同号异号的问题）
		至少有一个超出，或者结果超出：
			Mul()
			【存在问题】：当两个数特别大时，程序会崩溃
*/
BigData BigData::operator*(const BigData & bigData)
{
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow() )
	{
		//如果两个操作数有一个为0 直接返回0   这里检查一下，有可能有问题
		if (_value == 0 || bigData._value == 0)
		{
			return BigData("0");
		}

		if (_strData[0] == bigData._strData[0] )	//如果符号相同
		{
			if (
				_strData[0] == '+'  && MAX_INT64 / _value >= bigData._value				//这里检查一下，估计有问题
				|| _strData[0] == '0' && MIN_INT64 / _value <= bigData._value
				)
			{
				return BigData(_value * bigData._value);
			}
		}
		else    //异号
		{
			if (_strData[0] == '+'  && MAX_INT64 / _value <= bigData._value				//这里检查一下，估计有问题
				|| _strData[0] == '0' && MIN_INT64 / _value >= bigData._value
				)
			{
				return BigData(_value * bigData._value);
			}
		}
	}
	return BigData((char*)(Mul(_strData, bigData._strData).c_str()));
}

//BigData BigData::operator/(const BigData & bigData)
//{
//	return BigData();
//}

BigData BigData::operator/(const BigData & bigData)
{
	if (bigData._strData[1] == '0')
	{
		assert(false);
		//
	}
	if (IsINT64Overflow() && bigData.IsINT64Overflow())
	{
		return BigData(_value / bigData._value);
	}
	if (_strData.size() < bigData._strData.size() ||
		strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1) < 0 )			//还少一个条件
	{
		return BigData(INT64(0));
	}
	if (bigData._strData == "+1" || bigData._strData == "-1")
	{
		string ret = _strData;
		if (_strData[0] != bigData._strData[0] )//异号
		{
			ret[0] = '-';
		}
		return BigData((char*)ret.c_str() );
	}
	if (_strData.size() == bigData._strData.size() &&
		strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1) == 0)
	{
		string ret = "+1";
		if (_strData[0] != bigData._strData[0])//异号
		{
			ret[0] = '-';
		}
		return BigData((char*)ret.c_str());
	}
	return BigData( (char*) (Div(_strData, bigData._strData).c_str()) );
}


string BigData::Mul(string left, string right)
{
	int LSize = left.size();
	int RSize = right.size();
	if (LSize > RSize)
	{
		swap(left, right);
		swap(LSize, RSize);
	}
	char cSymbol = '+';
	string strRet;
	strRet.resize(LSize + RSize - 1);
	if (left[0] != right[0])
	{
		cSymbol = '-';
	}
	strRet[0] = cSymbol;

	char cStep = 0;
	int  Datalen = strRet.size();
	int offset = 0; //错位
	for (int iLidx = 1; iLidx < LSize; ++iLidx)
	{
		char cLeft = left[LSize - iLidx] - '0';
		cStep = 0;
		if (cLeft == 0)
		{
			offset++;
			continue;
		}
		for (int iRidx = 1; iRidx < RSize; ++iRidx)    //这里有问题，貌似是越界访问了
		{
			char cRet = cLeft * ( right[RSize - iRidx] - '0' );
			cRet += strRet[LSize - iRidx - offset] - '0';
			cRet += cStep;
			cStep = cRet / 10;
			strRet[LSize - iRidx - offset] = (cRet % 10 + '0');
		}
		strRet[Datalen - RSize - offset] += cStep;
		++offset;
	}
	return strRet;
}

/*
	除法：
		1、如果right为0：

		2、如果都没有超出：
			left = 0 —— 0
			left < right   —— 0
			right == +-1   —— +-left
			left == +-right  ——	+-1
		
		3、如果有超出：
		Div 

		循环相减：
		保证pLeft >= 除数  
		(感觉老师写的那种用循环相减的方式有点麻烦了，直接相除 相%即可吧？（貌似）)
		(不行，不行。    要考虑大数的情况！！)

*/


string BigData::Div(string left, string right)
{
	string sRet;
	sRet.append(1, '+');   //第一位追加正号
	if (left[0] != right[0])   //异号
	{
		sRet[0] = '-';
	}
	char *pLeft = (char*)(left.c_str() ) + 1;
	char *pRight = (char*)(right.c_str() + 1);
	int Datalen = right.size() - 1;
	int LSize = left.size() - 1;
	for (int iIdx = 0; iIdx < LSize; )
	{
		if (*pLeft == '0')
		{
			sRet.append(1, '0');
			pLeft++;
			iIdx++;
			continue;
		}
		if (!IsLeftBig(pLeft, Datalen, pRight, right.size() - 1))
		{
			sRet.append(1, '0');
			Datalen++;
			if (Datalen + iIdx > LSize)
			{
				break;
			}
		}
		else
		{
			sRet.append(1, SubLoop(pLeft, Datalen, pRight, right.size() - 1));			//可以考虑用引用传参
			while (*pLeft == '0' && Datalen > 0)
			{
				pLeft++;
				iIdx++;
				Datalen--;
			}
			Datalen++;
			if (Datalen + iIdx > LSize)
			{
				break;
			}
		}
	}
	return sRet;

}


char BigData::SubLoop(char* pLeft, int LSize, char *pRight, int RSize)
{
	assert(pLeft != NULL && pRight != NULL);
	//int cCount = 0;
	char cRet = '0';
	while (true)
	{
		if (!IsLeftBig(pLeft, LSize, pRight, RSize))
		{
			break;
		}
		//做减法
		int iLidx = LSize;
		int iRidx = RSize;

		//这里有问题！！ 
		//while (iLidx)
		//{
		//	pLeft[iLidx] -= pRight[iRidx];
		//	if (pLeft[iLidx] < 0)	//借位
		//	{
		//		pLeft[iLidx - 1] -= 1;
		//		pLeft[iLidx] += 10;
		//	}
		//	iLidx--;
		//	iRidx--;
		//}


		/*int LdataLen = LSize - 1;

		for (int iIdx = 0; iIdx < LdataLen; ++iIdx)
		{
			char ret = pLeft[LSize - iIdx ] - '0';
			ret -= pRight[RSize - iIdx - 1] - '0';
			if (ret < 0)
			{
				pLeft[LSize - iIdx - 2] -= 1;
				ret += 10;
			}

			pLeft[LSize - iIdx - 1] = ret + '0';*/


		int LDataLen = LSize - 1;
		int RDataLen = RSize - 1;
		while (LDataLen >= 0 && RDataLen >= 0)
		{
			char ret = pLeft[LDataLen] - '0';
			ret -= pRight[RDataLen] - '0';
			if (ret < 0)
			{
				pLeft[LDataLen - 1] -= 1;
				ret += 10;
			}
			pLeft[LDataLen] = ret + '0';
			LDataLen--;
			RDataLen--;
		}
		//去掉前置0
		while (*pLeft == '0' && LSize > 0)
		{
			pLeft++;
			LSize--;
		}
		cRet++;
		return cRet;
	}
}

bool BigData::IsLeftBig(char * pLeft, int LSize, char * pRight, int RSize)
{
	if (LSize > RSize || LSize == RSize && strcmp(pLeft, pRight) >= 0)
	{
		return true;
	}
	return false;
}

size_t BigData::_GetSize(INT64 value)
{
	int ret = 1;
	while (value >= 10 || value <= -10)
	{
		value /= 10;
		++ret;
	}
	return ret;
}
