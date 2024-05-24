#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/orm/DbClient.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class MyClient : public oatpp::orm::DbClient {
public:
	MyClient(const std::shared_ptr<oatpp::orm::Executor>& executor)
		: oatpp::orm::DbClient(executor)
	{}

	QUERY(getAllUsers,
		"SELECT * FROM users"
	)

	QUERY(getTodosByUserId,
		"SELECT * FROM todos WHERE userId=:userId",
		PARAM(oatpp::String, userId)
	)
};

#include OATPP_CODEGEN_END(DbClient)