/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2016 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KBE_REDIS_HELPER_H
#define KBE_REDIS_HELPER_H

#include "common.h"
#include "common/common.h"
#include "common/memorystream.h"
#include "helper/debug_helper.h"
#include "db_interface_redis.h"

namespace KBEngine{ 

class RedisHelper
{
public:
	RedisHelper()
	{
	}

	virtual ~RedisHelper()
	{
	}

	static bool check_array_results(redisReply* pRedisReply)
	{
		for(size_t j = 0; j < pRedisReply->elements; ++j) 
		{
			if(pRedisReply->element[j]->type != REDIS_REPLY_INTEGER && 
				pRedisReply->element[j]->type != REDIS_REPLY_STRING)
			{
				return false;
			}
		}
		
		return true;
	}
	
	static bool hasTable(DBInterfaceRedis* pdbi, const std::string& name, bool showExecInfo = true)
	{
		uint64 index = 0;
		
		redisReply* pRedisReply = NULL;
		std::string sqlstr = fmt::format("scan {} MATCH {}", name);
		
		try
		{
			pdbi->query(sqlstr.c_str(), sqlstr.size(), &pRedisReply, showExecInfo);
		}
		catch(...)
		{
		}
		
		if(pRedisReply)
			freeReplyObject(pRedisReply); 
		
		return true;
	}
	
	static bool dropTable(DBInterfaceRedis* pdbi, const std::string& name, bool showExecInfo = true)
	{
		uint64 index = 0;
		
		redisReply* pRedisReply = NULL;
		std::string sqlstr = fmt::format("scan {} MATCH {}", name);
		
		try
		{
			pdbi->query(sqlstr.c_str(), sqlstr.size(), &pRedisReply, showExecInfo);
		}
		catch(...)
		{
		}
		
		if(pRedisReply)
			freeReplyObject(pRedisReply); 
		
		return true;
	}
};

}
#endif // KBE_REDIS_HELPER_H