#include "stdafx.h"
#include "char.h"
TJobInitialPoints JobInitialPoints[JOB_MAX_NUM] = 
/*
   {
   int st, ht, dx, iq;
   int max_hp, max_sp;
   int hp_per_ht, sp_per_iq;
   int hp_per_lv_begin, hp_per_lv_end;
   int sp_per_lv_begin, sp_per_lv_end;
   int max_stamina;
   int stamina_per_con;
   int stamina_per_lv_begin, stamina_per_lv_end;
   }
 */
{
	// str con dex int 초기HP 초기SP  CON/HP INT/SP  HP랜덤/lv   MP랜덤/lv  초기stam  stam/con stam/lv
	{   6,  4,  3,  3,  600,   200,     40,    20,    36, 44,     18, 22,     800,      5,      1, 3  }, // JOB_WARRIOR  16
	{   4,  3,  6,  3,  650,   200,     40,    20,    36, 44,     18, 22,     800,      5,      1, 3  }, // JOB_ASSASSIN 16
	{   5,  3,  3,  5,  650,   200,     40,    20,    36, 44,     18, 22,     800,      5,      1, 3  }, // JOB_SURA	 16
	{   3,  4,  3,  6,  700,   200,     40,    20,    36, 44,     18, 22,     800,      5,      1, 3  },  // JOB_SHAMANa  16
	{   6,  6,  2,  2,  600,   200,     40,    20,    36, 44,     18, 22,     800,      5,      1, 3  } // JOB_WOLFMAN  16  // TODO: 4개능력치 초기값 외에 다른 스탯 필요 (기획자한테 요청)
};

THorseStat c_aHorseStat[51] =
/*
   int iMinLevel;	// 탑승할 수 있는 최소 레벨
   int iNPCRace;
   int iMaxHealth;	// 말의 최대 체력
   int iMaxStamina;	// 말의 최대 스테미너
   int iST;
   int iDX;
   int iHT;
   int iIQ;
   int iDamMean;
   int iDamMin;
   int iDamMax;
   int iDef;
 */
{
	{  0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0  },
	{ 25,	20101,	3,	4,	26,	35,	18,	9,	54,	43,	64,	32 },	// 1 (초급)
	{ 25,	20101,	4,	4,	27,	36,	18,	9,	55,	44,	66,	33 },
	{ 25,	20101,	5,	5,	28,	38,	19,	9,	56,	44,	67,	33 },
	{ 25,	20101,	7,	5,	29,	39,	19,	10,	57,	45,	68,	34 },
	{ 25,	20101,	8,	6,	30,	40,	20,	10,	58,	46,	69,	34 },
	{ 25,	20101,	9,	6,	31,	41,	21,	10,	59,	47,	70,	35 },
	{ 25,	20101,	11,	7,	32,	42,	21,	11,	60,	48,	72,	36 },
	{ 25,	20101,	12,	7,	33,	44,	22,	11,	61,	48,	73,	36 },
	{ 25,	20101,	13,	8,	34,	45,	22,	11,	62,	49,	74,	37 },
	{ 25,	20101,	15,	10,	35,	46,	23,	12,	63,	50,	75,	37 },
	{ 35,	20104,	18,	30,	40,	53,	27,	13,	69,	55,	82,	41 },	// 11 (중급)
	{ 35,	20104,	19,	35,	41,	54,	27,	14,	70,	56,	84,	42 },
	{ 35,	20104,	21,	40,	42,	56,	28,	14,	71,	56,	85,	42 },
	{ 35,	20104,	22,	50,	43,	57,	28,	14,	72,	57,	86,	43 },
	{ 35,	20104,	24,	55,	44,	58,	29,	15,	73,	58,	87,	43 },
	{ 35,	20104,	25,	60,	44,	59,	30,	15,	74,	59,	88,	44 },
	{ 35,	20104,	27,	65,	45,	60,	30,	15,	75,	60,	90,	45 },
	{ 35,	20104,	28,	70,	46,	62,	31,	15,	76,	60,	91,	45 },
	{ 35,	20104,	30,	80,	47,	63,	31,	16,	77,	61,	92,	46 },
	{ 35,	20104,	32,	100,	48,	64,	32,	16,	78,	62,	93,	46 },
	{ 50,	20107,	35,	120,	53,	71,	36,	18,	84,	67,	100,	50 },	// 21 (고급)
	{ 50,	20107,	36,	125,	55,	74,	37,	18,	86,	68,	103,	51 },
	{ 50,	20107,	37,	130,	57,	76,	38,	19,	88,	70,	105,	52 },
	{ 50,	20107,	38,	135,	59,	78,	39,	20,	90,	72,	108,	54 },
	{ 50,	20107,	40,	140,	60,	80,	40,	20,	91,	72,	109,	54 },
	{ 50,	20107,	42,	145,	61,	81,	40,	20,	92,	73,	110,	55 },
	{ 50,	20107,	44,	150,	62,	83,	42,	21,	94,	75,	112,	56 },
	{ 50,	20107,	46,	160,	63,	84,	42,	21,	95,	76,	114,	57 },
	{ 50,	20107,	48,	170,	65,	87,	43,	22,	97,	77,	116,	58 },
	{ 50,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	59 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	60 },	// 31
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	61 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	62 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	63 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	64 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	65 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	66 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	67 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	68 },
	{ 65,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	69 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	70 },	// 41
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	71 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	72 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	73 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	74 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	75 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	76 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	77 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	78 },
	{ 75,	20107,	50,	200,	67,	89,	45,	22,	99,	79,	118,	79 }
};

const TMobRankStat MobRankStats[MOB_RANK_MAX_NUM] =
/*
   {
   int         iGoldPercent;
   }
 */
{
	{  20,  }, // MOB_RANK_PAWN, 
	{  20,  }, // MOB_RANK_S_PAWN, 
	{  25,  }, // MOB_RANK_KNIGHT, 
	{  30,  }, // MOB_RANK_S_KNIGHT, 
	{  50,  }, // MOB_RANK_BOSS, 
	{ 100,  }  // MOB_RANK_KING,
};

