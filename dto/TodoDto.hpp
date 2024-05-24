#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

class TodoDto : public oatpp::DTO {
	DTO_INIT(TodoDto, DTO);
	//�������� �������
	DTO_FIELD(String, name);
	//�������� �������
	DTO_FIELD(String, description);
	//��������� (0 - ������, 1 - �������, 2 - �������)
	DTO_FIELD(Int16, priority);
};


#include OATPP_CODEGEN_END(DTO)