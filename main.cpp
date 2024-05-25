#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "AppComponent.hpp"
#include "controller/AirplanesController.hpp"
#include "oatpp-swagger/Controller.hpp"

// функция, для запуска сервера
void runServer() {
	AppComponent components;

	OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter);

	oatpp::web::server::api::Endpoints docEndpoints;

	docEndpoints.append(httpRouter->addController(std::make_shared<AirplanesController>())->getEndpoints());

	httpRouter->addController(oatpp::swagger::Controller::createShared(docEndpoints));

	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler);

	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider);

	oatpp::network::Server server(serverConnectionProvider, serverConnectionHandler);

	OATPP_LOGI("App", "Сервер запущен");

	server.run();
}

int main() {
	setlocale(LC_CTYPE, "Rus");
	oatpp::base::Environment::init();
	runServer();
	return 0;
}