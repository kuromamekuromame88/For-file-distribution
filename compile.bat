@echo off
setlocal

rem === 初回は環境付きで再起動 ===
if "%DEV_ENV%"=="" (
    set DEV_ENV=1
    %comspec% /k ""C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars32.bat" && set DEV_ENV=1 && call "%~f0""
    exit
)

:loop
echo.
echo プロジェクト名を入力してください。
set "PROJECT="
set /p PROJECT=
cd /d "%~dp0%PROJECT%"

echo.
echo 1: コンパイルして実行
echo 2: ビルド済み実行ファイルの実行
echo.

set "BATMODE="
set /p BATMODE=
if "%BATMODE%"=="1" (
  echo #コンパイルモード
  echo コンパイル中...
  cl /EHsc *.cpp

  if errorlevel 1 (
    echo コンパイル失敗
    cd /d "%~dp0"
    goto loop
  )

  echo 実行中（Ctrl+Cで停止できます）...
  start "" cmd /k "cd /d %cd% && %PROJECT%.exe" <nul
  echo プログラムの実行が終了しました!
  
) else (
  echo #実行モード
  echo 実行中（Ctrl+Cで停止できます）...
  start "" cmd /k "%PROJECT%.exe" <nul
  echo プログラムの実行が終了しました!
)

cd /d "%~dp0"
goto loop