TBattleTypeStat BattleTypeStats[BATTLE_TYPE_MAX_NUM] =
/*
   {
   int         AttGradeBias;
   int         DefGradeBias;
   int         MagicAttGradeBias;
   int         MagicDefGradeBias;
   }
 */
{
	{	  0,	  0,	  0,	-10	}, // BATTLE_TYPE_MELEE, 
	{	 10,	-20,	-10,	-15	}, // BATTLE_TYPE_RANGE,
	{	 -5,	 -5,	 10,	 10	}, // BATTLE_TYPE_MAGIC,  
	{	  0,	  0,	  0,	  0	}, // BATTLE_TYPE_SPECIAL,
	{	 10,	-10,	  0,	-15	}, // BATTLE_TYPE_POWER,  
	{	-10,	 10,	-10,	  0	}, // BATTLE_TYPE_TANKER,
	{	 20,	-20,	  0,	-10	}, // BATTLE_TYPE_SUPER_POWER,
	{	-20,	 20,	-10,	  0	}, // BATTLE_TYPE_SUPER_TANKER,
};

const unsigned long long * exp_table = NULL;

unsigned long long exp_table_unify[PLAYER_EXP_TABLE_MAX + 1] =
{
	0ULL,	//	0
	300ULL,		
	800ULL,		
	1500ULL,		
	2500ULL,		
	4300ULL,		
	7200ULL,		
	11000ULL,		
	17000ULL,		
	24000ULL,		
	33000ULL,	//	10
	43000ULL,		
	58000ULL,		
	76000ULL,		
	100000ULL,		
	130000ULL,		
	169000ULL,		
	219000ULL,		
	283000ULL,		
	365000ULL,		
	472000ULL,	//	20
	610000ULL,		
	705000ULL,		
	813000ULL,		
	937000ULL,		
	1077000ULL,		
	1237000ULL,		
	1418000ULL,		
	1624000ULL,		
	1857000ULL,		
	2122000ULL,	//	30
	2421000ULL,		
	2761000ULL,		
	3145000ULL,		
	3580000ULL,		
	4073000ULL,		
	4632000ULL,		
	5194000ULL,		
	5717000ULL,		
	6264000ULL,		
	6837000ULL,	//	40
	7600000ULL,		
	8274000ULL,		
	8990000ULL,		
	9753000ULL,		
	10560000ULL,		
	11410000ULL,		
	12320000ULL,		
	13270000ULL,		
	14280000ULL,		
	15340000ULL,	//	50
	16870000ULL,		
	18960000ULL,		
	19980000ULL,		
	21420000ULL,		
	22930000ULL,		
	24530000ULL,		
	26200000ULL,		
	27960000ULL,		
	29800000ULL,		
	32780000ULL,	//	60
	36060000ULL,		
	39670000ULL,		
	43640000ULL,		
	48000000ULL,		
	52800000ULL,		
	58080000ULL,		
	63890000ULL,		
	70280000ULL,		
	77310000ULL,		
	85040000ULL,	//	70
	93540000ULL,		
	102900000ULL,		
	113200000ULL,		
	124500000ULL,		
	137000000ULL,		
	150700000ULL,		
	165700000ULL,		
	236990000ULL,		
	260650000ULL,		
	286780000ULL,	//	80
	315380000ULL,		
	346970000ULL,		
	381680000ULL,		
	419770000ULL,		
	461760000ULL,		
	508040000ULL,		
	558740000ULL,		
	614640000ULL,		
	676130000ULL,		
	743730000ULL,	//	90
	1041222000ULL,		
	1145344200ULL,		
	1259878620ULL,		
	1385866482ULL,		
	1524453130ULL,		
	1676898443ULL,		
	1844588288ULL,		
	2029047116ULL,		
	2050000000ULL,	//	99레벨 일 때 필요경험치 (100레벨이 되기 위한)
	2150000000ULL,	//	100
	2210000000ULL,		
	2250000000ULL,		
	2280000000ULL,		
	2310000000ULL,		
	2330000000ULL,	//	105
	2350000000ULL,		
	2370000000ULL,		
	2390000000ULL,		
	2400000000ULL,		
	2410000000ULL,	//	110
	2420000000ULL,		
	2430000000ULL,		
	2440000000ULL,		
	2450000000ULL,		
	2460000000ULL,	//	115
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	120
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	125
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	130
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	135
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	140
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	145
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	150
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	155
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	160
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	165
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	170
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	175
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	180
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	185
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	190
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	195
	2470000000ULL,		
	2480000000ULL,		
	2490000000ULL,		
	2490000000ULL,		
	2500000000ULL,	//	200
};

const int * aiPercentByDeltaLev = NULL;
const int * aiPercentByDeltaLevForBoss = NULL;

// 적과 나와의 레벨차이에 의한 계산에 사용되는 테이블
// MIN(MAX_EXP_DELTA_OF_LEV - 1, (적렙 + 15) - 내렙))
const int aiPercentByDeltaLevForBoss_euckr[MAX_EXP_DELTA_OF_LEV] =
{
	1,      // -15  0
	3,          // -14  1
	5,          // -13  2
	7,          // -12  3
	15,         // -11  4
	30,         // -10  5
	60,         // -9   6
	90,         // -8   7
	91,         // -7   8
	92,         // -6   9
	93,         // -5   10
	94,         // -4   11
	95,         // -3   12
	97,         // -2   13
	99,         // -1   14
	100,        // 0    15
	105,        // 1    16
	110,        // 2    17
	115,        // 3    18
	120,        // 4    19
	125,        // 5    20
	130,        // 6    21
	135,        // 7    22
	140,        // 8    23
	145,        // 9    24
	150,        // 10   25
	155,        // 11   26
	160,        // 12   27
	165,        // 13   28
	170,        // 14   29
	180         // 15   30
};



