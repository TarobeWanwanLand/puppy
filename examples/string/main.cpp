#include <puppy/core/log.hpp>

int main(int, char*[])
{
	PUPPY_LOG_TRACE("Hello!");
	_PUPPY_LOG_CORE_CRITICAL("aaa");

    return 0;
}
