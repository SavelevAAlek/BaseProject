#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

class SwaggerComponent {
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
		oatpp::swagger::DocumentInfo::Builder builder;

		builder.setTitle("Todo Application");
		builder.setDescription("First C++ backend app");
		builder.setVersion("0.0.1");
		builder.setContactName("Alexey Savelyev");
		builder.setContactEmail("savelyev.main@gmail.com");
		return builder.build();
		}());

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
		return oatpp::swagger::Resources::loadResources("Dependencies\\oatp-swagger\\include\\oatpp-1.3.0\\bin\\oatpp-swagger\\res");
		}());
};