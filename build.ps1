param(
    [switch]$Clean
)

$root = Split-Path -Parent $MyInvocation.MyCommand.Definition
$buildDir = Join-Path $root "build"
$releaseDir = Join-Path $buildDir "Release"

if ($Clean -and (Test-Path $buildDir)) {
    Write-Host "Cleaning previous build..."
    Remove-Item $buildDir -Recurse -Force
}

if (!(Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

Write-Host "Configuring CMake..."
cmake -S $root -B $buildDir -DCMAKE_BUILD_TYPE=Release

Write-Host "Building project..."
cmake --build $buildDir --config Release

Write-Host "Building C# Adapter..."
$adapterProj = Join-Path $root "adapter"
msbuild "$adapterProj\Program.csproj" /p:Configuration=Release /t:Build /verbosity:minimal

Write-Host "`n✅ Build completed successfully!"
Write-Host "Artifacts located in: $releaseDir"