const int aiPercentByDeltaLev_euckr[MAX_EXP_DELTA_OF_LEV] =
{
	1,  //  -15 0
	5,  //  -14 1
	10, //  -13 2
	20, //  -12 3
	30, //  -11 4
	50, //  -10 5
	70, //  -9  6
	80, //  -8  7
	85, //  -7  8
	90, //  -6  9
	92, //  -5  10
	94, //  -4  11
	96, //  -3  12
	98, //  -2  13
	100,    //  -1  14
	100,    //  0   15
	105,    //  1   16
	110,    //  2   17
	115,    //  3   18
	120,    //  4   19
	125,    //  5   20
	130,    //  6   21
	135,    //  7   22
	140,    //  8   23
	145,    //  9   24
	150,    //  10  25
	155,    //  11  26
	160,    //  12  27
	165,    //  13  28
	170,    //  14  29
	180,    //  15  30
};

const DWORD party_exp_distribute_table[PLAYER_MAX_LEVEL_CONST + 1] = 
{
	0,
	10,		10,		10,		10,		15,		15,		20,		25,		30,		40,		// 1 - 10
	50,		60,		80,		100,	120,	140,	160,	184,	210,	240,	// 11 - 20
	270,	300,	330,	360,	390,	420,	450,	480,	510,	550,	// 21 - 30
	600,	640,	700,	760,	820,	880,	940,	1000,	1100,	1180,	// 31 - 40
	1260,	1320,	1380,	1440,	1500,	1560,	1620,	1680,	1740,	1800,	// 41 - 50
	1860,	1920,	2000,	2100,	2200,	2300,	2450,	2600,	2750,	2900,	// 51 - 60
	3050,	3200,	3350,	3500,	3650,	3800,	3950,	4100,	4250,	4400,	// 61 - 70
	4600,	4800,	5000,	5200,	5400,	5600,	5800,	6000,	6200,	6400,	// 71 - 80
	6600,	6900,	7100,	7300,	7600,	7800,	8000,	8300,	8500,	8800,	// 81 - 90
	9000,	9000,	9000,	9000,	9000,	9000,	9000,	9000,	9000,	9000,	// 91 - 100
	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	10000,	// 101 - 110
	12000,	12000,	12000,	12000,	12000,	12000,	12000,	12000,	12000,	12000,	// 111 - 120
};

Coord aArroundCoords[ARROUND_COORD_MAX_NUM] = 
{
	{	     0,	      0	    },
	{        0,      50     },
	{       35,     35      },
	{       50,     -0      },
	{       35,     -35     },
	{       0,      -50     },
	{       -35,    -35     },
	{       -50,    0       },
	{       -35,    35      },
	{       0,      100     },
	{       71,     71      },
	{       100,    -0      },
	{       71,     -71     },
	{       0,      -100    },
	{       -71,    -71     },
	{       -100,   0       },
	{       -71,    71      },
	{       0,      150     },
	{       106,    106     },
	{       150,    -0      },
	{       106,    -106    },
	{       0,      -150    },
	{       -106,   -106    },
	{       -150,   0       },
	{       -106,   106     },
	{       0,      200     },
	{       141,    141     },
	{       200,    -0      },
	{       141,    -141    },
	{       0,      -200    },
	{       -141,   -141    },
	{       -200,   0       },
	{       -141,   141     },
	{       0,      250     },
	{       177,    177     },
	{       250,    -0      },
	{       177,    -177    },
	{       0,      -250    },
	{       -177,   -177    },
	{       -250,   0       },
	{       -177,   177     },
	{       0,      300     },
	{       212,    212     },
	{       300,    -0      },
	{       212,    -212    },
	{       0,      -300    },
	{       -212,   -212    },
	{       -300,   0       },
	{       -212,   212     },
	{       0,      350     },
	{       247,    247     },
	{       350,    -0      },
	{       247,    -247    },
	{       0,      -350    },
	{       -247,   -247    },
	{       -350,   0       },
	{       -247,   247     },
	{       0,      400     },
	{       283,    283     },
	{       400,    -0      },
	{       283,    -283    },
	{       0,      -400    },
	{       -283,   -283    },
	{       -400,   0       },
	{       -283,   283     },
	{       0,      450     },
	{       318,    318     },
	{       450,    -0      },
	{       318,    -318    },
	{       0,      -450    },
	{       -318,   -318    },
	{       -450,   0       },
	{       -318,   318     },
	{       0,      500     },
	{       354,    354     },
	{       500,    -0      },
	{       354,    -354    },
	{       0,      -500    },
	{       -354,   -354    },
	{       -500,   0       },
	{       -354,   354     },
	{       0,      550     },
	{       389,    389     },
	{       550,    -0      },
	{       389,    -389    },
	{       0,      -550    },
	{       -389,   -389    },
	{       -550,   0       },
	{       -389,   389     },
	{       0,      600     },
	{       424,    424     },
	{       600,    -0      },
	{       424,    -424    },
	{       0,      -600    },
	{       -424,   -424    },
	{       -600,   0       },
	{       -424,   424     },
	{       0,      650     },
	{       460,    460     },
	{       650,    -0      },
	{       460,    -460    },
	{       0,      -650    },
	{       -460,   -460    },
	{       -650,   0       },
	{       -460,   460     },
	{       0,      700     },
	{       495,    495     },
	{       700,    -0      },
	{       495,    -495    },
	{       0,      -700    },
	{       -495,   -495    },
	{       -700,   0       },
	{       -495,   495     },
	{       0,      750     },
	{       530,    530     },
	{       750,    -0      },
	{       530,    -530    },
	{       0,      -750    },
	{       -530,   -530    },
	{       -750,   0       },
	{       -530,   530     },
	{       0,      800     },
	{       566,    566     },
	{       800,    -0      },
	{       566,    -566    },
	{       0,      -800    },
	{       -566,   -566    },
	{       -800,   0       },
	{       -566,   566     },
	{       0,      850     },
	{       601,    601     },
	{       850,    -0      },
	{       601,    -601    },
	{       0,      -850    },
	{       -601,   -601    },
	{       -850,   0       },
	{       -601,   601     },
	{       0,      900     },
	{       636,    636     },
	{       900,    -0      },
	{       636,    -636    },
	{       0,      -900    },
	{       -636,   -636    },
	{       -900,   0       },
	{       -636,   636     },
	{       0,      950     },
	{       672,    672     },
	{       950,    -0      },
	{       672,    -672    },
	{       0,      -950    },
	{       -672,   -672    },
	{       -950,   0       },
	{       -672,   672     },
	{       0,      1000    },
	{       707,    707     },
	{       1000,   -0      },
	{       707,    -707    },
	{       0,      -1000   },
	{       -707,   -707    },
	{       -1000,  0       },
	{       -707,   707     },
};

