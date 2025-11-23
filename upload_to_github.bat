@echo off
REM GitHub上传脚本
REM 使用前请先在GitHub上创建仓库，然后修改下面的YOUR_USERNAME和REPO_NAME

echo ========================================
echo BFLA-01KP GitHub 上传脚本
echo ========================================
echo.

REM 请修改下面的变量为您的GitHub信息
set GITHUB_USERNAME=YOUR_USERNAME
set REPO_NAME=BFLA-01KP

echo 请先确认：
echo 1. 已在GitHub上创建仓库: %REPO_NAME%
echo 2. 已修改此脚本中的 GITHUB_USERNAME 和 REPO_NAME
echo.
pause

echo.
echo 正在添加远程仓库...
git remote add origin https://github.com/%GITHUB_USERNAME%/%REPO_NAME%.git

if %errorlevel% neq 0 (
    echo 警告: 远程仓库可能已存在，尝试更新...
    git remote set-url origin https://github.com/%GITHUB_USERNAME%/%REPO_NAME%.git
)

echo.
echo 正在推送代码到GitHub...
git branch -M main
git push -u origin main

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo 上传成功！
    echo 请访问: https://github.com/%GITHUB_USERNAME%/%REPO_NAME%
    echo ========================================
) else (
    echo.
    echo ========================================
    echo 上传失败，请检查：
    echo 1. GitHub仓库URL是否正确
    echo 2. 是否已配置GitHub认证
    echo 3. 网络连接是否正常
    echo ========================================
)

pause

