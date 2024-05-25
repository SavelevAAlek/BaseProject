#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/orm/DbClient.hpp"
#include "../dto/AirplaneDto.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class MyClient : public oatpp::orm::DbClient {
public:
	MyClient(const std::shared_ptr<oatpp::orm::Executor>& executor)
		: oatpp::orm::DbClient(executor)
	{}

	QUERY(getAllUsers,
    "SELECT * FROM user"
)

    QUERY(getAllAirplanes,
        "SELECT * FROM airplane"
    )

    QUERY(getAirplanesByUserId,
        "SELECT * FROM airplane WHERE userid=:userid",
        PARAM(oatpp::Int16, userid)
    )

    QUERY(getOneAirplaneById,
        "SELECT * FROM airplane WHERE id=:id",
        PARAM(oatpp::Int16, id)
    )

    QUERY(addAirplane,
        "INSERT INTO airplane "
        "(model, type, manufacturer, country, engines_amount, userid, description) VALUES "
        "(:airplaneDto.model, :airplaneDto.type, :airplaneDto.manufacturer, :airplaneDto.country, :airplaneDto.engines_amount, :airplaneDto.userid, :airplaneDto.description);",
        PARAM(oatpp::Object<AirplaneDto>, airplaneDto)
    )

    QUERY(updateAirplane,
        "UPDATE airplane SET "
        "model = :airplaneDto.model, type = :airplaneDto.type, manufacturer = :airplaneDto.manufacturer, country = :airplaneDto.country, engines_amount = :airplaneDto.engines_amount, description = :airplaneDto.description, userid = :airplaneDto.userid "
        "WHERE id = :id;",
        PARAM(oatpp::Object<AirplaneDto>, airplaneDto),
        PARAM(oatpp::Int16, id)
    )

    QUERY(deleteAirplane,
        "DELETE FROM airplane "
        "WHERE id = :id;",
        PARAM(oatpp::Int16, id)
    )
};

#include OATPP_CODEGEN_END(DbClient)