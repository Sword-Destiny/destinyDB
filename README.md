<html>
<head>
<title>destinyDB</title>
</head>
<body>
<p>
<pre>
# destinyDB<br />
a simple and embedded database<br />
һ���򵥵�Ƕ��ʽ���ݿ�<br />
version: 0.1<br />
��˵Ƕ��ʽ���ݿ��������ܸ߶˴����ϵ��Σ�������Ϊһ�������ѧ�����������ʵ�����㲻��ʲô���ݿ⣬<br />
��������֧��һЩ�����Ĳ������ѡ�<br />
����������:<br />
	1.��֧���������ͣ������������ַ�����ʽ�洢��<br />
	2.�Զ��ύ��������ʹ��autocommit��������Զ��ύѡ�<br />
	3.ֻ���������������¡����Ժ�Ὺ�����������Ա�̽ӿڡ���<br />
	4.�﷨���׼��SQL�淶�����𡣣�����������Ľ��ܡ���<br />
	5.��ѯ����ʱ֧��������ʽƥ�䡣<br />
	6.֧�����������Ա������������Դ�С����Ӣ�����ֵ�˳�������ڴ���ţʵ��ƴ�����߱ʻ�����<br />
	7.֧��ͬʱִ�ж�������Էֺŷָ���<br />
	8.֧����һ����������в���������ݡ�<br />
	9.��ѯ����Ƕ�ס�<br />
destinyDB����:<br />
        help: ��ӡ������Ϣ.<br />
            : ʾ��: help<br />
        exit: �˳�destinyDB.<br />
            : ʾ��: exit<br />
     version: ��ӡ�汾��Ϣ.<br />
            : ʾ��: version<br />
        open: �򿪻򴴽����ݿ��ļ�.<br />
            : ʾ��: open main.ddb<br />
         run: ����destinyDB�ű��ļ�.<br />
            : ʾ��: run main.ddbsql<br />
           ;: �ֺ�.�ָ���.<br />
            : ʾ��: ;<br />
      commit: �ύ����.<br />
            : ʾ��: commit<br />
      create: ������.<br />
            : ʾ��: create table student id,name<br />
      insert: �������ݵ�����(������һ�������в����������).<br />
            : ʾ��: insert into tbl_student 1,Lili 2,Tom ...<br />
      rename: �����������ƻ���������.<br />
            : ʾ��1:��������studentΪtbl_student<br />
                  : rename table student tbl_student<br />
            : ʾ��2:��������tbl_student�е�id��Ϊstu_id<br />
                  : rename column id in tbl_student std_id<br />
        show: ��ʾһЩ����.<br />
            : ʾ��1: show tables<br />
            : ʾ��2: show database_file<br />
  autocommit: ����auto_commit����.yes/y/true/t�����Զ��ύ,no/n/false/f�����Զ��ύ(���Դ�Сд).<br />
            : ʾ��: autocommit true<br />
      select: ��ѯ���(֧������������ʽƥ��,��Ƕ�ײ�ѯ).<br />
            : ʾ��1: select id,name where id=1||name=Tom from tbl_student<br />
            : ʾ��2: select id where name=Tom from select id,name where id>0 from tbl_student<br />
      delete: ɾ������.<br />
            : ʾ��: delete from tbl_student where id=1<br />
        drop: ɾ����.<br />
            : ʾ��: drop table tbl_student<br />
        sort: ��������(������������ǰ,�������,���Ӣ��).<br />
            : ʾ��: sort tbl_student by id<br />
