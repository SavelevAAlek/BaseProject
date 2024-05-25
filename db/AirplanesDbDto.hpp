#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

class AirplaneDbDto : public oatpp::DTO {
	DTO_INIT(AirplaneDbDto, DTO);
	// ������������� ��������
	DTO_FIELD(Int16, id);
	// ������ ��������
	DTO_FIELD(String, model);
	// ��� ��������
	DTO_FIELD(String, type);
	// ������������� ��������
	DTO_FIELD(String, manufacturer);
	// ������-������������� ��������
	DTO_FIELD(String, country);
	// ���������� ���������� ��������
	DTO_FIELD(Int16, engines_amount);
	// ������������� ������������
	DTO_FIELD(Int16, userid);
	// ��������
	DTO_FIELD(String, description);
};


#include OATPP_CODEGEN_END(DTO)