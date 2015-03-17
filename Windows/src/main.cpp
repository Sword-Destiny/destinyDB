/*******************************************************
 *	main.cpp
 *	author:��������
 *	copyright(c) 2015 - ~: ���Ķ� LICENSE �ļ�
 *	Description(����):DestinyDB��һ��С�͵�Ƕ��ʽ���ݿ�
 ******************************************************/

#include "command_cycle.h"

using namespace DatabaseFile;
using namespace Error;
using namespace CommandCycle;
using namespace DestinyDB;

/*��ں���*/
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
			print_error(error_no_such_file, "�Ѵ��������ݿ��ļ�:", file_path);
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
				print_error(error_no_such_file, "�Ѵ��������ݿ��ļ�:", file_path);
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