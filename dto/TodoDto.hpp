#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

class TodoDto : public oatpp::DTO {
	DTO_INIT(TodoDto, DTO);
	//название заметки
	DTO_FIELD(String, name);
	//описание заметки
	DTO_FIELD(String, description);
	//приоритет (0 - низкий, 1 - средний, 2 - высокий)
	DTO_FIELD(Int16, priority);
};


#include OATPP_CODEGEN_END(DTO)