const DWORD guild_exp_table[GUILD_MAX_LEVEL+1] =
{
	0,
	15000UL,
	45000UL,
	90000UL,
	160000UL,
	235000UL,
	325000UL,
	430000UL,
	550000UL,
	685000UL,
	835000UL,
	1000000UL,
	1500000UL,
	2100000UL,
	2800000UL,
	3600000UL,
	4500000UL,
	6500000UL,
	8000000UL,
	10000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL,
	42000000UL
};

const int aiMobEnchantApplyIdx[MOB_ENCHANTS_MAX_NUM] =
{
	APPLY_CURSE_PCT,
	APPLY_SLOW_PCT,
	APPLY_POISON_PCT,
	APPLY_STUN_PCT,
	APPLY_CRITICAL_PCT,
	APPLY_PENETRATE_PCT,
};

const int aiMobResistsApplyIdx[MOB_RESISTS_MAX_NUM] =
{
	APPLY_RESIST_SWORD,
	APPLY_RESIST_TWOHAND,
	APPLY_RESIST_DAGGER,
	APPLY_RESIST_BELL,
	APPLY_RESIST_FAN,
	APPLY_RESIST_BOW,
	APPLY_RESIST_FIRE,
	APPLY_RESIST_ELEC,
	APPLY_RESIST_MAGIC,
	APPLY_RESIST_WIND,
	APPLY_POISON_REDUCE,
};

const int aiSocketPercentByQty[5][4] =
{
	{  0,  0,  0,  0 },
	{  3,  0,  0,  0 },
	{ 10,  1,  0,  0 },
	{ 15, 10,  1,  0 },
	{ 20, 15, 10,  1 }
};

const int aiWeaponSocketQty[WEAPON_NUM_TYPES] =
{
	3, // WEAPON_SWORD,
	3, // WEAPON_DAGGER,
	3, // WEAPON_BOW,
	3, // WEAPON_TWO_HANDED,
	3, // WEAPON_BELL,
	3, // WEAPON_FAN,
	0, // WEAPON_ARROW,
	0, // WEAPON_MOUNT_SPEAR
};

const int aiArmorSocketQty[ARMOR_NUM_TYPES] =
{
	3, // ARMOR_BODY,
	1, // ARMOR_HEAD,
	1, // ARMOR_SHIELD,
	0, // ARMOR_WRIST,
	0, // ARMOR_FOOTS,
	0  // ARMOR_ACCESSORY
};

TItemAttrMap g_map_itemAttr;
TItemAttrMap g_map_itemRare;

