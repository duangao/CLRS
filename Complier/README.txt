in.cpp �ļ��������׺���ʽ��Դ�ļ�
pre.cpp �ļ������ǰ׺���ʽ��Դ�ļ�

�����Ǹ��˵��﷨���壺
ǰ׺���ʽ��
	    expr="(" op number number ")" | "��" expr "��" |number
        number= [0-9]*
        op='+' | '-' | '* | '/'
��׺���ʽ��
		expr=term | (('+'|'-')term)*
		term=factor | (('*'|'/')factor)* 
		factor=number|"(" expr ")"
		number=[0-9]*

���ɵ�exe�ļ������������Ľ���������ʽ��ֵ������q�˳�����