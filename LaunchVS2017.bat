@call "%~dp0path.bat"

@set GENERATE=%~dp0\UnrealEngine\UnrealEngine-release\Engine\Build\BatchFiles\GenerateProjectFiles.bat
@set UPROJECT=%~dp0TEA\TEA.uproject
@set SOLUTION=%~dp0TEA\TEA.sln

@if not exist "%VS2017%" goto ERROR_VS2017
@if not exist "%GENERATE%" goto ERROR_GENERATE
@if not exist "%UPROJECT%" goto ERROR_UPROJECT

@call "%GENERATE%" "-CurrentPlatform" "-2017" "%UPROJECT%" "-Game" "-Engine"
@if not exist "%SOLUTION%" goto ERROR_SOLUTION

@start "%VS2017%" "%SOLUTION%"
@exit /B %ERRORLEVEL%

:ERROR_VS2017
@echo ERROR: "%VS2017%" does not exist.
@pause
@exit /B 1

:ERROR_GENERATE
@echo ERROR: "%GENERATE%" does not exist.
@pause
@exit /B 1

:ERROR_UPROJECT
@echo ERROR: "%UPROJECT%" does not exist.
@pause
@exit /B 1

:ERROR_SOLUTION
@echo ERROR: "%SOLUTION%" does not exist.
@pause
@exit /B 1