2.6.22.6�汾����Ŀ¼�µ�Makefile �﷨���� ���߲���2010-01-14 19:03# Documentation targets
# ---------------------------------------------------------------------------
%docs: scripts_basic FORCE
$(Q)$(MAKE) $(build)=Documentation/DocBook $@
# ������һ������Ŀ����%docs��������ϵ��scripts_basic FORCE
# $@��Makefile���Զ�����������ʾ��ǰ�����Ŀ�꼯�� 
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
# ��һ�и�����KBUILD_MODULES��ֵ1.
# �ڶ��и�����PHONY׷��ֵ��
# �����ж�����һ��αĿ��crmodverdir
# mkdir��linux shell�´����ļ��е�������﷨�ǣ�mkdir [-p] dirName 
# rm��linux shell��ɾ���ļ����ļ��е�������﷨�ǣ�rm [ѡ��]... �ļ�...

PHONY += $(objtree)/Module.symvers
$(objtree)/Module.symvers:
@test -e $(objtree)/Module.symvers || ( \
echo; \
echo " WARNING: Symbol version dump $(objtree)/Module.symvers"; \
echo "           is missing; modules will have no dependencies and modversions."; \
echo )
# ��һ�и�����PHONY׷��ֵ��
# �ڶ��ж�����һ��ΪĿ��$(objtree)/Module.symvers��
# ����@���ַ���������ǰ����ô����������make��ʾ������
# echo��Makefile�е�һ����������ַ���������׼����ؼ��֣����﷨�ǣ�echo [-ne][�ַ���] 
# test��linux shell�µ�һ���Ե�����⡢�ж��ĺ��������﷨�ǣ�test [ѡ��] string 
# �ַ���\�����������ܣ�һ�ǣ����У����ǣ�ת�塣

module-dirs := $(addprefix _module_,$(KBUILD_EXTMOD))
PHONY += $(module-dirs) modules
$(module-dirs): crmodverdir $(objtree)/Module.symvers
$(Q)$(MAKE) $(build)=$(patsubst _module_%,%,$@)
# ��һ�н�����addprefix�ķ���ֵչ���󸳸�����module-dirs��
# �ڶ��и�����PHONY׷��ֵ��
# �����ж�����һ������Ŀ����$(module-dirs)�������ļ���crmodverdir $(objtree)/Module.symvers
# addprefix��Makefile�е�һ����ǰ׺�������������﷨�ǣ�$(addprefix <prefix>;,<names...>;)
# patsubst��Makefile�е�һ��ģʽ�ַ����滻������
# ���﷨�ǣ�$(patsubst <pattern>;,<replacement>;,<text>;)
# ����<text>;�еĵ����Ƿ����ģʽ<pattern>;�����ƥ��Ļ�������<replacement>;�滻��

modules: $(module-dirs)
@echo ' Building modules, stage 2.';
$(Q)$(MAKE) -f $(srctree)/scripts/Makefile.modpost
# ���涨����һ������Ŀ����modules�������ļ���$(module-dirs)��
# ����@���ַ���������ǰ����ô����������make��ʾ������
# echo��Makefile�е�һ����������ַ���������׼����ؼ��֣����﷨�ǣ�echo [-ne][�ַ���]

PHONY += modules_install
modules_install: _emodinst_ _emodinst_post
# ��һ�и�����PHONY׷��ֵ
# �ڶ��ж�����һ��������ϵ��Ŀ����modules_install�������ļ���_emodinst_ _emodinst_post

install-dir := $(if $(INSTALL_MOD_DIR),$(INSTALL_MOD_DIR),extra)
PHONY += _emodinst_
_emodinst_:
$(Q)mkdir -p $(MODLIB)/$(install-dir)
$(Q)$(MAKE) -f $(srctree)/scripts/Makefile.modinst
# ��һ�н�if�����ķ���ֵչ���󸳸�����install-dir��
# �ڶ��и�����PHONY׷��ֵ��
# �����ж�����һ��αĿ��_emodinst_
# mkdir��linux shell�µ�һ�������ļ��е�������﷨�ǣ�mkdir [-p] dirName

# Run depmod only is we have System.map and depmod is executable
quiet_cmd_depmod = DEPMOD $(KERNELRELEASE)
cmd_depmod = if [ -r System.map -a -x $(DEPMOD) ]; then \
$(DEPMOD) -ae -F System.map             \
$(if $(strip $(INSTALL_MOD_PATH)),      \
-b $(INSTALL_MOD_PATH) -r)              \
$(KERNELRELEASE);                       \
fi
# ��һ���зֱ������quiet_cmd_depmod��cmd_depmod��ֵ��
# strip��Makefile�е�ȥ�ո��������﷨�ǣ�$(strip <string>;)
# �ַ���\�����������ܣ�һ�ǣ����У����ǣ�ת�塣