const TApplyInfo aApplyInfo[MAX_APPLY_NUM] =
/*
{
   DWORD dwPointType;
}
 */
{
	// Point Type
	{ POINT_NONE,			},   // APPLY_NONE,		0
	{ POINT_MAX_HP,		        },   // APPLY_MAX_HP,		1
	{ POINT_MAX_SP,		        },   // APPLY_MAX_SP,		2
	{ POINT_HT,			        },   // APPLY_CON,		3
	{ POINT_IQ,			        },   // APPLY_INT,		4
	{ POINT_ST,			        },   // APPLY_STR,		5
	{ POINT_DX,			        },   // APPLY_DEX,		6
	{ POINT_ATT_SPEED,		        },   // APPLY_ATT_SPEED,	7
	{ POINT_MOV_SPEED,		        },   // APPLY_MOV_SPEED,	8
	{ POINT_CASTING_SPEED,	        },   // APPLY_CAST_SPEED,	9
	{ POINT_HP_REGEN,			},   // APPLY_HP_REGEN,		10
	{ POINT_SP_REGEN,			},   // APPLY_SP_REGEN,		11
	{ POINT_POISON_PCT,		        },   // APPLY_POISON_PCT,	12
	{ POINT_STUN_PCT,		        },   // APPLY_STUN_PCT,		13
	{ POINT_SLOW_PCT,		        },   // APPLY_SLOW_PCT,		14
	{ POINT_CRITICAL_PCT,		},   // APPLY_CRITICAL_PCT,	15
	{ POINT_PENETRATE_PCT,	        },   // APPLY_PENETRATE_PCT,	16
	{ POINT_ATTBONUS_HUMAN,	        },   // APPLY_ATTBONUS_HUMAN,	17
	{ POINT_ATTBONUS_ANIMAL,	        },   // APPLY_ATTBONUS_ANIMAL,	18
	{ POINT_ATTBONUS_ORC,		},   // APPLY_ATTBONUS_ORC,	19
	{ POINT_ATTBONUS_MILGYO,	        },   // APPLY_ATTBONUS_MILGYO,	20
	{ POINT_ATTBONUS_UNDEAD,	        },   // APPLY_ATTBONUS_UNDEAD,	21
	{ POINT_ATTBONUS_DEVIL,	        },   // APPLY_ATTBONUS_DEVIL,	22
	{ POINT_STEAL_HP,		        },   // APPLY_STEAL_HP,		23
	{ POINT_STEAL_SP,		        },   // APPLY_STEAL_SP,		24
	{ POINT_MANA_BURN_PCT,	        },   // APPLY_MANA_BURN_PCT,	25
	{ POINT_DAMAGE_SP_RECOVER,	        },   // APPLY_DAMAGE_SP_RECOVER,26
	{ POINT_BLOCK,		        },   // APPLY_BLOCK,		27
	{ POINT_DODGE,		        },   // APPLY_DODGE,		28
	{ POINT_RESIST_SWORD,		},   // APPLY_RESIST_SWORD,	29
	{ POINT_RESIST_TWOHAND,	        },   // APPLY_RESIST_TWOHAND,	30
	{ POINT_RESIST_DAGGER,	        },   // APPLY_RESIST_DAGGER,	31
	{ POINT_RESIST_BELL,		},   // APPLY_RESIST_BELL,	32
	{ POINT_RESIST_FAN,		        },   // APPLY_RESIST_FAN,	33
	{ POINT_RESIST_BOW,		        },   // APPLY_RESIST_BOW,	34
	{ POINT_RESIST_FIRE,		},   // APPLY_RESIST_FIRE,	35
	{ POINT_RESIST_ELEC,		},   // APPLY_RESIST_ELEC,	36
	{ POINT_RESIST_MAGIC,		},   // APPLY_RESIST_MAGIC,	37
	{ POINT_RESIST_WIND,		},   // APPLY_RESIST_WIND,	38
	{ POINT_REFLECT_MELEE,	        },   // APPLY_REFLECT_MELEE,	39
	{ POINT_REFLECT_CURSE,	        },   // APPLY_REFLECT_CURSE,	40
	{ POINT_POISON_REDUCE,	        },   // APPLY_POISON_REDUCE,	41
	{ POINT_KILL_SP_RECOVER,	        },   // APPLY_KILL_SP_RECOVER,	42
	{ POINT_EXP_DOUBLE_BONUS,	        },   // APPLY_EXP_DOUBLE_BONUS,	43
	{ POINT_GOLD_DOUBLE_BONUS,	        },   // APPLY_GOLD_DOUBLE_BONUS,44
	{ POINT_ITEM_DROP_BONUS,	        },   // APPLY_ITEM_DROP_BONUS,	45
	{ POINT_POTION_BONUS,		},   // APPLY_POTION_BONUS,	46
	{ POINT_KILL_HP_RECOVERY,	        },   // APPLY_KILL_HP_RECOVER,	47
	{ POINT_IMMUNE_STUN,		},   // APPLY_IMMUNE_STUN,	48
	{ POINT_IMMUNE_SLOW,		},   // APPLY_IMMUNE_SLOW,	49
	{ POINT_IMMUNE_FALL,		},   // APPLY_IMMUNE_FALL,	50
	{ POINT_NONE,			},   // APPLY_SKILL,		51
	{ POINT_BOW_DISTANCE,		},   // APPLY_BOW_DISTANCE,	52
	{ POINT_ATT_GRADE_BONUS,	        },   // APPLY_ATT_GRADE,	53
	{ POINT_DEF_GRADE_BONUS,	        },   // APPLY_DEF_GRADE,	54
	{ POINT_MAGIC_ATT_GRADE_BONUS,      },   // APPLY_MAGIC_ATT_GRADE,	55
	{ POINT_MAGIC_DEF_GRADE_BONUS,      },   // APPLY_MAGIC_DEF_GRADE,	56
	{ POINT_CURSE_PCT,			},   // APPLY_CURSE_PCT,	57
	{ POINT_MAX_STAMINA			},   // APPLY_MAX_STAMINA	58
	{ POINT_ATTBONUS_WARRIOR		},   // APPLY_ATTBONUS_WARRIOR  59
	{ POINT_ATTBONUS_ASSASSIN		},   // APPLY_ATTBONUS_ASSASSIN 60
	{ POINT_ATTBONUS_SURA		},   // APPLY_ATTBONUS_SURA     61
	{ POINT_ATTBONUS_SHAMAN		},   // APPLY_ATTBONUS_SHAMAN   62
	{ POINT_ATTBONUS_MONSTER		},   //	APPLY_ATTBONUS_MONSTER  63
	{ POINT_ATT_BONUS		},   // 64 // APPLY_MALL_ATTBONUS
	{ POINT_MALL_DEFBONUS		},   // 65
	{ POINT_MALL_EXPBONUS		},   // 66 APPLY_MALL_EXPBONUS
	{ POINT_MALL_ITEMBONUS		},   // 67
	{ POINT_MALL_GOLDBONUS		},   // 68
	{ POINT_MAX_HP_PCT			},		// 69
	{ POINT_MAX_SP_PCT			},		// 70
	{ POINT_SKILL_DAMAGE_BONUS		},	// 71
	{ POINT_NORMAL_HIT_DAMAGE_BONUS	},	// 72

	// DEFEND_BONUS_ATTRIBUTES
	{ POINT_SKILL_DEFEND_BONUS		},	// 73
	{ POINT_NORMAL_HIT_DEFEND_BONUS	},	// 74
	// END_OF_DEFEND_BONUS_ATTRIBUTES

	// PC_BANG_ITEM_ADD
	{ POINT_PC_BANG_EXP_BONUS	},		// 75
	{ POINT_PC_BANG_DROP_BONUS	},		// 76
	// END_PC_BANG_ITEM_ADD

	{ POINT_NONE,		},				// 77 사용시 HP 소모 APPLY_EXTRACT_HP_PCT

	{ POINT_RESIST_WARRIOR,		},		// 78 무사에게 저항 APPLY_RESIST_WARRIOR
	{ POINT_RESIST_ASSASSIN,	},		// 79 자객에게 저항 APPLY_RESIST_ASSASSIN
	{ POINT_RESIST_SURA,		},		// 80 수라에게 저항 APPLY_RESIST_SURA
	{ POINT_RESIST_SHAMAN,		},		// 81 무당에게 저항 APPLY_RESIST_SHAMAN
	{ POINT_ENERGY				},		// 82 기력 
	{ POINT_DEF_GRADE			},		// 83 방어력. DEF_GRADE_BONUS는 클라에서 두배로 보여지는 의도된 버그(...)가 있다.
	{ POINT_COSTUME_ATTR_BONUS	},		// 84 코스튬에 붙은 속성에 대해서만 보너스를 주는 기력
	{ POINT_MAGIC_ATT_BONUS_PER },			// 85 마법 공격력 +x%
	{ POINT_MELEE_MAGIC_ATT_BONUS_PER		},			// 86 APPLY_MELEE_MAGIC_ATTBONUS_PER
	{ POINT_RESIST_ICE,			},   // APPLY_RESIST_ICE,	87
	{ POINT_RESIST_EARTH,		},   // APPLY_RESIST_EARTH,	88
	{ POINT_RESIST_DARK,		},   // APPLY_RESIST_DARK,	89
	{ POINT_RESIST_CRITICAL,		},   // APPLY_ANTI_CRITICAL_PCT,	90
	{ POINT_RESIST_PENETRATE,		},   // APPLY_ANTI_PENETRATE_PCT,	91

	{ POINT_ATTBONUS_WOLFMAN,		},	 // APPLY_ATTBONUS_WOLFMAN,		//92 수인족에게 강함
	{ POINT_RESIST_WOLFMAN,			},	 // APPLY_RESIST_WOLFMAN,		//93 수인족에게 저항
	{ POINT_RESIST_CLAW,			},	 // APPLY_RESIST_CLAW,			//94 CLAW에게 저항
};

