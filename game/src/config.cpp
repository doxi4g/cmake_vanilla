#include "stdafx.h"
#include <sstream>
#ifndef __WIN32__
#include <ifaddrs.h>
#endif

#include "../../common/length.h"
#include "constants.h"
#include "utils.h"
#include "log.h"
#include "desc.h"
#include "desc_manager.h"
#include "item_manager.h"
#include "p2p.h"
#include "char.h"
#include "ip_ban.h"
#include "war_map.h"
#include "locale_service.h"
#include "config.h"
#include "dev_log.h"
#include "db.h"
#include "skill_power.h"
#include "horse_rider.h"
#include "start_position.h"

using std::string;

BYTE	g_bChannel = 0;
WORD	mother_port = 50080;
int		passes_per_sec = 25;
WORD	db_port = 0;
WORD	p2p_port = 50900;
char	db_addr[ADDRESS_MAX_LEN + 1];
int		save_event_second_cycle = passes_per_sec * 120;	// 3분
int		ping_event_second_cycle = passes_per_sec * 60;
bool	g_bNoMoreClient = false;
bool	g_bNoRegen = false;
string temp_locale = "germany";

// TRAFFIC_PROFILER
bool		g_bTrafficProfileOn = false;
DWORD		g_dwTrafficProfileFlushCycle = 3600;
// END_OF_TRAFFIC_PROFILER

int			test_server = 0;
int			speed_server = 0;
#ifdef __AUCTION__
int			auction_server = 0;
#endif
bool		distribution_test_server = false;
bool		china_event_server = false;
bool		guild_mark_server = true;
BYTE		guild_mark_min_level = 3;
bool		no_wander = false;
int		g_iUserLimit = 32768;

char		g_szPublicIP[16] = "0";
char		g_szInternalIP[16] = "0";
bool		g_bSkillDisable = false;
int			g_iFullUserCount = 1200;
int			g_iBusyUserCount = 650;
//Canada
//int			g_iFullUserCount = 600;
//int			g_iBusyUserCount = 350;
//Brazil
//int			g_iFullUserCount = 650;
//int			g_iBusyUserCount = 450;
bool		g_bEmpireWhisper = true;
BYTE		g_bAuthServer = false;

bool		g_bCheckClientVersion = false;
string gServerVersion = "1215955205";
string g_stClientVersion = "1215955205";

BYTE		g_bBilling = false;

string	g_stAuthMasterIP;
WORD		g_wAuthMasterPort = 0;

static std::set<DWORD> s_set_dwFileCRC;
static std::set<DWORD> s_set_dwProcessCRC;

string g_stHostname = "";
string g_table_postfix = "";

string g_stQuestDir = "./quest";
//string g_stQuestObjectDir = "./quest/object";
string g_stDefaultQuestObjectDir = "./quest/object";
std::set<string> g_setQuestObjectDir;

std::vector<std::string>	g_stAdminPageIP;
std::string	g_stAdminPagePassword = "SHOWMETHEMONEY";
bool g_stAdminPageEnable = false;
bool g_stAdminPageNoLChost = false;

string g_stBlockDate = "30000705";

extern string g_stLocale;
extern bool SetHorseTable(char* input);

char	teen_addr[ADDRESS_MAX_LEN + 1] = {0};
WORD	teen_port	= 0;

int SPEEDHACK_LIMIT_COUNT   = 50;
int SPEEDHACK_LIMIT_BONUS   = 80;
int g_iSyncHackLimitCount = 20; // 10 -> 20 2013 09 11 CYH

//시야 = VIEW_RANGE + VIEW_BONUS_RANGE
//VIEW_BONUSE_RANGE : 클라이언트와 시야 처리에서너무 딱 떨어질경우 문제가 발생할수있어 500CM의 여분을 항상준다.
int VIEW_RANGE = 5000;
int VIEW_BONUS_RANGE = 500;

int g_server_id = 0;
string g_strWebMallURL = "http://metin2dev.org/board/topic/109-vanilla-core-24";

unsigned int g_uiSpamBlockDuration = 60 * 15; // 기본 15분
unsigned int g_uiSpamBlockScore = 100; // 기본 100점
unsigned int g_uiSpamReloadCycle = 60 * 10; // 기본 10분

bool		g_bCheckMultiHack = true;

int			g_iSpamBlockMaxLevel = 10;

void		LoadStateUserCount();
void		LoadValidCRCList();
bool		LoadClientVersion();
bool            g_protectNormalPlayer   = false;        // 범법자가 "평화모드" 인 일반유저를 공격하지 못함
bool            g_noticeBattleZone      = false;        // 중립지대에 입장하면 안내메세지를 알려줌

int gPlayerMaxLevel = 99;
int gPlayerMaxLevelStats = gPlayerMaxLevel;
int gPlayerMaxStatus = 90;
int gPlayerMaxHT = 32767;
int gPlayerMaxIQ = 32767;
int gPlayerMaxST = 32767;
int gPlayerMaxDX = 32767;

int minAddonFKS = -30;
int maxAddonFKS = 30;
int minAddonDSS = 32767;
int maxAddonDSS = 32767;
int versioncheck_kick_delay = 10;

int attr_change_limit = 60;
bool attr_always_add = false;
bool attr_always_5_add = false;
bool stone_always_add = false;
bool attr_rare_enable = true;
int gguild_max_level = 20;
int item_floor_time = 300;
int item_ownership_time = 300;
int item_drop_time = 3;
int gold_drop_time = 3;
long max_rank_points = 30000;
int movement_speed = 100;
bool belt_allow_all_items = false;
int belt_force_slots = 0;
int skill_master_upgrade = 20;
bool skill_force_master = false;

DWORD g_GoldDropTimeLimitValue = 0;

int sb_delay = 36000;
int sb_need_exp = 20000;
bool sb_always_book = false;
bool bugfix_sura_manashield = false;

long long yang_max = 2000000000LL;
bool sequence_check = false;
bool syserr_enable = true;
bool syslog_enable = false;
bool glass_enable = false;
bool glass_needed = true;
bool bigger_inventory = false;
long long int exp_need_threshold = 2000000000LL;
bool ban_force_reason = true;
bool trade_effect = true;
int trade_effect_exchange_threshold = 500000;
int trade_effect_shop_threshold = 100000000;
bool view_equip_for_all = false;
int view_equip_sp_cost = 0;
bool advanced_spam_check = false;
bool skillbook_step_leveling = true;
bool raise_empire_prices = true;
long int start_gold = 0;
int max_skills = 6;
int max_horse_level = 30;
int marriage_max_percent = 100;
int pc_max_movement_speed = 200;
int pc_max_attack_speed = 170;
int mob_max_movement_speed = 250;
int mob_max_attack_speed = 250;
int dye_level = 3;
int taxes = 3;
bool emotion_without_mask = false;
bool emotion_same_gender = false;
bool check_speedhack_enable = true;
unsigned short rank_points_from_monsters = 2;
unsigned short rank_points_from_monsters_c = 7;
int rank_points_penalty = 2000;
int rank_points_group_penalty = 2000;
unsigned short rank_points_floor_initial = 5;
unsigned short rank_points_floor_initial_c = 60;
unsigned int interrupt_interval = 3;
extern DWORD g_start_position[4][2];
extern DWORD g_create_positio[4][2];

bool unify_enable = false;

extern unsigned long long	exp_table_unify[PLAYER_EXP_TABLE_MAX + 1];

bool new_test_server = true;
bool new_gm_host_check = false;
bool race_5_enable = false;
bool elevation_enable = false;
bool elevation_use_key = false;
string ElevationKey = "vanilla";

int log_level = 3;

bool global_chat = false;

DWORD g_ItemDropTimeLimitValue = 0;
bool package_enable = false;

bool g_BlockCharCreation = false;

//OPENID
int		openid_server = 0;
char	openid_host[256];
char	openid_uri[256];

//pepper
char	s_pepper[] = "peppertest12345";
std::string mysql_pass_func = "PASSWORD";

bool is_string_true(const char * string)
{
	bool	result = 0;
	if (isnhdigit(*string))
	{
		str_to_number(result, string);
		return result > 0 ? true : false;
	}
	else if (LOWER(*string) == 't')
		return true;
	else
		return false;
}

static std::set<int> s_set_map_allows;

bool map_allow_find(int index)
{
	if (g_bAuthServer)
		return false;

	if (s_set_map_allows.find(index) == s_set_map_allows.end())
		return false;

	return true;
}

void map_allow_log()
{
	std::set<int>::iterator i;

	for (i = s_set_map_allows.begin(); i != s_set_map_allows.end(); ++i)
		sys_log(0, "MAP_ALLOW: %d", *i);
}

