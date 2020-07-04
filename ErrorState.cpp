#include <iostream>
#include <cstring>
#include <string>
#include "ErrorState.h"


using namespace std;
namespace ama {
	ErrorState::ErrorState(const char* errorMessage) {
		if (errorMessage == nullptr || strlen(errorMessage) <= 0) {
			messageAddress = nullptr;
		}
		else {
			messageAddress = new char[strlen(errorMessage) + 1];
			for (unsigned int i = 0; i < strlen(errorMessage); i++) {
				messageAddress[i] = errorMessage[i];
			}
			messageAddress[strlen(errorMessage) + 1] = '\0';
		}
	}

	ErrorState::~ErrorState() {
		delete[] messageAddress;
		messageAddress = nullptr;
	}

	ErrorState::operator bool() const {
		return !(messageAddress == nullptr);
	}

	ErrorState& ErrorState::operator=(const char* pText) {
		if (pText == nullptr || strlen(pText) <= 0) {
			messageAddress = nullptr;
		}
		else {
			messageAddress = new char[strlen(pText) + 1];
			for (unsigned int i = 0; i < strlen(pText); i++) {
				messageAddress[i] = pText[i];
			}
			messageAddress[strlen(pText) + 1] = '\0';
		}
		return *this;
	}

	void ErrorState::message(const char* pText) {
		if (pText == nullptr || strlen(pText) <= 0) {
			messageAddress = nullptr;
		}
		else {
			messageAddress = new char[strlen(pText)];
			//for (unsigned int i = 0; i < strlen(pText); i++) {
			//	messageAddress[i] = pText[i];
			//}
            strncpy(messageAddress, pText, strlen(pText));
			messageAddress[strlen(pText)] = '\0';
		}
	}

	const char* ErrorState::message()const {
		if (messageAddress == nullptr) {
			return nullptr;
		}
		else {
			return messageAddress;
		}
	}


	std::ostream& operator<<(std::ostream& os, const ErrorState& em) {
		if (em.message() != nullptr) {
			os << em.message();
		}
		return os;
	}
}