const int aiItemMagicAttributePercentHigh[ITEM_ATTRIBUTE_MAX_LEVEL] =
{
	//25, 25, 40, 8, 2,
	30, 40, 20, 8, 2
};

const int aiItemMagicAttributePercentLow[ITEM_ATTRIBUTE_MAX_LEVEL] =
{
	//45, 25, 20, 10, 0,
	50, 40, 10, 0, 0
};

// ADD_ITEM_ATTRIBUTE
int aiItemAttributeAddPercent[ITEM_ATTRIBUTE_MAX_NUM] =
{
	100, 80, 60, 50, 30, 0, 0, 
};
// END_OF_ADD_ITEM_ATTRIBUTE

const int aiExpLossPercents[PLAYER_EXP_TABLE_MAX + 1] =
{
	0,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 4, // 1 - 10
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, // 11 - 20
	4, 4, 4, 4, 4, 4, 4, 3, 3, 3, // 21 - 30
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, // 31 - 40
	3, 3, 3, 3, 2, 2, 2, 2, 2, 2, // 41 - 50
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // 51 - 60
	2, 2, 1, 1, 1, 1, 1, 1, 1, 1, // 61 - 70
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 71 - 80
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 81 - 90
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 91 - 100
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 101 - 110
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 111 - 120
};

const int aiSkillBookCountForLevelUp[10] =
{
	3, 3, 3, 3, 3, 4, 4, 5, 5, 6
};

// ADD_GRANDMASTER_SKILL
const int aiGrandMasterSkillBookCountForLevelUp[10] =
{
	3, 3, 5, 5, 7, 7, 10, 10, 10, 20, 
};

const int aiGrandMasterSkillBookMinCount[10] = 
{
//	1, 1, 3, 5, 10, 15, 20, 30, 40, 50, 
//	3, 3, 5, 5, 10, 10, 15, 15, 20, 30
	1, 1, 1, 2,  2,  3,  3,  4,  5,  6
};

const int aiGrandMasterSkillBookMaxCount[10] = 
{
//	6, 15, 30, 45, 60, 80, 100, 120, 160, 200,
//	6, 10, 15, 20, 30, 40, 50, 60, 70, 80
	5,  7,  9, 11, 13, 15, 20, 25, 30, 35
};
// END_OF_ADD_GRANDMASTER_SKILL

const int CHN_aiPartyBonusExpPercentByMemberCount[9] =
{
	0, 0, 12, 18, 26, 40, 53, 70, 100
};


// UPGRADE_PARTY_BONUS
const int KOR_aiPartyBonusExpPercentByMemberCount[9] =
{
	0, 
	0, 
	30, // 66% * 2 - 100  
	60, // 53% * 3 - 100 
	75, // 44% * 4 - 100
	90, // 38% * 5 - 100
	105, // 34% * 6 - 100
	110, // 30% * 7 - 100
	140, // 30% * 8 - 100
};

const int KOR_aiUniqueItemPartyBonusExpPercentByMemberCount[9] =
{
	0, 
	0, 
	15*2, 
	14*3, 
	13*4, 
	12*5, 
	11*6, 
	10*7, 
	10*8,
};
// END_OF_UPGRADE_PARTY_BONUS

const int * aiChainLightningCountBySkillLevel = NULL;

const int aiChainLightningCountBySkillLevel_euckr[SKILL_MAX_LEVEL+1] =
{
	0,	// 0
	2,	// 1
	2,	// 2
	2,	// 3
	2,	// 4
	2,	// 5
	2,	// 6
	2,	// 7
	2,	// 8
	3,	// 9
	3,	// 10
	3,	// 11
	3,	// 12
	3,	// 13
	3,	// 14
	3,	// 15
	3,	// 16
	3,	// 17
	3,	// 18
	4,	// 19
	4,	// 20
	4,	// 21
	4,	// 22
	4,	// 23
	5,	// 24
	5,	// 25
	5,	// 26
	5,	// 27
	5,	// 28
	5,	// 29
	5,	// 30
	5,	// 31
	5,	// 32
	5,	// 33
	5,	// 34
	5,	// 35
	5,	// 36
	5,	// 37
	5,	// 38
	5,	// 39
	5,	// 40
};

const SStoneDropInfo aStoneDrop[STONE_INFO_MAX_NUM] =
{
	//  mob		pct	{+0	+1	+2	+3	+4}
	{8005,	60,	{30,	30,	30,	9,	1}	},
	{8006,	60,	{28,	29,	31,	11,	1}	},
	{8007,	60,	{24,	29,	32,	13,	2}	},
	{8008,	60,	{22,	28,	33,	15,	2}	},
	{8009,	60,	{21,	27,	33,	17,	2}	},
	{8010,	60,	{18,	26,	34,	20,	2}	},
	{8011,	60,	{14,	26,	35,	22,	3}	},
	{8012,	60,	{10,	26,	37,	24,	3}	},
	{8013,	60,	{2,	26,	40,	29,	3}	},
	{8014,	60,	{0,	26,	41,	30,	3}	},
};