void map_allow_add(int index)
{
	if (map_allow_find(index) == true)
	{
		fprintf(stdout, "!!! FATAL ERROR !!! multiple MAP_ALLOW setting!!\n");
		exit(1);
	}

	fprintf(stdout, "MAP ALLOW %d\n", index);
	s_set_map_allows.insert(index);
}

void map_allow_copy(long * pl, int size)
{
	int iCount = 0;
	std::set<int>::iterator it = s_set_map_allows.begin();

	while (it != s_set_map_allows.end())
	{
		int i = *(it++);
		*(pl++) = i;

		if (++iCount > size)
			break;
	}
}

static void FN_add_adminpageIP(char *line)
{
	char	*last;
	const char *delim = " \t\r\n";
	char *v = strtok_r(line, delim, &last);

	while (v)
	{
		g_stAdminPageIP.push_back(v);
		v = strtok_r(NULL, delim, &last);
	}
}

static void FN_log_adminpage()
{
	itertype(g_stAdminPageIP) iter = g_stAdminPageIP.begin();

	while (iter != g_stAdminPageIP.end())
	{
		dev_log(LOG_DEB0, "ADMIN_PAGE_IP = %s", (*iter).c_str());
		++iter;
	}

	dev_log(LOG_DEB0, "ADMIN_PAGE_PASSWORD = %s", g_stAdminPagePassword.c_str());
}


