#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include "header.h"
#include "Parameter.h"
#include "Util.h"
//{ modified by slacker 2009-11-23
#include "srilm-lib/lmsridll.h"    //linux : "lmsri.h"  linux_bin "mmlm.h"  windows : "lmsridll.h";   
//#include "lmsridll.h"
//}
using namespace std;
#pragma comment(lib,"srilm-lib/lmsridll.lib")

class LanguageModel
{
public:	
	string lm_file;                                  // 文件	
	int lm_order;                                    // 阶数
	double lm_alpha;
	void* srilm;                               // 指针
	long ngram_sricall;                              // 调用次数
	//map<string, double> lm_prob_pool;                // cache
	
	// 构造函数
	LanguageModel(Parameter* para) {
		lm_file = remove_sides( para->get_para("LM_FILE") );
		lm_order = atoi(para->get_para("LM_ORDER").c_str());

		//cout << "The lm_file is: \"" << lm_file << "\"" << endl << endl;
		//cout << "The lm_order is: " << lm_order << endl << endl;
	};
	//带一个语言模型名称的构造函数
	LanguageModel(const string& lm_file):lm_file(lm_file), lm_order(LM_NGRAM_NUM)
	{
		lm_alpha = 1.0;
	}
	// 加载
	void load_lang_model() {
		cout << "Reading language model from \"" << lm_file << "\"..." << endl << endl;

		ifstream is(lm_file.c_str());
		if(!is) {
			cerr << "Load_lang_model, fail to read language model!" << endl;
			exit(1);
		}
		is.close();
		srilm = sriLoadLM(lm_file.c_str(), 1, lm_order, 1, 0);
		lm_alpha = 1.0;//权重设置成1.0
	};
	// 卸载
	void unload_lang_model() {
		cout << "Releasing language model..." << endl << endl;
		sriUnloadLM(srilm);
	};
	double calc_word_lm_score(const string &word, const string &ctx = "");
	double calc_str_lm_score(const string &str, const string &ctx = "");	
	double cal_ngram_probability(const string& str);
};

inline double LanguageModel::cal_ngram_probability(const string& str)
{
	string context;
	vector<string> s_v = get_all_words(str);
    unsigned int n = str.size();
    unsigned int context_len = 0;
	double ngram_score = 0.0;
    for (unsigned int i = 0; i < n; i++)
	{
        const std::string& word = s_v[i];
        double prob;

        if (i == 0 && word == "<s>") 
		{
            context += "<s> ";
            context_len += 1;
            continue;
        }
        prob = sriWordProb(srilm, word.c_str(), context.c_str());
		/*order的意思是？*/
        if (context_len >= lm_order - 1)
            ngram_score += prob;
       // full += prob;
        context += " ";
        context += word;
        context_len += 1;
    }
	return ngram_score;
}

inline double LanguageModel::calc_word_lm_score(const string &word, const string &ctx)
{
	if(word.empty() || (word == "<s>" && ctx.empty())) {
		return 0.0;
	}
	static double prob;
	static double r;
	prob = sriWordProb(srilm, word.c_str(), ctx.c_str()) / lm_alpha;
	r = prob < -100 ? -100 : prob;
	return r;
}


inline double LanguageModel::calc_str_lm_score(const string &str, const string &ctx)
{
	map<string, double>::iterator ite;

	vector<string> lstr = split_str(ctx, " ");
	vector<string> tmp;
	double prob = 0;
	string cont;
	int pos = (int)lstr.size();

	tmp = split_str(str, " ");
	lstr.insert(lstr.end(), tmp.begin(), tmp.end());

	for (int i = pos; i < (int)lstr.size(); ++i) {
		cont = join_str(lstr.begin() + max(0, i - lm_order + 1), lstr.begin() + i);
		prob += calc_word_lm_score(lstr[i], cont);
	}
	return prob;
}
#endif
