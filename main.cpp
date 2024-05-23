#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "AppComponent.hpp"

class HelloHandler : public oatpp::web::server::HttpRequestHandler {
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		OATPP_COMPONENT(std::string, helloString);
		return ResponseFactory::createResponse(Status::CODE_200, helloString);
	}
};

class SumHandler : public oatpp::web::server::HttpRequestHandler {
public:
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {

		auto aPtr = request->getQueryParameter("a").get();
		auto bPtr = request->getQueryParameter("b").get();

		auto acceptLanguageHandler = request->getHeader("Accept-Language").get();
		OATPP_LOGW("App", acceptLanguageHandler->c_str());

		if (aPtr == nullptr || bPtr == nullptr) {
			OATPP_LOGE("App", "Не все параметры указаны");
			return ResponseFactory::createResponse(Status::CODE_400, "Не все параметры указаны");
		}

		float a = atof(aPtr->c_str());
		float b = atof(bPtr->c_str());

		auto response = ResponseFactory::createResponse(Status::CODE_200, std::to_string(a + b));
		response->putHeaderIfNotExists("SumResult", std::to_string(a + b));

		OATPP_LOGD("App", "Результат вычислен успешно");

		return response;
	}
};

// функция, для запуска сервера
void runServer() {
	AppComponent components;

	OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter);

	httpRouter->route("GET", "/sum", std::make_shared<SumHandler>());
	httpRouter->route("GET", "/hello", std::make_shared<HelloHandler>());

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