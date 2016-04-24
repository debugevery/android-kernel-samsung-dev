2.6.22.6版本的主目录下的Makefile 语法分析 第七部分2010-01-14 19:03# Documentation targets
# ---------------------------------------------------------------------------
%docs: scripts_basic FORCE
$(Q)$(MAKE) $(build)=Documentation/DocBook $@
# 定义了一个规则，目标是%docs，依赖关系是scripts_basic FORCE
# $@是Makefile的自动化变量，表示当前规则的目标集。 
else # KBUILD_EXTMOD

###
# External module support.
# When building external modules the kernel used as basis is considered
# read-only, and no consistency checks are made and the make
# system is not used on the basis kernel. If updates are required
# in the basis kernel ordinary make commands (without M=...) must
# be used.
#
# The following are the only valid targets when building external
# modules.
# make M=dir clean     Delete all automatically generated files
# make M=dir modules   Make all modules in specified dir
# make M=dir        Same as 'make M=dir modules'
# make M=dir modules_install
#                      Install the modules built in the module directory
#                      Assumes install directory is already created

# We are always building modules
KBUILD_MODULES := 1
PHONY += crmodverdir
crmodverdir:
$(Q)mkdir -p $(MODVERDIR)
$(Q)rm -f $(MODVERDIR)/*
# 第一行给变量KBUILD_MODULES赋值1.
# 第二行给变量PHONY追加值。
# 第三行定义了一个伪目标crmodverdir
# mkdir是linux shell下创建文件夹的命令，其语法是：mkdir [-p] dirName 
# rm是linux shell下删除文件或文件夹的命令，其语法是：rm [选项]... 文件...

PHONY += $(objtree)/Module.symvers
$(objtree)/Module.symvers:
@test -e $(objtree)/Module.symvers || ( \
echo; \
echo " WARNING: Symbol version dump $(objtree)/Module.symvers"; \
echo "           is missing; modules will have no dependencies and modversions."; \
echo )
# 第一行给变量PHONY追加值。
# 第二行定义了一个为目标$(objtree)/Module.symvers。
# 当“@”字符在命令行前，那么这个命令将不被make显示出来。
# echo是Makefile中的一个将输入的字符串送往标准输出关键字，其语法是：echo [-ne][字符串] 
# test是linux shell下的一个对档案侦测、判定的函数，其语法是：test [选项] string 
# 字符“\”有两个功能：一是：续行；二是：转义。

module-dirs := $(addprefix _module_,$(KBUILD_EXTMOD))
PHONY += $(module-dirs) modules
$(module-dirs): crmodverdir $(objtree)/Module.symvers
$(Q)$(MAKE) $(build)=$(patsubst _module_%,%,$@)
# 第一行将函数addprefix的返回值展开后赋给变量module-dirs。
# 第二行给变量PHONY追加值。
# 第三行定义了一个规则，目标是$(module-dirs)，依赖文件是crmodverdir $(objtree)/Module.symvers
# addprefix是Makefile中的一个加前缀函数函数，其语法是：$(addprefix <prefix>;,<names...>;)
# patsubst是Makefile中的一个模式字符串替换函数，
# 其语法是：$(patsubst <pattern>;,<replacement>;,<text>;)
# 查找<text>;中的单词是否符合模式<pattern>;，如果匹配的话，则以<replacement>;替换。

modules: $(module-dirs)
@echo ' Building modules, stage 2.';
$(Q)$(MAKE) -f $(srctree)/scripts/Makefile.modpost
# 上面定义了一个规则，目标是modules，依赖文件是$(module-dirs)。
# 当“@”字符在命令行前，那么这个命令将不被make显示出来。
# echo是Makefile中的一个将输入的字符串送往标准输出关键字，其语法是：echo [-ne][字符串]

PHONY += modules_install
modules_install: _emodinst_ _emodinst_post
# 第一行给变量PHONY追加值
# 第二行定义了一个依赖关系，目标是modules_install，依赖文件是_emodinst_ _emodinst_post

install-dir := $(if $(INSTALL_MOD_DIR),$(INSTALL_MOD_DIR),extra)
PHONY += _emodinst_
_emodinst_:
$(Q)mkdir -p $(MODLIB)/$(install-dir)
$(Q)$(MAKE) -f $(srctree)/scripts/Makefile.modinst
# 第一行将if函数的返回值展开后赋给变量install-dir。
# 第二行给变量PHONY追加值。
# 第三行定义了一个伪目标_emodinst_
# mkdir是linux shell下的一个创建文件夹的命令，其语法是：mkdir [-p] dirName

# Run depmod only is we have System.map and depmod is executable
quiet_cmd_depmod = DEPMOD $(KERNELRELEASE)
cmd_depmod = if [ -r System.map -a -x $(DEPMOD) ]; then \
$(DEPMOD) -ae -F System.map             \
$(if $(strip $(INSTALL_MOD_PATH)),      \
-b $(INSTALL_MOD_PATH) -r)              \
$(KERNELRELEASE);                       \
fi
# 第一二行分别给变量quiet_cmd_depmod和cmd_depmod赋值。
# strip是Makefile中的去空格函数，其语法是：$(strip <string>;)
# 字符“\”有两个功能：一是：续行；二是：转义。

PHONY += _emodinst_post
_emodinst_post: _emodinst_
$(call cmd,depmod)
# 第一行给变量PHONY追加值。
# 第二行定义了一个规则，目标是_emodinst_post，依赖文件是_emodinst_
# call是Makefile中一个用来创建新的参数化的函数，
# 其语法是：$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)
# <expression>;参数中的变量，会被参数<parm1>;，<parm2>;，<parm3>;依次取代。

clean-dirs := $(addprefix _clean_,$(KBUILD_EXTMOD))
# 上面将函数addprefix的返回值展开后赋给变量clean-dirs。
# addprefix是Makefile中一个加前缀函数，其语法是：$(addprefix <prefix>;,<names...>;)
# 功能：把前缀<prefix>;加到<names>;中的每个单词后面。

PHONY += $(clean-dirs) clean
$(clean-dirs):
$(Q)$(MAKE) $(clean)=$(patsubst _clean_%,%,$@)
# 第一行给变量PHONY追加值。
# 第二行定义了一个为目标$(clean-dirs)，
# patsubst是Makefile中的一个模式字符串替换函数，
# 其语法是：$(patsubst <pattern>;,<replacement>;,<text>;)
# 查找<text>;中的单词是否符合模式<pattern>;，如果匹配的话，则以<replacement>;替换。

clean: rm-dirs := $(MODVERDIR)
clean: $(clean-dirs)
$(call cmd,rmdirs)
@find $(KBUILD_EXTMOD) $(RCS_FIND_IGNORE) \
\( -name '*.[oas]' -o -name '*.ko' -o -name '.*.cmd' \
-o -name '.*.d' -o -name '.*.tmp' -o -name '*.mod.c' \) \
-type f -print | xargs rm -f
# 第一行定义了一个规则，目标是clean，依赖文件是rm-dirs，命令是给依赖文件rm-dirs赋值
# call是Makefile中一个用来创建新的参数化的函数，
# 当“@”字符在命令行前，那么这个命令将不被make显示出来。
# find是linux shell下的一个查找命令，其语法是：find path option [-print -exec -ok]
# 字符“\”有两个功能：一是：续行；二是：转义。

help:
@echo ' Building external modules.'
@echo ' Syntax: make -C path/to/kernel/src M=$$PWD target'
@echo ''
@echo ' modules         - default target, build the module(s)'
@echo ' modules_install - install the module'
@echo ' clean           - remove generated files in module directory only'
@echo ''
# 上面定义了一个伪目标help。
# 当“@”字符在命令行前，那么这个命令将不被make显示出来。
# echo是Makefile中的一个将输入的字符串送往标准输出关键字，其语法是：echo [-ne][字符串]

# Dummies...
PHONY += prepare scripts
prepare: ;
scripts: ;
endif # KBUILD_EXTMOD
# 第一行给变量PHONY追加值
# 第二三行分别定义了一个为目标，命令为空命令。

# Generate tags for editors
# ---------------------------------------------------------------------------

#We want __srctree to totally vanish out when KBUILD_OUTPUT is not set
#(which is the most common case IMHO) to avoid unneeded clutter in the big tags file.
#Adding $(srctree) adds about 20M on i386 to the size of the output file!

ifeq ($(src),$(obj))
__srctree =
else
__srctree = $(srctree)/
endif
#　ifeq是Makefile中的一个条件关键字，其语法是：ifeq (<arg1>;, <arg2>;)
# 功能：比较参数“arg1”和“arg2”的值是否相同。

ifeq ($(ALLSOURCE_ARCHS),)
ifeq ($(ARCH),um)
ALLINCLUDE_ARCHS := $(ARCH) $(SUBARCH)
else # 这个else与ifeq ($(ARCH),um)对应。
ALLINCLUDE_ARCHS := $(ARCH)
endif   # 这个endif与ifeq ($(ARCH),um)对应。
else   # 这个else与外层的ifeq ($(ALLSOURCE_ARCHS),)对应
#Allow user to specify only ALLSOURCE_PATHS on the command line, keeping existing behavour.
ALLINCLUDE_ARCHS := $(ALLSOURCE_ARCHS)
endif   # 这个endif与外层的ifeq ($(ALLSOURCE_ARCHS),)对应
# ifeq是Makefile中的一个条件关键字，其语法是：ifeq (<arg1>;, <arg2>;)
# 功能：比较参数“arg1”和“arg2”的值是否相同。
# 上面在ifeq ($(ALLSOURCE_ARCHS),)里面嵌入了一个ifeq ($(ARCH),um)。

ALLSOURCE_ARCHS := $(ARCH)
# 给变量ALLSOURCE_ARCHS赋值

define find-sources
( for ARCH in $(ALLSOURCE_ARCHS) ; do \
find $(__srctree)arch/$${ARCH} $(RCS_FIND_IGNORE) \
-name $1 -print; \
done ; \
find $(__srctree)security/selinux/include $(RCS_FIND_IGNORE) \
-name $1 -print; \
find $(__srctree)include $(RCS_FIND_IGNORE) \
\( -name config -o -name 'asm-*' \) -prune \
-o -name $1 -print; \
for ARCH in $(ALLINCLUDE_ARCHS) ; do \
find $(__srctree)include/asm-$${ARCH} $(RCS_FIND_IGNORE) \
-name $1 -print; \
done ; \
find $(__srctree)include/asm-generic $(RCS_FIND_IGNORE) \
-name $1 -print; \
find $(__srctree) $(RCS_FIND_IGNORE) \
\( -name include -o -name arch \) -prune -o \
-name $1 -print; \
)
endef
# define是Makefile中的一个定义命令包（相同的命令序列）的关键字，
# find是linux shell下的一个查找命令，其语法是：find path option [-print -exec -ok]
# 字符“\”有两个功能：一是：续行；二是：转义。

define all-sources
$(call find-sources,'*.[chS]')
endef
define all-kconfigs
$(call find-sources,'Kconfig*')
endef
define all-defconfigs
$(call find-sources,'defconfig')
endef
# define是Makefile中的一个定义命令包（相同的命令序列）的关键字，
# call是Makefile中的唯一一个来创建新的参数化的函数，
# 其语法是：$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)
# <expression>;参数中的变量，会被参数<parm1>;，<parm2>;，<parm3>;依次取代。

define xtags
if $1 --version 2>&1 | grep -iq exuberant; then \
$(all-sources) | xargs $1 -a \
-I __initdata,__exitdata,__acquires,__releases \
-I EXPORT_SYMBOL,EXPORT_SYMBOL_GPL \
--extra=+f --c-kinds=+px \
--regex-asm='/ENTRY\(([^)]*)\).*/\1/'; \
$(all-kconfigs) | xargs $1 -a \
--langdef=kconfig \
--language-force=kconfig \
--regex-kconfig='/^[[:blank:]]*config[[:blank:]]+([[:alnum:]_]+)/\1/'; \
$(all-defconfigs) | xargs -r $1 -a \
--langdef=dotconfig \
--language-force=dotconfig \
--regex-dotconfig='/^#?[[:blank:]]*(CONFIG_[[:alnum:]_]+)/\1/'; \
elif $1 --version 2>&1 | grep -iq emacs; then \
$(all-sources) | xargs $1 -a; \
$(all-kconfigs) | xargs $1 -a \
--regex='/^[ \t]*config[ \t]+\([a-zA-Z0-9_]+\)/\1/'; \
$(all-defconfigs) | xargs -r $1 -a \
--regex='/^#?[ \t]?\(CONFIG_[a-zA-Z0-9_]+\)/\1/'; \
else \
$(all-sources) | xargs $1 -a; \
fi
endef
# define是Makefile中的一个定义命令包（相同的命令序列）的关键字，
# 字符“\”有两个功能：一是：续行；二是：转义。
# 字符“|”是管道的标志，它的作用是：将上一个命令的stdout重定向到下一个命令的stdin。
# grep是linux shell中一个在文件中查找字符串的命令。其语法是：grep 字符串 文件名
# xargs是linux shell中的一个对输出执行其他某些命令的命令。

