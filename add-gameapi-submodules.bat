@echo off
REM Helper script to add GameAPI submodules for any mod folders that don't have one, then update all submodules to latest commit
REM Fun fact: I HATE WORKING WITH GIT SUBMODULES!!!!
for /d %%i in (*) do (
    if %%i NEQ ".git" if not exist %%i/GameAPI git submodule add https://github.com/RSDKModding/RSDKv5-GameAPI %%i/GameAPI
)
git submodule update --remote --init
