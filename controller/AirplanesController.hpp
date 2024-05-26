#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/Types.hpp"
#include "../dto/UserDto.hpp"
#include "../dto/AirplaneDto.hpp"
#include "../db/AirplanesDbDto.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)


class AirplanesController : public oatpp::web::server::api::ApiController {
private:
	OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

	OATPP_COMPONENT(std::shared_ptr<MyClient>, dbClient);

	List<Object<AirplaneDto>> airplanes = List<Object<AirplaneDto>>::createShared();

	// функция для проверки данных авторизации
    int checkAuth(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject> authObject, oatpp::Int16& userRole) {
        auto result = dbClient->getAllUsers();
        auto users = result->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

        for (auto i = 0; i < users->size(); i++) {
            if (users[i]->username == authObject->userId && users[i]->password == authObject->password) {
                userRole = users[i]->role;
                return users[i]->id;
            }
        }
        throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_403, "Forbidden", {});
    }
public:
	AirplanesController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		: oatpp::web::server::api::ApiController(objectMapper)
	{
		setDefaultAuthorizationHandler(std::make_shared<oatpp::web::server::handler::BasicAuthorizationHandler>("auth-handler"));
	}

    ENDPOINT_INFO(airplanesAll) {
        info->summary = "Get all airplanes";
        info->tags = std::list<oatpp::String>{ "Airplanes" };
        info->addSecurityRequirement("Authorization required");
    }
    ENDPOINT("GET", "airplanes/all", airplanesAll, 
        AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
        oatpp::Int16 userRole;
        int userId = checkAuth(authObject, userRole);
        if (userRole != 0 && userRole != 1) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_403, "Forbidden", {});
        }
        auto result = dbClient->getAllAirplanes();
        auto airplanes = result->fetch<oatpp::Vector<oatpp::Object<AirplaneDbDto>>>();
        return ResponseFactory::createResponse(Status::CODE_200, airplanes, objectMapper);
    }

    ENDPOINT_INFO(airplanesOne) {
        info->summary = "Get one airplane by id";
        info->tags = std::list<oatpp::String>{ "Airplanes" };
        info->addSecurityRequirement("Authorization required");
    }
    ENDPOINT("GET", "airplanes/{id}", airplanesOne, PATH(Int16, id), 
        AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
        oatpp::Int16 userRole;
        int userId = checkAuth(authObject, userRole);
        if (userRole != 0 && userRole != 1) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_403, "Forbidden", {});
        }
        auto result = dbClient->getOneAirplaneById(id);
        auto airplanes = result->fetch<oatpp::Vector<oatpp::Object<AirplaneDbDto>>>();
        if (airplanes->size() == 0) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_404, "Airplane not found", {});
        }
        auto airplane = airplanes[0];
        return ResponseFactory::createResponse(Status::CODE_200, airplane, objectMapper);
    }


    ENDPOINT_INFO(airplanesAdd) {
        info->summary = "Add an airplane to database";
        info->tags = std::list<oatpp::String>{ "Airplanes" };
        info->addSecurityRequirement("Authorization required");
    }
    ENDPOINT("POST", "/airplanes", airplanesAdd, BODY_DTO(Object<AirplaneDto>, airplaneDto), 
        AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
        oatpp::Int16 userRole;
        int userId = checkAuth(authObject, userRole);
        if (userRole != 1) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_403, "Forbidden", {});
        }
        airplaneDto->userid = userId;
        dbClient->addAirplane(airplaneDto);
        return ResponseFactory::createResponse(Status::CODE_201, airplaneDto, objectMapper);
    }

    ENDPOINT_INFO(airplanesUpdate) {
        info->summary = "Update airplane fields by id";
        info->tags = std::list<oatpp::String>{ "Airplanes" };
        info->pathParams["id"].description = "Description of ID";
        info->addSecurityRequirement("Authorization required");
    }
    ENDPOINT("PUT", "/airplanes/{id}", airplanesUpdate, BODY_DTO(Object<AirplaneDto>, airplaneDto), PATH(Int16, id), 
        AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
        oatpp::Int16 userRole;
        int userId = checkAuth(authObject, userRole);
        if (userRole != 1) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_403, "Forbidden", {});
        }
        auto result = dbClient->getOneAirplaneById(id);
        auto airplanes = result->fetch<oatpp::Vector<oatpp::Object<AirplaneDbDto>>>();
        if (airplanes->size() == 0) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_404, "Airplane not found", {});
        }
        auto airplane = airplanes[0];
        airplaneDto->userid = userId;
        dbClient->updateAirplane(airplaneDto, id);
        return ResponseFactory::createResponse(Status::CODE_200, airplaneDto, objectMapper);
    }

    ENDPOINT_INFO(airplanesDelete) {
        info->summary = "Delete airplane by id";
        info->tags = std::list<oatpp::String>{ "Airplanes" };
        info->addSecurityRequirement("Authorization required");
    }
    ENDPOINT("DELETE", "/airplanes/{id}", airplanesDelete, PATH(Int16, id), 
        AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
        oatpp::Int16 userRole;
        int userId = checkAuth(authObject, userRole);
        if (userRole != 1) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_403, "Forbidden", {});
        }
        auto result = dbClient->getOneAirplaneById(id);
        auto airplanes = result->fetch<oatpp::Vector<oatpp::Object<AirplaneDbDto>>>();
        if (airplanes->size() == 0) {
            throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_404, "Airplane not found", {});
        }
        dbClient->deleteAirplane(id);
        return ResponseFactory::createResponse(Status::CODE_204, "");
    }

};

#include OATPP_CODEGEN_END(ApiController)