quiet_cmd_cscope-file = FILELST cscope.files
cmd_cscope-file = (echo \-k; echo \-q; $(all-sources)) > cscope.files
# 第一二行分别给变量quiet_cmd_cscope-file、cmd_cscope-file 赋值。
# echo是Makefile中的一个将输入的字符串送往标准输出关键字，其语法是：echo [-ne][字符串] 
# 字符“\”有两个功能：一是：续行；二是：转义。
# 字符“>”是重定向标志，功能将前一个命令的stdou重定向到档案（文件等）。

quiet_cmd_cscope = MAKE    cscope.out
cmd_cscope = cscope -b
# 分别给变量quiet_cmd_cscope和cmd_cscope赋值。

cscope: FORCE
$(call cmd,cscope-file)
$(call cmd,cscope)
# 上面定义了一个规则，目标是cscope，依赖文件是FORCE。
# call是Makefile中的唯一一个来创建新的参数化的函数，
# 其语法是：$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)

quiet_cmd_TAGS = MAKE   $@
define cmd_TAGS
rm -f $@; \
$(call xtags,etags)
endef
# 第一行给变量quiet_cmd_TAGS赋值。
# $@是Makefile的自动化变量，它代表当前规则的目标文件集。
# define是Makefile中的一个定义命令包（相同的命令序列）的关键字，
# rm是linux shell下删除文件或文件夹的命令，其语法是：rm [选项]... 文件...
# call是Makefile中的唯一一个来创建新的参数化的函数，
# 其语法是：$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)

TAGS: FORCE
$(call cmd,TAGS)
# 上面定义了一个规则，目标是TAGS，依赖文件是FORCE。
# call是Makefile中的唯一一个来创建新的参数化的函数，
# 其语法是：$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)

quiet_cmd_tags = MAKE   $@
define cmd_tags
rm -f $@; \
$(call xtags,ctags)
endef
# 第一行给变量quiet_cmd_tags赋值。
# $@是Makefile的自动化变量，它代表当前规则的目标文件集。
# define是Makefile中的一个定义命令包（相同的命令序列）的关键字，
# rm是linux shell下删除文件或文件夹的命令，其语法是：rm [选项]... 文件...
# call是Makefile中的唯一一个来创建新的参数化的函数，
# 其语法是：$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)

tags: FORCE
$(call cmd,tags)
# 上面定义了一个规则，目标是tags，依赖文件是FORCE
# call是Makefile中的唯一一个来创建新的参数化的函数，
# 其语法是：$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)


# Scripts to check various things for consistency
# ---------------------------------------------------------------------------
 
