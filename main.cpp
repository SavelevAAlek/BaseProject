#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "AppComponent.hpp"
#include "dto/ResultDto.hpp"
#include "dto/HelloDto.hpp"
#include "controller/MathController.hpp"

class HelloHandler : public oatpp::web::server::HttpRequestHandler {
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		OATPP_COMPONENT(std::string, helloString);

		OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

		auto list = HelloDto::createShared();

		auto element1 = ElementDto::createShared();
		list->elements = {};
		element1->id = 1;
		element1->name = "Alexey";

		auto element2 = ElementDto::createShared();
		element2->id = 2;
		element2->name = "Sergey";
		list->elements->push_back(element1);
		list->elements->push_back(element2);
		return ResponseFactory::createResponse(Status::CODE_200, list, objectMapper);
	}
};



// функция, для запуска сервера
void runServer() {
	AppComponent components;

	OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter);

	httpRouter->addController(std::make_shared<MathController>());

	//httpRouter->route("GET", "/sum", std::make_shared<SumHandler>());
	//httpRouter->route("GET", "/hello", std::make_shared<HelloHandler>());

	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler);

	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider);

	oatpp::network::Server server(serverConnectionProvider, serverConnectionHandler);

	OATPP_LOGI("App", "Сервер запущен");

	server.run();
}

int main() {
	setlocale(LC_ALL, "Rus");
	oatpp::base::Environment::init();
	runServer();
	return 0;
}