/*******************************************************
 *	log.h
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):错误日志记录
 ******************************************************/
#pragma once
#ifndef MAIN_LOG
#define MAIN_LOG

#include "includes.h"

#ifdef _WIN32
#include <Windows.h>
 /*日志记录组件*/
namespace Log {

	template<class T>
	/*记录日志*/
	static void log(const T &info) {
		SYSTEMTIME system_time;
		GetLocalTime(&system_time);
		ofstream os("./main.log", ios::app);
		os << endl << system_time.wYear << "-" << system_time.wMonth << "-" << system_time.wDay
			<< " " << system_time.wHour << ":" << system_time.wMinute << ":" << system_time.wSecond << " " << info;
		os.close();
	}
	template<class T>
	/*在新文件中记录日志*/
	static void log_in_new_file(const string &filePath, const T &info) {
		SYSTEMTIME system_time;
		GetLocalTime(&system_time);
		ofstream os(filePath, ios::app);
		os << endl << system_time.wYear << "-" << system_time.wMonth << "-" << system_time.wDay
			<< " " << system_time.wHour << ":" << system_time.wMinute << ":" << system_time.wSecond << " " << info;
		os.close();
	}

	/*清空日志*/
	static void clean_main_log() {
		SYSTEMTIME system_time;
		GetLocalTime(&system_time);
		ofstream os("./main.log", ios::out);
		os << "#destinyDB 日志记录 " << system_time.wYear << "-" << system_time.wMonth << "-" << system_time.wDay
			<< " " << system_time.wHour << ":" << system_time.wMinute << ":" << system_time.wSecond;
		os.close();
	}
}
#elif __gnu_linux__

#include <sys/time.h>
#include <time.h>
/*日志记录组件*/
namespace Log {

    template<class T>
    /*记录日志*/
    static void log(const T &info) {
        time_t now = time(0);
        struct tm *timenow;
        timenow = localtime(&now);
        ofstream os("./main.log", ios::app);
        os << endl << (timenow->tm_year + 1900) << "-" << (timenow->tm_mon + 1) << "-" << timenow->tm_mday
                << " " << timenow->tm_hour << ":" << timenow->tm_min << ":" << timenow->tm_sec << " " << info;
        os.close();
    }

    template<class T>
    /*在新文件中记录日志*/
    static void log_in_new_file(const string &filePath, const T &info) {
        time_t now = time(0);
        struct tm *timenow;
        timenow = localtime(&now);
        ofstream os(filePath, ios::app);
        os << endl << (timenow->tm_year + 1900) << "-" << (timenow->tm_mon + 1) << "-" << timenow->tm_mday
                << " " << timenow->tm_hour << ":" << timenow->tm_min << ":" << timenow->tm_sec << " " << info;
        os.close();
    }

    /*清空日志*/
    static void clean_main_log() {
        time_t now = time(0);
        struct tm *timenow;
        timenow = localtime(&now);
        ofstream os("./main.log", ios::out);
        os << endl << (timenow->tm_year + 1900) << "-" << (timenow->tm_mon + 1) << "-" << timenow->tm_mday
                << " " << timenow->tm_hour << ":" << timenow->tm_min << ":" << timenow->tm_sec;
        os.close();
    }
}
#else

#	endif
#endif