NOTICE:	�ڽ���select����ʱ������ʹ��������ʽ��������ʽ������ģ��ƥ�䣡��ƥ����������֧��ģ��ƥ��<br />
		����˵��: <br />
		�б�	tbl_student<br />
		|	id	|	name	|	*	|<br /><br />
		|	0	|	Tom		|	r0	|<br />
		|	1	|	Lisa	|	r1	|<br />
		|	2	|	Bob		|	r2	|<br />
		|	3	|	Jobs	|	r3	|<br />
		ִ�� select * where id>0 from t1;<br />
		�������<br />
		|	*	|<br /><br />
		|	r1	|<br />
		|	r2	|<br />
		|	r3	|<br />
		ִ�� select id,* where id>0 from t1;<br />
		�������<br />
		|	id	|	*	|<br /><br />
		|	1	|	r1	|<br />
		|	2	|	r2	|<br />
		|	3	|	r3	|<br />
		ִ�� select .* where id>0 from t1;<br />
		�������<br />
		|	id	|	name	|	*	|<br /><br />
		|	1	|	Lisa	|	r1	|<br />
		|	2	|	Bob		|	r2	|<br />
		|	3	|	Jobs	|	r3	|<br />
		ע��*��.*�Ĳ��.*��������ʽ���﷨������ƥ�����е��У���Ϊ����������ʽ������������ʽ��ģ��ƥ�䣨ʹ��*��?���ǳ�ͻ�ģ�<br />
		���Բ�֧��ʹ��ģ��ƥ���﷨���ڴ���ţ���������⡣<br />
NITICE:	ͬʱִ�ж�������ʱ�Էֺŷָ���<br />
		��:	version;exit;<br />
NOTICE:	��һ����������в���������ݡ�<br />
		��:	insert into tbl_student 1,Lisa,r1 2,Bob,r2 3,Jobs,r3<br />
NOTICE:	��ѯ���Ƕ��<br />
		ִ��	select id where name=Bob from select id,name where id>0 from tbl_student<br />
		���<br />
		|	id	|<br /><br />
		|	2	|<br />
NOTICE:	�߼��ж�ʱ֧��ʹ��=��==����ֵʱֻ����=��<br />
NOTICE:	where֮����߼����֧��ʹ��>,<,=,==,!=,!,>=,<=,&&,&,|��||���ַ����ȽϹ�������:<br />
		�����Ա���Ϊ��<br />
		�����Դ�СΪ��֧��С���͸���<br />
		Ӣ�İ����ֵ�����<br />
Linux*:	��������Ubuntu�±��룬��ϧGCC������ʽ��û�о���ʵ�֣�������Գɹ����ǽ�����ԣ��������ˡ�<br />
		�����뵽boost��������ʽҲ����ã�������ôһ����Ȼ����һ���ӾͰ��������ˣ���û���˽�����boost����<br />
		�ܹ�������Ǩ�Ƶ�Linux*�ϡ�<br />
		��Ҫ��ͷ�ļ�������д��includes.h��<br />
		#include <regex><br />
		using std::regex;<br />
		using std::regex_error;<br />
		using std::regex_match;<br />
		using std::regex_search;<br />
		using std::sregex_token_iterator;<br />
		��֪���ĳ�boost��֮���ܲ��ܱ���ɹ���û���Թ���<br />
		�����õ���ʱ���ȡ������GetSystemTime�������԰�����Windows.hͷ�ļ�<br />
		��Ҫ��Log.h��ʹ�ã�ҪǨ�ƵĻ�ҲҪ�޸��������ļ�<br />
		ʹ�ú��٣�Ӧ�ò����޸ġ�<br />
		���ں����������Զ�û����Linux�£���������������֮�������ĵط���������Ҳ��֪��<br />
		��ˣ�������Visual Studio�±��롣<br />
NOTICE:	�ļ���֯��ʽ<br />
		�ļ�Ҫ���ѧ�ڲ�ѧ��������Ҫ�������ַ����ķ�ʽ����ʵ�����Զ������л��ķ�ʽ��һ��database����д���ļ��Ͷ�ȡ<br />
		˵���˾��Ǵ��ֽڲ�����<br />
		������͵��ʹ���ֳɵ����л��⣬�ȽϿɿ�����boost��������ԭ���Ѿ��ᵽ��������Ҳ���˼��������ģ������������ã������Ϊ<br />
		�����Ŀ������٣���Ҳ���࣬����д��һЩserialize��deserialize������<br />
</pre>
</p>
</body>
</html>