const char * c_apszEmpireNames[EMPIRE_MAX_NUM] =
{
	"전제국",
	"신수국",
	"천조국",
	"진노국"
};

const char * c_apszPrivNames[MAX_PRIV_NUM] =
{
	"",
	"아이템이 나올 확률",
	"돈이 나올 확률",
	"돈 대박이 나올 확률",
	"경험치 배율",
};

const int aiPolymorphPowerByLevel[SKILL_MAX_LEVEL + 1] =
{
	10,   // 1
	11,   // 2
	11,   // 3
	12,   // 4
	13,   // 5
	13,   // 6
	14,   // 7
	15,   // 8
	16,   // 9
	17,   // 10
	18,   // 11
	19,   // 12
	20,   // 13
	22,   // 14
	23,   // 15
	24,   // 16
	26,   // 17
	27,   // 18
	29,   // 19
	31,   // 20
	33,   // 21
	35,   // 22
	37,   // 23
	39,   // 24
	41,   // 25
	44,   // 26
	46,   // 27
	49,   // 28
	52,   // 29
	55,   // 30
	59,   // 31
	62,   // 32
	66,   // 33
	70,   // 34
	74,   // 35
	79,   // 36
	84,   // 37
	89,   // 38
	94,   // 39
	100,  // 40
};

TGuildWarInfo KOR_aGuildWarInfo[GUILD_WAR_TYPE_MAX_NUM] =
/*
   {
   long lMapIndex;
   int iWarPrice;
   int iWinnerPotionRewardPctToWinner;
   int iLoserPotionRewardPctToWinner;
   int iInitialScore;
   int iEndScore;
   };
 */
{
	{ 0,        0,      0,      0,      0,      0       },
	{ 110,      0,      100,    50,     0,      100     },
	{ 111,      0,      100,    50,     0,      10      },
};

//
// 악세서리 소켓용 수치들
//

// 다이아몬드로 소켓을 추가할 때 확률
const int aiAccessorySocketAddPct[ITEM_ACCESSORY_SOCKET_MAX_NUM] =
{
	50, 50, 50
};

// 악세서리 수치 값의 몇%만큼의 성능을 추가하는지
const int aiAccessorySocketEffectivePct[ITEM_ACCESSORY_SOCKET_MAX_NUM + 1] = 
{
	0, 10, 20, 40
};

// 소켓 지속시간 24, 12, 6
const int aiAccessorySocketDegradeTime[ITEM_ACCESSORY_SOCKET_MAX_NUM + 1] =
{
	0, 3600 * 24, 3600 * 12, 3600 * 6
};

// 소켓 장착 성공률
const int aiAccessorySocketPutPct[ITEM_ACCESSORY_SOCKET_MAX_NUM + 1] =
{
	90, 80, 70, 0
};
// END_OF_ACCESSORY_REFINE

#include "../../common/length.h"
// from import_item_proto.c
typedef struct SValueName
{
    const char *	c_pszName;
    long		lValue;
} TValueName;

