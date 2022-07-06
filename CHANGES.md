# CHANGELOG.md

VERSION: 1.0.1
DATE: July 6th, 2022

# Features
- Added `LIBPATH_SEPARATOR` for accessing the platform's path separator
- Added `LIBPATH_FAILURE` for detecting when a file system operation fails
- Added `LIBPATH_SUCCESS` for detecting when a file system operation succeeds
- File globbing
- MS-DOS support for file globbing

# Misc.
- Added `liberror` as a dependency
- Added `libpath_internal.h`
- Put all functions in the same file
- Docgen-ified all function descriptions
- Macro and inclusion support for Macintosh and UNIXWare.

# Breaking Changes
- `libpath_join_path` now returns an integer
- `libpath_join_path` now automatically inserts path separators
