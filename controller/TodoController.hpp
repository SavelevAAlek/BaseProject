#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/Types.hpp"
#include "../dto/TodoDto.hpp"
#include "../dto/UserDto.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class TodoController : public oatpp::web::server::api::ApiController {
private:
	OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

	OATPP_COMPONENT(std::shared_ptr<MyClient>, dbClient);

	List<Object<TodoDto>> todos = List<Object<TodoDto>>::createShared();

	// функция для проверки данных авторизации
	int checkAuth(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject> authObject) {
		auto result = dbClient->getAllUsers();

		auto users = result->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

		OATPP_LOGI("App", objectMapper->writeToString(users)->c_str());

		for (auto i = 0; i < users->size(); i++) {
			if (users[i]->username == authObject->userId &&
				users[i]->password == authObject->password) {
				return users[i]->id;
			}
		}
	}
public:
	TodoController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		: oatpp::web::server::api::ApiController(objectMapper)
	{ 
		setDefaultAuthorizationHandler(std::make_shared<oatpp::web::server::handler::BasicAuthorizationHandler>("auth-handler"));
	}

	ENDPOINT_INFO(todosAll) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->addSecurityRequirement("Authorization required");
	}
	// получить список всех заметок
	ENDPOINT("GET", "todo/all", todosAll,
		AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		return ResponseFactory::createResponse(Status::CODE_200, todos, objectMapper);	
	}

	ENDPOINT("GET", "/todo/about", todosAbout) {
		std::string header = "<h1>Todo Controller</h1>";
		std::string list = "<ul><li>Create todos</li><li>Update todos></li><li>Delete todos</li></ul>";

		return ResponseFactory::createResponse(Status::CODE_200, header + list);
	}

	ENDPOINT_INFO(todosOne) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->addSecurityRequirement("Authorization required");
	}
	ENDPOINT("GET", "todo/{id}", todosOne, PATH(Int16, id),
		AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		if (id >= todos->size()) {
			return ResponseFactory::createResponse(Status::CODE_404, "Заметка не найдена");
		}
		return ResponseFactory::createResponse(Status::CODE_200, todos, objectMapper);
	}

	ENDPOINT_INFO(todosAdd) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->addSecurityRequirement("Authorization required");
	}
	ENDPOINT("POST", "/todo", todosAdd, BODY_DTO(Object<TodoDto>, todoDto),
		AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		todos->push_back(todoDto);
		return ResponseFactory::createResponse(Status::CODE_201, todoDto, objectMapper);
	}


	ENDPOINT_INFO(todosUpdate) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->pathParams["id"].description = "Description of ID";
		info->addSecurityRequirement("Authorization required");
	}
	ENDPOINT("PUT", "/todo/{id}", todosUpdate, BODY_DTO(Object<TodoDto>, todoDto), PATH(Int16, id),
		AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		if (id >= todos->size()) {
			return ResponseFactory::createResponse(Status::CODE_404, "Заметка не найдена");
		}

		todos[id] = todoDto;

		return ResponseFactory::createResponse(Status::CODE_200, todoDto, objectMapper);
	}

	ENDPOINT_INFO(todosDelete) {
		info->tags = std::list<oatpp::String>{ "Todo" };
		info->addSecurityRequirement("Authorization required");
	}
	ENDPOINT("DELETE", "/todo/{id}", todosDelete, PATH(Int16, id),
		AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBasicAuthorizationObject>, authObject)) {
		checkAuth(authObject);
		if (id >= todos->size()) {
			return ResponseFactory::createResponse(Status::CODE_404, "Заметка не найдена");
		}

		todos->remove(todos[id]);

		return ResponseFactory::createResponse(Status::CODE_204, "");
	}

};

#include OATPP_CODEGEN_END(ApiController)