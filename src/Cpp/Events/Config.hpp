#ifndef __CPP_EVENTS__CONFIG__HPP
#define __CPP_EVENTS__CONFIG__HPP

//Platform detection

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define PLATFORM_DIR WinApi
#elif defined(__GNUC__)
#  define PLATFORM_DIR POSIX
#else
#  error "Unsupported target platform!"
#endif

// Platform-specific path

#define PLATFORM_PATH_HELPER_0(Path) #Path
#define PLATFORM_PATH_HELPER_1(Dir, Path) PLATFORM_PATH_HELPER_0(Dir/Path)
#define PLATFORM_PATH_HELPER_2(Dir, Path) PLATFORM_PATH_HELPER_1(Dir, Path)
#define PLATFORM_PATH(Path) PLATFORM_PATH_HELPER_2(PLATFORM_DIR, Path)

#define DISABLE_COPY(Class) \
private: \
	Class(Class const &); \
	Class & operator=(Class const &);

#endif //__CPP_EVENTS__CONFIG__HPP