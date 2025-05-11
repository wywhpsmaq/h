$cppFiles = Get-ChildItem -Path "f:\h\c++code" -Recurse -Filter *.cpp
$gpp = "C:\mingw64\bin\g++.exe"
$maxJobs = 6   # 最大并发数，可根据CPU调整
$jobs = @()

foreach ($file in $cppFiles) {
    $src = $file.FullName
    $outdir = Join-Path $file.Directory.FullName "output"
    if (-not (Test-Path $outdir)) { 
        New-Item -ItemType Directory -Path $outdir -ErrorAction SilentlyContinue | Out-Null 
    }
    $exe = Join-Path $outdir ($file.BaseName + ".exe")
    # 控制并发数
    while ($jobs.Count -ge $maxJobs) {
        $finished = Wait-Job -Job $jobs -Any
        Receive-Job $finished
        $jobs = $jobs | Where-Object { $_.State -eq 'Running' }
    }
    $jobs += Start-Job -ScriptBlock {
        param($src, $exe, $gpp)
        & $gpp -g "$src" -o "$exe"
        if ($LASTEXITCODE -ne 0) {
            Write-Host "编译失败，跳过: $src"
        } else {
            Write-Host "编译成功: $src"
        }
    } -ArgumentList $src, $exe, $gpp
}

# 等待剩余任务
$jobs | ForEach-Object { Wait-Job $_; Receive-Job $_ }
Write-Host "全部编译完成"
