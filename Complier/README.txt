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

��չ�����׺���ʽ��
digti=[0-9]+ 
fact1=digit | "(" exp3 ")" 
fact2=(��|~)fact1    
term = fact2 ( ( "*" | "/" ) fact2) *  
exp = term ( ( "+" | "-" ) term) * 
exp2=exp ((<=|>=|<|>|==|!=) exp)* 
exp3=exp2 ((&&| || ) exp2)*

���ɵ�exe�ļ������������Ľ���������ʽ��ֵ������q�˳�����
