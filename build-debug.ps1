#rm -R .\build
#mkdir build | OUT-NULL
Push-Location .\build
try
{
    cmake ..
    cmake --preset vs2022-windows
    cmake --build . -v
}
finally
{
    Pop-Location
}