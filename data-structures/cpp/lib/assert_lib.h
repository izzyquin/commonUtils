#define ASSERT_RETURN(condition, returnvalue)\
	if (!(condition)) {\
		return returnvalue; \
	}

#define ASSERT(condition)\
	if (!(condition)) {\
		return; \
	}