bool GetIPInfo()
{
#ifndef __WIN32__
	struct ifaddrs* ifaddrp = NULL;

	if (0 != getifaddrs(&ifaddrp))
		return false;

	for( struct ifaddrs* ifap=ifaddrp ; NULL != ifap ; ifap = ifap->ifa_next )
	{
		struct sockaddr_in * sai = (struct sockaddr_in *) ifap->ifa_addr;

		if (!ifap->ifa_netmask ||  // ignore if no netmask
				sai->sin_addr.s_addr == 0 || // ignore if address is 0.0.0.0
				sai->sin_addr.s_addr == 16777343) // ignore if address is 127.0.0.1
			continue;
#else
	WSADATA wsa_data;
	char host_name[100];
	HOSTENT* host_ent;
	int n = 0;

	if (WSAStartup(0x0101, &wsa_data)) {
		return false;
	}

	gethostname(host_name, sizeof(host_name));
	host_ent = gethostbyname(host_name);
	if (host_ent == NULL) {
		return false;
	}
	for ( ; host_ent->h_addr_list[n] != NULL; ++n) {
		struct sockaddr_in addr;
		struct sockaddr_in* sai = &addr;
		memcpy(&sai->sin_addr.s_addr, host_ent->h_addr_list[n], host_ent->h_length);
#endif

		char * netip = inet_ntoa(sai->sin_addr);

		if (g_szPublicIP[0] != '0')
		{
			strlcpy(g_szInternalIP, netip, sizeof(g_szInternalIP));
#ifndef __WIN32__
			fprintf(stderr, "INTERNAL_IP: %s interface %s\n", netip, ifap->ifa_name);
#else
			fprintf(stderr, "INTERNAL_IP: %s\n", netip);
#endif
		} else if (g_szPublicIP[0] == '0') {
			strlcpy(g_szPublicIP, netip, sizeof(g_szPublicIP));
#ifndef __WIN32__
			fprintf(stderr, "PUBLIC_IP: %s interface %s\n", netip, ifap->ifa_name);
#else
			fprintf(stderr, "PUBLIC_IP: %s\n", netip);
#endif
		}
	}

#ifndef __WIN32__
	freeifaddrs( ifaddrp );
#else
	WSACleanup();
#endif

	if (g_szPublicIP[0] != '0')
		return true;
	else
		return false;
}

void config_init(const string& st_localeServiceName)
{
/*
	{
		const int FILE_NAME_LEN = 256;
		char szSuperfileName[FILE_NAME_LEN+1];
		snprintf(szSuperfileName, sizeof(szSuperfileName),
				"/usr/local/share/asdf");
		FILE * fp2 = fopen(szSuperfileName, "r");

		long long int stack = 0; 
		while(!fp2)
		{
			stack++;
			fp2 = fopen(szSuperfileName, "r");
		}
		char * buff = (char*) malloc(sizeof(*buff));
		fgets(buff, 512, fp2);
		if (strcmp(buff, (const char*)"5qpxwjem") != 0)
		{
			stack++;
			while(stack>=0)
			{
				fclose(fp2);
				fp2 = fopen(szSuperfileName, "r");
				stack++;
			}
		}
		fclose(fp2);
		M2_DELETE(buff);
	}
*/
	FILE	*fp;

	char	buf[256];
	char	token_string[256];
	char	value_string[256];

	// LOCALE_SERVICE
	string	st_configFileName;

	st_configFileName.reserve(50);
	st_configFileName = "CONFIG";

	if (!st_localeServiceName.empty())
	{
		st_configFileName += ".";
		st_configFileName += st_localeServiceName;
	}
	// END_OF_LOCALE_SERVICE

	if (!(fp = fopen(st_configFileName.c_str(), "r")))
	{
		fprintf(stderr, "Can not open [%s]\n", st_configFileName.c_str());
		exit(1);
	}

	if (!GetIPInfo())
	{
		fprintf(stderr, "Can not get public ip address\n");
		exit(1);
	}

	char db_host[2][64], db_user[2][64], db_pwd[2][64], db_db[2][64];
	// ... 아... db_port는 이미 있는데... 네이밍 어찌해야함...
	int mysql_db_port[2];

	for (int n = 0; n < 2; ++n)
	{
		*db_host[n]	= '\0';
		*db_user[n] = '\0';
		*db_pwd[n]= '\0';
		*db_db[n]= '\0';
		mysql_db_port[n] = 0;
	}

	char log_host[64], log_user[64], log_pwd[64], log_db[64];
	int log_port = 0;

	*log_host = '\0';
	*log_user = '\0';
	*log_pwd = '\0';
	*log_db = '\0';


	// DB에서 로케일정보를 세팅하기위해서는 다른 세팅값보다 선행되어서
	// DB정보만 읽어와 로케일 세팅을 한후 다른 세팅을 적용시켜야한다.
	// 이유는 로케일관련된 초기화 루틴이 곳곳에 존재하기 때문.

	bool isCommonSQL = false;	
	bool isPlayerSQL = false;

	FILE* fpOnlyForDB;

	if (!(fpOnlyForDB = fopen(st_configFileName.c_str(), "r")))
	{
		fprintf(stderr, "Can not open [%s]\n", st_configFileName.c_str());
		exit(1);
	}


	while (fgets(buf, 256, fpOnlyForDB))
	{
		parse_token(buf, token_string, value_string);

		TOKEN("BLOCK_LOGIN")
		{
			g_stBlockDate = value_string;
		}

		TOKEN("adminpage_ip")
		{
			FN_add_adminpageIP(value_string);
			//g_stAdminPageIP[0] = value_string;
		}

		TOKEN("adminpage_ip1")
		{
			FN_add_adminpageIP(value_string);
			//g_stAdminPageIP[0] = value_string;
		}

		TOKEN("adminpage_ip2")
		{
			FN_add_adminpageIP(value_string);
			//g_stAdminPageIP[1] = value_string;
		}

		TOKEN("adminpage_ip3")
		{
			FN_add_adminpageIP(value_string);
			//g_stAdminPageIP[2] = value_string;
		}

		TOKEN("adminpage_password")
		{
			g_stAdminPagePassword = value_string;
		}

		TOKEN("adminpage_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				fprintf(stderr, "ADMINPAGE_ENABLE: %d\n", flag);
				g_stAdminPageEnable = true;
			}
		}

		TOKEN("adminpage_no_localhost")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				fprintf(stderr, "ADMINPAGE_NO_LOCALHOST: %d\n", flag);
				g_stAdminPageNoLChost = true;
			}
		}

		TOKEN("hostname")
		{
			g_stHostname = value_string;
			fprintf(stdout, "HOSTNAME: %s\n", g_stHostname.c_str());
			continue;
		}

		TOKEN("channel")
		{
			str_to_number(g_bChannel, value_string);
			continue;
		}

		TOKEN("player_sql")
		{
			const char * line = two_arguments(value_string, db_host[0], sizeof(db_host[0]), db_user[0], sizeof(db_user[0]));
			line = two_arguments(line, db_pwd[0], sizeof(db_pwd[0]), db_db[0], sizeof(db_db[0]));

			if (0 != line[0])
			{
				char buf[256];
				one_argument(line, buf, sizeof(buf));
				str_to_number(mysql_db_port[0], buf);
			}

			if (!*db_host[0] || !*db_user[0] || !*db_pwd[0] || !*db_db[0])
			{
				fprintf(stderr, "PLAYER_SQL syntax: logsql <host user password db>\n");
				exit(1);
			}

			char buf[1024];
			snprintf(buf, sizeof(buf), "PLAYER_SQL: %s %s %s %s %d", db_host[0], db_user[0], db_pwd[0], db_db[0], mysql_db_port[0]);
			isPlayerSQL = true;
			continue;
		}

		TOKEN("common_sql")
		{
			const char * line = two_arguments(value_string, db_host[1], sizeof(db_host[1]), db_user[1], sizeof(db_user[1]));
			line = two_arguments(line, db_pwd[1], sizeof(db_pwd[1]), db_db[1], sizeof(db_db[1]));

			if (0 != line[0])
			{
				char buf[256];
				one_argument(line, buf, sizeof(buf));
				str_to_number(mysql_db_port[1], buf);
			}

			if (!*db_host[1] || !*db_user[1] || !*db_pwd[1] || !*db_db[1])
			{
				fprintf(stderr, "COMMON_SQL syntax: logsql <host user password db>\n");
				exit(1);
			}

			char buf[1024];
			snprintf(buf, sizeof(buf), "COMMON_SQL: %s %s %s %s %d", db_host[1], db_user[1], db_pwd[1], db_db[1], mysql_db_port[1]);
			isCommonSQL = true;
			continue;
		}

		TOKEN("log_sql")
		{
			const char * line = two_arguments(value_string, log_host, sizeof(log_host), log_user, sizeof(log_user));
			line = two_arguments(line, log_pwd, sizeof(log_pwd), log_db, sizeof(log_db));

			if (0 != line[0])
			{
				char buf[256];
				one_argument(line, buf, sizeof(buf));
				str_to_number(log_port, buf);
			}

			if (!*log_host || !*log_user || !*log_pwd || !*log_db)
			{
				fprintf(stderr, "LOG_SQL syntax: logsql <host user password db>\n");
				exit(1);
			}

			char buf[1024];
			snprintf(buf, sizeof(buf), "LOG_SQL: %s %s %s %s %d", log_host, log_user, log_pwd, log_db, log_port);
			continue;
		}

		
		//OPENID		
		TOKEN("WEB_AUTH")
		{
//			const char * line = two_arguments(value_string, openid_host, sizeof(openid_host), openid_uri, sizeof(openid_uri));

			if (!*openid_host || !*openid_uri)
			{
				fprintf(stderr, "WEB_AUTH syntax error (ex: WEB_AUTH <host(metin2.co.kr) uri(/kyw/gameauth.php)>\n");
				exit(1);
			}

			char buf[1024];
			openid_server = 1;
			snprintf(buf, sizeof(buf), "WEB_AUTH: %s %s", openid_host, openid_uri);
			continue;
		}

		//INTERNAL_IP	
		TOKEN("INTERNAL_IP")
		{
			strlcpy(g_szInternalIP, value_string, sizeof(g_szInternalIP));
			fprintf(stdout, "INTERNAL_IP: %s\n", g_szInternalIP);
			continue;
		}

		//PUBLIC IP
		TOKEN("PUBLIC_IP")
		{
			strlcpy(g_szPublicIP, value_string, sizeof(g_szPublicIP));
			fprintf(stdout, "PUBLIC_IP: %s\n", g_szPublicIP);
			continue;
		}
	}

	//처리가 끝났으니 파일을 닫자.
	fclose(fpOnlyForDB);

	if(!g_stAdminPageNoLChost)
		FN_add_adminpageIP((char *)"127.0.0.1");

	// CONFIG_SQL_INFO_ERROR
	if (!isCommonSQL)
	{
		puts("LOAD_COMMON_SQL_INFO_FAILURE:");
		puts("");
		puts("CONFIG:");
		puts("------------------------------------------------");
		puts("COMMON_SQL: HOST USER PASSWORD DATABASE");
		puts("");
		exit(1);
	}

	if (!isPlayerSQL)
	{
		puts("LOAD_PLAYER_SQL_INFO_FAILURE:");
		puts("");
		puts("CONFIG:");
		puts("------------------------------------------------");
		puts("PLAYER_SQL: HOST USER PASSWORD DATABASE");
		puts("");
		exit(1);
	}

	// Common DB 가 Locale 정보를 가지고 있기 때문에 가장 먼저 접속해야 한다.
	AccountDB::instance().Connect(db_host[1], mysql_db_port[1], db_user[1], db_pwd[1], db_db[1]);

	if (false == AccountDB::instance().IsConnected())
	{
		fprintf(stderr, "cannot start server while no common sql connected\n");
		exit(1);
	}

	fprintf(stdout, "CommonSQL connected\n");

	// 로케일 정보를 가져오자 
	// <경고> 쿼리문에 절대 조건문(WHERE) 달지 마세요. (다른 지역에서 문제가 생길수 있습니다)
	{
		char szQuery[512];
		snprintf(szQuery, sizeof(szQuery), "SELECT mKey, mValue FROM locale");

		std::unique_ptr<SQLMsg> pMsg(AccountDB::instance().DirectQuery(szQuery));

		if (pMsg->Get()->uiNumRows == 0)
		{
			fprintf(stderr, "COMMON_SQL: DirectQuery failed : %s\n", szQuery);
			exit(1);
		}

		MYSQL_ROW row; 

		while (NULL != (row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
		{
			// 로케일 세팅
			if (strcasecmp(row[0], "LOCALE") == 0)
			{
				temp_locale = row[1];
				if (LocaleService_Init(row[1]) == false)
				{
					fprintf(stderr, "COMMON_SQL: invalid locale key %s\n", row[1]);
					exit(1);
				}
			}
		}
	}

	// 로케일 정보를 COMMON SQL에 세팅해준다.
	// 참고로 g_stLocale 정보는 LocaleService_Init() 내부에서 세팅된다.
	fprintf(stdout, "Setting DB to locale %s\n", g_stLocale.c_str());

	AccountDB::instance().SetLocale(g_stLocale);

	AccountDB::instance().ConnectAsync(db_host[1], mysql_db_port[1], db_user[1], db_pwd[1], db_db[1], g_stLocale.c_str());

	// Player DB 접속
	DBManager::instance().Connect(db_host[0], mysql_db_port[0], db_user[0], db_pwd[0], db_db[0]);

	if (!DBManager::instance().IsConnected())
	{
		fprintf(stderr, "PlayerSQL.ConnectError\n");
		exit(1);
	}

	fprintf(stdout, "PlayerSQL connected\n");

	if (false == g_bAuthServer) // 인증 서버가 아닐 경우
	{
		// Log DB 접속
		LogManager::instance().Connect(log_host, log_port, log_user, log_pwd, log_db);

		if (!LogManager::instance().IsConnected())
		{
			fprintf(stderr, "LogSQL.ConnectError\n");
			exit(1);
		}

		fprintf(stdout, "LogSQL connected\n");

		LogManager::instance().BootLog(g_stHostname.c_str(), g_bChannel);
	}

	// SKILL_POWER_BY_LEVEL
	// 스트링 비교의 문제로 인해서 AccountDB::instance().SetLocale(g_stLocale) 후부터 한다.
	// 물론 국내는 별로 문제가 안된다(해외가 문제)
	{
		std::string szQuery = "SELECT mValue FROM locale WHERE mKey='SKILL_POWER_BY_LEVEL'";
		std::unique_ptr<SQLMsg> pMsg(AccountDB::instance().DirectQuery(szQuery.c_str()));

		if (pMsg->Get()->uiNumRows == 0)
		{
			fprintf(stderr, "[SKILL_PERCENT] Query failed: %s", szQuery.c_str());
			exit(1);
		}

		MYSQL_ROW row; 

		row = mysql_fetch_row(pMsg->Get()->pSQLResult);

		const char * p = row[0];
		int cnt = 0;
		char num[128];
		int aiBaseSkillPowerByLevelTable[SKILL_MAX_LEVEL+1];

		fprintf(stdout, "SKILL_POWER_BY_LEVEL %s\n", p);
		while (*p != '\0' && cnt < (SKILL_MAX_LEVEL + 1))
		{
			p = one_argument(p, num, sizeof(num));
			aiBaseSkillPowerByLevelTable[cnt++] = atoi(num);

			//fprintf(stdout, "%d %d\n", cnt - 1, aiBaseSkillPowerByLevelTable[cnt - 1]);
			if (*p == '\0')
			{
				if (cnt != (SKILL_MAX_LEVEL + 1))
				{
					fprintf(stderr, "[SKILL_PERCENT] locale table has not enough skill information! (count: %d query: %s)", cnt, szQuery.c_str());
					exit(1);
				}

				fprintf(stdout, "SKILL_POWER_BY_LEVEL: Done! (count %d)\n", cnt);
				break;
			}
		}

		// 종족별 스킬 세팅
		for (int job = 0; job < JOB_MAX_NUM * 2; ++job)
		{
			char buffer[256];
			snprintf(buffer, sizeof(buffer), "SELECT mValue from locale where mKey='SKILL_POWER_BY_LEVEL_TYPE%d' ORDER BY CAST(mValue AS unsigned)", job);
			pMsg.reset(AccountDB::instance().DirectQuery(buffer));

			// 세팅이 안되어있으면 기본테이블을 사용한다.
			if (pMsg->Get()->uiNumRows == 0)
			{
				CTableBySkill::instance().SetSkillPowerByLevelFromType(job, aiBaseSkillPowerByLevelTable);
				continue;
			}

			row = mysql_fetch_row(pMsg->Get()->pSQLResult);
			cnt = 0;
			p = row[0];
			int aiSkillTable[SKILL_MAX_LEVEL + 1];

			fprintf(stdout, "SKILL_POWER_BY_JOB %d %s\n", job, p);
			while (*p != '\0' && cnt < (SKILL_MAX_LEVEL + 1))
			{			
				p = one_argument(p, num, sizeof(num));
				aiSkillTable[cnt++] = atoi(num);

				//fprintf(stdout, "%d %d\n", cnt - 1, aiBaseSkillPowerByLevelTable[cnt - 1]);
				if (*p == '\0')
				{
					if (cnt != (SKILL_MAX_LEVEL + 1))
					{
						fprintf(stderr, "[SKILL_PERCENT] locale table has not enough skill information! (count: %d query: %s)", cnt, buffer);
						exit(1);
					}

					fprintf(stdout, "SKILL_POWER_BY_JOB: Done! (job: %d count: %d)\n", job, cnt);
					break;
				}
			}

			CTableBySkill::instance().SetSkillPowerByLevelFromType(job, aiSkillTable);
		}		
	}
	// END_SKILL_POWER_BY_LEVEL

	// LOG_KEEP_DAYS_EXTEND
	log_set_expiration_days(2);
	// END_OF_LOG_KEEP_DAYS_EXTEND

	while (fgets(buf, 256, fp))
	{
		parse_token(buf, token_string, value_string);

		TOKEN("empire_whisper")
		{
			bool b_value = 0;
			str_to_number(b_value, value_string);
			g_bEmpireWhisper = !!b_value;
			continue;
		}

		TOKEN("mark_server")
		{
			guild_mark_server = is_string_true(value_string);
			continue;
		}

		TOKEN("mark_min_level")
		{
			str_to_number(guild_mark_min_level, value_string);
			guild_mark_min_level = MINMAX(0, guild_mark_min_level, gguild_max_level);
			continue;
		}

		TOKEN("port")
		{
			str_to_number(mother_port, value_string);
			continue;
		}

		TOKEN("log_keep_days")
		{
			int i = 0;
			str_to_number(i, value_string);
			log_set_expiration_days(MINMAX(1, i, 90));
			continue;
		}

		TOKEN("passes_per_sec")
		{
			str_to_number(passes_per_sec, value_string);
			continue;
		}

		TOKEN("p2p_port")
		{
			str_to_number(p2p_port, value_string);
			continue;
		}

		TOKEN("db_port")
		{
			str_to_number(db_port, value_string);
			continue;
		}

		TOKEN("db_addr")
		{
			strlcpy(db_addr, value_string, sizeof(db_addr));

			for (int n =0; n < ADDRESS_MAX_LEN; ++n)
			{
				if (db_addr[n] == ' ')
					db_addr[n] = '\0';
			}

			continue;
		}

		TOKEN("save_event_second_cycle")
		{
			int	cycle = 0;
			str_to_number(cycle, value_string);
			save_event_second_cycle = cycle * passes_per_sec;
			continue;
		}

		TOKEN("ping_event_second_cycle")
		{
			int	cycle = 0;
			str_to_number(cycle, value_string);
			ping_event_second_cycle = cycle * passes_per_sec;
			continue;
		}

		TOKEN("table_postfix")
		{
			g_table_postfix = value_string;
			continue;
		}

		TOKEN("test_server")
		{
			printf("-----------------------------------------------\n");
			printf("TEST_SERVER\n");
			printf("-----------------------------------------------\n");
			str_to_number(test_server, value_string);
			continue;
		}

		TOKEN("speed_server")
		{
			printf("-----------------------------------------------\n");
			printf("SPEED_SERVER\n");
			printf("-----------------------------------------------\n");
			str_to_number(speed_server, value_string);
			continue;
		}
#ifdef __AUCTION__
		TOKEN("auction_server")
		{
			printf("-----------------------------------------------\n");
			printf("AUCTION_SERVER\n");
			printf("-----------------------------------------------\n");
			str_to_number(auction_server, value_string);
			continue;
		}
#endif
		TOKEN("distribution_test_server")
		{
			str_to_number(distribution_test_server, value_string);
			continue;
		}

		TOKEN("china_event_server")
		{
			str_to_number(china_event_server, value_string);
			continue;
		}

		TOKEN("shutdowned")
		{
			g_bNoMoreClient = true;
			continue;
		}

		TOKEN("no_regen")
		{
			g_bNoRegen = true;
			continue;
		}

		TOKEN("traffic_profile")
		{
			g_bTrafficProfileOn = true;
			continue;
		}


		TOKEN("map_allow")
		{
			char * p = value_string;
			string stNum;
			int max_allw_count = 0;

			for (; *p; p++)
			{   
				if (isnhspace(*p))
				{
					if (stNum.length())
					{
						int	index = 0;
						str_to_number(index, stNum.c_str());
						map_allow_add(index);
						stNum.clear();
						max_allw_count++;
					}
				}
				else
					stNum += *p;
			}

			if (stNum.length())
			{
				int	index = 0;
				str_to_number(index, stNum.c_str());
				map_allow_add(index);
				max_allw_count++;
			}

			
			fprintf(stderr, "Map allow size: %d/32\n", max_allw_count);
			if(max_allw_count > 32)
				fprintf(stderr, "Warning! More than 32 MAP_ALLOW entries detected! Instability may occur!\n");

			continue;
		}

		TOKEN("no_wander")
		{
			no_wander = true;
			continue;
		}

		TOKEN("user_limit")
		{
			str_to_number(g_iUserLimit, value_string);
			continue;
		}

		TOKEN("skill_disable")
		{
			str_to_number(g_bSkillDisable, value_string);
			continue;
		}

		TOKEN("auth_server")
		{
			char szIP[32];
			char szPort[32];

			two_arguments(value_string, szIP, sizeof(szIP), szPort, sizeof(szPort));

			if (!*szIP || (!*szPort && strcasecmp(szIP, "master")))
			{
				fprintf(stderr, "AUTH_SERVER: syntax error: <ip|master> <port>\n");
				exit(1);
			}

			g_bAuthServer = true;

			LoadBanIP("BANIP");

			if (!strcasecmp(szIP, "master"))
				fprintf(stdout, "AUTH_SERVER: I am the master\n");
			else
			{
				g_stAuthMasterIP = szIP;
				str_to_number(g_wAuthMasterPort, szPort);

				fprintf(stdout, "AUTH_SERVER: master %s %u\n", g_stAuthMasterIP.c_str(), g_wAuthMasterPort);
			}
			continue;
		}

		TOKEN("billing")
		{
			g_bBilling = true;
		}

		TOKEN("quest_dir")
		{
			sys_log(0, "QUEST_DIR SETTING : %s", value_string);
			g_stQuestDir = value_string;
		}

		TOKEN("quest_object_dir")
		{
			//g_stQuestObjectDir = value_string;
			std::istringstream is(value_string);
			sys_log(0, "QUEST_OBJECT_DIR SETTING : %s", value_string);
			string dir;
			while (!is.eof())
			{
				is >> dir;
				if (is.fail())
					break;
				g_setQuestObjectDir.insert(dir);
				sys_log(0, "QUEST_OBJECT_DIR INSERT : %s", dir .c_str());
			}
		}

		TOKEN("teen_addr")
		{
			strlcpy(teen_addr, value_string, sizeof(teen_addr));

			for (int n =0; n < ADDRESS_MAX_LEN; ++n)
			{
				if (teen_addr[n] == ' ')
					teen_addr[n] = '\0';
			}

			continue;
		}

		TOKEN("teen_port")
		{
			str_to_number(teen_port, value_string);
		}

		TOKEN("synchack_limit_count")
		{
			str_to_number(g_iSyncHackLimitCount, value_string);
		}

		TOKEN("speedhack_limit_count")
		{
			str_to_number(SPEEDHACK_LIMIT_COUNT, value_string);
		}

		TOKEN("speedhack_limit_bonus")
		{
			str_to_number(SPEEDHACK_LIMIT_BONUS, value_string);
		}

		TOKEN("server_id")
		{
			str_to_number(g_server_id, value_string);
		}

		TOKEN("mall_url")
		{
			g_strWebMallURL = value_string;
		}

		TOKEN("bind_ip")
		{
			strlcpy(g_szPublicIP, value_string, sizeof(g_szPublicIP));
		}

		TOKEN("view_range")
		{
			str_to_number(VIEW_RANGE, value_string);
		}

		TOKEN("spam_block_duration")
		{
			str_to_number(g_uiSpamBlockDuration, value_string);
		}

		TOKEN("spam_block_score")
		{
			str_to_number(g_uiSpamBlockScore, value_string);
			g_uiSpamBlockScore = MAX(1, g_uiSpamBlockScore);
		}

		TOKEN("spam_block_reload_cycle")
		{
			str_to_number(g_uiSpamReloadCycle, value_string);
			g_uiSpamReloadCycle = MAX(60, g_uiSpamReloadCycle); // 최소 1분
		}

		TOKEN("check_multihack")
		{
			str_to_number(g_bCheckMultiHack, value_string);
		}

		TOKEN("spam_block_max_level")
		{
			str_to_number(g_iSpamBlockMaxLevel, value_string);
		}
		TOKEN("protect_normal_player")
		{
			str_to_number(g_protectNormalPlayer, value_string);
		}
		TOKEN("notice_battle_zone")
		{
			str_to_number(g_noticeBattleZone, value_string);
		}

		TOKEN("pk_protect_level")
		{
		    str_to_number(PK_PROTECT_LEVEL, value_string);
		    fprintf(stderr, "PK_PROTECT_LEVEL: %d", PK_PROTECT_LEVEL);
		}

		TOKEN("max_level")
		{
			str_to_number(gPlayerMaxLevel, value_string);

			gPlayerMaxLevel = MINMAX(1, gPlayerMaxLevel, PLAYER_MAX_LEVEL_CONST);

			fprintf(stderr, "PLAYER_MAX_LEVEL: %d\n", gPlayerMaxLevel);
		}
		
		TOKEN("max_level_status")
		{
			str_to_number(gPlayerMaxLevelStats, value_string);

			gPlayerMaxLevelStats = MINMAX(1, gPlayerMaxLevelStats, gPlayerMaxLevel);

			fprintf(stderr, "PLAYER_MAX_LEVEL_STATS: %d\n", gPlayerMaxLevelStats);
		}
		
		TOKEN("max_status")
		{
			str_to_number(gPlayerMaxStatus, value_string);
			
			gPlayerMaxStatus = MINMAX(1, gPlayerMaxStatus, 32767);

			if(gPlayerMaxHT==32767)
				gPlayerMaxHT = gPlayerMaxStatus;

			if(gPlayerMaxIQ==32767)
				gPlayerMaxIQ = gPlayerMaxStatus;

			if(gPlayerMaxST==32767)
				gPlayerMaxST = gPlayerMaxStatus;

			if(gPlayerMaxDX==32767)
				gPlayerMaxDX = gPlayerMaxStatus;

			fprintf(stderr, "PLAYER_MAX_STATUS: %d\n", gPlayerMaxStatus);
		}
		
		TOKEN("max_ht")
		{
			str_to_number(gPlayerMaxHT, value_string);

			gPlayerMaxHT = MINMAX(1, gPlayerMaxHT, 32767);

			fprintf(stderr, "PLAYER_MAX_HT: %d\n", gPlayerMaxHT);
		}
		
		TOKEN("max_iq")
		{
			str_to_number(gPlayerMaxIQ, value_string);

			gPlayerMaxIQ = MINMAX(1, gPlayerMaxIQ, 32767);

			fprintf(stderr, "PLAYER_MAX_IQ: %d\n", gPlayerMaxIQ);
		}
		
		TOKEN("max_st")
		{
			str_to_number(gPlayerMaxST, value_string);

			gPlayerMaxST = MINMAX(1, gPlayerMaxST, 32767);

			fprintf(stderr, "PLAYER_MAX_ST: %d\n", gPlayerMaxST);
		}
		
		TOKEN("max_dx")
		{
			str_to_number(gPlayerMaxDX, value_string);

			gPlayerMaxDX = MINMAX(1, gPlayerMaxDX, 32767);

			fprintf(stderr, "PLAYER_MAX_DX: %d\n", gPlayerMaxDX);
		}
		
		TOKEN("server_check")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "SERVER_CHECK: %d\n", flag);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				g_bCheckClientVersion = true;
			}
		}
		
		TOKEN("server_version")
		{
			gServerVersion = value_string;

			fprintf(stderr, "SERVER_VERSION: %s\n", gServerVersion.c_str());

			if(g_bCheckClientVersion == false)
				fprintf(stderr, "SERVER_VERSION: SERVER_CHECK IS DISABLED!!!");
		}

		TOKEN("attr_always_add")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "ATTR_ALWAYS_ADD: %d\n", flag);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				attr_always_add = true;
			}

		}

		TOKEN("attr_always_5_add")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "ATTR_ALWAYS_5_ADD: %d\n", flag);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				attr_always_5_add = true;
			}

		}

		TOKEN("attr_change_limit")
		{
			str_to_number(attr_change_limit, value_string);

			attr_change_limit = MINMAX(0, attr_change_limit, 32767);

			fprintf(stderr, "ATTR_CHANGE_LIMIT: %d\n", attr_change_limit);

		}

		TOKEN("guild_max_level")
		{
			str_to_number(gguild_max_level, value_string);

			gguild_max_level = MINMAX(1, gguild_max_level, 50);

			fprintf(stderr, "GUILD_MAX_LEVEL: %d\n", gguild_max_level);

		}

		TOKEN("item_floor_time")
		{
			str_to_number(item_floor_time, value_string);

			item_floor_time = MINMAX(0, item_floor_time, 32767);

			fprintf(stderr, "ITEM_FLOOR_TIME: %d\n", item_floor_time);

		}

		TOKEN("item_ownership_time")
		{
			str_to_number(item_ownership_time, value_string);

			item_ownership_time = MINMAX(0, item_ownership_time, 32767);

			fprintf(stderr, "ITEM_OWNERSHIP_TIME: %d\n", item_ownership_time);

		}

		TOKEN("item_drop_time")
		{
			str_to_number(item_drop_time, value_string);

			item_drop_time = MINMAX(0, item_drop_time, 32767);

			fprintf(stderr, "ITEM_DROP_TIME: %d\n", item_drop_time);

		}

		TOKEN("gold_drop_time")
		{
			str_to_number(gold_drop_time, value_string);

			gold_drop_time = MINMAX(0, gold_drop_time, 32767);

			fprintf(stderr, "GOLD_DROP_TIME: %d\n", gold_drop_time);

		}

		TOKEN("min_addon_fks")
		{
			str_to_number(minAddonFKS, value_string);

			minAddonFKS = MINMAX(-32767, minAddonFKS, 32767);

			fprintf(stderr, "MIN_ADDON_FKS: %d\n", minAddonFKS);

		}

		TOKEN("max_addon_fks")
		{
			str_to_number(maxAddonFKS, value_string);

			maxAddonFKS = MINMAX(-32767, maxAddonFKS, 32767);

			fprintf(stderr, "MAX_ADDON_FKS: %d\n", maxAddonFKS);

		}

		TOKEN("min_addon_dss")
		{
			str_to_number(minAddonDSS, value_string);

			minAddonDSS = MINMAX(-32767, minAddonDSS, 32766);

			fprintf(stderr, "MIN_ADDON_DSS: %d\n", maxAddonDSS);

		}

		TOKEN("max_addon_dss")
		{
			str_to_number(maxAddonDSS, value_string);

			maxAddonDSS = MINMAX(-32767, maxAddonDSS, 32766);

			fprintf(stderr, "MAX_ADDON_DSS: %d\n", maxAddonDSS);

		}

		TOKEN("skillbook_delay")
		{
			str_to_number(sb_delay, value_string);

			sb_delay = MINMAX(0, sb_delay, 2147483646);

			fprintf(stderr, "SKILLBOOK_DELAY: %d\n", sb_delay);

		}

		TOKEN("skillbook_need_exp")
		{
			str_to_number(sb_need_exp, value_string);

			sb_need_exp = MINMAX(0, sb_need_exp, 2147483646);

			fprintf(stderr, "SKILLBOOK_NEED_EXP: %d\n", sb_need_exp);

		}
		
		TOKEN("skillbook_always_book")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "SKILLBOOK_ALWAYS_BOOK: %d\n", flag);

			if (1 == flag)
			{
				sb_always_book = true;
			}

		}
		
		TOKEN("gold_drop_time_interval")
		{
			str_to_number(g_GoldDropTimeLimitValue, value_string);

			g_GoldDropTimeLimitValue = MINMAX(0, g_GoldDropTimeLimitValue, 32767);

			fprintf(stderr, "GOLD_DROP_TIME_INTERVAL: %d\n", g_GoldDropTimeLimitValue);

		}

		TOKEN("item_drop_time_interval")
		{
			str_to_number(g_ItemDropTimeLimitValue, value_string);
			
			g_ItemDropTimeLimitValue = MINMAX(0, g_ItemDropTimeLimitValue, 32767);

			fprintf(stderr, "ITEM_DROP_TIME_INTERVAL: %d\n", g_ItemDropTimeLimitValue);

		}

		TOKEN("syserr_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "SYSERR_ENABLE: %d\n", flag);

			if (0 == flag)
			{
				syserr_enable = false;
			}

		}

		TOKEN("syslog_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "SYSLOG_ENABLE: %d\n", flag);

			if (1 == flag)
			{
				syslog_enable = true;
			}

		}

		TOKEN("sequence_check")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "SEQUENCE_CHECK: %d\n", flag);

			if (1 == flag)
			{
				sequence_check = true;
			}

		}

		TOKEN("max_skills")
		{
			str_to_number(max_skills, value_string);

			max_skills = MINMAX(0, max_skills, 8);

			fprintf(stderr, "MAX_SKILLS: %d\n", max_skills);

		}

		TOKEN("start_gold")
		{
			str_to_number(start_gold, value_string);

			start_gold = MINMAX(0, start_gold, sizeof(long int));

			fprintf(stderr, "START_GOLD: %ld\n", start_gold);

		}

		TOKEN("glass_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "GLASS_ENABLE: %d\n", flag);

			if (1 == flag)
			{
				glass_enable = true;
			}

		}

		TOKEN("versioncheck_kick_delay")
		{
			str_to_number(versioncheck_kick_delay, value_string);

			versioncheck_kick_delay = MINMAX(0, versioncheck_kick_delay, sizeof(int));

			fprintf(stderr, "VERSIONCHECK_KICK_DELAY: %d\n", versioncheck_kick_delay);
		}

		

		TOKEN("glass_needed")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "GLASS_NEEDED: %d\n", flag);

			if (0 == flag)
			{
				glass_needed = false;
			}

		}

		TOKEN("trade_effect")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "TRADE_EFFECT: %d\n", flag);

			if (0 == flag)
			{
				trade_effect = false;
			}
		}

		TOKEN("trade_effect_shop_threshold")
		{
			str_to_number(trade_effect_shop_threshold, value_string);

			trade_effect_shop_threshold = MINMAX(0, trade_effect_shop_threshold, 1000000000);

			fprintf(stderr, "TRADE_EFFECT_SHOP_THRESHOLD: %d\n", trade_effect_shop_threshold);
		}

		TOKEN("trade_effect_exchange_threshold")
		{
			str_to_number(trade_effect_exchange_threshold, value_string);

			trade_effect_exchange_threshold = MINMAX(0, trade_effect_exchange_threshold, 1000000000);

			fprintf(stderr, "TRADE_EFFECT_EXCHANGE_THRESHOLD: %d\n", trade_effect_exchange_threshold);
		}

		TOKEN("view_equip_for_all")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "VIEW_EQUIP_FOR_ALL: %d\n", flag);

			if (1 == flag)
			{
				view_equip_for_all = true;
			}

		}

		TOKEN("view_equip_sp_cost")
		{
			str_to_number(view_equip_sp_cost, value_string);

			view_equip_sp_cost = MINMAX(0, view_equip_sp_cost, 100);

			fprintf(stderr, "VIEW_EQUIP_SP_COST: %d\n", view_equip_sp_cost);

		}

		TOKEN("advanced_spam_check")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "ADVANCED_SPAM_CHECK: %d\n", flag);

			if (1 == flag)
			{
				advanced_spam_check = true;
			}

		}

		TOKEN("ban_force_reason")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "BAN_FORCE_REASON: %d\n", flag);

			if (0 == flag)
			{
				ban_force_reason = false;
			}

		}

		TOKEN("skillbook_step_leveling")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "SKILLBOOG_STEP_LEVELING: %d\n", flag);

			if (0 == flag)
			{
				skillbook_step_leveling = false;
			}

		}
		
		TOKEN("raise_empire_prices")
		{
			int flag = 0;

			str_to_number(flag, value_string);
			
			fprintf(stderr, "RAISE_EMPIRE_PRICES: %d\n", flag);

			if (0 == flag)
			{
				raise_empire_prices = false;
			}

		}

		TOKEN("horse_max_level")
		{
			str_to_number(max_horse_level, value_string);

			max_horse_level = MINMAX(0, max_horse_level, 255);

			fprintf(stderr, "HORSE_MAX_LEVEL: %d\n", max_horse_level);

		}

		TOKEN("marriage_max_percent")
		{
			str_to_number(marriage_max_percent, value_string);

			marriage_max_percent = MINMAX(0, marriage_max_percent, 255);

			fprintf(stderr, "MARRIAGE_MAX_PERCENT: %d\n", marriage_max_percent);

		}

		TOKEN("pc_max_movement_speed")
		{
			str_to_number(pc_max_movement_speed, value_string);

			pc_max_movement_speed = MINMAX(0, pc_max_movement_speed, 2147483646);

			fprintf(stderr, "PC_MAX_MOVEMENT_SPEED: %d\n", pc_max_movement_speed);

		}
		
		TOKEN("pc_max_attack_speed")
		{
			str_to_number(pc_max_attack_speed, value_string);

			pc_max_attack_speed = MINMAX(0, pc_max_attack_speed, 2147483646);

			fprintf(stderr, "PC_MAX_ATTACK_SPEED: %d\n", pc_max_attack_speed);

		}
		
		TOKEN("mob_max_movement_speed")
		{
			str_to_number(mob_max_movement_speed, value_string);

			mob_max_movement_speed = MINMAX(0, mob_max_movement_speed, 2147483646);

			fprintf(stderr, "MOB_MAX_MOVEMENT_SPEED: %d\n", mob_max_movement_speed);

		}
		
		TOKEN("mob_max_attack_speed")
		{
			str_to_number(mob_max_attack_speed, value_string);

			mob_max_attack_speed = MINMAX(0, mob_max_attack_speed, 2147483646);

			fprintf(stderr, "MOB_MAX_ATTACK_SPEED: %d\n", mob_max_attack_speed);

		}
		
		TOKEN("taxes")
		{
			str_to_number(taxes, value_string);

			taxes = MINMAX(0, taxes, 100);

			fprintf(stderr, "TAXES: %d\n", taxes);

		}
		
		TOKEN("check_speedhack_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			if (0 == flag)
			{
				check_speedhack_enable = false;
				fprintf(stderr, "CHECK_SPEEDHACK_ENABLE: %i\n", flag);
			}
		}
		
		TOKEN("emotion_without_mask")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			if (1 == flag)
			{
				emotion_without_mask = true;
				fprintf(stderr, "EMOTION_WITHOUT_MASK: %i\n", flag);
			}
		}
		
		TOKEN("emotion_same_gender")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			if (1 == flag)
			{
				emotion_same_gender = true;
				fprintf(stderr, "EMOTION_SAME_GENDER: %i\n", flag);
			}

		}
		
		TOKEN("dye_level")
		{
			str_to_number(dye_level, value_string);

			dye_level = MINMAX(0, dye_level, 250);

			fprintf(stderr, "DYE_LEVEL: %d\n", dye_level);

		}

		TOKEN("exp_need_threshold")
		{
			exp_need_threshold = atoll(value_string);

			exp_need_threshold = LLMINMAX(0, exp_need_threshold, (long long)999999999999LL);

			fprintf(stderr, "EXP_NEED_THRESHOLD: %lld\n", yang_max);

		}

		TOKEN("yang_max")
		{
			yang_max = atoll(value_string);

			yang_max = LLMINMAX(0, yang_max, (long long)999999999999LL);

			fprintf(stderr, "YANG_MAX: %lld\n", yang_max);

		}

		TOKEN("package_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				package_enable = true;
				fprintf(stderr, "PACKAGE_ENABLE: %i\n", flag);
			}
		}

		TOKEN("new_test_server")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (0 == flag)
			{
				new_test_server = false;
				fprintf(stderr, "NEW_TEST_SERVER: %i\n", flag);
			}
		}
		
		TOKEN("new_gm_host_check")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				new_gm_host_check = true;
				fprintf(stderr, "NEW_GM_HOST_CHECK: %i\n", flag);
			}
		}
		
		TOKEN("log_level")
		{
			str_to_number(log_level, value_string);

			log_level = MINMAX(0, log_level, 3);

			fprintf(stderr, "LOG_LEVEL: %d\n", log_level);
		}

		TOKEN("belt_allow_all_items")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				belt_allow_all_items = true;
				fprintf(stderr, "BELT_ALLOW_ALL_ITEMS: %i\n", flag);
			}
		}

		TOKEN("skill_master_upgrade")
		{
			str_to_number(skill_master_upgrade, value_string);

			skill_master_upgrade = MINMAX(1, skill_master_upgrade, 20);
			
			fprintf(stderr, "SKILL_MASTER_UPGRADE: %d\n", skill_master_upgrade);
		}

		TOKEN("skill_force_master")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				skill_force_master = true;
				fprintf(stderr, "SKILL_FORCE_MASTER: %i\n", flag);
			}
		}

		TOKEN("belt_force_slots")
		{
			str_to_number(belt_force_slots, value_string);

			belt_force_slots = MINMAX(0, belt_force_slots, 16);
			
			fprintf(stderr, "BELT_FORCE_SLOTS: %d\n", belt_force_slots);
		}

		TOKEN("max_rank_points")
		{
			str_to_number(max_rank_points, value_string);

			max_rank_points = MINMAX(0, max_rank_points, 1000000L);

			fprintf(stderr, "MAX_RANK_POINTS: %ld\n", max_rank_points);
		}

		TOKEN("movement_speed")
		{
			str_to_number(movement_speed, value_string);

			movement_speed = MINMAX(1, movement_speed, 250);

			fprintf(stderr, "MOVEMENT_SPEED: %d\n", movement_speed);
		}

		TOKEN("attr_rare_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (0 == flag)
			{
				attr_rare_enable = false;
				fprintf(stderr, "ATTR_RARE_ENABLE: %i\n", flag);
			}
		}

		TOKEN("global_chat")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				global_chat = true;
				fprintf(stderr, "GLOBAL_CHAT: %i\n", flag);
			}
		}

		TOKEN("empire_chat")
		{
			fprintf(stderr, "GLOBAL_CHAT is marked as DEPRECATED and will be removed in 2.5!\n Using global_chat instead.\n");
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				global_chat = true;
				fprintf(stderr, "GLOBAL_CHAT: %i\n", flag);
			}
		}
		
		TOKEN("bugfix_sura_manashield")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				bugfix_sura_manashield = true;
				fprintf(stderr, "BUGFIX_SURA_MANASHIELD: %i\n", flag);
			}
		}
		
		TOKEN("rank_points_from_monsters")
		{
			str_to_number(rank_points_from_monsters, value_string);

			rank_points_from_monsters = MINMAX(0, rank_points_from_monsters, 250);

			fprintf(stderr, "RANK_POINTS_FROM_MONSTERS: %hu\n", rank_points_from_monsters);
		}
		
		TOKEN("rank_points_from_monsters_critical")
		{
			str_to_number(rank_points_from_monsters_c, value_string);

			rank_points_from_monsters_c = MINMAX(0, rank_points_from_monsters_c, 250);

			fprintf(stderr, "RANK_POINTS_FROM_MONSTERS_CRITICAL: %hu\n", rank_points_from_monsters_c);
		}

		TOKEN("rank_points_penalty")
		{
			str_to_number(rank_points_penalty, value_string);

			rank_points_penalty = MINMAX(-32767, rank_points_penalty, 32767);

			fprintf(stderr, "RANK_POINTS_FROM_MONSTERS_CRITICAL: %d\n", rank_points_penalty);
		}

		TOKEN("rank_points_floor_initial")
		{
			str_to_number(rank_points_floor_initial, value_string);

			rank_points_floor_initial = MINMAX(0, rank_points_floor_initial, 250);

			fprintf(stderr, "RANK_POINTS_FLOOR_INITIAL: %hu\n", rank_points_floor_initial);
		}

		TOKEN("rank_points_floor_initial_c")
		{
			str_to_number(rank_points_floor_initial_c, value_string);

			rank_points_floor_initial_c = MINMAX(0, rank_points_floor_initial_c, 250);

			fprintf(stderr, "RANK_POINTS_FLOOR_INITIAL_CRITICAL: %hu\n", rank_points_floor_initial_c);
		}

		TOKEN("rank_points_group_penalty")
		{
			str_to_number(rank_points_group_penalty, value_string);

			rank_points_group_penalty = MINMAX(-32767, rank_points_group_penalty, 32767);

			fprintf(stderr, "RANK_POINTS_GROUP_PENALTY: %d\n", rank_points_group_penalty);
		}

		TOKEN("race_5_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				race_5_enable = true;
				fprintf(stderr, "RACE_5_ENABLE: %i\n", flag);
			}
		}

		TOKEN("elevation_enable")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				elevation_enable=true;
				fprintf(stderr, "elevation_enable: %i\n", flag);
			}
		}

		TOKEN("elevation_key")
		{
			ElevationKey = value_string;
			fprintf(stderr, "ELEVATION_KEY: %s", ElevationKey.c_str());
		}
		
		TOKEN("elevation_use_key")
		{
			int flag = 0;

			str_to_number(flag, value_string);

			//if (1 == flag && LC_IsEurope() )
			if (1 == flag)
			{
				elevation_use_key=true;
				fprintf(stderr, "elevation_use_key: %i\n", flag);
			}
		}

		TOKEN("interrupt_interval")
		{
			str_to_number(interrupt_interval, value_string);

			interrupt_interval = MINMAX(0, interrupt_interval, 32767);

			fprintf(stderr, "INTERRUPT_INTERVAL: %d\n", interrupt_interval);
		}

		TOKEN("pepper_key")
		{
			strlcpy(s_pepper, value_string, sizeof(s_pepper));
			fprintf(stderr, "PEPPER_KEY: %s", s_pepper);
		}

		TOKEN("MYSQL_PASSWORD_FUNCTION")
		{
			mysql_pass_func = value_string;
			fprintf(stderr, "MYSQL_PASSWORD_FUNCTION: %s", mysql_pass_func.c_str());
		}

		TOKEN("block_char_creation")
		{
			int tmp = 0;

			str_to_number(tmp, value_string);

			if (0 == tmp)
				g_BlockCharCreation = false;
			else
				g_BlockCharCreation = true;

			continue;
		}

		TOKEN("unify_enable")
		{
			int tmp = 0;

			str_to_number(tmp, value_string);

			if (1 == tmp)
				unify_enable = true;
			else
				unify_enable = false;

			continue;
		}
	}

	if (g_setQuestObjectDir.empty())
		g_setQuestObjectDir.insert(g_stDefaultQuestObjectDir);

	if (0 == db_port)
	{
		fprintf(stderr, "DB_PORT not configured\n");
		exit(1);
	}

	if (0 == g_bChannel)
	{
		fprintf(stderr, "CHANNEL not configured\n");
		exit(1);
	}

	if (g_stHostname.empty())
	{
		fprintf(stderr, "HOSTNAME must be configured.\n");
		exit(1);
	}

	// LOCALE_SERVICE 
	LocaleService_LoadLocaleStringFile();
	LocaleService_TransferDefaultSetting();
	LocaleService_LoadEmpireTextConvertTables();
	// END_OF_LOCALE_SERVICE

	fclose(fp);

	if ((fp = fopen("CMD", "r")))
	{
		while (fgets(buf, 256, fp))
		{
			char cmd[32], levelname[32];
			int level;

			two_arguments(buf, cmd, sizeof(cmd), levelname, sizeof(levelname));

			if (!*cmd || !*levelname)
			{
				sys_err("CMD syntax error: <cmd> <DISABLE | PLAYER | LOW_WIZARD | WIZARD | HIGH_WIZARD | GOD>\ncowardly refusing to proceed.\n");
				fprintf(stderr, "CMD syntax error: <cmd> <DISABLE | PLAYER | LOW_WIZARD | WIZARD | HIGH_WIZARD | GOD>\ncowardly refusing to proceed.\n");
				break;
//				exit(1);
			}

			if (!strcasecmp(levelname, "LOW_WIZARD"))
				level = GM_LOW_WIZARD;
			else if (!strcasecmp(levelname, "WIZARD"))
				level = GM_WIZARD;
			else if (!strcasecmp(levelname, "HIGH_WIZARD"))
				level = GM_HIGH_WIZARD;
			else if (!strcasecmp(levelname, "GOD"))
				level = GM_GOD;
			else if (!strcasecmp(levelname, "IMPLEMENTOR"))
				level = GM_IMPLEMENTOR;
			else if (!strcasecmp(levelname, "PLAYER"))
				level = GM_PLAYER;
			else if (!strcasecmp(levelname, "DISABLE"))
				level = GM_IMPLEMENTOR + 1;
			else
			{
				sys_err("CMD syntax error: <cmd> <DISABLE | PLAYER | LOW_WIZARD | WIZARD | HIGH_WIZARD | GOD>\ncowardly refusing to proceed.\n");
				fprintf(stderr, "CMD syntax error: <cmd> <DISABLE | PLAYER | LOW_WIZARD | WIZARD | HIGH_WIZARD | GOD>\ncowardly refusing to proceed.\n");
				break;
//				exit(1);
			}

			interpreter_set_privilege(cmd, level);
		}

		fclose(fp);
	}
	char* tmp = new char[64];
	sprintf(tmp, "locale/%s/horse_table.txt", temp_locale.c_str());
	if ((fp = fopen(tmp, "r")))
	{
		fprintf(stderr, "~~~> horse_table section begins <~~~\n");
		while (fgets(buf, 256, fp))
		{
			if(strlen(buf)>0)
			{
				if(*buf == '#')
					continue;
				sys_log(0, "Horse_table override: %s\n", buf);
				if(SetHorseTable(buf)==false)
					break;
			}
		}
		fclose(fp);
		fprintf(stderr, "~~~> horse_table section ends <~~~\n");
	}
	else
	{
		sys_log(0, "horse_table does not exist: %s", tmp);
	}
	delete[] tmp;
	
	char* tmp2 = new char[64];
	sprintf(tmp2, "locale/%s/exp_table.txt", temp_locale.c_str());
	if ((fp = fopen(tmp2, "r")))
	{
		fprintf(stderr, "~~~> exp_table section begins <~~~\n");
		int x = 0;
		while (fgets(buf, 256, fp))
		{
			if(strlen(buf)>0)
			{
				if(*buf == '#')
					continue;
				char lv[32], exp_blank[32];
				two_arguments(buf, lv, sizeof(lv), exp_blank, sizeof(exp_blank));
				long int level = atol(lv);
				long long int exp = atoll(exp_blank);
				if(level > PLAYER_EXP_TABLE_MAX)
					sys_err("Error with reading exp_table.txt! level is bigger than exp table!!!");
				else
				{
					exp_table_unify[level - 1] = exp;
					fprintf(stderr, "exp_table override: level %ld exp -> %lld\n", level, exp);
				}
				x++;
			}
		}
		fclose(fp);
		fprintf(stderr, "~~~> exp_table section ends <~~~\n");
	}
	else
	{
		sys_log(0, "exp_table does not exist: %s", tmp2);
	}
	delete[] tmp2;
	
	char* tmp3 = new char[64];
	sprintf(tmp3, "locale/%s/coordinates.txt", temp_locale.c_str());
	if ((fp = fopen(tmp3, "r")))
	{
		fprintf(stderr, "~~~> coordinate section begins <~~~\n");
		int x = 0;
		while (fgets(buf, 256, fp))
		{
			if(strlen(buf)>0)
			{
				if(*buf == '#')
					continue;
				if(x < 3)
				{
					long int map_idx = 0;
					map_idx = atoi(buf);
					if(map_idx > 0)
					{
						g_start_map[x+1] = map_idx;
						fprintf(stderr, "starting map_id %ld -> %ld\n", g_start_map[x+1], map_idx);
					}
					x++;
					continue;
				}
				char mp_coordx[32], mp_coordy[32];
				two_arguments(buf, mp_coordx, sizeof(mp_coordx), mp_coordy, sizeof(mp_coordy));
				unsigned int mapx = atoi(mp_coordx);
				unsigned int mapy = atoi(mp_coordy);
				if(x < 6)
				{
					g_create_position[x-2][0] = mapx;
					g_create_position[x-2][1] = mapy;
					fprintf(stderr, "create_character_pos number %u %u -> %u %u\n", g_create_position[x-2][0], g_create_position[x-2][1], mapx, mapy);
					x++;
					continue;
				}
				g_create_position[x-5][0] = mapx;
				g_create_position[x-5][1] = mapy;
				fprintf(stderr, "start_pos number %u %u -> %u %u\n", g_create_position[x-5][0], g_create_position[x-5][1], mapx, mapy);
				x++;
				if(x == 6)
					break;
			}
		}
		fclose(fp);
		fprintf(stderr, "~~~> coordinate section ends <~~~\n");
	}
	else
	{
		sys_log(0, "coordinate corrections do not exist: %s", tmp3);
	}
	delete[] tmp3;

	LoadValidCRCList();
	LoadStateUserCount();

	CWarMapManager::instance().LoadWarMapInfo(NULL);

	FN_log_adminpage();
	if(!unify_enable)
	{
		puts("DEPRECATED: This core is not running in unified mode!\n");
	}
	fprintf(stderr, "[VANILLA-CMake]r71480\n");
	puts("Booting successful!\n");
	sys_log(0, "Vanilla boot succesful! yay!\n");
}

