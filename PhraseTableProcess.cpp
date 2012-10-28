#include "PhraseTableProcess.h"


PhraseTableProcess::PhraseTableProcess(void)
{
}
//短语表中一行的结构是：前进 ||| 15 march ||| 0.0357143 4.48857e-11 0.333333 5.09856e-05 2.718 ||| ||| 28 3
//拆成：pair<string = 前进, record = 后面>
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
		source += temp;//注意source端没有空格" "
	}
	while(1)
	{
		in_line >> temp;
		if(temp == "|||")
			break;
		target += temp + " ";//注意target端的后面都有一个" ",target端后面有个空格便于进行推导的正反序组合，和按空格截取字符串
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
