project('bathory1', 'cpp', default_options : ['cpp_std=c++20'])
dep = [dependency('fmt')]
incdir = [include_directories('include')]
executable(
  'bathory1',
  'src/main.cpp',
  'src/identify.cpp',
  'src/codecs/convert_to.cpp',
  'src/codecs/convert_from.cpp',
  dependencies : dep,
  include_directories : incdir)
