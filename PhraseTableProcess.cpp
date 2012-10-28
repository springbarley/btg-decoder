#include "PhraseTableProcess.h"


PhraseTableProcess::PhraseTableProcess(void)
{
}
//�������һ�еĽṹ�ǣ�ǰ�� ||| 15 march ||| 0.0357143 4.48857e-11 0.333333 5.09856e-05 2.718 ||| ||| 28 3
//��ɣ�pair<string = ǰ��, record = ����>
pair<string, Record>  PhraseTableProcess::getTrieStructure(const string& line)
{
	size_t line_pos;
	istringstream in_line(line);
	string source, target, temp, feature_arr;
	Record record;
	while(1)
	{
		in_line >> temp;
		if(temp == "|||")
			break;
		source += temp;//ע��source��û�пո�" "
	}
	while(1)
	{
		in_line >> temp;
		if(temp == "|||")
			break;
		target += temp + " ";//ע��target�˵ĺ��涼��һ��" ",target�˺����и��ո���ڽ����Ƶ�����������ϣ��Ͱ��ո��ȡ�ַ���
	}
	record.setString(target);
	double feature_temp;
	for(int i = 0; i < FEATURE_NUM; i++)
	{
		in_line >> feature_temp;
		record.getFeatures()[i] = feature_temp;
	}
	return make_pair<string, Record>(source, record);
}
PhraseTableProcess::~PhraseTableProcess(void)
{
}
