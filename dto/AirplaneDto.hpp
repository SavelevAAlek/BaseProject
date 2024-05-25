#ifndef AirplaneDto_hpp
#define AirplaneDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

class AirplaneDto : public oatpp::DTO {
	DTO_INIT(AirplaneDto, DTO);
	// модель самолета
	DTO_FIELD(String, model);
	// тип самолета
	DTO_FIELD(String, type);
	// производитель самолета
	DTO_FIELD(String, manufacturer);
	// страна-производитель самолета
	DTO_FIELD(String, country);
	// количество двигателей самолета
	DTO_FIELD(Int16, engines_amount);
	// идентификатор пользователя
	DTO_FIELD(Int16, userid);
	// описание
	DTO_FIELD(String, description);
};


#include OATPP_CODEGEN_END(DTO)

#endif