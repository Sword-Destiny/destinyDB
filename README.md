# destinyDB

a simple and embedded database
一个简单的嵌入式数据库

version: 0.1

虽说嵌入式数据库听起来很高端大气上档次，不过作为一个大二的学生，我这个其实根本算不上什么数据库，
不过就是支持一些基本的操作而已。

其特性如下：

1.不支持数据类型，所有数据以字符串形式存储。
2.自动提交。（可以使用autocommit命令更改自动提交选项）
3.只能运行在命令行下。（以后会开发各主流语言编程接口。）
4.语法与标准的SQL规范有区别。（具体命令后文介绍。）
5.查询操作时支持正则表达式匹配。
6.支持排序。中文以编码排序，数字以大小排序，英文以字典顺序排序，期待大牛实现拼音或者笔划排序。
7.支持同时执行多条命令。以分号分隔。
8.支持在一条插入语句中插入多条数据。
9.查询语句可嵌套。

destinyDB命令:
        help: 打印帮助信息.
            : 示例: help

        exit: 退出destinyDB.
            : 示例: exit

     version: 打印版本信息.
            : 示例: version

        open: 打开或创建数据库文件.
            : 示例: open main.ddb

         run: 运行destinyDB脚本文件.
            : 示例: run main.ddbsql

           ;: 分号.分隔符.
            : 示例: ;

      commit: 提交更改.
            : 示例: commit

      create: 创建表.
            : 示例: create table student id,name

      insert: 插入数据到表中(可以在一条命令中插入多条数据).
            : 示例: insert into tbl_student 1,Lili 2,Tom ...

      rename: 重命名表名称或者列名称.
            : 示例1:重命名表student为tbl_student
                  : rename table student tbl_student
            : 示例2:重命名表tbl_student中的id列为stu_id
                  : rename column id in tbl_student std_id

        show: 显示一些变量.
            : 示例1: show tables
            : 示例2: show database_file

  autocommit: 更改auto_commit属性.yes/y/true/t代表自动提交,no/n/false/f代表不自动提交(忽略大小写).
            : 示例: autocommit true

      select: 查询语句(支持列名正则表达式匹配,可嵌套查询).
            : 示例1: select id,name where id=1||name=Tom from tbl_student
            : 示例2: select id where name=Tom from select id,name where id>0 from tbl_student

      delete: 删除数据.
            : 示例: delete from tbl_student where id=1

        drop: 删除表.
            : 示例: drop table tbl_student

        sort: 排序数据(排序结果中文在前,其次数字,最后英文).
            : 示例: sort tbl_student by id


NOTICE:	在进行select操作时，可以使用正则表达式（正则表达式不等于模糊匹配！）匹配列名，不支持模糊匹配
		举例说明: 
		有表	tbl_student

		|	id	|	name	|	*	|

		|	0	|	Tom		|	r0	|
		|	1	|	Lisa	|	r1	|
		|	2	|	Bob		|	r2	|
		|	3	|	Jobs	|	r3	|

		执行 select * where id>0 from t1;
		输出将是

		|	*	|
		|	r1	|
		|	r2	|
		|	r3	|

		执行 select id,* where id>0 from t1;
		输出将是

		|	id	|	*	|

		|	1	|	r1	|
		|	2	|	r2	|
		|	3	|	r3	|

		执行 select .* where id>0 from t1;
		输出将是

		|	id	|	name	|	*	|

		|	1	|	Lisa	|	r1	|
		|	2	|	Bob		|	r2	|
		|	3	|	Jobs	|	r3	|

		注意*与.*的差别，.*是正则表达式的语法，可以匹配所有的列，因为有了正则表达式，而且正则表达式与模糊匹配（使用*与?）是冲突的，
		所以不支持使用模糊匹配语法，期待大牛解决这个问题。

NITICE:	同时执行多条命令时以分号分隔。
		如:	version;exit;

NOTICE:	在一条插入语句中插入多条数据。
		如:	insert into tbl_student 1,Lisa,r1 2,Bob,r2 3,Jobs,r3

NOTICE:	查询语句嵌套
		执行	select id where name=Bob from select id,name where id>0 from tbl_student
		输出
		|	id	|
		
		|	2	|

NOTICE:	逻辑判断时支持使用=与==，赋值时只允许=。

NOTICE:	where之后的逻辑语句支持使用>,<,=,==,!=,!,>=,<=,&&,&,|和||，字符串比较规则如下:
		汉字以编码为序
		数字以大小为序，支持小数和负数
		英文按照字典排序

Linux*:	本来欲在Ubuntu下编译，可惜GCC正则表达式库没有具体实现，编译可以成功但是结果不对，最后放弃了。
		后来想到boost的正则表达式也许可用，可是这么一个庞然大物一下子就把我吓怕了，有没有人介绍下boost或者
		能够将代码迁移到Linux*上。
		主要的头文件包含都写在includes.h中
		#include <regex>
		using std::regex;
		using std::regex_error;
		using std::regex_match;
		using std::regex_search;
		using std::sregex_token_iterator;
		不知道改成boost库之后能不能编译成功，没有试过。

		由于用到了时间获取函数（GetSystemTime），所以包含了Windows.h头文件
		主要在Log.h中使用，要迁移的话也要修改这两个文件
		使用很少，应该不难修改。
		由于后来开发测试都没有在Linux下，除了这两个问题之外其他的地方有无问题也不知晓

		因此，建议在Visual Studio下编译。

NOTICE:	文件组织方式
		文件要这个学期才学，现在主要就是以字符串的方式，其实就是以对象序列化的方式将一个database对象写入文件和读取
		说白了就是纯字节操作。

		本来想偷懒使用现成的序列化库，比较可靠的是boost，放弃的原因已经提到过，后来也找了几个其他的，不过都不好用，最后因为
		这个项目代码很少，类也不多，就手写了一些serialize和deserialize方法。