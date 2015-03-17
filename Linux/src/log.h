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

#   ifdef __gnu_linux__
//或者是#ifdef __unix__
//又或者是#ifdef __linux__

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
#	endif
#endif
