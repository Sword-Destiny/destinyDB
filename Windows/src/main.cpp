/*******************************************************
 *	main.cpp
 *	author:天命剑主
 *	copyright(c) 2015 - ~: 请阅读 LICENSE 文件
 *	Description(描述):DestinyDB是一个小型的嵌入式数据库
 ******************************************************/

#include "command_cycle.h"

using namespace DatabaseFile;
using namespace Error;
using namespace CommandCycle;
using namespace DestinyDB;

/*入口函数*/
int main(int argc, char** argv) {
	if (argc == 1) {
		print_welcome();
		print_destiny_line_head();
		command_cycle(cin);
	}
	else if (argc == 2) {
		string file_path = argv[1];
		if (is_file_exists(file_path)) {
			open_file(file_path);
		}
		else {
			print_error(error_no_such_file, "已创建空数据库文件:", file_path);
			create_file(file_path);
			open_file(file_path);
		}
		print_destiny_line_head();
		command_cycle(cin);
	}
	else if (argc == 3) {
		string file_path = argv[2];
		string open = argv[1];
		if (open == keyword_open) {
			if (is_file_exists(file_path)) {
				open_file(file_path);
			}
			else {
				print_error(error_no_such_file, "已创建空数据库文件:", file_path);
				create_file(file_path);
				open_file(file_path);
			}
			print_destiny_line_head();
			command_cycle(cin);
		}
		else {
			print_usage();
		}
	}
	else {
		print_usage();
	}
	if (database != NULL) {
		delete database;
	}
	return 0;
}