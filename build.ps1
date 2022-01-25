rm -R .\build -Force
mkdir build | OUT-NULL
Push-Location .\build
try
{
    cmake ..
    cmake --preset vs2022-windows -DCOPY_OUTPUT=ON
    cmake --build . --config Release -v
}
finally
{
    Pop-Location
}
