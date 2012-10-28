#ifndef CONSTDEF_H
#define CONSTDEF_H

#include <string>
#include <vector>
#include <math.h>

using namespace std;

// ��������
const int RUN_DEV = 1;
const int RUN_TST1 = 2;
const int RUN_TST2 = 3;
const int RUN_TST3 = 4;
const int RUN_TST4 = 5;
const int RUN_TST5 = 6;

// �����delimiter
const string PHRA_SEP = " ||| ";
const string TAB_SEP = "\t";

// OOV�������
double const OOV_PROB = -10;

// MERM��������
const int HT_TRAIT = 1;
const int T_TRAIT = 2;
const int SYNT_TRAIT = 3;

// �������
const string S_SYM = "#S#";
const string X1_SYM = "#X1#";
const string X2_SYM = "#X2#";

// ��Լ���ս��
const char RN_E_SYM = 'E';// NODE_NODE ������ԭ��ROOT_NODE��
const char RN_X_SYM = 'X';// BP_NODE��XRULE_NODE��SRULE_NODE

// ����ڵ�����
const int NONE_NODE = 0;
const int BP_NODE = 1;
const int XRULE_NODE = 2;
const int SRULE_NODE = 3;
const string NODE[] = { "NONO_NODE", "BP_NODE", "XRULE_NODE", "SRULE_NODE" };

// �Ƶ�����
const int NONDE_DEDUCTION = 0;
const int BP_DEDUCTION = 1;
const int XRULE_DEDUCTION = 2;
const int SRULE_DEDUCTION = 3;
const string DEDUCTION[] = { "NONO_DEDUCTION", "BP_DEDUCTION", "XRULE_DEDUCTION", "SRULE_DEDUCTION" };

// �������
const int BP_REORDER = 1;
const int XRULE_REORDER = 2;
const int SRULE_REORDER = 3;
const string REORDER[] = { "", "BP_REORDER", "XRULE_REORDER", "SRULE_REORDER"};//, "BTG_MONO_REORDER", "BTG_INVERT_REORDER" };

// feat 0-3, 4������������� 
// feat 4��NԪ����ģ��
// feat 5���ʸ���
// feat 6���������
// feat 7��ճ�Ϲ������
const int TRANS_PROB_NUM = 4;
const int TR_FEAT_NUM = TRANS_PROB_NUM + 2;// ���������������
const int FEAT_NUM = 8;

// add hypo
const int COMB_HYPO = 1;
const int THRES_FILTER = 2;
const int REPL_MIN = 3;
const int BEAMSIZE_FILTER = 4;
const int ADD_STACK = 5;
const string ADD_HYPO_OPT[] = { "", "COMB_HYPO", "THRES_FILTER", "REPL_MIN", "BEAMSIZE_FILTER", "ADD_STACK" };
const int ADD_HYPO_OPT_NUM[] = { 0, 0, 0, 0, 0, 0 };

// extend hypo opt
const int EXTE_BP_SKEL = 1;
const int EXTE_XRULE1_SKEL = 2;
const int EXTE_XRULE1_X1 = 3;
const int EXTE_XRULE2_SKEL = 4;
const int EXTE_XRULE2_X1 = 5;
const int EXTE_XRULE2_X2 = 6;
const string EXT_HYPO_OPT[] = { "", "EXTE_BP_SKEL", "EXTE_XRULE1_SKEL", "EXTE_XRULE1_X1", "EXTE_XRULE2_SKEL", "EXTE_XRULE2_X1", "EXTE_XRULE2_X2" };
const int EXT_HYPO_OPT_NUM[] = { 0, 0, 0, 0, 0, 0, 0 };

// extend hypo result
const int HAS_SEARCH = 1;
const int SKEL_FAIL = 2;
const int X1_FAIL = 3;
const int X2_FAIL = 4;
const int SKEL_SUCC = 5;
const int X1_SUCC = 6;
const int X2_SUCC = 7;
const string EXT_HYPO_RESULT[] = { "", "SKEL_FAIL", "X1_FAIL", "X2_FAIL", "HAS_SEARCH", "SKEL_SUCC", "X1_SUCC", "X2_SUCC" };
const int EXT_HYPO_RESULT_NUM[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// ����
typedef pair<int,int> Span;

// ͳ��
struct TotalStatics
{
	double match_time;
	double trans_time;
	double gnbest_time;

	int count_sent;
	int count_word;

	int tpruned1_hypo_num;
	int bpruned2_hypo_num;	
	int added_hypo_num;
	int merged_hypo_num;
	long ngram_sricall;
};

#endif