TValueName c_aApplyTypeNames[] =
{
    { "STR",		APPLY_STR		},
    { "DEX",		APPLY_DEX		},
    { "CON",		APPLY_CON		},
    { "INT",		APPLY_INT		},
    { "MAX_HP",		APPLY_MAX_HP		},
    { "MAX_SP",		APPLY_MAX_SP		},
    { "MAX_STAMINA",	APPLY_MAX_STAMINA	},
    { "POISON_REDUCE",	APPLY_POISON_REDUCE	},
    { "EXP_DOUBLE_BONUS", APPLY_EXP_DOUBLE_BONUS },
    { "GOLD_DOUBLE_BONUS", APPLY_GOLD_DOUBLE_BONUS },
    { "ITEM_DROP_BONUS", APPLY_ITEM_DROP_BONUS	},
    { "HP_REGEN",	APPLY_HP_REGEN		},
    { "SP_REGEN",	APPLY_SP_REGEN		},
    { "ATTACK_SPEED",	APPLY_ATT_SPEED		},
    { "MOVE_SPEED",	APPLY_MOV_SPEED		},
    { "CAST_SPEED",	APPLY_CAST_SPEED	},
    { "ATT_BONUS",	APPLY_ATT_GRADE_BONUS	},
    { "DEF_BONUS",	APPLY_DEF_GRADE_BONUS	},
    { "MAGIC_ATT_GRADE",APPLY_MAGIC_ATT_GRADE	},
    { "MAGIC_DEF_GRADE",APPLY_MAGIC_DEF_GRADE	},
    { "SKILL",		APPLY_SKILL		},
    { "ATTBONUS_ANIMAL",APPLY_ATTBONUS_ANIMAL	},
    { "ATTBONUS_UNDEAD",APPLY_ATTBONUS_UNDEAD	},
    { "ATTBONUS_DEVIL", APPLY_ATTBONUS_DEVIL	},
    { "ATTBONUS_HUMAN", APPLY_ATTBONUS_HUMAN	},
    { "ADD_BOW_DISTANCE",APPLY_BOW_DISTANCE	},
    { "DODGE",		APPLY_DODGE		},
    { "BLOCK",		APPLY_BLOCK		},
    { "RESIST_SWORD",	APPLY_RESIST_SWORD	},
    { "RESIST_TWOHAND",	APPLY_RESIST_TWOHAND	},
    { "RESIST_DAGGER",	APPLY_RESIST_DAGGER    },
    { "RESIST_BELL",	APPLY_RESIST_BELL	},
    { "RESIST_FAN",	APPLY_RESIST_FAN	},
    { "RESIST_BOW",	APPLY_RESIST_BOW	},
    { "RESIST_FIRE",	APPLY_RESIST_FIRE	},
    { "RESIST_ELEC",	APPLY_RESIST_ELEC	},
    { "RESIST_MAGIC",	APPLY_RESIST_MAGIC	},
    { "RESIST_WIND",	APPLY_RESIST_WIND	},
	{ "REFLECT_MELEE",	APPLY_REFLECT_MELEE },
	{ "REFLECT_CURSE",	APPLY_REFLECT_CURSE },
    { "RESIST_ICE",		APPLY_RESIST_ICE	},
    { "RESIST_EARTH",	APPLY_RESIST_EARTH	},
    { "RESIST_DARK",	APPLY_RESIST_DARK	},
    { "RESIST_CRITICAL",	APPLY_ANTI_CRITICAL_PCT	},
    { "RESIST_PENETRATE",	APPLY_ANTI_PENETRATE_PCT	},
    { "POISON",		APPLY_POISON_PCT	},
    { "SLOW",		APPLY_SLOW_PCT		},
    { "STUN",		APPLY_STUN_PCT		},
    { "STEAL_HP",	APPLY_STEAL_HP		},
    { "STEAL_SP",	APPLY_STEAL_SP		},
    { "MANA_BURN_PCT",	APPLY_MANA_BURN_PCT	},
    { "CRITICAL",	APPLY_CRITICAL_PCT	},
    { "PENETRATE",	APPLY_PENETRATE_PCT	},
    { "KILL_SP_RECOVER",APPLY_KILL_SP_RECOVER	},
    { "KILL_HP_RECOVER",APPLY_KILL_HP_RECOVER	},
    { "PENETRATE_PCT",	APPLY_PENETRATE_PCT	},
    { "CRITICAL_PCT",	APPLY_CRITICAL_PCT	},
    { "POISON_PCT",	APPLY_POISON_PCT	},
    { "STUN_PCT",	APPLY_STUN_PCT		},
    { "ATT_BONUS_TO_WARRIOR",	APPLY_ATTBONUS_WARRIOR  },
    { "ATT_BONUS_TO_ASSASSIN",	APPLY_ATTBONUS_ASSASSIN },
    { "ATT_BONUS_TO_SURA",	APPLY_ATTBONUS_SURA	    },
    { "ATT_BONUS_TO_SHAMAN",	APPLY_ATTBONUS_SHAMAN   },
    { "ATT_BONUS_TO_MONSTER",	APPLY_ATTBONUS_MONSTER  },
    { "ATT_BONUS_TO_MOB",	APPLY_ATTBONUS_MONSTER  },
    { "MALL_ATTBONUS",	APPLY_MALL_ATTBONUS	},
    { "MALL_EXPBONUS",	APPLY_MALL_EXPBONUS	},
    { "MALL_DEFBONUS",	APPLY_MALL_DEFBONUS	},  
    { "MALL_ITEMBONUS",	APPLY_MALL_ITEMBONUS	},
    { "MALL_GOLDBONUS", APPLY_MALL_GOLDBONUS	},
    { "MAX_HP_PCT",	APPLY_MAX_HP_PCT	},
    { "MAX_SP_PCT",	APPLY_MAX_SP_PCT	},
    { "SKILL_DAMAGE_BONUS",	APPLY_SKILL_DAMAGE_BONUS	},
    { "NORMAL_HIT_DAMAGE_BONUS",APPLY_NORMAL_HIT_DAMAGE_BONUS	},
    { "SKILL_DEFEND_BONUS",	APPLY_SKILL_DEFEND_BONUS	},
    { "NORMAL_HIT_DEFEND_BONUS",APPLY_NORMAL_HIT_DEFEND_BONUS	},
    { "PCBANG_EXP_BONUS", APPLY_PC_BANG_EXP_BONUS	},
    { "PCBANG_DROP_BONUS", APPLY_PC_BANG_DROP_BONUS	},

    { "RESIST_WARRIOR",	APPLY_RESIST_WARRIOR},
    { "RESIST_ASSASSIN",	APPLY_RESIST_ASSASSIN},
    { "RESIST_SURA",		APPLY_RESIST_SURA},
    { "RESIST_SHAMAN",	APPLY_RESIST_SHAMAN},
    // by mhh game/affect.h 정의되어있음. INFINITE_AFFECT_DURATION = 0x1FFFFFFF
    { "INFINITE_AFFECT_DURATION", 0x1FFFFFFF	},
	{ "ENERGY", APPLY_ENERGY },		//	기력
	{ "COSTUME_ATTR_BONUS", APPLY_COSTUME_ATTR_BONUS },		//	기력
	{ "MAGIC_ATTBONUS_PER",	APPLY_MAGIC_ATTBONUS_PER	},
    { "MELEE_MAGIC_ATTBONUS_PER",	APPLY_MELEE_MAGIC_ATTBONUS_PER	},
    
    { NULL,		0			}
};
// from import_item_proto.c

long FN_get_apply_type(const char *apply_type_string)
{
	TValueName	*value_name;
	for (value_name = c_aApplyTypeNames; value_name->c_pszName; ++value_name)
	{
		if (0==strcasecmp(value_name->c_pszName, apply_type_string))
			return value_name->lValue;
	}
	return 0;
}

bool SetHorseTable(char* input)
{
	//int[12] tmp = new int(12);
	int h_table[13];
	int count = 0;
	char* copy = input;
	char* pch;
	pch = strtok (copy," ");
	while (pch != NULL)
	{
		int value = atoi(pch);
		h_table[count] = value;
		count++;
		pch = strtok (NULL, " ");
	}
	int current_col = h_table[0];
	c_aHorseStat[current_col].iMinLevel = h_table[1];
	c_aHorseStat[current_col].iNPCRace = h_table[2];
	c_aHorseStat[current_col].iMaxHealth = h_table[3];
	c_aHorseStat[current_col].iMaxStamina = h_table[4];
	c_aHorseStat[current_col].iST = h_table[5];
	c_aHorseStat[current_col].iDX = h_table[6];
	c_aHorseStat[current_col].iHT = h_table[7];
	c_aHorseStat[current_col].iIQ = h_table[8];
	c_aHorseStat[current_col].iDamMean = h_table[9];
	c_aHorseStat[current_col].iDamMin = h_table[10];
	c_aHorseStat[current_col].iDamMax = h_table[11];
	c_aHorseStat[current_col].iArmor = h_table[12];	
	fprintf(stderr, "Horse_table override: Horse level %d\n", current_col);
	return true;
}
