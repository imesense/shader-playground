call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

msbuild ShaderPlayground.Render.sln ^
    -p:Configuration=Debug ^
    -p:Platform=x86 ^
    -maxCpuCount ^
    -nologo ^
    -v:minimal
msbuild ShaderPlayground.Render.sln ^
    -p:Configuration=Release ^
    -p:Platform=x86 ^
    -maxCpuCount ^
    -nologo ^
    -v:minimal
msbuild ShaderPlayground.Render.sln ^
    -p:Configuration=Debug ^
    -p:Platform=x64 ^
    -maxCpuCount ^
    -nologo ^
    -v:minimal
msbuild ShaderPlayground.Render.sln ^
    -p:Configuration=Release ^
    -p:Platform=x64 ^
    -maxCpuCount ^
    -nologo ^
    -v:minimal

nuget pack src\RenderLibrary\RenderLibrary.nuspec ^
    -OutputDirectory pkg
