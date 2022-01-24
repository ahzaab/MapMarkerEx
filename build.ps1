rm -R .\build -Force
mkdir build | OUT-NULL
Push-Location .\build
try
{
    cmake ..
    cmake --preset vs2022-windows
    cmake --build . --config Release -v
}
finally
{
    Pop-Location
}