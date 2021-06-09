#ifndef SERIALIZE_H
#define SERIALIZE_H
#include <cstring>
template<class Type>
class Serialize
{
public:
	static size_t size(const Type input)
	{
		return sizeof(input);
	}
	static size_t serialize(char* const Buffer ,  Type input)
	{
		memcpy(Buffer, &input, sizeof(input));
		return sizeof(input);
	}
	static size_t deserialize(char*  Buffer, Type& output)
	{
		memcpy(&output, Buffer, sizeof(output));
		return sizeof(output);
	}
};
#endif // !SERIALIZE_H



