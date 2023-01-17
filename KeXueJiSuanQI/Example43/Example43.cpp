// Example43.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "atltime.h"
#include <iostream>
using namespace std;

int main()
{
	//CString strTime;
	//// 获取当前时间并保存到curTime   
	//CTime curTime = CTime::GetCurrentTime();

	//int nYear = curTime.GetYear();  // 获取当前年份   
	//int nMonth = curTime.GetMonth(); // 获取当前月份   
	//int nDay = curTime.GetDay();   // 获取当前日期   
	//int nHour = curTime.GetHour();  // 获取当前小时时间   
	//int nMin = curTime.GetMinute(); // 获取当前分钟时间   
	//int nSec = curTime.GetSecond(); // 获取当前秒时间   

	//								// 输出当前时间   
	//cout << "当前时间：" << endl;
	//cout << nYear << "年" << nMonth << "月" << nDay << "日" << nHour << "时" << nMin << "分" << nSec << "秒" << endl;

	//// 为计算时间差，设定一个起始时间并输出   
	//CTime startTime = CTime(2010, 7, 3, 10, 20, 30);
	//cout << "起始时间：" << endl;
	//cout << startTime.GetYear() << "年" << startTime.GetMonth() << "月" << startTime.GetDay() << "日" << startTime.GetHour() << "时" << startTime.GetMinute() << "分" << startTime.GetSecond() << "秒" << endl;

	//// 计算时间差   
	//CTimeSpan timeSpan;
	//timeSpan = curTime - startTime;
	//cout << "两时间相差：" << endl;
	//cout << timeSpan.GetDays() << "天" << timeSpan.GetHours() << "小时" << timeSpan.GetMinutes() << "分" << timeSpan.GetSeconds() << "秒" << endl;
	//cout << "总小时数：" << timeSpan.GetTotalHours() << "小时" << endl;
	//cout << "总分钟数：" << timeSpan.GetTotalMinutes() << "分" << endl;
	//cout << "总秒数：" << timeSpan.GetTotalSeconds() << "秒" << endl;

	//// 将当前时间curTime对象格式化为字符串   
	//strTime = curTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	//// 输出格式化字符串，由于字符串使用Unicode字符，所以要使用wcout输出   
	//wcout << (LPCTSTR)strTime << endl;
    return 0;
}

