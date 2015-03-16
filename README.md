<html>
<head>
<title>destinyDB</title>
</head>
<body>
<p>
<pre>
# destinyDB<br />
a simple and embedded database<br />
一个简单的嵌入式数据库<br />
version: 0.1<br />
虽说嵌入式数据库听起来很高端大气上档次，不过作为一个大二的学生，我这个其实根本算不上什么数据库，<br />
不过就是支持一些基本的操作而已。<br />
其特性如下:<br />
	1.不支持数据类型，所有数据以字符串形式存储。<br />
	2.自动提交。（可以使用autocommit命令更改自动提交选项）<br />
	3.只能运行在命令行下。（以后会开发各主流语言编程接口。）<br />
	4.语法与标准的SQL规范有区别。（具体命令后文介绍。）<br />
	5.查询操作时支持正则表达式匹配。<br />
	6.支持排序。中文以编码排序，数字以大小排序，英文以字典顺序排序，期待大牛实现拼音或者笔划排序。<br />
	7.支持同时执行多条命令。以分号分隔。<br />
	8.支持在一条插入语句中插入多条数据。<br />
	9.查询语句可嵌套。<br />
destinyDB命令:<br />
        help: 打印帮助信息.<br />
            : 示例: help<br />
        exit: 退出destinyDB.<br />
            : 示例: exit<br />
     version: 打印版本信息.<br />
            : 示例: version<br />
        open: 打开或创建数据库文件.<br />
            : 示例: open main.ddb<br />
         run: 运行destinyDB脚本文件.<br />
            : 示例: run main.ddbsql<br />
           ;: 分号.分隔符.<br />
            : 示例: ;<br />
      commit: 提交更改.<br />
            : 示例: commit<br />
      create: 创建表.<br />
            : 示例: create table student id,name<br />
      insert: 插入数据到表中(可以在一条命令中插入多条数据).<br />
            : 示例: insert into tbl_student 1,Lili 2,Tom ...<br />
      rename: 重命名表名称或者列名称.<br />
            : 示例1:重命名表student为tbl_student<br />
                  : rename table student tbl_student<br />
            : 示例2:重命名表tbl_student中的id列为stu_id<br />
                  : rename column id in tbl_student std_id<br />
        show: 显示一些变量.<br />
            : 示例1: show tables<br />
            : 示例2: show database_file<br />
  autocommit: 更改auto_commit属性.yes/y/true/t代表自动提交,no/n/false/f代表不自动提交(忽略大小写).<br />
            : 示例: autocommit true<br />
      select: 查询语句(支持列名正则表达式匹配,可嵌套查询).<br />
            : 示例1: select id,name where id=1||name=Tom from tbl_student<br />
            : 示例2: select id where name=Tom from select id,name where id>0 from tbl_student<br />
      delete: 删除数据.<br />
            : 示例: delete from tbl_student where id=1<br />
        drop: 删除表.<br />
            : 示例: drop table tbl_student<br />
        sort: 排序数据(排序结果中文在前,其次数字,最后英文).<br />
            : 示例: sort tbl_student by id<br />
NOTICE:	在进行select操作时，可以使用正则表达式（正则表达式不等于模糊匹配！）匹配列名，不支持模糊匹配<br />
		举例说明: <br />
		有表	tbl_student<br />
		|	id	|	name	|	*	|<br /><br />
		|	0	|	Tom		|	r0	|<br />
		|	1	|	Lisa	|	r1	|<br />
		|	2	|	Bob		|	r2	|<br />
		|	3	|	Jobs	|	r3	|<br />
		执行 select * where id>0 from t1;<br />
		输出将是<br />
		|	*	|<br /><br />
		|	r1	|<br />
		|	r2	|<br />
		|	r3	|<br />
		执行 select id,* where id>0 from t1;<br />
		输出将是<br />
		|	id	|	*	|<br /><br />
		|	1	|	r1	|<br />
		|	2	|	r2	|<br />
		|	3	|	r3	|<br />
		执行 select .* where id>0 from t1;<br />
		输出将是<br />
		|	id	|	name	|	*	|<br /><br />
		|	1	|	Lisa	|	r1	|<br />
		|	2	|	Bob		|	r2	|<br />
		|	3	|	Jobs	|	r3	|<br />
		注意*与.*的差别，.*是正则表达式的语法，可以匹配所有的列，因为有了正则表达式，而且正则表达式与模糊匹配（使用*与?）是冲突的，<br />
		所以不支持使用模糊匹配语法，期待大牛解决这个问题。<br />
NITICE:	同时执行多条命令时以分号分隔。<br />
		如:	version;exit;<br />
NOTICE:	在一条插入语句中插入多条数据。<br />
		如:	insert into tbl_student 1,Lisa,r1 2,Bob,r2 3,Jobs,r3<br />
NOTICE:	查询语句嵌套<br />
		执行	select id where name=Bob from select id,name where id>0 from tbl_student<br />
		输出<br />
		|	id	|<br /><br />
		|	2	|<br />
NOTICE:	逻辑判断时支持使用=与==，赋值时只允许=。<br />
NOTICE:	where之后的逻辑语句支持使用>,<,=,==,!=,!,>=,<=,&&,&,|和||，字符串比较规则如下:<br />
		汉字以编码为序<br />
		数字以大小为序，支持小数和负数<br />
		英文按照字典排序<br />
Linux*:	本来欲在Ubuntu下编译，可惜GCC正则表达式库没有具体实现，编译可以成功但是结果不对，最后放弃了。<br />
		后来想到boost的正则表达式也许可用，可是这么一个庞然大物一下子就把我吓怕了，有没有人介绍下boost或者<br />
		能够将代码迁移到Linux*上。<br />
		主要的头文件包含都写在includes.h中<br />
		#include <regex><br />
		using std::regex;<br />
		using std::regex_error;<br />
		using std::regex_match;<br />
		using std::regex_search;<br />
		using std::sregex_token_iterator;<br />
		不知道改成boost库之后能不能编译成功，没有试过。<br />
		由于用到了时间获取函数（GetSystemTime），所以包含了Windows.h头文件<br />
		主要在Log.h中使用，要迁移的话也要修改这两个文件<br />
		使用很少，应该不难修改。<br />
		由于后来开发测试都没有在Linux下，除了这两个问题之外其他的地方有无问题也不知晓<br />
		因此，建议在Visual Studio下编译。<br />
NOTICE:	文件组织方式<br />
		文件要这个学期才学，现在主要就是以字符串的方式，其实就是以对象序列化的方式将一个database对象写入文件和读取<br />
		说白了就是纯字节操作。<br />
		本来想偷懒使用现成的序列化库，比较可靠的是boost，放弃的原因已经提到过，后来也找了几个其他的，不过都不好用，最后因为<br />
		这个项目代码很少，类也不多，就手写了一些serialize和deserialize方法。<br />
</pre>
</p>
</body>
</html>
