# provides jsmn.h header library

set(FETCHCONTENT_UPDATES_DISCONNECTED_JSMN true)

FetchContent_Declare(JSMN
  GIT_REPOSITORY https://github.com/zserge/jsmn
  GIT_TAG        053d3cd29200edb1bfd181d917d140c16c1f8834
)

FetchContent_Populate(JSMN)

FetchContent_GetProperties(JSMN)
