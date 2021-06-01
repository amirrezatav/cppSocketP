#ifndef SERIALZE_H
#define SERIALZE
#include <cstring>
template<class Type>
class Serialize
{
public:
	static size_t serialize_Size(const Type input)
	{
		return sizeof(input);
	}
	static int serialize(char* const buffer, Type input)
	{
		memcpy(buffer, &input, sizeof(Type));
		return serialize_Size(input);
	}
	static int deSerialize(char* buffer, Type& Output)
	{
		memcpy(&Output, buffer, sizeof(Type));
		return serialize_Size(Output);
	}
};
#endif // !SERIALZE_H



