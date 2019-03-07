#ifndef __INC_METIN_II_GAME_UNIQUE_H
#define __INC_METIN_II_GAME_UNIQUE_H
#include "sectree_manager.h"
#include "char.h"

class CUnique
{
	typedef std::map<std::string, LPCHARACTER> TUniqueMobMap;

	template <class Func> Func ForEachMember(Func f);

	public:
		~CUnique();
		CUnique(std::string id);
		void SpawnUnique(const char* key, DWORD vnum, const char* pos, LPCHARACTER pChar);
		void SetUnique(const char* key, DWORD vid);
		void	KillUnique(const std::string& key, LPCHARACTER pChar);
		void	RemoveUnique(const std::string& key);
		void	PurgeUnique(const std::string& key);
		bool	IsUniqueDead(const std::string& key);
		float	GetUniqueHpPerc(const std::string& key);
		bool	CheckUniqueExists(const std::string& key);
		DWORD	GetUniqueVid(const std::string& key);
		void	UniqueSetMaxHP(const std::string& key, int iMaxHP);
		void	UniqueMoveToPos(const std::string& key, int x, int y);
		void	UniqueSetHP(const std::string& key, int iHP);
		void	UniqueSetDefGrade(const std::string& key, int iGrade);
		void	Clear();
		void	Initialize();
		std::string GetID() { return m_id; }

		//Mass functions
		std::vector<DWORD> MassGetUniqueVID();

	private:
		std::string 		m_id; // <Factor>
		TUniqueMobMap	m_map_UniqueMob;
};

class CUniqueManager : public singleton<CUniqueManager>
{
	typedef std::map<std::string, LPUNIQUE> TUniqueMap;

	public:
		LPUNIQUE Find(std::string id = "__DEFAULT__");
		CUniqueManager();
		virtual ~CUniqueManager();
		LPUNIQUE Create(std::string id = "__DEFAULT__");
		void	Remove(std::string id);
		void	Clear();
		std::vector<LPUNIQUE> GetUniqueList();
	private:
		TUniqueMap	m_map_pkUnique;
};
#endif