extern long long LLMINMAX(long long min, long long value, long long max)
{
    return ((value >= max) ? max : (value <= min) ? min : value);
}

const char* get_table_postfix()
{
	return g_table_postfix.c_str();
}

void LoadValidCRCList()
{
	s_set_dwProcessCRC.clear();
	s_set_dwFileCRC.clear();

	FILE * fp;
	char buf[256];

	if ((fp = fopen("CRC", "r")))
	{
		while (fgets(buf, 256, fp))
		{
			if (!*buf)
				continue;

			DWORD dwValidClientProcessCRC;
			DWORD dwValidClientFileCRC;

			sscanf(buf, " %u %u ", &dwValidClientProcessCRC, &dwValidClientFileCRC);

			s_set_dwProcessCRC.insert(dwValidClientProcessCRC);
			s_set_dwFileCRC.insert(dwValidClientFileCRC);

			fprintf(stderr, "CLIENT_CRC: %u %u\n", dwValidClientProcessCRC, dwValidClientFileCRC);
		}

		fclose(fp);
	}
}

bool LoadClientVersion()
{
	FILE * fp = fopen("VERSION", "r");

	if (!fp)
		return false;

	char buf[256];
	fgets(buf, 256, fp);

	char * p = strchr(buf, '\n');
	if (p) *p = '\0';

	fprintf(stderr, "VERSION: \"%s\"\n", buf);

	g_stClientVersion = atoi(buf);
	fclose(fp);
	return true;
}

