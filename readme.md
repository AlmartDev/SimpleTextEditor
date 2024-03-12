# Simple Text Editor
A rudimentary text editor in its infancy stages, likely to remain perpetually unfinished. Utilizing premake5 for project generation.

# Usage
`-d` to select working directory
`-s` to select style, either `dark`, `light` or `classic`, update your styles in `editor/style.h`

# Building
```sh
git clone --recursive https://github.com/almartdev/simpletexteditor.git
cd simpletexteditor/build
premake5 gmake2  # or visual studio etc... Make sure to have premake installed!
make
```
Your built binaries should be found in `/build/bin/debug/TextEditor`. You can also select `release` or `dist` build options!

# 3rdParty
Found in `editor/3rdParty/`
- premake imgui
- premake glfw
- imgui file diaglog

- premake glad (not really needed yet)
- stb image (not needed either)