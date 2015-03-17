/*******************************************************
 *	log.h
 *	author:��������
 *	copyright(c) 2015 - ~: ���Ķ� LICENSE �ļ�
 *	Description(����):������־��¼
 ******************************************************/
#pragma once
#ifndef MAIN_LOG
#define MAIN_LOG
#include "includes.h"

#ifdef _WIN32
#include <Windows.h>
 /*��־��¼���*/
namespace Log {

	template<class T>
	/*��¼��־*/
	static void log(const T &info) {
		SYSTEMTIME system_time;
		GetLocalTime(&system_time);
		ofstream os("./main.log", ios::app);
		os << endl << system_time.wYear << "-" << system_time.wMonth << "-" << system_time.wDay
			<< " " << system_time.wHour << ":" << system_time.wMinute << ":" << system_time.wSecond << " " << info;
		os.close();
	}
	template<class T>
	/*�����ļ��м�¼��־*/
	static void log_in_new_file(const string &filePath, const T &info) {
		SYSTEMTIME system_time;
		GetLocalTime(&system_time);
		ofstream os(filePath, ios::app);
		os << endl << system_time.wYear << "-" << system_time.wMonth << "-" << system_time.wDay
			<< " " << system_time.wHour << ":" << system_time.wMinute << ":" << system_time.wSecond << " " << info;
		os.close();
	}

	/*�����־*/
	static void clean_main_log() {
		SYSTEMTIME system_time;
		GetLocalTime(&system_time);
		ofstream os("./main.log", ios::out);
		os << "#destinyDB ��־��¼ " << system_time.wYear << "-" << system_time.wMonth << "-" << system_time.wDay
			<< " " << system_time.wHour << ":" << system_time.wMinute << ":" << system_time.wSecond;
		os.close();
	}
}
#	endif
#endif
