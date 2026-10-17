@echo off
rem File Centipede theme toggle: applies the ui/ sml overlay, swaps ui/css + icons
rem between themes\dark and themes\light, then restarts the app.
rem Run from inside an extracted File Centipede folder that also contains themes\.
setlocal
cd /d "%~dp0"
rem re-entrancy lock: ignore duplicate triggers within 15 seconds
set "LOCK=%TEMP%\fc_theme.lock"
if exist "%LOCK%" (
    powershell -NoProfile -Command "if((Get-Date)-((Get-Item '%LOCK%')).LastWriteTime).TotalSeconds -lt 15){exit 1}"
    if not errorlevel 1 del "%LOCK%"
)
if exist "%LOCK%" exit /b
echo.>"%LOCK%"
if exist "ui\css\theme_is_dark" (set "NEXT=light") else (set "NEXT=dark")
taskkill /IM fileu.exe /F >nul 2>&1
ping -n 2 127.0.0.1 >nul
rem ui overlay (Theme toolbar button + dark-safe inline colors), applied for both themes
xcopy /e /i /y "themes\sml" "ui" >nul
copy /y "themes\%NEXT%\default.css" "ui\css\default.css" >nul
xcopy /e /i /y "themes\%NEXT%\css_images" "ui\css\images" >nul
xcopy /e /i /y "themes\%NEXT%\icons" "icons" >nul
if "%NEXT%"=="dark" (echo.>"ui\css\theme_is_dark") else (if exist "ui\css\theme_is_dark" del "ui\css\theme_is_dark")
start "" "%~dp0fileu.exe"
del "%LOCK%"
endlocal