PHONY += _emodinst_post
_emodinst_post: _emodinst_
$(call cmd,depmod)
# ��һ�и�����PHONY׷��ֵ��
# �ڶ��ж�����һ������Ŀ����_emodinst_post�������ļ���_emodinst_
# call��Makefile��һ�����������µĲ������ĺ�����
# ���﷨�ǣ�$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)
# <expression>;�����еı������ᱻ����<parm1>;��<parm2>;��<parm3>;����ȡ����

clean-dirs := $(addprefix _clean_,$(KBUILD_EXTMOD))
# ���潫����addprefix�ķ���ֵչ���󸳸�����clean-dirs��
# addprefix��Makefile��һ����ǰ׺���������﷨�ǣ�$(addprefix <prefix>;,<names...>;)
# ���ܣ���ǰ׺<prefix>;�ӵ�<names>;�е�ÿ�����ʺ��档

PHONY += $(clean-dirs) clean
$(clean-dirs):
$(Q)$(MAKE) $(clean)=$(patsubst _clean_%,%,$@)
# ��һ�и�����PHONY׷��ֵ��
# �ڶ��ж�����һ��ΪĿ��$(clean-dirs)��
# patsubst��Makefile�е�һ��ģʽ�ַ����滻������
# ���﷨�ǣ�$(patsubst <pattern>;,<replacement>;,<text>;)
# ����<text>;�еĵ����Ƿ����ģʽ<pattern>;�����ƥ��Ļ�������<replacement>;�滻��

clean: rm-dirs := $(MODVERDIR)
clean: $(clean-dirs)
$(call cmd,rmdirs)
@find $(KBUILD_EXTMOD) $(RCS_FIND_IGNORE) \
\( -name '*.[oas]' -o -name '*.ko' -o -name '.*.cmd' \
-o -name '.*.d' -o -name '.*.tmp' -o -name '*.mod.c' \) \
-type f -print | xargs rm -f
# ��һ�ж�����һ������Ŀ����clean�������ļ���rm-dirs�������Ǹ������ļ�rm-dirs��ֵ
# call��Makefile��һ�����������µĲ������ĺ�����
# ����@���ַ���������ǰ����ô����������make��ʾ������
# find��linux shell�µ�һ������������﷨�ǣ�find path option [-print -exec -ok]
# �ַ���\�����������ܣ�һ�ǣ����У����ǣ�ת�塣

help:
@echo ' Building external modules.'
@echo ' Syntax: make -C path/to/kernel/src M=$$PWD target'
@echo ''
@echo ' modules         - default target, build the module(s)'
@echo ' modules_install - install the module'
@echo ' clean           - remove generated files in module directory only'
@echo ''
# ���涨����һ��αĿ��help��
# ����@���ַ���������ǰ����ô����������make��ʾ������
# echo��Makefile�е�һ����������ַ���������׼����ؼ��֣����﷨�ǣ�echo [-ne][�ַ���]

# Dummies...
PHONY += prepare scripts
prepare: ;
scripts: ;
endif # KBUILD_EXTMOD
# ��һ�и�����PHONY׷��ֵ
# �ڶ����зֱ�����һ��ΪĿ�꣬����Ϊ�����

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
#��ifeq��Makefile�е�һ�������ؼ��֣����﷨�ǣ�ifeq (<arg1>;, <arg2>;)
# ���ܣ��Ƚϲ�����arg1���͡�arg2����ֵ�Ƿ���ͬ��

ifeq ($(ALLSOURCE_ARCHS),)
ifeq ($(ARCH),um)
ALLINCLUDE_ARCHS := $(ARCH) $(SUBARCH)
else # ���else��ifeq ($(ARCH),um)��Ӧ��
ALLINCLUDE_ARCHS := $(ARCH)
endif   # ���endif��ifeq ($(ARCH),um)��Ӧ��
else   # ���else������ifeq ($(ALLSOURCE_ARCHS),)��Ӧ
#Allow user to specify only ALLSOURCE_PATHS on the command line, keeping existing behavour.
ALLINCLUDE_ARCHS := $(ALLSOURCE_ARCHS)
endif   # ���endif������ifeq ($(ALLSOURCE_ARCHS),)��Ӧ
# ifeq��Makefile�е�һ�������ؼ��֣����﷨�ǣ�ifeq (<arg1>;, <arg2>;)
# ���ܣ��Ƚϲ�����arg1���͡�arg2����ֵ�Ƿ���ͬ��
# ������ifeq ($(ALLSOURCE_ARCHS),)����Ƕ����һ��ifeq ($(ARCH),um)��

ALLSOURCE_ARCHS := $(ARCH)
# ������ALLSOURCE_ARCHS��ֵ

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
# define��Makefile�е�һ���������������ͬ���������У��Ĺؼ��֣�
# find��linux shell�µ�һ������������﷨�ǣ�find path option [-print -exec -ok]
# �ַ���\�����������ܣ�һ�ǣ����У����ǣ�ת�塣

define all-sources
$(call find-sources,'*.[chS]')
endef
define all-kconfigs
$(call find-sources,'Kconfig*')
endef
define all-defconfigs
$(call find-sources,'defconfig')
endef
# define��Makefile�е�һ���������������ͬ���������У��Ĺؼ��֣�
# call��Makefile�е�Ψһһ���������µĲ������ĺ�����
# ���﷨�ǣ�$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)
# <expression>;�����еı������ᱻ����<parm1>;��<parm2>;��<parm3>;����ȡ����

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
# define��Makefile�е�һ���������������ͬ���������У��Ĺؼ��֣�
# �ַ���\�����������ܣ�һ�ǣ����У����ǣ�ת�塣
# �ַ���|���ǹܵ��ı�־�����������ǣ�����һ�������stdout�ض�����һ�������stdin��
# grep��linux shell��һ�����ļ��в����ַ�����������﷨�ǣ�grep �ַ��� �ļ���
# xargs��linux shell�е�һ�������ִ������ĳЩ��������

quiet_cmd_cscope-file = FILELST cscope.files
cmd_cscope-file = (echo \-k; echo \-q; $(all-sources)) > cscope.files
# ��һ���зֱ������quiet_cmd_cscope-file��cmd_cscope-file ��ֵ��
# echo��Makefile�е�һ����������ַ���������׼����ؼ��֣����﷨�ǣ�echo [-ne][�ַ���] 
# �ַ���\�����������ܣ�һ�ǣ����У����ǣ�ת�塣
# �ַ���>�����ض����־�����ܽ�ǰһ�������stdou�ض��򵽵������ļ��ȣ���

quiet_cmd_cscope = MAKE    cscope.out
cmd_cscope = cscope -b
# �ֱ������quiet_cmd_cscope��cmd_cscope��ֵ��

cscope: FORCE
$(call cmd,cscope-file)
$(call cmd,cscope)
# ���涨����һ������Ŀ����cscope�������ļ���FORCE��
# call��Makefile�е�Ψһһ���������µĲ������ĺ�����
# ���﷨�ǣ�$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)

quiet_cmd_TAGS = MAKE   $@
define cmd_TAGS
rm -f $@; \
$(call xtags,etags)
endef
# ��һ�и�����quiet_cmd_TAGS��ֵ��
# $@��Makefile���Զ���������������ǰ�����Ŀ���ļ�����
# define��Makefile�е�һ���������������ͬ���������У��Ĺؼ��֣�
# rm��linux shell��ɾ���ļ����ļ��е�������﷨�ǣ�rm [ѡ��]... �ļ�...
# call��Makefile�е�Ψһһ���������µĲ������ĺ�����
# ���﷨�ǣ�$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)

TAGS: FORCE
$(call cmd,TAGS)
# ���涨����һ������Ŀ����TAGS�������ļ���FORCE��
# call��Makefile�е�Ψһһ���������µĲ������ĺ�����
# ���﷨�ǣ�$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)

quiet_cmd_tags = MAKE   $@
define cmd_tags
rm -f $@; \
$(call xtags,ctags)
endef
# ��һ�и�����quiet_cmd_tags��ֵ��
# $@��Makefile���Զ���������������ǰ�����Ŀ���ļ�����
# define��Makefile�е�һ���������������ͬ���������У��Ĺؼ��֣�
# rm��linux shell��ɾ���ļ����ļ��е�������﷨�ǣ�rm [ѡ��]... �ļ�...
# call��Makefile�е�Ψһһ���������µĲ������ĺ�����
# ���﷨�ǣ�$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)

tags: FORCE
$(call cmd,tags)
# ���涨����һ������Ŀ����tags�������ļ���FORCE
# call��Makefile�е�Ψһһ���������µĲ������ĺ�����
# ���﷨�ǣ�$(call <expression>;,<parm1>;,<parm2>;,<parm3>;...)


# Scripts to check various things for consistency
# ---------------------------------------------------------------------------
 
