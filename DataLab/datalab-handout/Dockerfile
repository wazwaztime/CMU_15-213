# 使用x86架构的Ubuntu基础镜像
FROM --platform=linux/amd64 ubuntu:22.04

# 安装必要的构建工具和32位库
RUN apt-get update && \
    apt-get install -y build-essential gcc-multilib libc6-dev-i386 make && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /lab
COPY . /lab/