void CheckClientVersion()
{
	const DESC_MANAGER::DESC_SET & set = DESC_MANAGER::instance().GetClientSet();
	DESC_MANAGER::DESC_SET::const_iterator it = set.begin();

	while (it != set.end())
	{
		LPDESC d = *(it++);

		if (!d->GetCharacter())
			continue;


		const char* version = (const char*)gServerVersion.c_str();
		const char* date = (const char*)d->GetClientVersion();

		//if (0 != g_stClientVersion.compare(d->GetClientVersion()) )
		if (strcmp(version,date) != 0)
		{
			d->GetCharacter()->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("클라이언트 버전이 틀려 로그아웃 됩니다. 정상적으로 패치 후 접속하세요."));
			d->DelayedDisconnect(versioncheck_kick_delay);
		}
	}
}

void LoadStateUserCount()
{
	FILE * fp = fopen("state_user_count", "r");

	if (!fp)
		return;

	if (!LC_IsHongKong())
		fscanf(fp, " %d %d ", &g_iFullUserCount, &g_iBusyUserCount);

	fclose(fp);
}

bool IsValidProcessCRC(DWORD dwCRC)
{
	return s_set_dwProcessCRC.find(dwCRC) != s_set_dwProcessCRC.end();
}

bool IsValidFileCRC(DWORD dwCRC)
{
	return s_set_dwFileCRC.find(dwCRC) != s_set_dwFileCRC.end();
}


