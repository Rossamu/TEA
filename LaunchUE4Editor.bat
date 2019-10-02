@call "%~dp0path.bat"

@set UEDITOR=%~dp0\UnrealEngine\UnrealEngine-release\Engine\Binaries\Win64\UE4Editor.exe
@set UPROJECT=%~dp0TEA\TEA.uproject

@if not exist "%UEDITOR%" goto ERROR_UEDITOR
@if not exist "%UPROJECT%" goto ERROR_UPROJECT

@start "" "%UEDITOR%" "%UPROJECT% -2017
@exit /B %ERRORLEVEL%

:ERROR_UEDITOR
@echo ERROR: "%UEDITOR%" does not exist.
@pause
@exit /B 1

:ERROR_UPROJECT
@echo ERROR: "%UPROJECT%" does not exist.
@pause
@exit /B 1