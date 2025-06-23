# 强制使用 x86-64 架构的 Ubuntu
FROM --platform=linux/amd64 ubuntu:22.04

# 安装必要工具（x86-64 专用）
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    gdb \
    gcc-multilib \
    libc6-dbg \
    libc6-dev-i386 \
    vim \
    && rm -rf /var/lib/apt/lists/*

# 设置工作目录
WORKDIR /lab
COPY . /lab/
RUN mkdir -p ~/.config/gdb
RUN echo "set auto-load safe-path /" > ~/.config/gdb/gdbinit
CMD ["/bin/bash"]