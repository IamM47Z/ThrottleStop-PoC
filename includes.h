#pragma once

#include <iostream>
#include <Windows.h>

#include "exploit/exploit.h"

#pragma pack( push, 1 )
union DebugCtl
{
	struct
	{
		bool		lbr : 1;
		bool		btf : 1;
		uint32_t	reserved : 4;
		bool		tr : 1;
		bool		bts : 1;
		bool		btint : 1;
		bool		bts_off_os : 1;
		bool		bts_off_usr : 1;
		bool		freeze_lbrs_on_pmi : 1;
		bool		freeze_perfmon_on_pmi : 1;
		uint32_t	reserved2 : 1;
		bool		freeze_while_smm_en : 1;
		bool		rtm : 1;
		uint32_t	reserved3 : 16;
	};

	uint64_t value;
};
#pragma pack( pop )