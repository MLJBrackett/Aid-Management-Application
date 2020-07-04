#ifndef ErrorState_h
#define ErrorState_h

#include <iostream>
#include <cstring>
#include <string>

using namespace std;
namespace ama {

	class ErrorState {
		char* messageAddress;

	public:

		explicit ErrorState(const char* errorMessage = nullptr);

		ErrorState(const ErrorState& other) = delete;

		ErrorState& operator=(const ErrorState& other) = delete;

		~ErrorState();

		operator bool() const;

		ErrorState& operator=(const char* pText);

		void message(const char* pText);

		const char* message() const;

	};
	std::ostream& operator<<(std::ostream& os, const ErrorState& em);
}

#endif /* ErrorState_h */
