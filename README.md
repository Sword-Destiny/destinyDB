# destinyDB

a simple and embedded database
һ���򵥵�Ƕ��ʽ���ݿ�

version: 0.1

��˵Ƕ��ʽ���ݿ��������ܸ߶˴����ϵ��Σ�������Ϊһ�������ѧ�����������ʵ�����㲻��ʲô���ݿ⣬
��������֧��һЩ�����Ĳ������ѡ�

���������£�

1.��֧���������ͣ������������ַ�����ʽ�洢��
2.�Զ��ύ��������ʹ��autocommit��������Զ��ύѡ�
3.ֻ���������������¡����Ժ�Ὺ�����������Ա�̽ӿڡ���
4.�﷨���׼��SQL�淶�����𡣣�����������Ľ��ܡ���
5.��ѯ����ʱ֧��������ʽƥ�䡣
6.֧�����������Ա������������Դ�С����Ӣ�����ֵ�˳�������ڴ���ţʵ��ƴ�����߱ʻ�����
7.֧��ͬʱִ�ж�������Էֺŷָ���
8.֧����һ����������в���������ݡ�
9.��ѯ����Ƕ�ס�

destinyDB����:
        help: ��ӡ������Ϣ.
            : ʾ��: help

        exit: �˳�destinyDB.
            : ʾ��: exit

     version: ��ӡ�汾��Ϣ.
            : ʾ��: version

        open: �򿪻򴴽����ݿ��ļ�.
            : ʾ��: open main.ddb

         run: ����destinyDB�ű��ļ�.
            : ʾ��: run main.ddbsql

           ;: �ֺ�.�ָ���.
            : ʾ��: ;

      commit: �ύ����.
            : ʾ��: commit

      create: ������.
            : ʾ��: create table student id,name

      insert: �������ݵ�����(������һ�������в����������).
            : ʾ��: insert into tbl_student 1,Lili 2,Tom ...

      rename: �����������ƻ���������.
            : ʾ��1:��������studentΪtbl_student
                  : rename table student tbl_student
            : ʾ��2:��������tbl_student�е�id��Ϊstu_id
                  : rename column id in tbl_student std_id

        show: ��ʾһЩ����.
            : ʾ��1: show tables
            : ʾ��2: show database_file

  autocommit: ����auto_commit����.yes/y/true/t�����Զ��ύ,no/n/false/f�����Զ��ύ(���Դ�Сд).
            : ʾ��: autocommit true

      select: ��ѯ���(֧������������ʽƥ��,��Ƕ�ײ�ѯ).
            : ʾ��1: select id,name where id=1||name=Tom from tbl_student
            : ʾ��2: select id where name=Tom from select id,name where id>0 from tbl_student

      delete: ɾ������.
            : ʾ��: delete from tbl_student where id=1

        drop: ɾ����.
            : ʾ��: drop table tbl_student

        sort: ��������(������������ǰ,�������,���Ӣ��).
            : ʾ��: sort tbl_student by id


NOTICE:	�ڽ���select����ʱ������ʹ��������ʽ��������ʽ������ģ��ƥ�䣡��ƥ����������֧��ģ��ƥ��
		����˵��: 
		�б�	tbl_student

		|	id	|	name	|	*	|

		|	0	|	Tom		|	r0	|
		|	1	|	Lisa	|	r1	|
		|	2	|	Bob		|	r2	|
		|	3	|	Jobs	|	r3	|

		ִ�� select * where id>0 from t1;
		�������

		|	*	|
		|	r1	|
		|	r2	|
		|	r3	|

		ִ�� select id,* where id>0 from t1;
		�������

		|	id	|	*	|

		|	1	|	r1	|
		|	2	|	r2	|
		|	3	|	r3	|

		ִ�� select .* where id>0 from t1;
		�������

		|	id	|	name	|	*	|

		|	1	|	Lisa	|	r1	|
		|	2	|	Bob		|	r2	|
		|	3	|	Jobs	|	r3	|

		ע��*��.*�Ĳ��.*��������ʽ���﷨������ƥ�����е��У���Ϊ����������ʽ������������ʽ��ģ��ƥ�䣨ʹ��*��?���ǳ�ͻ�ģ�
		���Բ�֧��ʹ��ģ��ƥ���﷨���ڴ���ţ���������⡣

NITICE:	ͬʱִ�ж�������ʱ�Էֺŷָ���
		��:	version;exit;

NOTICE:	��һ����������в���������ݡ�
		��:	insert into tbl_student 1,Lisa,r1 2,Bob,r2 3,Jobs,r3

NOTICE:	��ѯ���Ƕ��
		ִ��	select id where name=Bob from select id,name where id>0 from tbl_student
		���
		|	id	|
		
		|	2	|

NOTICE:	�߼��ж�ʱ֧��ʹ��=��==����ֵʱֻ����=��

NOTICE:	where֮����߼����֧��ʹ��>,<,=,==,!=,!,>=,<=,&&,&,|��||���ַ����ȽϹ�������:
		�����Ա���Ϊ��
		�����Դ�СΪ��֧��С���͸���
		Ӣ�İ����ֵ�����

Linux*:	��������Ubuntu�±��룬��ϧGCC������ʽ��û�о���ʵ�֣�������Գɹ����ǽ�����ԣ��������ˡ�
		�����뵽boost��������ʽҲ����ã�������ôһ����Ȼ����һ���ӾͰ��������ˣ���û���˽�����boost����
		�ܹ�������Ǩ�Ƶ�Linux*�ϡ�
		��Ҫ��ͷ�ļ�������д��includes.h��
		#include <regex>
		using std::regex;
		using std::regex_error;
		using std::regex_match;
		using std::regex_search;
		using std::sregex_token_iterator;
		��֪���ĳ�boost��֮���ܲ��ܱ���ɹ���û���Թ���

		�����õ���ʱ���ȡ������GetSystemTime�������԰�����Windows.hͷ�ļ�
		��Ҫ��Log.h��ʹ�ã�ҪǨ�ƵĻ�ҲҪ�޸��������ļ�
		ʹ�ú��٣�Ӧ�ò����޸ġ�
		���ں����������Զ�û����Linux�£���������������֮�������ĵط���������Ҳ��֪��

		��ˣ�������Visual Studio�±��롣

NOTICE:	�ļ���֯��ʽ
		�ļ�Ҫ���ѧ�ڲ�ѧ��������Ҫ�������ַ����ķ�ʽ����ʵ�����Զ������л��ķ�ʽ��һ��database����д���ļ��Ͷ�ȡ
		˵���˾��Ǵ��ֽڲ�����

		������͵��ʹ���ֳɵ����л��⣬�ȽϿɿ�����boost��������ԭ���Ѿ��ᵽ��������Ҳ���˼��������ģ������������ã������Ϊ
		�����Ŀ������٣���Ҳ���࣬����д��һЩserialize��deserialize������