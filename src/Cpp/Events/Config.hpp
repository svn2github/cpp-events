#ifndef __CPP_EVENTS__CONFIG__HPP
#define __CPP_EVENTS__CONFIG__HPP

//Platform detection

#if defined(_MSC_VER)
#  define PLATFORM_DIR Win32
#elif defined(POSIX)
#  define PLATFORM_DIR POSIX
#else
#  error "Unsupported target platform!"
#endif

// Platform-specific path

#define PLATFORM_PATH_HELPER_0(Path) #Path
#define PLATFORM_PATH_HELPER_1(Dir, Path) PLATFORM_PATH_HELPER_0(Dir ## / ## Path)
#define PLATFORM_PATH_HELPER_2(Dir, Path) PLATFORM_PATH_HELPER_1(Dir, Path)
#define PLATFORM_PATH(Path) PLATFORM_PATH_HELPER_2(PLATFORM_DIR, Path)

#define DISABLE_COPY(Class) \
private: \
	Class(Class const &); \
	Class & operator=(Class const &);

#endif //__CPP_EVENTS__CONFIG__HPP