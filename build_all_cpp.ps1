$cppFiles = Get-ChildItem -Path "f:\h\c++code" -Recurse -Filter *.cpp
$gpp = "C:\mingw64\bin\g++.exe"
$maxJobs = 6   # ��󲢷������ɸ���CPU����
$jobs = @()

foreach ($file in $cppFiles) {
    $src = $file.FullName
    $outdir = Join-Path $file.Directory.FullName "output"
    if (-not (Test-Path $outdir)) { 
        New-Item -ItemType Directory -Path $outdir -ErrorAction SilentlyContinue | Out-Null 
    }
    $exe = Join-Path $outdir ($file.BaseName + ".exe")
    # ���Ʋ�����
    while ($jobs.Count -ge $maxJobs) {
        $finished = Wait-Job -Job $jobs -Any
        Receive-Job $finished
        $jobs = $jobs | Where-Object { $_.State -eq 'Running' }
    }
    $jobs += Start-Job -ScriptBlock {
        param($src, $exe, $gpp)
        & $gpp -g "$src" -o "$exe"
        if ($LASTEXITCODE -ne 0) {
            Write-Host "����ʧ�ܣ�����: $src"
        } else {
            Write-Host "����ɹ�: $src"
        }
    } -ArgumentList $src, $exe, $gpp
}

# �ȴ�ʣ������
$jobs | ForEach-Object { Wait-Job $_; Receive-Job $_ }
Write-Host "ȫ���������"
