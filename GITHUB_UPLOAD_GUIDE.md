# GitHub 上传指南

本地 Git 仓库已经初始化完成，所有文件已提交。现在需要连接到 GitHub 并推送代码。

## 步骤 1: 在 GitHub 上创建新仓库

1. 登录 [GitHub](https://github.com)
2. 点击右上角的 **"+"** 按钮，选择 **"New repository"**
3. 填写仓库信息：
   - **Repository name**: `BFLA-01KP` (或您喜欢的名称)
   - **Description**: `Binary Flow Learning Algorithm for 0-1 Knapsack Problem`
   - **Visibility**: 选择 Public 或 Private
   - **不要**勾选 "Initialize this repository with a README"（我们已经有了）
   - **不要**添加 .gitignore 或 license（我们已经有了）
4. 点击 **"Create repository"**

## 步骤 2: 连接本地仓库到 GitHub

GitHub 创建仓库后会显示一个页面，其中包含仓库的 URL。请复制仓库 URL，然后运行以下命令：

### 如果使用 HTTPS（推荐）：

```bash
git remote add origin https://github.com/YOUR_USERNAME/BFLA-01KP.git
```

### 如果使用 SSH：

```bash
git remote add origin git@github.com:YOUR_USERNAME/BFLA-01KP.git
```

**注意**: 请将 `YOUR_USERNAME` 替换为您的 GitHub 用户名。

## 步骤 3: 推送代码到 GitHub

推送代码到 GitHub 主分支：

```bash
git branch -M main
git push -u origin main
```

如果您的默认分支是 `master`，使用：

```bash
git push -u origin master
```

## 快速命令汇总

在项目根目录下执行（替换 YOUR_USERNAME 和 REPO_NAME）：

```bash
# 添加远程仓库（使用 HTTPS）
git remote add origin https://github.com/YOUR_USERNAME/REPO_NAME.git

# 或者使用 SSH（如果您配置了 SSH 密钥）
git remote add origin git@github.com:YOUR_USERNAME/REPO_NAME.git

# 推送代码
git branch -M main
git push -u origin main
```

## 验证上传

上传完成后，访问您的 GitHub 仓库页面，您应该能看到：
- ✅ 所有源代码文件
- ✅ README.md 文档
- ✅ 所有 notebooks
- ✅ 实例文件 ZIP
- ✅ 编译脚本

## 常见问题

### 1. 如果远程仓库已存在

如果您之前已经创建了仓库并添加了文件，可能需要先拉取：

```bash
git pull origin main --allow-unrelated-histories
```

然后再推送。

### 2. 认证问题（HTTPS）

如果遇到认证问题，GitHub 现在需要使用 Personal Access Token：
- 生成 token: GitHub Settings > Developer settings > Personal access tokens > Tokens (classic)
- 在推送时使用 token 作为密码

### 3. 使用 SSH（推荐避免认证问题）

如果配置了 SSH 密钥，可以使用 SSH URL：
```bash
git remote set-url origin git@github.com:YOUR_USERNAME/REPO_NAME.git
```

## 已提交的文件

本地仓库已包含以下文件：
- ✅ 源代码 (src/BFLA_01KP.cpp)
- ✅ 文档 (README.md, SETUP.md 等)
- ✅ Notebooks (5个分析笔记本)
- ✅ 编译脚本 (compile.sh, compile.bat)
- ✅ 实例文件 (Instance_01KP_36.zip)
- ✅ 配置文件 (.gitignore)

---

**下一步**: 按照步骤 1-3 在 GitHub 上创建仓库并推送代码。

